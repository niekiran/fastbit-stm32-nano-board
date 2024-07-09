/*
 * mpu6050.h
 *
 *  Created on: Apr 12, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

/* Slave address*/
#define MPU6050_ADDR        0x68

/* Gyroscopes full scale range */
#define FS_GYRO_250         0
#define FS_GYRO_500         8
#define FS_GYRO_1000        9
#define FS_GYRO_2000        10

/* Accelerometer full scale range */
#define FS_ACC_2G           0
#define FS_ACC_4G           8
#define FS_ACC_8G           9
#define FS_ACC_16G          10

#define REG_CONFIG_GYRO     27  // Accelerometer Configuration
#define REG_CONFIG_ACC      28  // Gyroscope Configuration
#define REG_USR_CTRL        107 // Power Management
#define REG_DATA            59  // FIFO Read Write

// Define accelerometer sensitivity for different full-scale ranges
#define ACC_FS_SENSITIVITY_0 16384.0  // Sensitivity for FS_ACC_2G
#define ACC_FS_SENSITIVITY_1 8192.0   // Sensitivity for FS_ACC_4G
#define ACC_FS_SENSITIVITY_2 4096.0   // Sensitivity for FS_ACC_8G
#define ACC_FS_SENSITIVITY_3 2048.0   // Sensitivity for FS_ACC_16G

// Define gyroscope sensitivity for different full-scale ranges
#define GYR_FS_SENSITIVITY_0 131.0    // Sensitivity for FS_GYRO_250
#define GYR_FS_SENSITIVITY_1 65.5     // Sensitivity for FS_GYRO_500
#define GYR_FS_SENSITIVITY_2 32.8     // Sensitivity for FS_GYRO_1000
#define GYR_FS_SENSITIVITY_3 16.4     // Sensitivity for FS_GYRO_2000


void mpu6050_init();
void mpu6050_read();

#endif /* INC_MPU6050_H_ */
