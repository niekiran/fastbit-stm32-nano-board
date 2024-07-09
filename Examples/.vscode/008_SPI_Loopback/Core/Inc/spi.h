/*
 * spi.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include <stdint.h>

/* Function prototype */
void spi_transmit_receive(uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t tx_size);

#endif /* INC_SPI_H_ */
