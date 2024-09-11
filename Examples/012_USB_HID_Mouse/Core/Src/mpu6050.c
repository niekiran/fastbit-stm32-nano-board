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

#define MPU6050_ADDR        0x68
#define WHO_AM_I_REG 				0x75
#define PWR_MGMT_1_REG 			0x6B
#define SMPLRT_DIV_REG 			0x19
#define ACCEL_CONFIG_REG 		0x1C
#define ACCEL_XOUT_H_REG 		0x3B
#define TEMP_OUT_H_REG 			0x41
#define GYRO_CONFIG_REG 		0x1B
#define GYRO_XOUT_H_REG 		0x43

uint8_t temp_data;
extern I2C_HandleTypeDef hi2c1;
uint32_t timer;
static void init_delay(uint32_t delay);
static void power_management_config();
static void gyro_config();
static void accelerometer_config();

/**
  * @brief Initializes the Kalman filter parameters.
  * @param kf Pointer to the Kalman filter structure.
  * @param process_variance Process variance parameter.
  * @param measurement_variance Measurement variance parameter.
  * @param estimated_error Estimated error parameter.
  * @retval None
  */
void KalmanFilter_Init(KalmanFilter *kf, double process_variance, double measurement_variance, double estimated_error) {
  kf->process_variance = process_variance;
  kf->measurement_variance = measurement_variance;
  kf->estimated_error = estimated_error;
  kf->posteri_estimate = 0.0;
  kf->posteri_error = 1.0;
}

/**
  * @brief Updates the Kalman filter with a new measurement.
  * @param kf Pointer to the Kalman filter structure.
  * @param measurement The new measurement value.
  * @retval The updated estimated value after applying the Kalman filter.
  */
double KalmanFilter_Update(KalmanFilter *kf, double measurement) {
  double priori_estimate = kf->posteri_estimate;
  double priori_error = kf->posteri_error + kf->process_variance;
  double blending_factor = priori_error / (priori_error + kf->measurement_variance);

  kf->posteri_estimate = priori_estimate + blending_factor * (measurement - priori_estimate);
  kf->posteri_error = (1 - blending_factor) * priori_error;

  return kf->posteri_estimate;
}


/**
  * @brief Initializes the MPU6050 sensor by configuring power management, gyroscope, and accelerometer.
  * @param None
  * @retval None
  */
void MPU6050_Init() {
  init_delay(100);
  power_management_config();
  gyro_config();
  accelerometer_config();
}

/**
 * @brief Applies a delay for initialization purposes.
 * @param delay The delay time in milliseconds.
 * @retval None
 */
static void init_delay(uint32_t delay) {
  HAL_Delay(delay);
}

/**
  * @brief Configures the power management settings of the MPU6050 sensor to exit sleep mode.
  * @param None
  * @retval None
  */
static void power_management_config()
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
  * @brief Configures the gyroscope settings of the MPU6050 sensor.
  * @param None
  * @retval None
  */
static void gyro_config()
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
static void accelerometer_config()
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
	DataStruct->Ax = DataStruct->Accel_X_RAW / ACC_FS_SENSITIVITY_3;
	DataStruct->Ay = DataStruct->Accel_Y_RAW / ACC_FS_SENSITIVITY_3;
	DataStruct->Az = DataStruct->Accel_Z_RAW / ACC_FS_SENSITIVITY_3;
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
	DataStruct->Gx = DataStruct->Gyro_X_RAW / GYR_FS_SENSITIVITY_3;
	DataStruct->Gy = DataStruct->Gyro_Y_RAW / GYR_FS_SENSITIVITY_3;
	DataStruct->Gz = DataStruct->Gyro_Z_RAW / GYR_FS_SENSITIVITY_3;
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

	DataStruct->Ax = DataStruct->Accel_X_RAW / ACC_FS_SENSITIVITY_3;
	DataStruct->Ay = DataStruct->Accel_Y_RAW / ACC_FS_SENSITIVITY_3;
	DataStruct->Az = DataStruct->Accel_Z_RAW / ACC_FS_SENSITIVITY_3;

	DataStruct->Temperature = (float) ((int16_t) temp / (float) 340.0 + (float) 36.53);

	DataStruct->Gx = DataStruct->Gyro_X_RAW / GYR_FS_SENSITIVITY_3;
	DataStruct->Gy = DataStruct->Gyro_Y_RAW / GYR_FS_SENSITIVITY_3;
	DataStruct->Gz = DataStruct->Gyro_Z_RAW / GYR_FS_SENSITIVITY_3;
	//printf("%d   %d   %d\n", DataStruct->Accel_X_RAW, DataStruct->Accel_Y_RAW, DataStruct->Accel_Z_RAW);
}

/**
  * @brief Applies a filtering algorithm to gyroscope data.
  * @param gyroz Pointer to the gyroscope data for the Z-axis.
  * @param gyroy Pointer to the gyroscope data for the Y-axis.
  * @retval None
  */
void filter_gyro_data(double *gyroz, double *gyroy) {
  static KalmanFilter kf_gyroz;
  static KalmanFilter kf_gyroy;
  static int kf_initialized = 0;

  if (!kf_initialized) {
    KalmanFilter_Init(&kf_gyroz, 1e-5, 1e-2, 1.0);
    KalmanFilter_Init(&kf_gyroy, 1e-5, 1e-2, 1.0);
    kf_initialized = 1;
  }

  *gyroz = KalmanFilter_Update(&kf_gyroz, *gyroz);
  *gyroy = KalmanFilter_Update(&kf_gyroy, *gyroy);
}

/**
  * @brief  Reads and processes gyroscope data from the MPU6050 sensor.
  * @param  mpu6050_data: Pointer to the MPU6050 data structure.
  * @param  gyroz: Pointer to store the processed gyroscope Z-axis data.
  * @param  gyroy: Pointer to store the processed gyroscope Y-axis data.
  * @retval None
  */
void read_gyro_data(MPU6050_t *mpu6050_data, double *gyroz, double *gyroy)
{
  MPU6050_Read_All(mpu6050_data);
  *gyroz = mpu6050_data->Gz;
  *gyroy = mpu6050_data->Gy;
  filter_gyro_data(gyroz, gyroy);
}
