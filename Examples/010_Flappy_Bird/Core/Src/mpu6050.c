/*
 * mpu6050.c
 *
 *  Created on: Apr 12, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "mpu6050.h"
#include <main.h>
#include <math.h>
#include <stdio.h>

uint8_t temp_data = 0;

/* Private function prototypes */
static void init_delay(uint32_t delay) ;
static void power_management_config();
static void gyro_config();
static void accelerometer_config();

/**
  * @brief Initializes the MPU6050 sensor by configuring power management, gyroscope, and accelerometer.
  * @param None
  * @retval None
  */
void mpu6050_init() {
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
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, REG_USR_CTRL, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
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
  temp_data = FS_GYRO_500;

  /* Write the value to the gyroscope configuration register via I2C communication */
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, REG_CONFIG_GYRO, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
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
  temp_data = FS_ACC_4G;

  /* Write the value to the accelerometer configuration register via I2C communication */
  if ( (HAL_I2C_Mem_Write(&hi2c1, (MPU6050_ADDR << 1) + 0, REG_CONFIG_ACC, 1, &temp_data, 1, HAL_MAX_DELAY) == HAL_OK) ) {
    printf("Configuring accelerometer...\n");
  } else {
    printf("Failed to configure accelerometer...\n");
  }
}


/**
  * @brief Reads data from the MPU6050 sensor, including accelerometer and gyroscope values,
  *        and calculates roll and pitch angles using the accelerometer data.
  * @param None
  * @retval None
  */
void mpu6050_read() {
  uint8_t data[14];                         // Data buffer to hold all sensor data (accelerometer and gyroscope)
  int16_t x_acc, y_acc, z_acc;              // Accelerometer data for x, y, and z axes
  int16_t x_gyro, y_gyro, z_gyro;           // Gyroscope data for x, y, and z axes
  double accx,accy,accz,gyrox,gyroy,gyroz;
  double radianx, radiany;
  // Read all sensor data from the MPU6050
  HAL_I2C_Mem_Read(&hi2c1, (MPU6050_ADDR << 1), REG_DATA, 1, data, 14, HAL_MAX_DELAY);
  /* Extract accelerometer data (16-bit 2's complement format, high byte first) */
  x_acc = (int16_t)((data[0] << 8) | data[1]);
  y_acc = (int16_t)((data[2] << 8) | data[3]);
  z_acc = (int16_t)((data[4] << 8) | data[5]);

  /* Extract gyroscope data (16-bit 2's complement format, high byte first) */
  x_gyro = (int16_t)((data[8] << 8) | data[9]);
  y_gyro = (int16_t)((data[10] << 8) | data[11]);
  z_gyro = (int16_t)((data[12] << 8) | data[13]);

  /*Convert accelerometer raw values in to 'g'(acceleration due to gravity) values */
  accx = (double)x_acc / ACC_FS_SENSITIVITY_3;
  accy = (double)y_acc / ACC_FS_SENSITIVITY_3;
  accz = (double)z_acc / ACC_FS_SENSITIVITY_3;

  /* Convert gyroscope raw values to degrees per second ('°/s') */
  gyrox = (double)x_gyro / GYR_FS_SENSITIVITY_3;
  gyroy = (double)y_gyro / GYR_FS_SENSITIVITY_3;
  gyroz = (double)z_gyro / GYR_FS_SENSITIVITY_3;

  /* Calculate roll and pitch angles using accelerometer data */
  radianx = asin(accx / sqrt(accx * accx + accz * accz)); // Fix the arguments passed to asin
  radiany = asin(accy / sqrt(accy * accy + accz * accz)); // Fix the arguments passed to asin

  /* Convert roll and pitch angles from radians to degrees */
  degreex = radianx * (180.0 / M_PI); // Roll
  degreey = radiany * (180.0 / M_PI); // Pitch

  /* Print out the accelerometer and gyroscope values along with roll and pitch angles in SWV terminal */
  printf("Acc(g)=> X:%.2f Y:%.2f Z:%.2f   Gyro(dps)=> X:%.2f Y:%.2f Z:%.2f\n", accx, accy, accz, gyrox, gyroy, gyroz);
  printf("Roll: %.2f degrees, Pitch: %.2f degrees\n", degreex, degreey);
}


