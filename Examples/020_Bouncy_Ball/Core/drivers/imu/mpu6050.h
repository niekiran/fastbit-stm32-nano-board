/*
 * mpu6050.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "error.h"

/* -------------------------------------------------------------------------- */
/*                             Device definitions                             */
/* -------------------------------------------------------------------------- */

#define MPU6050_I2C_ADDR_AD0_LOW          0x68U
#define MPU6050_I2C_ADDR_AD0_HIGH         0x69U

/* -------------------------------------------------------------------------- */
/*                              Register map                                  */
/* -------------------------------------------------------------------------- */

#define MPU6050_REG_SMPLRT_DIV            0x19U
#define MPU6050_REG_CONFIG                0x1AU
#define MPU6050_REG_GYRO_CONFIG           0x1BU
#define MPU6050_REG_ACCEL_CONFIG          0x1CU
#define MPU6050_REG_INT_ENABLE            0x38U
#define MPU6050_REG_ACCEL_XOUT_H          0x3BU
#define MPU6050_REG_TEMP_OUT_H            0x41U
#define MPU6050_REG_GYRO_XOUT_H           0x43U
#define MPU6050_REG_PWR_MGMT_1            0x6BU
#define MPU6050_REG_WHO_AM_I              0x75U

/* -------------------------------------------------------------------------- */
/*                           Full-scale range values                          */
/* -------------------------------------------------------------------------- */

#define MPU6050_ACCEL_FS_2G               0x00U
#define MPU6050_ACCEL_FS_4G               0x08U
#define MPU6050_ACCEL_FS_8G               0x10U
#define MPU6050_ACCEL_FS_16G              0x18U

#define MPU6050_GYRO_FS_250DPS            0x00U
#define MPU6050_GYRO_FS_500DPS            0x08U
#define MPU6050_GYRO_FS_1000DPS           0x10U
#define MPU6050_GYRO_FS_2000DPS           0x18U

/* -------------------------------------------------------------------------- */
/*                              Sensitivity values                            */
/* -------------------------------------------------------------------------- */

#define MPU6050_ACCEL_SENS_2G             16384.0f
#define MPU6050_ACCEL_SENS_4G             8192.0f
#define MPU6050_ACCEL_SENS_8G             4096.0f
#define MPU6050_ACCEL_SENS_16G            2048.0f

#define MPU6050_GYRO_SENS_250DPS          131.0f
#define MPU6050_GYRO_SENS_500DPS          65.5f
#define MPU6050_GYRO_SENS_1000DPS         32.8f
#define MPU6050_GYRO_SENS_2000DPS         16.4f

/* -------------------------------------------------------------------------- */
/*                                Data types                                  */
/* -------------------------------------------------------------------------- */

typedef struct mpu6050_device_t *mpu6050_handle_t;

typedef struct
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
} mpu6050_sample_t;

typedef struct
{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} mpu6050_gyro_sample_t;

typedef struct
{
    mpu6050_sample_t      accel_raw;
    mpu6050_gyro_sample_t gyro_raw;

    float accel_x_g;
    float accel_y_g;
    float accel_z_g;

    float gyro_x_dps;
    float gyro_y_dps;
    float gyro_z_dps;

    float roll_deg;
    float pitch_deg;
} mpu6050_data_t;

/* -------------------------------------------------------------------------- */
/*                               Public API                                   */
/* -------------------------------------------------------------------------- */

mpu6050_handle_t mpu6050_create(uint8_t i2c_addr);
void             mpu6050_destroy(mpu6050_handle_t hdl);

err_t mpu6050_init(mpu6050_handle_t hdl);
err_t mpu6050_calibrate(mpu6050_handle_t hdl);

err_t mpu6050_read_accel(mpu6050_handle_t hdl, mpu6050_sample_t *sample);
err_t mpu6050_read_gyro(mpu6050_handle_t hdl, mpu6050_gyro_sample_t *sample);
err_t mpu6050_read_all(mpu6050_handle_t hdl, mpu6050_data_t *data);

err_t mpu6050_get_tilt_deg(mpu6050_handle_t hdl, float *roll_deg, float *pitch_deg);

#ifdef __cplusplus
}
#endif

#endif /* INC_MPU6050_H_ */
