/*
 * led.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */
#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>

void led_on(uint8_t led_number);
void led_off(uint8_t led_number);
void led_toggle(uint8_t led_number, uint32_t time_delay);

#endif /* INC_LED_H_ */
