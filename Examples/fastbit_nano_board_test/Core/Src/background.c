/*
 * background.c
 *
 *  Created on: Apr 25, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "background.h"
#include "main.h"

/**
  * @brief  Set the background color on the LCD.
  * @retval None
  */
void bsp_lcd_set_background() {
	gc9a01a_fill_rect(0,(BSP_LCD_BACKGROUND_WIDTH),0,(BSP_LCD_BACKGROUND_HEIGHT), BACKGROUND);
}

/**
  * @brief  Fill the player trace area with the background color.
  * @retval None
  */
void fill_player_trace(){
  if( obstacle.x >= (player.x + player.w) || obstacle.x + 30 <= player.x) {
    gc9a01a_fill_rect(player.x, player.w, 30, 180, BACKGROUND);
  } else if( obstacle.x <= (player.x + player.w) || obstacle.x + 30 >= player.x) {
    gc9a01a_fill_rect(player.x, player.w, (obstacle.y + obstacle.h),  obstacle.g, BACKGROUND);
  }
}

/**
  * @brief  Display bush images on the LCD.
  * @retval None
  */
void display_bush() {
  gc9a01a_draw_image(0, 60, 210, 30, (uint16_t *)bush);
  gc9a01a_draw_image(60,60, 210, 30, (uint16_t *)bush);
  gc9a01a_draw_image(120, 60, 210, 30, (uint16_t *)bush);
  gc9a01a_draw_image(180, 60, 210, 30, (uint16_t *)bush);
}

/**
  * @brief  Set the background and display bush images for the Flappy Bird game.
  * @retval None
  */
void flappy_game_set_back_ground() {
	bsp_lcd_set_background();
  display_bush();
}

/**
  * @brief  Fill the countdown trace area with the background color.
  * @retval None
  */
void fill_countdown_trace() {
  gc9a01a_fill_rect(0,240,107,26, BACKGROUND);
  gc9a01a_fill_rect(116,16,140,26, BACKGROUND);
}

/**
  * @brief  Fill the game over trace area with the background color.
  * @retval None
  */
void set_gameover_background() {
  gc9a01a_fill_rect(0, 240, 30, 180, BACKGROUND);
}

/**
  * @brief  Display the game title on the LCD.
  * @retval None
  */
void display_game_title() {
  gc9a01a_draw_image(20, 200, 30, 40, (uint16_t *)Flappy_font1);
  gc9a01a_draw_image(20, 200, 70, 39, (uint16_t *)Flappy_font2);
}
