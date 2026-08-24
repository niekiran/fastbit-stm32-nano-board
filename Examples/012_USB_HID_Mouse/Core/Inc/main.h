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

/* Board / IMU sensor selection -----------------------------------------
 * Fastbit STM32 Nano v2.0 carries an MPU6050; v2.1 replaces it with a
 * BMI270. Define exactly one of these to match the board being built for.
 */
#define NANO_BOARD_V2_1
/* #define NANO_BOARD_V2_0 */

#if defined(NANO_BOARD_V2_0) && defined(NANO_BOARD_V2_1)
#error "Define only one of NANO_BOARD_V2_0 / NANO_BOARD_V2_1"
#endif

#if defined(NANO_BOARD_V2_0)
#define IMU_MPU6050
#elif defined(NANO_BOARD_V2_1)
#define IMU_BMI270
#else
#error "Define NANO_BOARD_V2_0 or NANO_BOARD_V2_1 to select the onboard IMU driver"
#endif
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct {
  uint8_t button;
  int8_t mouse_x;
  int8_t mouse_y;
  int8_t wheel;
} mouseHID;

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
extern I2C_HandleTypeDef hi2c1;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEFT_BUTTON_Pin         GPIO_PIN_1
#define LEFT_BUTTON_GPIO_Port   GPIOA
#define RIGHT_BUTTON_Pin        GPIO_PIN_3
#define RIGHT_BUTTON_GPIO_Port  GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
