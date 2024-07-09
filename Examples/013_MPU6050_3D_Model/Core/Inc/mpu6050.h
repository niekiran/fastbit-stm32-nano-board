/*
 * map.h
 *
 *  Created on: May 31, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include <stdint.h>

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

/* Accelerometer sensitivity for different full-scale ranges */
#define ACC_FS_SENSITIVITY_0  16384.0  // Sensitivity for FS_ACC_2G
#define ACC_FS_SENSITIVITY_1  8192.0   // Sensitivity for FS_ACC_4G
#define ACC_FS_SENSITIVITY_2  4096.0   // Sensitivity for FS_ACC_8G
#define ACC_FS_SENSITIVITY_3  2048.0   // Sensitivity for FS_ACC_16G

/* Gyroscope sensitivity for different full-scale ranges */
#define GYR_FS_SENSITIVITY_0  131.0    // Sensitivity for FS_GYRO_250
#define GYR_FS_SENSITIVITY_1  65.5     // Sensitivity for FS_GYRO_500
#define GYR_FS_SENSITIVITY_2  32.8     // Sensitivity for FS_GYRO_1000
#define GYR_FS_SENSITIVITY_3  16.4     // Sensitivity for FS_GYRO_2000

/*  MPU6050 structure */
typedef struct {

	int16_t Accel_X_RAW;
	int16_t Accel_Y_RAW;
	int16_t Accel_Z_RAW;
	double Ax;
	double Ay;
	double Az;

	int16_t Gyro_X_RAW;
	int16_t Gyro_Y_RAW;
	int16_t Gyro_Z_RAW;
	double Gx;
	double Gy;
	double Gz;

	float Temperature;
	double Gyro_angle_z;

	double Kalman_angle_x;
	double Kalman_angle_y;
} MPU6050_t;

/* Kalman structure */
typedef struct {
    double Q_angle;
    double Q_bias;
    double R_measure;
    double angle;
    double bias;
    double P[2][2];
} Kalman_t;

void MPU6050_Init();
void PowerManagement_Config();
void Data_Rate_Config();
void Gyro_Config();
void Accelerometer_Config();
void MPU6050_Read_Accel(MPU6050_t *DataStruct);
void MPU6050_Read_Gyro(MPU6050_t *DataStruct);
void MPU6050_Read_Temp(MPU6050_t *DataStruct);
void MPU6050_Read_All(MPU6050_t *DataStruct);
double apply_threshold(double value, double lower_threshold);
double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);


#endif /* INC_MPU6050_H_ */
