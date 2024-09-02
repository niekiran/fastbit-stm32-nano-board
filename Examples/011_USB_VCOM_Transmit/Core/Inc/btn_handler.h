/*
 * btn_handler.h
 *
 *  Created on: Jun 15, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_BTN_HANDLER_H_
#define INC_BTN_HANDLER_H_

#include <stdint.h>
#include "main.h"

typedef enum {
  NOT_PRESSED,
  BOUNCE,
  PRESSED
} button_state_t;

uint8_t handle_user_btn(uint8_t btn_value);
uint8_t read_btn_state(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
char* getDayofweek(uint8_t number);
void process_button_press(RTC_HandleTypeDef *hrtc);

#endif /* INC_BTN_HANDLER_H_ */
