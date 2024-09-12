/*
 * decimal_to_binary.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "decimal_to_binary.h"

/**
  * @brief Converts a decimal number to binary and stores it in the provided buffer.
  * @param decimal: The decimal number to convert.
  * @param binary: The buffer to store the binary representation.
  * @retval None
  */
void decimal_to_binary(int decimal, uint8_t *binary)
{
  int i = 0;

  /* Convert decimal to binary */
  while (decimal > 0) {
    binary[i] = decimal % 2 + '0';
    decimal /= 2;
    i++;
  }
  binary[i] = '\0';

  /* Reverse the binary string */
  int left = 0;
  int right = strlen((char *)binary) - 1;
  while (left < right) {
    char temp = binary[left];
    binary[left] = binary[right];
    binary[right] = temp;
    left++;
    right--;
  }
}

/**
 * @brief Processes decimal input from UART and converts it to binary.
 * @param huart: Pointer to the UART handle.
 */
void process_decimal_input(UART_HandleTypeDef *huart) {
  uint8_t rdata; // Received character
  uint8_t buf[MAX_BUF_SIZE]; // Buffer to store received characters
  uint8_t binary[MAX_BINARY_SIZE]; // Buffer to store binary representation
  const char *menu = "Enter a decimal number to be converted to binary:";
  size_t len = strlen(menu);

  HAL_UART_Receive(huart, &rdata, 1, HAL_MAX_DELAY);

  if (rdata == '\r') {
    int decimal = atoi((char *)buf); // Convert received string to integer
    decimal_to_binary(decimal, binary); // Decimal to binary conversion

    HAL_UART_Transmit(huart, binary, strlen((char *)binary), HAL_MAX_DELAY); // Transmit binary number
    HAL_UART_Transmit(huart, (uint8_t *)"\r\n", strlen("\r\n"), HAL_MAX_DELAY); // Transmit newline character
    HAL_UART_Transmit(huart, (uint8_t *)menu, len, HAL_MAX_DELAY); // Transmit menu message

    memset(buf, 0, sizeof(buf)); // Reset buffer
  } else {
    buf[strlen((char *)buf)] = rdata; // Store received character in buffer
  }
}

