/*
 * spi.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "main.h"
#include "spi.h"
#include <stdio.h>
#include <stdint.h>

extern SPI_HandleTypeDef hspi1;

/**
  * @brief  Transmit and receive data over SPI.
  * @param  tx_buffer: Pointer to the transmit buffer.
  * @param  rx_buffer: Pointer to the receive buffer.
  * @param  tx_size: Size of the transmit buffer.
  * @retval None
  */
void spi_transmit_receive(uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t tx_size) {
  /* Assuming the size of the received buffer is the same as the transmit buffer */
  uint8_t rx_size = tx_size;
  if (tx_size > 0) {
    HAL_SPI_TransmitReceive(&hspi1, tx_buffer, rx_buffer, tx_size, HAL_MAX_DELAY);
  }
  /* Print received data in the SWV terminal */
  printf("Received data: ");
  for (int i = 0; i < rx_size; i++) {
    printf("%02X ", rx_buffer[i]);
  }
  printf("\n");
}
