/*
 * app.c
 *
 *  Created on: Mar 14, 2026
 *      Author: Shreyas Acharya, Fastbit Embedded
 */

#include "app.h"
#include "stm32f3xx_hal.h"

#define BLUE_LED_PIN         GPIO_PIN_1
#define GREEN_LED_PIN        GPIO_PIN_2
#define LED_GPIO_PORT        GPIOA

#define LED_BLINK_PERIOD_MS  1000U

err_t app_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin   = BLUE_LED_PIN | GREEN_LED_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_GPIO_PORT, BLUE_LED_PIN | GREEN_LED_PIN, GPIO_PIN_RESET);

    return ERR_OK;
}

void app_run(void)
{
    uint32_t last_blink = HAL_GetTick();

    while (1) {
        uint32_t now = HAL_GetTick();
        if ((now - last_blink) >= LED_BLINK_PERIOD_MS) {
            HAL_GPIO_TogglePin(LED_GPIO_PORT, BLUE_LED_PIN | GREEN_LED_PIN);
            last_blink = now;
        }
    }
}
