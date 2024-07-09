/*
 * bird.c
 *
 *  Created on: Apr 18, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "player.h"
#include "background.h"

/**
  * @brief  Move the player on the LCD.
  * @param  hlcd: Pointer to LCD handle.
  * @param  y_pos: Starting position of the player.
  * @retval None
  */
void move_player(bsp_lcd_t *hlcd,  int y_pos) {
	static int wing_movement=1;
	fill_player_trace(hlcd);
	if(wing_movement%5==0){
		bsp_lcd_fill_image(hlcd, (uint16_t *)image_data_bird, PLAYER_xSTART, PLAYER_WIDTH, y_pos, PLAYER_HEIGHT);
	} else {
		bsp_lcd_fill_image(hlcd, (uint16_t *)image_data_bird2, PLAYER_xSTART, PLAYER_WIDTH, y_pos, PLAYER_HEIGHT);
	}
	wing_movement++;
}


