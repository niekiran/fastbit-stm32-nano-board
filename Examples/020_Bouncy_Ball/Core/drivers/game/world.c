/*
 * world.c
 *
 *  Created on: Mar 13, 2026
 *      Author: Shreyas Acharya, Fastbit Embedded
 */

#include "world.h"

void world_init(world_t *world,
                uint16_t width,
                uint16_t height,
                uint16_t background_colour)
{
    if (world == 0) {
        return;
    }

    world->width = width;
    world->height = height;
    world->center_x = (float)width / 2.0f;
    world->center_y = (float)height / 2.0f;
    world->radius = ((float)width / 2.0f) - 2.0f;
    world->background_colour = background_colour;
}
