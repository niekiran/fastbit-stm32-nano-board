/*
 * user_button_led.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */


#include "main.h"
#include "user_button_led.h"

/**
  * @brief  Controls an LED based on the state of a user button.
  * @note   This function initializes the GPIO pins for the user button and LED,
  *         and continuously reads the state of the user button to control the LED.
  * @param  None
  * @retval None
  */
void user_button_led() {
  GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

  if (pinState == GPIO_PIN_SET) {
    /* Delay for a short period to debounce the switch */
    HAL_Delay(50);

    /* Turn on the LED */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
  } else {
    /* Turn off the LED */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
  }
}
