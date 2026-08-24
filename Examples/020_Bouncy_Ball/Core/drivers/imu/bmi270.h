/*
 * bmi270.h
 *
 *  Created on: Aug 24, 2026
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 *
 *  Driver for the Bosch BMI270 6-axis IMU, used as the MPU6050 replacement
 *  on Fastbit STM32 Nano board v2.1. Mirrors this project's handle-based
 *  mpu6050.h API (create/destroy/init/calibrate/read_accel/read_gyro) so
 *  game.c can select either sensor via IMU_MPU6050 / IMU_BMI270 without
 *  changing its own logic. Configured to the same +-2G / +-500dps ranges
 *  as the MPU6050 path, so raw LSB counts (and therefore game feel) match
 *  between board revisions.
 */

#ifndef INC_BMI270_H_
#define INC_BMI270_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "error.h"

/* -------------------------------------------------------------------------- */
/*                             Device definitions                             */
/* -------------------------------------------------------------------------- */

/* SDO pin tied low, matches the MPU6050 address/pin so no board wiring
 * change is required between v2.0 and v2.1 */
#define BMI270_I2C_ADDR_SDO_LOW           0x68U
#define BMI270_I2C_ADDR_SDO_HIGH          0x69U

/* -------------------------------------------------------------------------- */
/*                              Sensitivity values                            */
/* -------------------------------------------------------------------------- */

/* LSB/g at +-2G -- matches MPU6050_ACCEL_SENS_2G exactly */
#define BMI270_ACCEL_SENS_2G              16384.0f
/* LSB/(deg/s) at +-500dps -- matches MPU6050_GYRO_SENS_500DPS exactly */
#define BMI270_GYRO_SENS_500DPS           65.5f

/* -------------------------------------------------------------------------- */
/*                                Data types                                  */
/* -------------------------------------------------------------------------- */

typedef struct bmi270_device_t *bmi270_handle_t;

typedef struct
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
} bmi270_sample_t;

typedef struct
{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} bmi270_gyro_sample_t;

/* -------------------------------------------------------------------------- */
/*                               Public API                                   */
/* -------------------------------------------------------------------------- */

bmi270_handle_t bmi270_create(uint8_t i2c_addr);
void            bmi270_destroy(bmi270_handle_t hdl);

err_t bmi270_init(bmi270_handle_t hdl);
err_t bmi270_calibrate(bmi270_handle_t hdl);

err_t bmi270_read_accel(bmi270_handle_t hdl, bmi270_sample_t *sample);
err_t bmi270_read_gyro(bmi270_handle_t hdl, bmi270_gyro_sample_t *sample);

#ifdef __cplusplus
}
#endif

#endif /* INC_BMI270_H_ */
