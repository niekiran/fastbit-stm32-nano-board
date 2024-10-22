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

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_TE_Pin 				GPIO_PIN_1
#define LCD_TE_GPIO_Port 		GPIOA
#define LCD_CSX_Pin 			GPIO_PIN_3
#define LCD_CSX_GPIO_Port 		GPIOA
#define BL_A_Pin 				GPIO_PIN_4
#define BL_A_GPIO_Port 			GPIOA
#define LCD_RDX_Pin 			GPIO_PIN_0
#define LCD_RDX_GPIO_Port 		GPIOB
#define DCX_Pin 				GPIO_PIN_1
#define DCX_GPIO_Port 			GPIOB
#define BD7_Pin 				GPIO_PIN_10
#define BD7_GPIO_Port 			GPIOB
#define BD6_Pin 				GPIO_PIN_11
#define BD6_GPIO_Port 			GPIOB
#define BD5_Pin 				GPIO_PIN_12
#define BD5_GPIO_Port 			GPIOB
#define BD4_Pin 				GPIO_PIN_13
#define BD4_GPIO_Port 			GPIOB
#define BD3_Pin 				GPIO_PIN_14
#define BD3_GPIO_Port 			GPIOB
#define BD2_Pin 				GPIO_PIN_15
#define BD2_GPIO_Port 			GPIOB
#define BD1_Pin 				GPIO_PIN_9
#define BD1_GPIO_Port 			GPIOA
#define BD0_Pin 				GPIO_PIN_10
#define BD0_GPIO_Port 			GPIOA
#define WRD_Pin 				GPIO_PIN_15
#define WRD_GPIO_Port 			GPIOA
#define TP_RST_Pin 				GPIO_PIN_4
#define TP_RST_GPIO_Port 		GPIOB
#define TP_IN_Pin 				GPIO_PIN_5
#define TP_IN_GPIO_Port 		GPIOB
#define TP_IN_EXTI_IRQn 		EXTI9_5_IRQn
#define TP_SCL_Pin 				GPIO_PIN_6
#define TP_SCL_GPIO_Port 		GPIOB
#define TP_SDA_Pin 				GPIO_PIN_7
#define TP_SDA_GPIO_Port 		GPIOB
#define LCD_RST_Pin 			GPIO_PIN_8
#define LCD_RST_GPIO_Port 		GPIOB

/* USER CODE BEGIN Private defines */
extern I2C_HandleTypeDef hi2c1;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
