/*
 * led.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "led.h"
#include "main.h"

/**
  * @brief  Turns on the LED.
  * @note   the LED is connected to GPIO_PIN_1 (BLUE_LED), GPIO_PIN_2 (GREEN_LED), and GPIO_PIN_3 (RED_LED).
  * @retval None
  */
void led_on() {
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
}

/**
  * @brief  Turns off the LEDs.
  * @note   the LED is connected to GPIO_PIN_1 (BLUE_LED), GPIO_PIN_2 (GREEN_LED), and GPIO_PIN_3 (RED_LED).
  * @retval None
  */
void led_off(int press_count) {
  switch (press_count) {
  case 1:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    break;
  default:
    /* Reset button press count and turn off all LEDs */
    press_count = 0;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);
    break;
  }
}
