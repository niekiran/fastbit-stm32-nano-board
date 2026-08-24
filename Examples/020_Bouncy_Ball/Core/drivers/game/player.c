/*
 * player.c
 *
 *  Created on: Mar 13, 2026
 *      Author: Shreyas Acharya, Fastbit Embedded
 */


#include "player.h"
#include <math.h>

#define PLAYER_ACCEL_GAIN      150.0f
#define PLAYER_FRICTION        0.99f
#define PLAYER_BOUNCE_FACTOR   0.85f
#define PLAYER_MAX_SPEED       230.0f

static float clampf(float value, float min_val, float max_val)
{
    if (value < min_val) {
        return min_val;
    }
    if (value > max_val) {
        return max_val;
    }
    return value;
}

err_t player_init(player_t *player,
                  float     x,
                  float     y,
                  uint16_t  radius,
                  uint16_t  colour)
{
    if (player == 0) {
        return ERR_INVALID_PARAM;
    }

    player->x = x;
    player->y = y;
    player->vx = 0.0f;
    player->vy = 0.0f;
    player->radius = radius;
    player->colour = colour;

    return ERR_OK;
}

err_t player_update(player_t *player,
                    float     tilt_x,
                    float     tilt_y,
                    float     dt_s)
{
    if (player == 0) {
        return ERR_INVALID_PARAM;
    }

    player->vx += tilt_x * PLAYER_ACCEL_GAIN * dt_s;
    player->vy += tilt_y * PLAYER_ACCEL_GAIN * dt_s;

    player->vx *= PLAYER_FRICTION;
    player->vy *= PLAYER_FRICTION;

    player->vx = clampf(player->vx, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);
    player->vy = clampf(player->vy, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);

    player->x += player->vx * dt_s;
    player->y += player->vy * dt_s;

    return ERR_OK;
}

err_t player_bounce_in_round_world(player_t *player,
                                   float     cx,
                                   float     cy,
                                   float     world_radius)
{
    float dx;
    float dy;
    float distance;
    float limit;
    float nx;
    float ny;
    float dot;

    if (player == 0) {
        return ERR_INVALID_PARAM;
    }

    dx = player->x - cx;
    dy = player->y - cy;
    distance = sqrtf((dx * dx) + (dy * dy));
    limit = world_radius - (float)player->radius;

    if (distance > limit && distance > 0.0f) {
        nx = dx / distance;
        ny = dy / distance;

        player->x = cx + (nx * limit);
        player->y = cy + (ny * limit);

        dot = (player->vx * nx) + (player->vy * ny);

        if (dot > 0.0f) {
            player->vx = player->vx - (2.0f * dot * nx);
            player->vy = player->vy - (2.0f * dot * ny);

            player->vx *= PLAYER_BOUNCE_FACTOR;
            player->vy *= PLAYER_BOUNCE_FACTOR;
        }
    }

    return ERR_OK;
}
