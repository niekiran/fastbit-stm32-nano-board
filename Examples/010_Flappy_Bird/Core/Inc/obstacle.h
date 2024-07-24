/*
 * obstacle.h
 *
 *  Created on: Apr 25, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_OBSTACLE_H_
#define INC_OBSTACLE_H_

#include "main.h"
#include "background.h"

#define BSP_LCD_OBSTACLE_WIDTH		30
#define BSP_LCD_OBSTACLE_HEIGHT		80

void bsp_lcd_set_obstacle(bsp_lcd_t *hlcd);
int generate_obstacle_height(int x_start);
void move_obstacle(bsp_lcd_t *hlcd, int x);
void score_card_background(bsp_lcd_t *hlcd);
uint8_t get_obstacle_speed(int score);

#endif /* INC_OBSTACLE_H_ */
