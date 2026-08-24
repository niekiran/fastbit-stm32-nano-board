/*
 * app.c
 *
 *  Created on: Mar 13, 2026
 *      Author: bhara
 */


#include "app.h"
#include "game.h"
#include "stm32f3xx_hal.h"

#define APP_FRAME_TIME_MS   16U

err_t app_init(void)
{
    return game_init();
}

void app_run(void)
{
    uint32_t last_tick;
    uint32_t now_tick;
    float dt_s;

    last_tick = HAL_GetTick();

    while (1) {
        now_tick = HAL_GetTick();
        dt_s = (float)(now_tick - last_tick) / 1000.0f;
        last_tick = now_tick;

        if (game_update(dt_s) == ERR_OK) {
            (void)game_render();
        }

        HAL_Delay(APP_FRAME_TIME_MS);
    }
}
