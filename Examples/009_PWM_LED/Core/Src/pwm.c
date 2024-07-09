/*
 * pwm.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */
#include "main.h"

uint16_t brightness = 0;
/* array to store three TIM channel identifiers */
uint32_t channels[3] = {TIM_CHANNEL_2, TIM_CHANNEL_4, TIM_CHANNEL_3};
uint8_t num_channels = sizeof(channels) / sizeof(channels[0]);
extern TIM_HandleTypeDef htim2;

void pwm_led() {
  for (int i = 0; i < num_channels; i++)
  {
    while (brightness < htim2.Init.Period)
    {
      brightness += 20;
      __HAL_TIM_SET_COMPARE(&htim2, channels[i], brightness);
      HAL_Delay(1);
    }
    while (brightness > 0)
    {
      brightness -= 20;
      __HAL_TIM_SET_COMPARE(&htim2, channels[i], brightness);
      HAL_Delay(1);
    }
  }
}
