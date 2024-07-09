/*
 * text_mssg.c
 *
 *  Created on: May 2, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "text_mssg.h"
#include "background.h"
#include <stdio.h>
#include "../../GC9A01A/font.h"

/**
  * @brief Initializes the game message display.
  * @param None
  * @retval None
  */
void game_init_mssg(bsp_lcd_t *hlcd) {
	const char* game_init_message1 = " PRESS USER-BUTTON ";
	const char* game_init_message2 = "TO START ";

	display_game_title(hlcd);
	GC9A01A_WriteString(15, 140, (const char*)game_init_message1, Font_11x18, BLACK, BACKGROUND565);
	GC9A01A_WriteString(55, 170, (const char*)game_init_message2, Font_16x26, WHITE, BACKGROUND565);
}

/**
  * @brief Displays game over message on the screen.
  * @param None
  * @retval None
  */
void game_over_mssg(bsp_lcd_t *hlcd) {
	const char* game_over_message = "GAME OVER";
	const char* restart_message = "PRESS USER-BUTTON TO RESTART";

	GC9A01A_WriteString(48, 70, (const char*)game_over_message, Font_16x26, BLACK, BACKGROUND565);
	fill_gameover_trace(hlcd);
	GC9A01A_WriteString(22, 100, (const char*)restart_message, Font_7x10, RED565, BACKGROUND565);
}

/**
  * @brief Renders the countdown before the game starts.
  * @param None
  * @retval None
  */
void render_gamestart_countdown(bsp_lcd_t *hlcd) {
	static uint32_t prestart_time = 0;
	countdown_complete = false;
	prestart_time++;
	if (prestart_time < 50) {
		GC9A01A_WriteString(116, 107, (const char*)"3", Font_16x26, BLACK, BACKGROUND565);
	} else if(prestart_time > 50 && prestart_time < 100) {
		GC9A01A_WriteString(116, 107, (const char*)"2", Font_16x26, BLACK, BACKGROUND565);
	} else if(prestart_time > 100 && prestart_time < 150) {
		GC9A01A_WriteString(116, 107, (const char*)"1", Font_16x26, BLACK, BACKGROUND565);
	} else if(prestart_time > 150) {
		prestart_time = 0;
		fill_countdown_trace(hlcd);
		countdown_complete = true;
	}
}

/**
  * @brief Displays the player's score on the screen.
  * @param player: Pointer to the Player struct containing player information.
  * @retval None
  */
void player_show_score(Player *player) {
	char score_str[100]="000";

	if(( player->score/12)<10){
		sprintf(score_str, "00%d", player->score/12);
		GC9A01A_WriteString(96, 0, score_str, Font_16x26, BLACK, OBSTACLE565);
	} else if( player->score/12<100){
		sprintf(score_str, "0%d", player->score/12);
		GC9A01A_WriteString(96, 0, score_str, Font_16x26, BLACK, OBSTACLE565);
	} else if( player->score/12<1000){
		sprintf(score_str, "%d", player->score/12);
		GC9A01A_WriteString(96, 0, score_str, Font_16x26, BLACK, OBSTACLE565);
	} else {
		GC9A01A_WriteString(96, 0, "WIN", Font_16x26, BLACK, OBSTACLE565);
	}
}
