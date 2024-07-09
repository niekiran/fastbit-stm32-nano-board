/*
 * decimal_to_binary.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_DECIMAL_TO_BINARY_H_
#define INC_DECIMAL_TO_BINARY_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_BUF_SIZE 64
#define MAX_BINARY_SIZE 32

/* Function prototypes */
void decimal_to_binary(int decimal, uint8_t *binary);
void process_decimal_input(UART_HandleTypeDef *huart);

#endif /* INC_DECIMAL_TO_BINARY_H_ */
