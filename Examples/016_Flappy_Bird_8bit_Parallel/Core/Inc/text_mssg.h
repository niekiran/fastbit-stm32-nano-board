/*
 * text_mssg.h
 *
 *  Created on: May 2, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_TEXT_MSSG_H_
#define INC_TEXT_MSSG_H_

#include "main.h"
#include "GC9A01A.h"

typedef enum {
  NOT_PRESSED,
  PRESSED
} button_state_t;

void game_init_mssg();
void game_over_mssg();
void render_gamestart_countdown();
void player_show_score(Player *player);
uint8_t start_btn_state();
uint8_t restart_btn_state();

#endif /* INC_TEXT_MSSG_H_ */
