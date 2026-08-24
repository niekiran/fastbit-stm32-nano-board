/*
 * mpu6050.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 *      Updated to match handle-based mpu6050.h API
 */

#include "mpu6050.h"
#include "main.h"

#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*                            Private configuration                           */
/* -------------------------------------------------------------------------- */

#define MPU6050_REG_PWR_MGMT_1        0x6BU
#define MPU6050_REG_SMPLRT_DIV        0x19U
#define MPU6050_REG_CONFIG            0x1AU
#define MPU6050_REG_GYRO_CONFIG       0x1BU
#define MPU6050_REG_ACCEL_CONFIG      0x1CU
#define MPU6050_REG_ACCEL_XOUT_H      0x3BU
#define MPU6050_REG_GYRO_XOUT_H       0x43U

#define MPU6050_ACCEL_FS_2G_CFG       0x00U
#define MPU6050_GYRO_FS_500DPS_CFG    0x08U

#define MPU6050_ACCEL_SENS_2G         16384.0f


/* -------------------------------------------------------------------------- */
/*                              Private data type                             */
/* -------------------------------------------------------------------------- */

struct mpu6050_device_t
{
    uint8_t i2c_addr;
    int16_t accel_x_offset;
    int16_t accel_y_offset;
    int16_t accel_z_offset;
    uint8_t is_calibrated;
};

/* -------------------------------------------------------------------------- */
/*                         External peripheral handle                         */
/* -------------------------------------------------------------------------- */

extern I2C_HandleTypeDef hi2c1;

/* -------------------------------------------------------------------------- */
/*                           Private helper prototypes                        */
/* -------------------------------------------------------------------------- */

static err_t mpu6050_write_reg(mpu6050_handle_t hdl, uint8_t reg, uint8_t value);
static err_t mpu6050_read_regs(mpu6050_handle_t hdl, uint8_t reg, uint8_t *data, uint16_t len);

/* -------------------------------------------------------------------------- */
/*                              Public functions                              */
/* -------------------------------------------------------------------------- */

mpu6050_handle_t mpu6050_create(uint8_t i2c_addr)
{
    mpu6050_handle_t hdl;

    hdl = (mpu6050_handle_t)malloc(sizeof(struct mpu6050_device_t));
    if (hdl == NULL) {
        return NULL;
    }

    memset(hdl, 0, sizeof(struct mpu6050_device_t));
    hdl->i2c_addr = i2c_addr;

    return hdl;
}

void mpu6050_destroy(mpu6050_handle_t hdl)
{
    if (hdl == NULL) {
        return;
    }

    free(hdl);
}

err_t mpu6050_init(mpu6050_handle_t hdl)
{
    err_t status;

    if (hdl == NULL) {
        return ERR_INVALID_PARAM;
    }

    HAL_Delay(200);

    status = mpu6050_write_reg(hdl, MPU6050_REG_PWR_MGMT_1, 0x00U);
    if (status != ERR_OK) {
        return status;
    }

    HAL_Delay(10);

    status = mpu6050_write_reg(hdl, MPU6050_REG_SMPLRT_DIV, 0x07U);
    if (status != ERR_OK) {
        return status;
    }

    status = mpu6050_write_reg(hdl, MPU6050_REG_CONFIG, 0x00U);
    if (status != ERR_OK) {
        return status;
    }

    status = mpu6050_write_reg(hdl, MPU6050_REG_GYRO_CONFIG, MPU6050_GYRO_FS_500DPS_CFG);
    if (status != ERR_OK) {
        return status;
    }

    status = mpu6050_write_reg(hdl, MPU6050_REG_ACCEL_CONFIG, MPU6050_ACCEL_FS_2G_CFG);
    if (status != ERR_OK) {
        return status;
    }

    return ERR_OK;
}

err_t mpu6050_calibrate(mpu6050_handle_t hdl)
{
    mpu6050_sample_t sample;
    int32_t sum_x = 0;
    int32_t sum_y = 0;
    int32_t sum_z = 0;
    const uint16_t samples_count = 200U;

    if (hdl == NULL) {
        return ERR_INVALID_PARAM;
    }

    hdl->accel_x_offset = 0;
    hdl->accel_y_offset = 0;
    hdl->accel_z_offset = 0;
    hdl->is_calibrated = 0U;

    for (uint16_t i = 0; i < samples_count; i++) {
        if (mpu6050_read_accel(hdl, &sample) != ERR_OK) {
            return ERR_HW_FAILURE;
        }

        sum_x += sample.accel_x;
        sum_y += sample.accel_y;
        sum_z += sample.accel_z;

        HAL_Delay(2);
    }

    hdl->accel_x_offset = (int16_t)(sum_x / (int32_t)samples_count);
    hdl->accel_y_offset = (int16_t)(sum_y / (int32_t)samples_count);

    /*
     * At rest, Z axis sees gravity.
     * For ±2g mode, 1g ~= 16384 LSB.
     */
    hdl->accel_z_offset = (int16_t)((sum_z / (int32_t)samples_count) - (int32_t)MPU6050_ACCEL_SENS_2G);

    hdl->is_calibrated = 1U;

    return ERR_OK;
}

err_t mpu6050_read_accel(mpu6050_handle_t hdl, mpu6050_sample_t *sample)
{
    uint8_t raw_data[6];
    int16_t raw_x;
    int16_t raw_y;
    int16_t raw_z;
    err_t status;

    if ((hdl == NULL) || (sample == NULL)) {
        return ERR_INVALID_PARAM;
    }

    status = mpu6050_read_regs(hdl, MPU6050_REG_ACCEL_XOUT_H, raw_data, sizeof(raw_data));
    if (status != ERR_OK) {
        return status;
    }

    raw_x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    raw_y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    raw_z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

    if (hdl->is_calibrated != 0U) {
        raw_x -= hdl->accel_x_offset;
        raw_y -= hdl->accel_y_offset;
        raw_z -= hdl->accel_z_offset;
    }

    sample->accel_x = raw_x;
    sample->accel_y = raw_y;
    sample->accel_z = raw_z;

    return ERR_OK;
}


err_t mpu6050_read_gyro(mpu6050_handle_t hdl, mpu6050_gyro_sample_t *sample)
{
    uint8_t raw_data[6];
    int16_t raw_x;
    int16_t raw_y;
    int16_t raw_z;
    err_t status;

    if ((hdl == NULL) || (sample == NULL)) {
        return ERR_INVALID_PARAM;
    }

    status = mpu6050_read_regs(hdl, MPU6050_REG_GYRO_XOUT_H, raw_data, sizeof(raw_data));
    if (status != ERR_OK) {
        return status;
    }

    raw_x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    raw_y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    raw_z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

    sample->gyro_x = raw_x;
    sample->gyro_y = raw_y;
    sample->gyro_z = raw_z;

    return ERR_OK;
}

/* -------------------------------------------------------------------------- */
/*                              Private helpers                               */
/* -------------------------------------------------------------------------- */

static err_t mpu6050_write_reg(mpu6050_handle_t hdl, uint8_t reg, uint8_t value)
{
    HAL_StatusTypeDef hal_status;

    if (hdl == NULL) {
        return ERR_INVALID_PARAM;
    }

    hal_status = HAL_I2C_Mem_Write(&hi2c1,
                                   (uint16_t)(hdl->i2c_addr << 1),
                                   reg,
                                   I2C_MEMADD_SIZE_8BIT,
                                   &value,
                                   1,
                                   HAL_MAX_DELAY);

    if (hal_status != HAL_OK) {
        return ERR_HW_FAILURE;
    }

    return ERR_OK;
}

static err_t mpu6050_read_regs(mpu6050_handle_t hdl, uint8_t reg, uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef hal_status;

    if ((hdl == NULL) || (data == NULL) || (len == 0U)) {
        return ERR_INVALID_PARAM;
    }

    hal_status = HAL_I2C_Mem_Read(&hi2c1,
                                  (uint16_t)(hdl->i2c_addr << 1),
                                  reg,
                                  I2C_MEMADD_SIZE_8BIT,
                                  data,
                                  len,
                                  HAL_MAX_DELAY);

    if (hal_status != HAL_OK) {
        return ERR_HW_FAILURE;
    }

    return ERR_OK;
}
