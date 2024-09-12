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

#include "../../GC9A01A/font.h"
#include "../../GC9A01A/GC9A01A.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define DB_SIZE 					(15UL * 1024UL)

uint8_t bsp_db[DB_SIZE];
uint8_t bsp_wb[DB_SIZE];

bsp_lcd_t lcd_handle;
bsp_lcd_t *hlcd = &lcd_handle;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
double degreex, degreey;
int collision_detected = false;
int countdown_complete = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
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
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  Player_ctor(&player, 70, 30, 100, 30);
  Obstacle_ctor(&obstacle, 240, 30, 30, 80, 5);
  mpu6050_init();
  nano_lcd_Init();

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

		if(HAL_GetTick() - current_time >= 5) {
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
  hi2c1.Init.Timing = 0x00000001;
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

  /** I2C Fast mode Plus enable
  */
  __HAL_SYSCFG_FASTMODEPLUS_ENABLE(I2C_FASTMODEPLUS_I2C1);
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, LCD_RESET_Pin|LCD_CS_Pin|LCD_RS_A0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RESET_Pin LCD_CS_Pin LCD_RS_A0_Pin */
  GPIO_InitStruct.Pin = LCD_RESET_Pin|LCD_CS_Pin|LCD_RS_A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
  * @brief Initializes the Nano LCD display.
  * @param None
  * @retval None
  */
void nano_lcd_Init(void) {
	gc9a01a_hw_reset();
	gc9a01a_config2();
	lcd_area_t area;
	area.x1 = 0;
	area.x2 = 240;
	area.y1 = 0;
	area.y2 = 240;
	gc9a01a_set_display_area(&area);
	gc9a01a_set_orientation(LANDSCAPE);

	hlcd->draw_buffer1 = bsp_db;
	hlcd->draw_buffer2 = bsp_wb;
	hlcd->buff_to_draw = NULL;
	hlcd->buff_to_flush = NULL;
	hlcd->db_size = DB_SIZE;

	flappy_game_set_back_ground(hlcd);
}

/**
  * @brief Updates the game state based on events and conditions.
  * @param None
  * @retval None
  */
void tick() {
	switch (game_state) {
		case GAME_INIT: {
			GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
			game_init_mssg(hlcd);

			if (pinState == GPIO_PIN_SET) {
				HAL_Delay(25);
				flappy_game_set_back_ground(hlcd);
				game_state = GAME_PRESTART;
			}
		}
		break;

		case GAME_PRESTART: {
			move_player(hlcd, player.y);
			render_gamestart_countdown(hlcd);
			if(countdown_complete == true) {
				game_state = GAME_START;
			}
		}
		break;

		case GAME_START: {
			is_Collide(&obstacle, &player);
			if(collision_detected == true) {
				set_gameover_background(hlcd);
				game_state = GAME_OVER;
			} else {
				obstacle.speed = get_obstacle_speed(player.score);
				obstacle.x -= obstacle.speed;
				move_player(hlcd, player.y);

				if(obstacle.x >= 0) {
					move_obstacle(hlcd,obstacle.x);
				}else{
					bsp_lcd_fill_rect(hlcd, BACKGROUND , 0, 40, 0, 240);
					obstacle.x = 240;
				}
				player_show_score(&player);
			}
		}
		break;

		case GAME_OVER: {
			collision_detected = false;
			game_over_mssg(hlcd);
			GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
			if (pinState == GPIO_PIN_SET) {
				Player_ctor(&player, 70, 30, 100, 30);
				Obstacle_ctor(&obstacle, 240, 30, 30, 80, 5);
				flappy_game_set_back_ground(hlcd);
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
	int player_right = player->x + player->w  -5;
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
