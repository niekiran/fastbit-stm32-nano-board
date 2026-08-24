/*
 * mouse_handler.c
 *
 *  Created on: Jun 11, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "mouse_handler.h"
#include "main.h"
#include <math.h>

/**
  * @brief  Debounce handler for mouse button input.
  * @param  btn_value: Raw input value of the button (non-zero if pressed, zero if not pressed).
  * @retval Debounced button value (non-zero if debounced as pressed, zero otherwise).
  */
uint8_t handle_mouse_button(uint8_t btn_value) {
  static button_state_t btn_sm_state = NOT_PRESSED;
  static uint32_t curr_time = 0;
  uint32_t new_time = HAL_GetTick();

  switch (btn_sm_state) {
    case NOT_PRESSED:
      if (btn_value) {
        btn_sm_state = BOUNCE;
        curr_time = new_time;
      }
      break;
    case BOUNCE:
      if ((new_time - curr_time) >= 50) {
        if (btn_value) {
          btn_sm_state = PRESSED;
          return btn_value;
        } else {
          btn_sm_state = NOT_PRESSED;
        }
      }
      break;
    case PRESSED:
      if (!btn_value) {
        btn_sm_state = BOUNCE;
        curr_time = new_time;
      }else {
        return btn_value;
      }
      break;
  }
  return 0;
}


/**
  * @brief  Read button state.
  * @param  GPIOx: GPIO port.
  * @param  GPIO_Pin: GPIO pin.
  * @retval Button state
  */
uint8_t read_btn_state(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/**
  * @brief  Updates the mouse HID buttons based on the button pad value.
  * @param  mouse_hid: Pointer to the mouse HID structure.
  * @param  btn_pad_value: Value representing the state of the buttons.
  *                        Bit 0 corresponds to the left button, and
  *                        bit 1 corresponds to the right button.
  * @retval None
  */
void update_btn_state(mouseHID *mouse_hid, uint8_t btn_pad_value)
{
  if (btn_pad_value & 0x01) {
      mouse_hid->button |= 0x01;
  } else {
      mouse_hid->button &= ~0x01;
  }

  if (btn_pad_value & 0x02) {
      mouse_hid->button |= 0x02;
  } else {
      mouse_hid->button &= ~0x02;
  }
}

/* --- Gyro-driven cursor motion -------------------------------------------
 * Sensor-agnostic pipeline shared by MPU6050 and BMI270: Kalman smoothing,
 * startup calibration bias removal, deadzone, and a pointer-acceleration
 * curve. Both IMU drivers used to embed their own copy of this Kalman
 * filter internally; it now lives in exactly one place so the two board
 * revisions can never diverge in feel, and so drivers only ever hand back
 * raw physical-unit data (their *_Read_All() functions), matching the
 * layered Application/Middleware/Drivers/HAL split used elsewhere.
 * ------------------------------------------------------------------------- */

typedef struct {
  double process_variance;
  double measurement_variance;
  double estimated_error;
  double posteri_estimate;
  double posteri_error;
} GyroKalmanFilter;

static GyroKalmanFilter s_kf_gz;
static GyroKalmanFilter s_kf_gy;
static uint8_t s_kf_initialized = 0;

/* Bias measured at startup by gyro_calibrate_bias(), in raw dps. */
static double s_gyro_bias_z = 0.0;
static double s_gyro_bias_y = 0.0;

/* Post-filter, post-bias dps magnitude treated as zero. MEMS gyro noise
 * left over after Kalman smoothing is typically a few dps even at rest;
 * 3.0 is small enough not to eat real slow-cursor intent but large enough
 * to null out residual jitter. TUNE ON HARDWARE. */
#define GYRO_DEADZONE_DPS   3.0

/* Pointer-acceleration curve: output = sign(x) * (|x| / GYRO_CURVE_K) ^ GYRO_CURVE_P.
 * GYRO_CURVE_K anchors the curve near the old flat "/20" feel at moderate
 * speed; GYRO_CURVE_P > 1 gives finer control at low speed and
 * progressively more travel at high speed, instead of one flat scale for
 * every motion size. TUNE ON HARDWARE. */
#define GYRO_CURVE_K        20.0
#define GYRO_CURVE_P        1.3

/**
  * @brief Kalman filter init, identical algorithm to the one previously
  *        duplicated in mpu6050.c / bmi270.c.
  */
static void kalman_init(GyroKalmanFilter *kf, double process_variance,
                         double measurement_variance, double estimated_error) {
  kf->process_variance = process_variance;
  kf->measurement_variance = measurement_variance;
  kf->estimated_error = estimated_error;
  kf->posteri_estimate = 0.0;
  kf->posteri_error = 1.0;
}

/**
  * @brief Kalman filter update.
  */
static double kalman_update(GyroKalmanFilter *kf, double measurement) {
  double priori_estimate = kf->posteri_estimate;
  double priori_error = kf->posteri_error + kf->process_variance;
  double blending_factor = priori_error / (priori_error + kf->measurement_variance);

  kf->posteri_estimate = priori_estimate + blending_factor * (measurement - priori_estimate);
  kf->posteri_error = (1 - blending_factor) * priori_error;

  return kf->posteri_estimate;
}

/**
  * @brief Zeroes out values below the deadzone threshold.
  */
static double apply_deadzone(double value, double deadzone) {
  return (fabs(value) < deadzone) ? 0.0 : value;
}

/**
  * @brief Non-linear pointer-acceleration response curve.
  */
static double apply_accel_curve(double value) {
  double sign = (value < 0.0) ? -1.0 : 1.0;
  double magnitude = fabs(value) / GYRO_CURVE_K;
  return sign * pow(magnitude, GYRO_CURVE_P);
}

/**
  * @brief Saturates a double into the int8_t range used by the HID report
  *        (the HID report descriptor's logical range is -127..127). Fixes
  *        a wraparound bug where an out-of-range value (e.g. a computed
  *        150) would silently truncate to a negative number (-106) on
  *        implicit conversion, flipping cursor direction instantly.
  */
static int8_t clamp_to_int8(double value) {
  if (value > 127.0) return 127;
  if (value < -127.0) return -127;
  return (int8_t)value;
}

/**
  * @brief  Records the gyro bias measured while the board was held still
  *         at startup, so it can be subtracted from every later reading.
  * @param  bias_z: Average raw Z-axis gyro reading (dps) while stationary.
  * @param  bias_y: Average raw Y-axis gyro reading (dps) while stationary.
  * @retval None
  */
void gyro_calibrate_bias(double bias_z, double bias_y) {
  s_gyro_bias_z = bias_z;
  s_gyro_bias_y = bias_y;
}

/**
  * @brief  Update mouse movement based on gyroscope.
  * @param  raw_gz: Raw (unfiltered, un-biased) gyroscope Z-axis value (dps).
  * @param  raw_gy: Raw (unfiltered, un-biased) gyroscope Y-axis value (dps).
  * @param  mouse_hid: Pointer to the mouse HID structure.
  * @retval None
  */
void process_gyro_and_update_cursor(double raw_gz, double raw_gy, mouseHID *mouse_hid) {
  if (!s_kf_initialized) {
    kalman_init(&s_kf_gz, 1e-5, 1e-2, 1.0);
    kalman_init(&s_kf_gy, 1e-5, 1e-2, 1.0);
    s_kf_initialized = 1;
  }

  double filtered_gz = kalman_update(&s_kf_gz, raw_gz);
  double filtered_gy = kalman_update(&s_kf_gy, raw_gy);

  double unbiased_gz = filtered_gz - s_gyro_bias_z;
  double unbiased_gy = filtered_gy - s_gyro_bias_y;

  double dz_gz = apply_deadzone(unbiased_gz, GYRO_DEADZONE_DPS);
  double dz_gy = apply_deadzone(unbiased_gy, GYRO_DEADZONE_DPS);

  mouse_hid->mouse_x = clamp_to_int8(-apply_accel_curve(dz_gz));
  mouse_hid->mouse_y = clamp_to_int8(-apply_accel_curve(dz_gy));
}
