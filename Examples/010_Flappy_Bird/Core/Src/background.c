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
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void bsp_lcd_set_background(bsp_lcd_t *hlcd) {
	bsp_lcd_fill_rect(hlcd, BACKGROUND,0,(BSP_LCD_BACKGROUND_WIDTH),0,(BSP_LCD_BACKGROUND_HEIGHT));
}

/**
  * @brief  Fill the player trace area with the background color.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void fill_player_trace(bsp_lcd_t *hlcd){
	bsp_lcd_fill_rect(hlcd, BACKGROUND , player.x, player.w, 30, 180);
}

/**
  * @brief  Display bush images on the LCD.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void display_bush(bsp_lcd_t *hlcd) {
	bsp_lcd_fill_image(hlcd, (uint16_t *)bush, 0, 60, 210, 30);
	bsp_lcd_fill_image(hlcd, (uint16_t *)bush, 60, 60, 210, 30);
	bsp_lcd_fill_image(hlcd, (uint16_t *)bush, 120, 60, 210, 30);
	bsp_lcd_fill_image(hlcd, (uint16_t *)bush, 180, 60, 210, 30);
}

/**
  * @brief  Set the background and display bush images for the Flappy Bird game.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void flappy_game_set_back_ground(bsp_lcd_t *hlcd) {
	bsp_lcd_set_background(hlcd);
  display_bush(hlcd);
}

/**
  * @brief  Fill the countdown trace area with the background color.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void fill_countdown_trace(bsp_lcd_t *hlcd) {
	bsp_lcd_fill_rect(hlcd, BACKGROUND,0,240,107,26);
	bsp_lcd_fill_rect(hlcd, BACKGROUND,116,16,140,26);
}

/**
  * @brief  Fill the game over trace area with the background color.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void set_gameover_background(bsp_lcd_t *hlcd) {
	bsp_lcd_fill_rect(hlcd, BACKGROUND , 0, 240, 30, 180);
}

/**
  * @brief  Display the game title on the LCD.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void display_game_title(bsp_lcd_t *hlcd) {
	bsp_lcd_fill_image(hlcd, (uint16_t *)Flappy_font1, 20, 200, 30, 40);
	bsp_lcd_fill_image(hlcd, (uint16_t *)Flappy_font2, 20, 200, 70, 39);
}
