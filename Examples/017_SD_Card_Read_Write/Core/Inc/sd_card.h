/*
 * sd_card.h
 *
 *  Created on: Jul 11, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef SD_CARD_H_
#define SD_CARD_H_

#include <stdint.h>

enum {
  false, true
};

typedef enum
{
  SD_CARD_INSERTED = 0U,
  SD_CARD_NOT_INSERTED
}SD_status;


/* SD_Card Functions prototypes*/
uint8_t check_sd_card_status(void);
void set_filename(const char *new_filename);
void write_to_sd_card(const char *data, uint16_t length);
void read_sd_card_file(void);
void store_received_data(void);
void display_stored_data(void);
#endif /* SD_CARD_H_ */
