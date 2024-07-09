/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern SPI_HandleTypeDef hspi1;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define false 0
#define true 1
extern int countdown_complete;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
typedef struct player {
	int x;
	int y;
  int score;
}Player;

typedef struct obstacle {
  int x;
	int y;
}Obstacle;

typedef enum {
	GAME_INIT,
	GAME_PRESTART,
	GAME_START,
	GAME_OVER
}GamteState;

extern GamteState game_state ;
extern Player player;
extern Obstacle obstacle;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_RESET_Pin 					GPIO_PIN_3
#define LCD_RESET_GPIO_Port 		GPIOA
#define LCD_CS_Pin 							GPIO_PIN_4
#define LCD_CS_GPIO_Port 				GPIOA
#define LCD_RS_A0_Pin 					GPIO_PIN_6
#define LCD_RS_A0_GPIO_Port 		GPIOA

/* USER CODE BEGIN Private defines */
#define RGB888(r,g,b) 					(((r) << 16) | ((g) << 8) | (b))

#define VIOLET   								RGB888(148,0,211)
#define INDIGO   								RGB888(75,0,130)
#define BLUE   									RGB888(0,0,255)
#define GREEN   								RGB888(0,255,0)
#define YELLOW   								RGB888(255,255,0)
#define ORANGE   								RGB888(255,127,0)
#define RED   									RGB888(255,0,0)
#define WHITE   								RGB888(255,255,255)
#define BLACK										RGB888(0,0,0)
#define BACKGROUND   						RGB888(154,232,246)
#define BROWN   								RGB888(71,11,11)
#define BROWN565								0x4041
#define BACKGROUND565						0x9F5E
#define RED565									0xF841
#define SCORE_BOARD_SHADE_1		  RGB888(114,113,113)
#define SCORE_BOARD_SHADE_2			RGB888(150,149,149)
#define SCORE_BOARD_SHADE_3			RGB888(228,224,224)

#define OBSTACLE_SHADE_1        RGB888(81,121,0)
#define OBSTACLE_SHADE_2        RGB888(120,178,1)
#define OBSTACLE_SHADE_3        RGB888(152,225,0)
#define OBSTACLE_SHADE_4        RGB888(216,255,135)
#define OBSTACLE565							0xE71C

#define OBSTACLE_WIDTH  				30
#define OBSTACLE_HEIGHT					40
#define OBSTACLE_GAP						80
#define OBSTACLE_ySTART_POINT		30
#define OBSTACLE_yEND_POINT			210

#define PLAYER_xSTART						70
#define PLAYER_ySTART_POINT			30
#define PLAYER_yEND_POINT				180
#define PLAYER_WIDTH    				30
#define PLAYER_HEIGHT   				30

#define GRAVITY_PULL						2

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
