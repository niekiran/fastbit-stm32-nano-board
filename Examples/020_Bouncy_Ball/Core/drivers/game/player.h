/*
 * player.h
 *
 *  Created on: Mar 13, 2026
 *      Author: Shreyas Acharya, Fastbit Embedded
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "error.h"

typedef struct player_t {
    float    x;
    float    y;
    float    vx;
    float    vy;
    uint16_t radius;
    uint16_t colour;
} player_t;

err_t player_init(player_t *player,
                  float     x,
                  float     y,
                  uint16_t  radius,
                  uint16_t  colour);

err_t player_update(player_t *player,
                    float     tilt_x,
                    float     tilt_y,
                    float     dt_s);

err_t player_bounce_in_round_world(player_t *player,
                                   float     cx,
                                   float     cy,
                                   float     world_radius);

#endif /* PLAYER_H */
