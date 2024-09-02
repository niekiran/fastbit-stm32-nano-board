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
void printmsg(char *format,...);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SD_CS_Pin GPIO_PIN_13
#define SD_CS_GPIO_Port GPIOC
#define User_btn_Pin GPIO_PIN_0
#define User_btn_GPIO_Port GPIOA
#define User_btn_EXTI_IRQn EXTI0_IRQn
#define SD_SCL_Pin GPIO_PIN_5
#define SD_SCL_GPIO_Port GPIOA
#define SD_MISO_Pin GPIO_PIN_6
#define SD_MISO_GPIO_Port GPIOA
#define SD_MOSI_Pin GPIO_PIN_7
#define SD_MOSI_GPIO_Port GPIOA
#define SD_DET_Pin GPIO_PIN_9
#define SD_DET_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern uint8_t data_received;
extern uint8_t button_press;
#define RX_BUF_SIZE     100
extern uint8_t uart_rx_buff1[RX_BUF_SIZE];
extern uint8_t uart_rx_buff2[RX_BUF_SIZE];
extern uint8_t *current_rx_buff;
extern uint8_t *processing_buff;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
