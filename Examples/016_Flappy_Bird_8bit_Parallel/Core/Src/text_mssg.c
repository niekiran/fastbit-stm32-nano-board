/*
 * text_mssg.c
 *
 *  Created on: May 2, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "text_mssg.h"
#include "background.h"
#include <stdio.h>
#include <string.h>
#include "font.h"
#include "CST816S.h"

#define BTN_TXT           0xFFFB
#define BUTTON            0x0B85
#define START_BTN_WIDTH   100
#define START_BTN_HEIGHT  40
/**
  * @brief Initializes the game message display.
  * @param None
  * @retval None
  */
void game_init_mssg() {
  const char* game_start_btn = "START";
  display_game_title();

  gc9a01a_fill_rect( 70, 10, 140, 26, BUTTON);
  gc9a01a_fill_rect(160, 10, 140, 26, BUTTON);
  gc9a01a_fill_rect( 70,100, 130, 10, BUTTON);
  gc9a01a_fill_rect( 70,100, 166, 10, BUTTON);
  gc9a01a_write_string(80, 140, (const char*)game_start_btn, Font_16x26, BTN_TXT, BUTTON);
}

/**
  * @brief Displays game over message on the screen.
  * @param None
  * @retval None
  */
void game_over_mssg() {
	const char* game_over_message = "GAME OVER";
	const char* restart_message = "RESTART";

	gc9a01a_write_string(48, 70, (const char*)game_over_message, Font_16x26, RED, BACKGROUND);
  gc9a01a_fill_rect( 54, 10, 140, 26, BUTTON);
  gc9a01a_fill_rect(176, 10, 140, 26, BUTTON);
  gc9a01a_fill_rect( 54,132, 130, 10, BUTTON);
  gc9a01a_fill_rect( 54,132, 166, 10, BUTTON);
	gc9a01a_write_string(64, 140, (const char*)restart_message, Font_16x26, BTN_TXT, BUTTON);
}

/**
  * @brief Renders the countdown before the game starts.
  * @param None
  * @retval None
  */
void render_gamestart_countdown() {
	static uint32_t prestart_time = 0;
	countdown_complete = false;
	prestart_time++;
	if (prestart_time < 50) {
		gc9a01a_write_string(116, 107, (const char*)"3", Font_16x26, BLACK, BACKGROUND);
	} else if(prestart_time > 50 && prestart_time < 100) {
		gc9a01a_write_string(116, 107, (const char*)"2", Font_16x26, BLACK, BACKGROUND);
	} else if(prestart_time > 100 && prestart_time < 150) {
		gc9a01a_write_string(116, 107, (const char*)"1", Font_16x26, BLACK, BACKGROUND);
	} else if(prestart_time > 150) {
		prestart_time = 0;
		fill_countdown_trace();
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

	if(( player->score)<10){
		sprintf(score_str, "00%d", player->score);
		gc9a01a_write_string(96, 0, score_str, Font_16x26, BLACK, SCORE_BOARD);
	} else if( player->score<100){
		sprintf(score_str, "0%d", player->score);
		gc9a01a_write_string(96, 0, score_str, Font_16x26, BLACK, SCORE_BOARD);
	} else if( player->score<1000){
		sprintf(score_str, "%d", player->score);
		gc9a01a_write_string(96, 0, score_str, Font_16x26, BLACK, SCORE_BOARD);
	} else {
		gc9a01a_write_string(96, 0, "WIN", Font_16x26, BLACK, SCORE_BOARD);
	}
}

/**
  * @brief  Checks if the start button is pressed based on touch coordinates.
  * @retval uint8_t: PRESSED if the start button is pressed, otherwise NOT_PRESSED.
  */
uint8_t start_btn_state() {
  struct touch_data data;
  if(CST816S_data_available()) {
    memcpy(&data, CST816S_get_data(), sizeof(struct touch_data));
    if(data.y >= 70 && data.y <= 170) {
      if(data.x >= 130 && data.x <= 176) {
        return PRESSED;
      }
    }
  }
  return NOT_PRESSED;
}

/**
  * @brief  Checks if the restart button is pressed based on touch coordinates.
  * @retval uint8_t: PRESSED if the restart button is pressed, otherwise NOT_PRESSED.
  */
uint8_t restart_btn_state() {
  struct touch_data data;
  if(CST816S_data_available()) {
    memcpy(&data, CST816S_get_data(), sizeof(struct touch_data));
    if(data.y >= 54 && data.y <= 186) {
      if(data.x >= 130 && data.x <= 176) {
        return PRESSED;
      }
    }
  }
  return NOT_PRESSED;
}
