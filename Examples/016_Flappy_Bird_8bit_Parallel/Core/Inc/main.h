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
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
	int w;
	int y;
	int h;
  int score;
}Player;

typedef struct obstacle {
  int x;
  int w;
	int y;
	int h;
	int g;
	int speed;
	bool passed;
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
#define LCD_TE_Pin              GPIO_PIN_1
#define LCD_TE_GPIO_Port        GPIOA
#define LCD_CSX_Pin             GPIO_PIN_3
#define LCD_CSX_GPIO_Port       GPIOA
#define BL_A_Pin                GPIO_PIN_4
#define BL_A_GPIO_Port          GPIOA
#define LCD_RDX_Pin             GPIO_PIN_0
#define LCD_RDX_GPIO_Port       GPIOB
#define DCX_Pin                 GPIO_PIN_1
#define DCX_GPIO_Port           GPIOB
#define BD7_Pin                 GPIO_PIN_10
#define BD7_GPIO_Port           GPIOB
#define BD6_Pin                 GPIO_PIN_11
#define BD6_GPIO_Port           GPIOB
#define BD5_Pin                 GPIO_PIN_12
#define BD5_GPIO_Port           GPIOB
#define BD4_Pin                 GPIO_PIN_13
#define BD4_GPIO_Port           GPIOB
#define BD3_Pin                 GPIO_PIN_14
#define BD3_GPIO_Port           GPIOB
#define BD2_Pin                 GPIO_PIN_15
#define BD2_GPIO_Port           GPIOB
#define BD1_Pin                 GPIO_PIN_9
#define BD1_GPIO_Port           GPIOA
#define BD0_Pin                 GPIO_PIN_10
#define BD0_GPIO_Port           GPIOA
#define WRD_Pin                 GPIO_PIN_15
#define WRD_GPIO_Port           GPIOA
#define TP_RST_Pin              GPIO_PIN_4
#define TP_RST_GPIO_Port        GPIOB
#define TP_IN_Pin               GPIO_PIN_5
#define TP_IN_GPIO_Port         GPIOB
#define TP_IN_EXTI_IRQn         EXTI9_5_IRQn
#define TP_SCL_Pin              GPIO_PIN_6
#define TP_SCL_GPIO_Port        GPIOB
#define TP_SDA_Pin              GPIO_PIN_7
#define TP_SDA_GPIO_Port        GPIOB
#define LCD_RST_Pin             GPIO_PIN_8
#define LCD_RST_GPIO_Port       GPIOB

/* USER CODE BEGIN Private defines */
#define BACKGROUND              0x9F5E // RGB888(154,232,246)

#define SCORE_BOARD_SHADE_1     0x738E // RGB888(114,113,113)
#define SCORE_BOARD_SHADE_2     0x94B2 // RGB888(150,149,149)
#define SCORE_BOARD_SHADE_3     0xE71C // RGB888(228,224,224)

#define OBSTACLE_SHADE_1        0x53C0 // RGB888(81,121,0)
#define OBSTACLE_SHADE_2        0x7D80 // RGB888(120,178,1)
#define OBSTACLE_SHADE_3        0x9F00 // RGB888(152,225,0)
#define OBSTACLE_SHADE_4        0xDFF0 // RGB888(216,255,135)

#define SCORE_BOARD							0xE71C

#define OBSTACLE_ySTART_POINT		30
#define OBSTACLE_yEND_POINT			210

#define PLAYER_ySTART_POINT			30
#define PLAYER_yEND_POINT				180

#define GRAVITY_PULL						2

extern I2C_HandleTypeDef hi2c1;
extern double degreex, degreey;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
