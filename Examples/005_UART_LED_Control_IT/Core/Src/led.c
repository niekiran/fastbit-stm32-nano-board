/*
 * led.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "main.h"
#include "led.h"
#include "uart.h"
#include <string.h>

extern uint32_t invalid_command_printed;

/**
  * @brief  Turns on the specified LED.
  * @param  ledNumber: The number of the LED to turn on (1, 2, or 3).
  * @retval None
  */
void led_on(uint8_t led_number) {
  switch(led_number) {
  case 1:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
    break;
  case 2:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
    break;
  case 3:
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    break;
  default:
    if (!invalid_command_printed) {
      display_invalid_argument(&huart1);
      invalid_command_printed = 1; // Set the flag
    }
  }
}

/**
  * @brief  Turns off the specified LED.
  * @param  ledNumber: The number of the LED to turn off (1, 2, or 3).
  * @retval None
  */
void led_off(uint8_t led_number) {
  switch(led_number) {
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
    if (!invalid_command_printed) {
      display_invalid_argument(&huart1);
      invalid_command_printed = 1;
    }
  }
}

/**
  * @brief  Toggles the specified LED with a specified delay.
  * @param  ledNumber: The number of the LED to toggle (1, 2, or 3).
  * @param  timedelay: The delay duration in milliseconds.
  * @retval None
  */
void led_toggle(uint8_t led_number, uint32_t time_delay) {
  switch(led_number) {
  case 1:
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
    HAL_Delay(time_delay); break;
  case 2:
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    HAL_Delay(time_delay); break;
  case 3:
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
    HAL_Delay(time_delay); break;
  default:
    if (!invalid_command_printed) {
      display_invalid_argument(&huart1);
      invalid_command_printed = 1;
    }
  }
}
