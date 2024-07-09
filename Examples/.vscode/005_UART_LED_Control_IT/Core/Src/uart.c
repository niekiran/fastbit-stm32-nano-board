/*
 * uart.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */


#include "uart.h"
#include "queue.h"
#include "led.h"
#include "main.h"
#include <string.h>

extern uint32_t invalid_command_printed;
extern UART_HandleTypeDef huart1;

/**
 * @brief Display the menu of valid commands.
 *
 * This function transmits the menu of valid commands via UART.
 *
 * @param huart Pointer to the UART handle structure.
 */
void display_menu(UART_HandleTypeDef *huart) {
  const uint8_t *menu = (const uint8_t *)"\r\nEnter Valid commands:\r\n"
                          "LEDON [1/2/3] - Turn on LED 1, 2, or 3\r\n"
                          "LEDOFF [1/2/3] - Turn off LED 1, 2, or 3\r\n"
                          "LEDTOGGLE [1/2/3] [delay] - Toggle LED 1, 2, or 3 with specified delay\r\n";
  HAL_UART_Transmit(huart, menu, strlen((char *)menu), HAL_MAX_DELAY);
}

/**
  * @brief Sends an "Invalid Argument" message over UART.
  *
  * This function transmits the message "Invalid Argument\r\n" via UART.
  *
  * @param huart Pointer to the UART handle structure.
  */
void display_invalid_command(UART_HandleTypeDef *huart) {
  HAL_UART_Transmit(huart, (uint8_t *)"Invalid Command\r\n", strlen("Invalid Command\r\n"), HAL_MAX_DELAY);
}

/**
  * @brief Sends an "Invalid Command" message over UART.
  *
  * This function transmits the message "Invalid Command\r\n" via UART.
  *
  * @param huart Pointer to the UART handle structure.
  */
void display_invalid_argument(UART_HandleTypeDef *huart) {
  HAL_UART_Transmit(huart, (uint8_t *)"Invalid Argument\r\n", strlen("Invalid Argument\r\n"), HAL_MAX_DELAY);
}
/**
 * @brief Process the command queue and transmit menu.
 *
 * This function checks if the command queue is not empty. If it's not empty, it dequeues a command,
 * disables the USART1 interrupt, executes the command, enables the USART1 interrupt, resets the flag
 * for invalid command printed, transmits the menu, and updates the previous command.
 * If the command queue is empty, it executes the previous command (if it exists).
 */
void process_command_queue() {
  if(!isEmpty(&command_queue)) {
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    command = dequeue(&command_queue);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    invalid_command_printed = 0;
    execute_command(command);
    prev_cmd = command;
    /* Transmit the menu after command execution */
    display_menu(&huart1);
  }
  else {
    /* if prev_commad was toggle */
    execute_command(prev_cmd);
  }
}

/**
  * @brief  Processes the received commands from the queue and executes them.
  * @param  commandQueue: Pointer to the queue containing the commands to be executed.
  * @retval None
  */
void execute_command(struct led_command_data data) {
  if (strcmp(data.command, "LEDON") == 0) {
    led_on(data.argument);
  } else if (strcmp(data.command, "LEDOFF") == 0) {
    led_off(data.argument);
  } else if (strcmp(data.command, "LEDTOGGLE") == 0) {
    led_toggle(data.argument, data.delay);
  } else {
    if (!isEmpty(&command_queue) && !invalid_command_printed) {
      display_invalid_command(&huart1);
      invalid_command_printed = 1; // Set the flag
    }
  }
}
