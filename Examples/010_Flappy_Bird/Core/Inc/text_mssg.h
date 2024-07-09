/*
 * text_mssg.h
 *
 *  Created on: May 2, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_TEXT_MSSG_H_
#define INC_TEXT_MSSG_H_

#include "main.h"
#include "../../GC9A01A/GC9A01A.h"

void game_init_mssg(bsp_lcd_t *hlcd);
void game_over_mssg(bsp_lcd_t *hlcd);
void render_gamestart_countdown(bsp_lcd_t *hlcd);
void player_show_score(Player *player);

#endif /* INC_TEXT_MSSG_H_ */
