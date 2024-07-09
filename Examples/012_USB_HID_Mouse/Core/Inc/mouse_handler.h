/*
 * mouse_handler.h
 *
 *  Created on: Jun 11, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_MOUSE_HANDLER_H_
#define INC_MOUSE_HANDLER_H_

#include <stdint.h>
#include "main.h"
#include "mpu6050.h"

typedef enum {
  NOT_PRESSED,
  BOUNCE,
  PRESSED
} button_state_t;

/* mouse btn handling function prototytpe */
uint8_t handle_mouse_button(uint8_t btn_value);
uint8_t read_btn_state(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void move_cursor(double gyroz, double gyroy, mouseHID *mouse_hid);
void update_btn_state(mouseHID *mouse_hid, uint8_t btn_pad_value);

#endif /* INC_MOUSE_HANDLER_H_ */
