/*
 * led.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "led.h"
#include "mpu6050.h"
#include "main.h"

extern double degreex, degreey;
/**
  * @brief Turns on or off LEDs based on the condition of degree x and y.
  * @param None
  * @retval None
  */
void led_on()
{
  /* Turn on LED on pin PA2 if degreey is greater than 10 */
  if(degreey > 10) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
  }
  /* Turn on LED on pin PA3 if degreex is greater than 25 or less than -25 */
  if( (degreex > 25) || (degreex < -25)) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
  }
  /* Turn on LED on pin PA1 if degreey is less than -10 */
  if(degreey < -10) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  }
}
