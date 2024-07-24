/*
 * bird.c
 *
 *  Created on: Apr 18, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "player.h"
#include "background.h"
#include "main.h"
/**
  * @brief  Move the player on the LCD.
  * @param  y_pos: Starting position of the player.
  * @retval None
  */
void move_player( int y_pos) {
	static int wing_movement=1;
	fill_player_trace();
	if(wing_movement%5==0){
	  gc9a01a_draw_image( player.x, player.w, y_pos, player.h, (uint16_t *)image_data_bird);
	} else {
	  gc9a01a_draw_image( player.x, player.w, y_pos, player.h, (uint16_t *)image_data_bird2);
	}
	wing_movement++;
}


