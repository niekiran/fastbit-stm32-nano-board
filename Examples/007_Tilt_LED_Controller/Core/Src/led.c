/*
 * led.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "led.h"
#include "main.h"

/**
  * @brief Turns on or off LEDs based on the condition of degree x and y.
  * @param None
  * @retval None
  */
void led_indicate()
{
  double roll = 0.0, pitch = 0.0;
  /* Read sensor data from the MPU6050 */
  mpu6050_read();

  roll  = degreex;
  pitch = degreey;
  /* Turn on LED on pin PA2 if degreey is greater than 10 */
  if(pitch > 10) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
  }
  /* Turn on LED on pin PA3 if degreex is greater than 25 or less than -25 */
  if( (roll > 10) || (roll < -10)) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
  }
  /* Turn on LED on pin PA1 if degreey is less than -10 */
  if(pitch < -10) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  }
}
