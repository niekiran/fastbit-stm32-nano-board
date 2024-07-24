/*
 * obstacle.c
 *
 *  Created on: Apr 25, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "obstacle.h"
#include "background.h"
#include <stdlib.h>
#include "main.h"

/**
  * @brief  Generate the height of the obstacle.
  * @param  x_start: Starting position of the obstacle.
  * @retval The height of the obstacle.
  */
int generate_obstacle_height(int x_start) {
	static int top_obstacle_height = -1; // Initialize with -1 to indicate it's not set yet
	// Generate random top_obstacle_height if it's not set yet or x_start is 210
	if (top_obstacle_height == -1 || x_start == 240) {
		top_obstacle_height = rand() % (90 - 20 + 1) + 20;
	}
	return top_obstacle_height;
}

/**
  * @brief  Display the obstacle on the LCD.
  * @param  hlcd: Pointer to LCD handle.
  * @param  x_start: Starting position of the obstacle.
  * @retval None
  */
void display_obstacle(bsp_lcd_t *hlcd, int x_start) {
	score_card_background(hlcd);
	
	obstacle.h = generate_obstacle_height(x_start);
	int bottom_obstacle_ystart = obstacle.h + obstacle.y + obstacle.g;
	int bottom_obstacle_height = OBSTACLE_yEND_POINT - bottom_obstacle_ystart;

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_1,x_start,3, obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_1,x_start,3,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_1,x_start,obstacle.w,( obstacle.h+obstacle.y-2),2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_1,x_start,obstacle.w,bottom_obstacle_ystart,2);

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_2,x_start+3,2,obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_2,x_start+3,2,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_3,x_start+5,2,obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_3,x_start+5,2,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	bsp_lcd_fill_rect(hlcd, WHITE, x_start+7,10,obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, WHITE, x_start+7,10,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_3,x_start+17,3,obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_3,x_start+17,3,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_2,x_start+20,3,obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_2,x_start+20,3,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_1,x_start+23,7,obstacle.y, obstacle.h-2);
	bsp_lcd_fill_rect(hlcd, OBSTACLE_SHADE_1,x_start+23,7,(bottom_obstacle_ystart+2),(bottom_obstacle_height-2));

	/* filling traces of obstacle */
	bsp_lcd_fill_rect(hlcd, BACKGROUND,(x_start+30), obstacle.speed, obstacle.y,  obstacle.h);
	bsp_lcd_fill_rect(hlcd, BACKGROUND,(x_start+30), obstacle.speed, bottom_obstacle_ystart, bottom_obstacle_height);
}

/**
  * @brief  Move the obstacle on the LCD.
  * @param  hlcd: Pointer to LCD handle.
  * @param  x: Position to move the obstacle to.
  * @retval None
  */
void move_obstacle(bsp_lcd_t *hlcd, int x) {
	display_obstacle(hlcd, x);
	display_bush(hlcd);
}

/**
  * @brief  Draw the background for the score card on the LCD.
  * @param  hlcd: Pointer to LCD handle.
  * @retval None
  */
void score_card_background(bsp_lcd_t *hlcd) {
	bsp_lcd_fill_rect(hlcd, SCORE_BOARD_SHADE_3, 0, 96,0,26);
	bsp_lcd_fill_rect(hlcd, SCORE_BOARD_SHADE_3, 144, 96,0,26);
	bsp_lcd_fill_rect(hlcd, SCORE_BOARD_SHADE_2, 0, 240,26,2);
	bsp_lcd_fill_rect(hlcd, SCORE_BOARD_SHADE_1, 0, 240,28,2);
}

/**
  * @brief  Calculates the speed of obstacles based on the player's score.
  * @param  score: The player's score.
  * @retval uint8_t: The calculated obstacle speed.
  */
uint8_t get_obstacle_speed(int score) {
  int base_speed = 5;
  float speed_increment = 1.6;
  return base_speed * speed_increment;
}
