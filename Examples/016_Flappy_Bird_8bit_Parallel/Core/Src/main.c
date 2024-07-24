/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "mpu6050.h"
#include "player.h"
#include "background.h"
#include "obstacle.h"
#include "text_mssg.h"
#include "font.h"
#include "GC9A01A.h"
#include "CST816S.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
double degreex, degreey;
int collision_detected = false;
int countdown_complete = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void is_Collide(Obstacle *obstacle, Player *player);
void nano_lcd_Init(void);
void tick();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
GamteState game_state ;
Player player;
Obstacle obstacle;

static void Player_ctor(Player* player, int player_x, int player_w, int player_y, int player_h) {
	player->x = player_x;
	player->w = player_w;
	player->y = player_y;
	player->h = player_h;
	player->score = 0;
}

static void Obstacle_ctor(Obstacle* obstacle, int obstacle_x, int obstacle_w, int obstacle_y, int obstacle_g,
                            int obstacle_s) {
	obstacle->x = obstacle_x;
	obstacle->w = obstacle_w;
	obstacle->y = obstacle_y;
	obstacle->h = 0;
	obstacle->g = obstacle_g;
	obstacle->speed  = obstacle_s;
	obstacle->passed = false;
}
/* USER CODE END 0 */
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	static uint32_t current_time;
	current_time = HAL_GetTick();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  Player_ctor(&player, 70, 30, 100, 30);
  Obstacle_ctor(&obstacle, 240, 30, 30, 80, 5);
  mpu6050_Init();
  bsp_lcd_init();
  CST816S_init();
  flappy_game_set_back_ground();

  double prev_degreey = degreey; // Initialize previous angle variable
  static double angle_delta = 0.0; // Variable to store the angle change
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  	mpu6050_read();

    if(HAL_GetTick() - current_time >= 2) {

      current_time = HAL_GetTick();

      angle_delta = degreey - prev_degreey;
      prev_degreey = degreey;
      double smoothing_factor = 6;

      player.y -= smoothing_factor * angle_delta;
      player.y += GRAVITY_PULL;

      if (player.y <= PLAYER_ySTART_POINT) {
        player.y = PLAYER_ySTART_POINT;
      } else if (player.y >= PLAYER_yEND_POINT) {
        player.y = PLAYER_yEND_POINT;
      }
      tick();
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_TE_Pin|LCD_CSX_Pin|BL_A_Pin|BD1_Pin
                          |BD0_Pin|WRD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_RDX_Pin|DCX_Pin|BD7_Pin|BD6_Pin
                          |BD5_Pin|BD4_Pin|BD3_Pin|BD2_Pin
                          |TP_RST_Pin|LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_TE_Pin LCD_CSX_Pin BL_A_Pin BD1_Pin
                           BD0_Pin WRD_Pin */
  GPIO_InitStruct.Pin = LCD_TE_Pin|LCD_CSX_Pin|BL_A_Pin|BD1_Pin
                          |BD0_Pin|WRD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RDX_Pin DCX_Pin BD7_Pin BD6_Pin
                           BD5_Pin BD4_Pin BD3_Pin BD2_Pin
                           TP_RST_Pin LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RDX_Pin|DCX_Pin|BD7_Pin|BD6_Pin
                          |BD5_Pin|BD4_Pin|BD3_Pin|BD2_Pin
                          |TP_RST_Pin|LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_IN_Pin */
  GPIO_InitStruct.Pin = TP_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TP_IN_GPIO_Port, &GPIO_InitStruct);

  /**/
  HAL_I2CEx_EnableFastModePlus(SYSCFG_CFGR1_I2C_PB8_FMP);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
  * @brief Updates the game state based on events and conditions.
  * @param None
  * @retval None
  */
void tick() {
	switch (game_state) {
		case GAME_INIT: {
		  uint8_t start_btn =  start_btn_state();
			game_init_mssg();

			if (start_btn == PRESSED) {
				flappy_game_set_back_ground();
				game_state = GAME_PRESTART;
			}
		}
		break;

		case GAME_PRESTART: {
			move_player(player.y);
			render_gamestart_countdown();
			if(countdown_complete == true) {
				game_state = GAME_START;
			}
		}
		break;

		case GAME_START: {
			is_Collide(&obstacle, &player);
			if(collision_detected == true) {
			  set_gameover_background();
				game_state = GAME_OVER;
			} else {
			  obstacle.speed = get_obstacle_speed(player.score);
			  obstacle.x -= obstacle.speed;

			  move_player( player.y);
				if(obstacle.x >= 0) {
					move_obstacle(obstacle.x);
				} else {
				  gc9a01a_fill_rect(0, 40, 0, 240,BACKGROUND);
					obstacle.x = 240;
				}
				player_show_score(&player);
			}
		}
		break;

		case GAME_OVER: {
			collision_detected = false;
			game_over_mssg();
			uint8_t restart_btn =  restart_btn_state();
			if (restart_btn == PRESSED) {
			  Player_ctor(&player, 70, 30, 100, 30);
				Obstacle_ctor(&obstacle, 240, 30, 30, 80, 5);
				flappy_game_set_back_ground();
				game_state = GAME_PRESTART;
			}
		}
		break;
	}
}

/**
  * @brief Checks for collision between an obstacle and the player.
  * @param obstacle: Pointer to the Obstacle struct containing obstacle information.
  * @param player: Pointer to the Player struct containing player information.
  * @retval None
  */
void is_Collide(Obstacle *obstacle, Player *player) {
	int player_left = player->x;
	int player_right = player->x + player->w -5;
	int player_top = player->y;
	int player_bottom = player->y + player->h-5;

	int obstacle_left = obstacle->x;
	int obstacle_right = obstacle->x + obstacle->w;

	obstacle->h = generate_obstacle_height(obstacle->x);
	int obstacle_bottom = OBSTACLE_ySTART_POINT + obstacle->h -5;

	if (player_right  >= obstacle_left && player_left <= obstacle_right ){
		if( (player_top  < obstacle_bottom) || (player_bottom > (obstacle_bottom + obstacle->g +10))) {
			collision_detected = true;
		} else if (!obstacle->passed) {  // Only update score if the obstacle hasn't been passed
      player->score += 1;
      obstacle->passed = true;  // Mark the obstacle as passed
    }
	} else {
    obstacle->passed = false;   // Reset the flag when the player is not near the obstacle
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
