/*
 * bmi270.h
 *
 *  Created on: Aug 22, 2026
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 *
 *  Driver for the Bosch BMI270 6-axis IMU, used as the MPU6050 replacement
 *  on Fastbit STM32 Nano board v2.1. Same public interface as mpu6050.h
 *  (bmi270_init / bmi270_read) so main.c can switch sensors with one macro.
 */

#ifndef INC_BMI270_H_
#define INC_BMI270_H_

/* Slave address (SDO pin tied low, matches MPU6050 address/pin so no board
 * wiring change is required between v2.0 and v2.1) */
#define BMI270_ADDR             0x68

/* Register map (subset actually used by this driver) */
#define BMI270_REG_CHIP_ID      0x00
#define BMI270_REG_DATA         0x0C  // ACC_X_LSB, 12-byte burst read: acc xyz + gyro xyz
#define BMI270_REG_INTERNAL_STATUS 0x21
#define BMI270_REG_ACC_CONF     0x40
#define BMI270_REG_ACC_RANGE    0x41
#define BMI270_REG_GYR_CONF     0x42
#define BMI270_REG_GYR_RANGE    0x43
#define BMI270_REG_INIT_CTRL    0x59
#define BMI270_REG_INIT_ADDR_0  0x5B
#define BMI270_REG_INIT_DATA    0x5E
#define BMI270_REG_PWR_CONF     0x7C
#define BMI270_REG_PWR_CTRL     0x7D
#define BMI270_REG_CMD          0x7E

#define BMI270_CHIP_ID_VAL      0x24
#define BMI270_CMD_SOFTRESET    0xB6

/* Accelerometer full-scale range (matches FS_ACC_16G on the MPU6050 path so
 * both boards feel the same in-game) */
#define BMI270_ACC_RANGE_16G    0x03
#define BMI270_ACC_FS_SENSITIVITY 2048.0 // LSB/g at +-16G

/* Gyroscope full-scale range (matches the sensitivity actually used by
 * mpu6050_read(), i.e. GYR_FS_SENSITIVITY_3 / +-2000dps) */
#define BMI270_GYR_RANGE_2000   0x00
#define BMI270_GYR_FS_SENSITIVITY 16.4  // LSB/(deg/s) at +-2000dps

void bmi270_init(void);
void bmi270_read(void);

#endif /* INC_BMI270_H_ */
