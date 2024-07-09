/*
 * map.c
 *
 *  Created on: May 31, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include <math.h>
#include <stdio.h>
#include "mpu6050.h"
#include "main.h"
#define RAD_TO_DEG 57.295779513082320876798154814105

#define WHO_AM_I_REG 				0x75
#define PWR_MGMT_1_REG 			0x6B
#define SMPLRT_DIV_REG 			0x19
#define ACCEL_CONFIG_REG 		0x1C
#define ACCEL_XOUT_H_REG 		0x3B
#define TEMP_OUT_H_REG 			0x41
#define GYRO_CONFIG_REG 		0x1B
#define GYRO_XOUT_H_REG 		0x43

// Setup MPU6050
uint8_t temp_data;
#define MPU6050_ADDR 0x68
extern I2C_HandleTypeDef hi2c1;
uint32_t timer;

Kalman_t KalmanX = {
	.Q_angle   = 0.001f,
	.Q_bias    = 0.003f,
	.R_measure = 0.03f
};

Kalman_t KalmanY = {
	.Q_angle   = 0.001f,
	.Q_bias    = 0.003f,
	.R_measure = 0.03f,
};
/**
  * @brief Initializes the MPU6050 sensor by configuring power management, gyroscope, and accelerometer.
  * @param None
  * @retval None
  */
void MPU6050_Init() {
  PowerManagement_Config();
  Data_Rate_Config();
  Gyro_Config();
  Accelerometer_Config();
}

/**
  * @brief Configures the power management settings of the MPU6050 sensor to exit sleep mode.
  * @param None
  * @retval None
  */
void PowerManagement_Config()
{
  /* Set the value to be written to the power management register */
  temp_data = 0x00;

  /* Write the value to the power management register via I2C communication */
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, PWR_MGMT_1_REG, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
    /*print in SWV terminal*/
    printf("Exiting from sleep mode...\n");
  } else {
    printf("Failed to exit from sleep mode...\n");
  }
}

/**
  * @brief Configures the Data rate settings of the MPU6050 sensor.
  * @param None
  * @retval None
  */
void Data_Rate_Config()
{
  /* Set the value to be written to the accelerometer configuration register */
  temp_data = 0x07;

  /* Write the value to the accelerometer configuration register via I2C communication */
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, SMPLRT_DIV_REG, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
    printf("Configuring data rate of 1KHz...\n");
  } else {
    printf("Failed to configure data rate of 1KHz...\n");
  }
}

/**
  * @brief Configures the gyroscope settings of the MPU6050 sensor.
  * @param None
  * @retval None
  */
void Gyro_Config()
{
  /* Set the value to be written to the gyroscope configuration register */
  temp_data = FS_GYRO_2000;

  /* Write the value to the gyroscope configuration register via I2C communication */
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, GYRO_CONFIG_REG, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
    printf("Configuring gyroscope...\n");
  } else {
    printf("Failed to configure gyroscope...\n");
  }
}

/**
  * @brief Configures the accelerometer settings of the MPU6050 sensor.
  * @param None
  * @retval None
  */
void Accelerometer_Config()
{
  /* Set the value to be written to the accelerometer configuration register */
  temp_data = FS_ACC_16G;

  /* Write the value to the accelerometer configuration register via I2C communication */
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, ACCEL_CONFIG_REG, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
    printf("Configuring accelerometer...\n");
  } else {
    printf("Failed to configure accelerometer...\n");
  }
}


/**
  * @brief  Reads the gyroscope data from the MPU6050 sensor
  * @param  DataStruct: Pointer to the MPU6050_t structure to store the gyroscope data
  * @retval None
  */
void MPU6050_Read_Accel(MPU6050_t *DataStruct) {
	uint8_t Rec_Data[6];

	/*Read 6 BYTES of data starting from ACCEL_XOUT_H register */
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, HAL_MAX_DELAY);

	DataStruct->Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
	DataStruct->Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
	DataStruct->Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

	/* convert the RAW values into acceleration in 'g' */
	DataStruct->Ax = DataStruct->Accel_X_RAW / ACC_FS_SENSITIVITY_0;
	DataStruct->Ay = DataStruct->Accel_Y_RAW / ACC_FS_SENSITIVITY_0;
	DataStruct->Az = DataStruct->Accel_Z_RAW / ACC_FS_SENSITIVITY_0;
}

/**
  * @brief  Reads the accelerometer data from the MPU6050 sensor
  * @param  DataStruct: Pointer to the MPU6050_t structure to store the accelerometer data
  * @retval None
  */
void MPU6050_Read_Gyro(MPU6050_t *DataStruct) {
	uint8_t Rec_Data[6];

	/* Read 6 BYTES of data starting from GYRO_XOUT_H register */
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, HAL_MAX_DELAY);

	DataStruct->Gyro_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
	DataStruct->Gyro_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
	DataStruct->Gyro_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

	/* convert the RAW values into dps (�/s) */
	DataStruct->Gx = DataStruct->Gyro_X_RAW / GYR_FS_SENSITIVITY_0;
	DataStruct->Gy = DataStruct->Gyro_Y_RAW / GYR_FS_SENSITIVITY_0;
	DataStruct->Gz = DataStruct->Gyro_Z_RAW / GYR_FS_SENSITIVITY_0;
}

/**
  * @brief  Reads the temperature data from the MPU6050 sensor
  * @param  DataStruct: Pointer to the MPU6050_t structure to store the temperature data
  * @retval None
  */
void MPU6050_Read_Temp(MPU6050_t *DataStruct) {
	uint8_t Rec_Data[2];
	int16_t temp;

	/* Read 2 BYTES of data starting from TEMP_OUT_H_REG register */
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, TEMP_OUT_H_REG, 1, Rec_Data, 2, HAL_MAX_DELAY);

	temp = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
	DataStruct->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);
}

/**
  * @brief  Reads all sensor data from the MPU6050
  * @param  DataStruct: Pointer to the MPU6050_t structure to store the sensor data
  * @retval None
  */
void MPU6050_Read_All(MPU6050_t *DataStruct) {
	uint8_t Rec_Data[14];
	int16_t temp;

	/* Read 14 BYTES of data starting from ACCEL_XOUT_H register */
	if (HAL_I2C_Mem_Read(&hi2c1, (MPU6050_ADDR << 1), ACCEL_XOUT_H_REG, 1, Rec_Data, 14, HAL_MAX_DELAY)!= HAL_OK) {
    printf("Failed to read from MPU6050\n");
    return;
  }

	DataStruct->Accel_X_RAW = (int16_t) (Rec_Data[0] << 8 | Rec_Data[1]);
	DataStruct->Accel_Y_RAW = (int16_t) (Rec_Data[2] << 8 | Rec_Data[3]);
	DataStruct->Accel_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);

	temp = (int16_t) (Rec_Data[6] << 8 | Rec_Data[7]);

	DataStruct->Gyro_X_RAW = (int16_t) (Rec_Data[8] << 8 | Rec_Data[9]);
	DataStruct->Gyro_Y_RAW = (int16_t) (Rec_Data[10] << 8 | Rec_Data[11]);
	DataStruct->Gyro_Z_RAW = (int16_t) (Rec_Data[12] << 8 | Rec_Data[13]);

	DataStruct->Ax = DataStruct->Accel_X_RAW / ACC_FS_SENSITIVITY_0;
	DataStruct->Ay = DataStruct->Accel_Y_RAW / ACC_FS_SENSITIVITY_0;
	DataStruct->Az = DataStruct->Accel_Z_RAW / ACC_FS_SENSITIVITY_0;

	DataStruct->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);

	DataStruct->Gx = DataStruct->Gyro_X_RAW / GYR_FS_SENSITIVITY_0;
	DataStruct->Gy = DataStruct->Gyro_Y_RAW / GYR_FS_SENSITIVITY_0;
	DataStruct->Gz = DataStruct->Gyro_Z_RAW / GYR_FS_SENSITIVITY_0;
	//printf("%d   %d   %d\n", DataStruct->Accel_X_RAW, DataStruct->Accel_Y_RAW, DataStruct->Accel_Z_RAW);
	// Kalman angle solve
	double dt = (double) (HAL_GetTick() - timer) / 1000;
	timer = HAL_GetTick();

	DataStruct->Gyro_angle_z += (DataStruct->Gz)*dt;
	double roll;
	double roll_sqrt = sqrt(
					DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
	if (roll_sqrt != 0.0) {
			roll = atan(DataStruct->Accel_Y_RAW / roll_sqrt) * RAD_TO_DEG;
	} else {
			roll = 0.0;
	}
	double pitch = atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW) * RAD_TO_DEG;
	if ((pitch < -90 && DataStruct->Kalman_angle_y > 90) || (pitch > 90 && DataStruct->Kalman_angle_y < -90)) {
			KalmanY.angle = pitch;
			DataStruct->Kalman_angle_y = pitch;
	} else {
			DataStruct->Kalman_angle_y = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
	}
	if (fabs(DataStruct->Kalman_angle_y) > 90)
			DataStruct->Gx = -DataStruct->Gx;
	DataStruct->Kalman_angle_x = Kalman_getAngle(&KalmanX, roll, DataStruct->Gy, dt);
}

/**
  * @brief  Get the estimated angle using the Kalman filter
  * @param  Kalman: Pointer to the Kalman_t structure containing the filter state
  * @param  newAngle: The new measured angle
  * @param  newRate: The new measured rate
  * @param  dt: The time interval since the last update
  * @retval The estimated angle
  */
double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt) {
	double rate = newRate - Kalman->bias;
	Kalman->angle += dt * rate;

	Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
	Kalman->P[0][1] -= dt * Kalman->P[1][1];
	Kalman->P[1][0] -= dt * Kalman->P[1][1];
	Kalman->P[1][1] += Kalman->Q_bias * dt;

	double S = Kalman->P[0][0] + Kalman->R_measure;
	double K[2];
	K[0] = Kalman->P[0][0] / S;
	K[1] = Kalman->P[1][0] / S;

	double y = newAngle - Kalman->angle;
	Kalman->angle += K[0] * y;
	Kalman->bias += K[1] * y;

	double P00_temp = Kalman->P[0][0];
	double P01_temp = Kalman->P[0][1];

	Kalman->P[0][0] -= K[0] * P00_temp;
	Kalman->P[0][1] -= K[0] * P01_temp;
	Kalman->P[1][0] -= K[1] * P00_temp;
	Kalman->P[1][1] -= K[1] * P01_temp;

	return Kalman->angle;
};
