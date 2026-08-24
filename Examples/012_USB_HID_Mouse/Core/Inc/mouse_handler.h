/*
 * mouse_handler.h
 *
 *  Created on: Jun 11, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_MOUSE_HANDLER_H_
#define INC_MOUSE_HANDLER_H_

#include <stdint.h>
#include "main.h"

typedef enum {
  NOT_PRESSED,
  BOUNCE,
  PRESSED
} button_state_t;

/* mouse btn handling function prototytpe */
uint8_t handle_mouse_button(uint8_t btn_value);
uint8_t read_btn_state(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void update_btn_state(mouseHID *mouse_hid, uint8_t btn_pad_value);

/* gyro-driven cursor motion: sensor-agnostic Kalman smoothing + calibration
 * bias removal + deadzone + acceleration curve, shared by whichever IMU
 * driver (MPU6050 or BMI270) is compiled in. */

/* Call once at startup, right after the IMU driver's init function, with the
 * average raw gyro Z/Y (dps) measured while the board is held still. */
void gyro_calibrate_bias(double bias_z, double bias_y);

/* Call every loop iteration with RAW (unfiltered, un-biased) gyro Z/Y (dps)
 * straight from the driver's *_Read_All() struct fields. Writes the
 * resulting HID motion into mouse_hid->mouse_x/mouse_y. */
void process_gyro_and_update_cursor(double raw_gz, double raw_gy, mouseHID *mouse_hid);

#endif /* INC_MOUSE_HANDLER_H_ */
