/*
 * uart.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "queue.h"
#include "main.h"

/* Function prototypes */
void display_menu(UART_HandleTypeDef *huart);
void display_invalid_command(UART_HandleTypeDef *huart);
void display_invalid_argument(UART_HandleTypeDef *huart);
void process_command_queue();
void execute_command(struct led_command_data data);

#endif /* INC_UART_H_ */
