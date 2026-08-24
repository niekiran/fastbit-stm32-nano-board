/*
 * bmi270.c
 *
 *  Created on: Aug 24, 2026
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "bmi270.h"
#include "bmi270_config_file.h"
#include <main.h>
#include <stdio.h>

/* Bosch recommends uploading the config file in bursts; 32 bytes keeps each
 * I2C transaction well within HAL/I2C1 limits. Must stay even (INIT_ADDR is
 * a 16-bit word address, i.e. 2 bytes per step). */
#define BMI270_INIT_CHUNK_SIZE 32

#define BMI270_REG_TEMPERATURE 0x22

typedef struct {
  double process_variance;
  double measurement_variance;
  double estimated_error;
  double posteri_estimate;
  double posteri_error;
} Bmi270KalmanFilter;

/* Private function prototypes */
static uint8_t check_chip_id(void);
static void soft_reset(void);
static void disable_adv_power_save(void);
static void upload_config_file(void);
static uint8_t confirm_init_ok(void);
static void configure_acc_gyro(void);
static void power_on_acc_gyro(void);
static void bmi270_kalman_filter_init(Bmi270KalmanFilter *kf, double process_variance,
                                       double measurement_variance, double estimated_error);
static double bmi270_kalman_filter_update(Bmi270KalmanFilter *kf, double measurement);
static void bmi270_filter_gyro_data(double *gyroz, double *gyroy);

/**
  * @brief Initializes the BMI270 sensor: reset, mandatory config-file upload,
  *        accelerometer/gyroscope configuration, and power-on.
  * @param None
  * @retval None
  */
void bmi270_init(void) {
  HAL_Delay(100);

  if (!check_chip_id()) {
    printf("BMI270 chip ID mismatch...\n");
  }

  soft_reset();
  disable_adv_power_save();
  upload_config_file();

  if (confirm_init_ok()) {
    printf("BMI270 initialization file loaded OK...\n");
  } else {
    printf("BMI270 initialization file load FAILED...\n");
  }

  configure_acc_gyro();
  power_on_acc_gyro();
}

/**
  * @brief Reads the CHIP_ID register and compares it against the expected value.
  * @retval 1 if the ID matches, 0 otherwise.
  */
static uint8_t check_chip_id(void) {
  uint8_t chip_id = 0;
  HAL_I2C_Mem_Read(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_CHIP_ID, 1, &chip_id, 1, HAL_MAX_DELAY);
  return (chip_id == BMI270_CHIP_ID_VAL);
}

/**
  * @brief Issues a soft reset and waits for the sensor to come back up.
  * @retval None
  */
static void soft_reset(void) {
  uint8_t cmd = BMI270_CMD_SOFTRESET;
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_CMD, 1, &cmd, 1, HAL_MAX_DELAY);
  HAL_Delay(2);
}

/**
  * @brief Disables advanced power save mode. Required before the config file
  *        can be uploaded, and while the mouse continuously polls the sensor.
  * @retval None
  */
static void disable_adv_power_save(void) {
  uint8_t pwr_conf = 0x00;
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_PWR_CONF, 1, &pwr_conf, 1, HAL_MAX_DELAY);
  HAL_Delay(1);
}

/**
  * @brief Uploads the mandatory 8192-byte BMI270 configuration image in
  *        chunks, per Bosch's initialization sequence.
  * @retval None
  */
static void upload_config_file(void) {
  uint8_t init_ctrl = 0x00;
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_INIT_CTRL, 1, &init_ctrl, 1, HAL_MAX_DELAY);

  for (uint16_t offset = 0; offset < BMI270_CONFIG_FILE_SIZE; offset += BMI270_INIT_CHUNK_SIZE) {
    uint16_t addr_word = offset / 2;
    /* INIT_ADDR_0 holds only bits[3:0] of the word address; INIT_ADDR_1
     * holds bits[11:4]. This is NOT a plain 16-bit little-endian split. */
    uint8_t addr_buf[2] = { (uint8_t)(addr_word & 0x0F), (uint8_t)(addr_word >> 4) };

    HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_INIT_ADDR_0, 1, addr_buf, 2, HAL_MAX_DELAY);
    HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_INIT_DATA, 1,
                       (uint8_t *)&bmi270_config_file[offset], BMI270_INIT_CHUNK_SIZE, HAL_MAX_DELAY);
  }

  init_ctrl = 0x01;
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_INIT_CTRL, 1, &init_ctrl, 1, HAL_MAX_DELAY);
  HAL_Delay(20);
}

/**
  * @brief Reads INTERNAL_STATUS and checks the init-complete message field.
  * @retval 1 if initialization succeeded, 0 otherwise.
  */
static uint8_t confirm_init_ok(void) {
  uint8_t status = 0;
  HAL_I2C_Mem_Read(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_INTERNAL_STATUS, 1, &status, 1, HAL_MAX_DELAY);
  return ((status & 0x0F) == 0x01);
}

/**
  * @brief Configures accelerometer and gyroscope ODR/bandwidth/range.
  *        Uses Bosch's published "normal mode, performance optimized"
  *        register values (ACC_CONF=0xA8, GYR_CONF=0xA9).
  * @retval None
  */
static void configure_acc_gyro(void) {
  uint8_t acc_conf = 0xA8;   // filter_perf=1, bwp=normal_avg4, odr=100Hz
  uint8_t acc_range = BMI270_ACC_RANGE_16G;
  uint8_t gyr_conf = 0xA9;   // filter_perf=1, noise_perf=0, bwp=normal, odr=200Hz
  uint8_t gyr_range = BMI270_GYR_RANGE_2000;

  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_ACC_CONF, 1, &acc_conf, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_ACC_RANGE, 1, &acc_range, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_GYR_CONF, 1, &gyr_conf, 1, HAL_MAX_DELAY);
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_GYR_RANGE, 1, &gyr_range, 1, HAL_MAX_DELAY);
}

/**
  * @brief Enables the accelerometer and gyroscope in PWR_CTRL.
  * @retval None
  */
static void power_on_acc_gyro(void) {
  uint8_t pwr_ctrl = 0x06; // acc_en | gyr_en
  HAL_I2C_Mem_Write(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_PWR_CTRL, 1, &pwr_ctrl, 1, HAL_MAX_DELAY);
  HAL_Delay(1);
}

/**
  * @brief Reads accelerometer, gyroscope, and die-temperature data from the
  *        BMI270 into a BMI270_t, mirroring MPU6050_Read_All().
  * @param data_struct Pointer to the BMI270_t structure to populate.
  * @retval None
  */
void bmi270_read_all(BMI270_t *data_struct) {
  uint8_t data[12];
  uint8_t temp_data[2];
  int16_t raw_temp;

  if (HAL_I2C_Mem_Read(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_DATA, 1, data, 12, HAL_MAX_DELAY) != HAL_OK) {
    printf("Failed to read from BMI270\n");
    return;
  }

  /* BMI270 data registers are little-endian (LSB first), unlike MPU6050 */
  data_struct->Accel_X_RAW = (int16_t)((data[1] << 8) | data[0]);
  data_struct->Accel_Y_RAW = (int16_t)((data[3] << 8) | data[2]);
  data_struct->Accel_Z_RAW = (int16_t)((data[5] << 8) | data[4]);

  data_struct->Gyro_X_RAW = (int16_t)((data[7] << 8) | data[6]);
  data_struct->Gyro_Y_RAW = (int16_t)((data[9] << 8) | data[8]);
  data_struct->Gyro_Z_RAW = (int16_t)((data[11] << 8) | data[10]);

  data_struct->Ax = data_struct->Accel_X_RAW / BMI270_ACC_FS_SENSITIVITY;
  data_struct->Ay = data_struct->Accel_Y_RAW / BMI270_ACC_FS_SENSITIVITY;
  data_struct->Az = data_struct->Accel_Z_RAW / BMI270_ACC_FS_SENSITIVITY;

  data_struct->Gx = data_struct->Gyro_X_RAW / BMI270_GYR_FS_SENSITIVITY;
  data_struct->Gy = data_struct->Gyro_Y_RAW / BMI270_GYR_FS_SENSITIVITY;
  data_struct->Gz = data_struct->Gyro_Z_RAW / BMI270_GYR_FS_SENSITIVITY;

  HAL_I2C_Mem_Read(&hi2c1, (BMI270_ADDR << 1), BMI270_REG_TEMPERATURE, 1, temp_data, 2, HAL_MAX_DELAY);
  raw_temp = (int16_t)((temp_data[1] << 8) | temp_data[0]);
  /* Bosch datasheet: 0x8000 reads back when temperature data is not (yet) available */
  data_struct->Temperature = (raw_temp == (int16_t)0x8000) ? 0.0f : ((float)raw_temp / 512.0f) + 23.0f;
}

/**
  * @brief Kalman filter init, identical algorithm to KalmanFilter_Init() in
  *        mpu6050.c, kept as a private copy under a distinct name since both
  *        files are always linked together in this project.
  */
static void bmi270_kalman_filter_init(Bmi270KalmanFilter *kf, double process_variance,
                                       double measurement_variance, double estimated_error) {
  kf->process_variance = process_variance;
  kf->measurement_variance = measurement_variance;
  kf->estimated_error = estimated_error;
  kf->posteri_estimate = 0.0;
  kf->posteri_error = 1.0;
}

/**
  * @brief Kalman filter update, identical algorithm to KalmanFilter_Update()
  *        in mpu6050.c.
  */
static double bmi270_kalman_filter_update(Bmi270KalmanFilter *kf, double measurement) {
  double priori_estimate = kf->posteri_estimate;
  double priori_error = kf->posteri_error + kf->process_variance;
  double blending_factor = priori_error / (priori_error + kf->measurement_variance);

  kf->posteri_estimate = priori_estimate + blending_factor * (measurement - priori_estimate);
  kf->posteri_error = (1 - blending_factor) * priori_error;

  return kf->posteri_estimate;
}

/**
  * @brief Applies Kalman filtering to gyroscope data, matching
  *        filter_gyro_data() in mpu6050.c.
  */
static void bmi270_filter_gyro_data(double *gyroz, double *gyroy) {
  static Bmi270KalmanFilter kf_gyroz;
  static Bmi270KalmanFilter kf_gyroy;
  static int kf_initialized = 0;

  if (!kf_initialized) {
    bmi270_kalman_filter_init(&kf_gyroz, 1e-5, 1e-2, 1.0);
    bmi270_kalman_filter_init(&kf_gyroy, 1e-5, 1e-2, 1.0);
    kf_initialized = 1;
  }

  *gyroz = bmi270_kalman_filter_update(&kf_gyroz, *gyroz);
  *gyroy = bmi270_kalman_filter_update(&kf_gyroy, *gyroy);
}

/**
  * @brief Reads and Kalman-filters gyroscope data from the BMI270, matching
  *        read_gyro_data() in mpu6050.c.
  * @param bmi270_data Pointer to the BMI270 data structure.
  * @param gyroz Pointer to store the processed gyroscope Z-axis data.
  * @param gyroy Pointer to store the processed gyroscope Y-axis data.
  * @retval None
  */
void bmi270_read_gyro_data(BMI270_t *bmi270_data, double *gyroz, double *gyroy) {
  bmi270_read_all(bmi270_data);
  *gyroz = bmi270_data->Gz;
  *gyroy = bmi270_data->Gy;
  bmi270_filter_gyro_data(gyroz, gyroy);
}
