/*
 * bmi270.c
 *
 *  Created on: Aug 24, 2026
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 *      Handle-based API matching this project's mpu6050.c
 */

#include "bmi270.h"
#include "bmi270_config_file.h"
#include "main.h"

#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*                          Register map (subset used)                        */
/* -------------------------------------------------------------------------- */

#define BMI270_REG_CHIP_ID          0x00U
#define BMI270_REG_DATA             0x0CU  /* ACC_X_LSB, 12-byte burst: acc xyz + gyro xyz */
#define BMI270_REG_INTERNAL_STATUS  0x21U
#define BMI270_REG_ACC_CONF         0x40U
#define BMI270_REG_ACC_RANGE        0x41U
#define BMI270_REG_GYR_CONF         0x42U
#define BMI270_REG_GYR_RANGE        0x43U
#define BMI270_REG_INIT_CTRL        0x59U
#define BMI270_REG_INIT_ADDR_0      0x5BU
#define BMI270_REG_INIT_DATA        0x5EU
#define BMI270_REG_PWR_CONF         0x7CU
#define BMI270_REG_PWR_CTRL         0x7DU
#define BMI270_REG_CMD              0x7EU

#define BMI270_CHIP_ID_VAL          0x24U
#define BMI270_CMD_SOFTRESET        0xB6U

/* +-2G, matching MPU6050_ACCEL_FS_2G_CFG for identical raw-count meaning */
#define BMI270_ACC_RANGE_2G         0x00U
/* +-500dps, matching MPU6050_GYRO_FS_500DPS_CFG for identical raw-count meaning */
#define BMI270_GYR_RANGE_500        0x02U

/* Bosch recommends uploading the config file in bursts; 32 bytes keeps each
 * I2C transaction well within HAL/I2C1 limits. Must stay even (INIT_ADDR is
 * a 16-bit word address, i.e. 2 bytes per step). */
#define BMI270_INIT_CHUNK_SIZE      32U

/* -------------------------------------------------------------------------- */
/*                              Private data type                             */
/* -------------------------------------------------------------------------- */

struct bmi270_device_t
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

static err_t bmi270_write_reg(bmi270_handle_t hdl, uint8_t reg, uint8_t value);
static err_t bmi270_write_regs(bmi270_handle_t hdl, uint8_t reg, const uint8_t *data, uint16_t len);
static err_t bmi270_read_regs(bmi270_handle_t hdl, uint8_t reg, uint8_t *data, uint16_t len);
static err_t bmi270_upload_config_file(bmi270_handle_t hdl);

/* -------------------------------------------------------------------------- */
/*                              Public functions                              */
/* -------------------------------------------------------------------------- */

bmi270_handle_t bmi270_create(uint8_t i2c_addr)
{
    bmi270_handle_t hdl;

    hdl = (bmi270_handle_t)malloc(sizeof(struct bmi270_device_t));
    if (hdl == NULL) {
        return NULL;
    }

    memset(hdl, 0, sizeof(struct bmi270_device_t));
    hdl->i2c_addr = i2c_addr;

    return hdl;
}

void bmi270_destroy(bmi270_handle_t hdl)
{
    if (hdl == NULL) {
        return;
    }

    free(hdl);
}

err_t bmi270_init(bmi270_handle_t hdl)
{
    err_t status;
    uint8_t chip_id = 0U;
    uint8_t cmd;
    uint8_t pwr_conf;
    uint8_t internal_status = 0U;
    uint8_t acc_conf;
    uint8_t acc_range;
    uint8_t gyr_conf;
    uint8_t gyr_range;
    uint8_t pwr_ctrl;

    if (hdl == NULL) {
        return ERR_INVALID_PARAM;
    }

    HAL_Delay(100);

    status = bmi270_read_regs(hdl, BMI270_REG_CHIP_ID, &chip_id, 1U);
    if (status != ERR_OK) {
        return status;
    }
    if (chip_id != BMI270_CHIP_ID_VAL) {
        return ERR_HW_FAILURE;
    }

    /* Soft reset */
    cmd = BMI270_CMD_SOFTRESET;
    status = bmi270_write_reg(hdl, BMI270_REG_CMD, cmd);
    if (status != ERR_OK) {
        return status;
    }
    HAL_Delay(2);

    /* Disable advanced power save -- required before the config file can be
     * uploaded, and while the game continuously polls the sensor */
    pwr_conf = 0x00U;
    status = bmi270_write_reg(hdl, BMI270_REG_PWR_CONF, pwr_conf);
    if (status != ERR_OK) {
        return status;
    }
    HAL_Delay(1);

    status = bmi270_upload_config_file(hdl);
    if (status != ERR_OK) {
        return status;
    }

    status = bmi270_read_regs(hdl, BMI270_REG_INTERNAL_STATUS, &internal_status, 1U);
    if (status != ERR_OK) {
        return status;
    }
    if ((internal_status & 0x0FU) != 0x01U) {
        return ERR_HW_FAILURE;
    }

    /* Accel/gyro config: normal mode, performance optimized (Bosch's
     * published register values), ranges matched to the MPU6050 path */
    acc_conf = 0xA8U;   /* filter_perf=1, bwp=normal_avg4, odr=100Hz */
    acc_range = BMI270_ACC_RANGE_2G;
    gyr_conf = 0xA9U;   /* filter_perf=1, noise_perf=0, bwp=normal, odr=200Hz */
    gyr_range = BMI270_GYR_RANGE_500;

    status = bmi270_write_reg(hdl, BMI270_REG_ACC_CONF, acc_conf);
    if (status != ERR_OK) {
        return status;
    }
    status = bmi270_write_reg(hdl, BMI270_REG_ACC_RANGE, acc_range);
    if (status != ERR_OK) {
        return status;
    }
    status = bmi270_write_reg(hdl, BMI270_REG_GYR_CONF, gyr_conf);
    if (status != ERR_OK) {
        return status;
    }
    status = bmi270_write_reg(hdl, BMI270_REG_GYR_RANGE, gyr_range);
    if (status != ERR_OK) {
        return status;
    }

    /* Power on accelerometer + gyroscope */
    pwr_ctrl = 0x06U; /* acc_en | gyr_en */
    status = bmi270_write_reg(hdl, BMI270_REG_PWR_CTRL, pwr_ctrl);
    if (status != ERR_OK) {
        return status;
    }
    HAL_Delay(1);

    return ERR_OK;
}

err_t bmi270_calibrate(bmi270_handle_t hdl)
{
    bmi270_sample_t sample;
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
        if (bmi270_read_accel(hdl, &sample) != ERR_OK) {
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
     * For +-2g mode, 1g ~= 16384 LSB.
     */
    hdl->accel_z_offset = (int16_t)((sum_z / (int32_t)samples_count) - (int32_t)BMI270_ACCEL_SENS_2G);

    hdl->is_calibrated = 1U;

    return ERR_OK;
}

err_t bmi270_read_accel(bmi270_handle_t hdl, bmi270_sample_t *sample)
{
    uint8_t raw_data[6];
    int16_t raw_x;
    int16_t raw_y;
    int16_t raw_z;
    err_t status;

    if ((hdl == NULL) || (sample == NULL)) {
        return ERR_INVALID_PARAM;
    }

    status = bmi270_read_regs(hdl, BMI270_REG_DATA, raw_data, sizeof(raw_data));
    if (status != ERR_OK) {
        return status;
    }

    /* BMI270 data registers are little-endian (LSB first), unlike MPU6050's
     * big-endian layout */
    raw_x = (int16_t)((raw_data[1] << 8) | raw_data[0]);
    raw_y = (int16_t)((raw_data[3] << 8) | raw_data[2]);
    raw_z = (int16_t)((raw_data[5] << 8) | raw_data[4]);

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

err_t bmi270_read_gyro(bmi270_handle_t hdl, bmi270_gyro_sample_t *sample)
{
    uint8_t raw_data[12];
    err_t status;

    if ((hdl == NULL) || (sample == NULL)) {
        return ERR_INVALID_PARAM;
    }

    /* Gyro registers immediately follow accel in the same 12-byte burst
     * (offsets 6-11); read the full burst rather than a separate 6-byte
     * transaction starting at the gyro registers directly, since BMI270
     * (unlike MPU6050) has no dedicated GYRO_XOUT_H-style short-cut read. */
    status = bmi270_read_regs(hdl, BMI270_REG_DATA, raw_data, sizeof(raw_data));
    if (status != ERR_OK) {
        return status;
    }

    sample->gyro_x = (int16_t)((raw_data[7] << 8) | raw_data[6]);
    sample->gyro_y = (int16_t)((raw_data[9] << 8) | raw_data[8]);
    sample->gyro_z = (int16_t)((raw_data[11] << 8) | raw_data[10]);

    return ERR_OK;
}

/* -------------------------------------------------------------------------- */
/*                              Private helpers                               */
/* -------------------------------------------------------------------------- */

static err_t bmi270_write_reg(bmi270_handle_t hdl, uint8_t reg, uint8_t value)
{
    return bmi270_write_regs(hdl, reg, &value, 1U);
}

static err_t bmi270_write_regs(bmi270_handle_t hdl, uint8_t reg, const uint8_t *data, uint16_t len)
{
    HAL_StatusTypeDef hal_status;

    if ((hdl == NULL) || (data == NULL) || (len == 0U)) {
        return ERR_INVALID_PARAM;
    }

    hal_status = HAL_I2C_Mem_Write(&hi2c1,
                                    (uint16_t)(hdl->i2c_addr << 1),
                                    reg,
                                    I2C_MEMADD_SIZE_8BIT,
                                    (uint8_t *)data,
                                    len,
                                    HAL_MAX_DELAY);

    if (hal_status != HAL_OK) {
        return ERR_HW_FAILURE;
    }

    return ERR_OK;
}

static err_t bmi270_read_regs(bmi270_handle_t hdl, uint8_t reg, uint8_t *data, uint16_t len)
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

/**
  * @brief Uploads the mandatory 8192-byte BMI270 configuration image in
  *        chunks, per Bosch's initialization sequence. The BMI270 will not
  *        produce valid accel/gyro data without this.
  */
static err_t bmi270_upload_config_file(bmi270_handle_t hdl)
{
    err_t status;
    uint8_t init_ctrl;

    init_ctrl = 0x00U;
    status = bmi270_write_reg(hdl, BMI270_REG_INIT_CTRL, init_ctrl);
    if (status != ERR_OK) {
        return status;
    }

    for (uint16_t offset = 0; offset < BMI270_CONFIG_FILE_SIZE; offset += BMI270_INIT_CHUNK_SIZE) {
        uint16_t addr_word = offset / 2U;
        /* INIT_ADDR_0 holds only bits[3:0] of the word address; INIT_ADDR_1
         * holds bits[11:4]. This is NOT a plain 16-bit little-endian split. */
        uint8_t addr_buf[2] = { (uint8_t)(addr_word & 0x0FU), (uint8_t)(addr_word >> 4) };

        status = bmi270_write_regs(hdl, BMI270_REG_INIT_ADDR_0, addr_buf, 2U);
        if (status != ERR_OK) {
            return status;
        }

        status = bmi270_write_regs(hdl, BMI270_REG_INIT_DATA,
                                    &bmi270_config_file[offset], BMI270_INIT_CHUNK_SIZE);
        if (status != ERR_OK) {
            return status;
        }
    }

    init_ctrl = 0x01U;
    status = bmi270_write_reg(hdl, BMI270_REG_INIT_CTRL, init_ctrl);
    if (status != ERR_OK) {
        return status;
    }
    HAL_Delay(20);

    return ERR_OK;
}
