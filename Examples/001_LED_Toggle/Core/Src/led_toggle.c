/*
 * led_toggle.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "led_toggle.h"

/**
  * @brief Toggles the state of the LED.
  * @retval None
  */
void led_toggle() {
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); // Toggle BLUE_LED
  HAL_Delay(250);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3); // Toggle RED_LED
  HAL_Delay(250);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2); // Toggle GREEN_LED
  HAL_Delay(250);

  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2); // Toggle GREEN_LED
  HAL_Delay(250);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3); // Toggle RED_LED
  HAL_Delay(250);
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1); // Toggle BLUE_LED
  HAL_Delay(250);
}
