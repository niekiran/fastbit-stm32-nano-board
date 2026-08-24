/*
 * world.h
 *
 *  Created on: Mar 13, 2026
 *      Author: Shreyas Acharya, Fastbit Embedded
 */

#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>

typedef struct {
    uint16_t width;
    uint16_t height;
    float    center_x;
    float    center_y;
    float    radius;
    uint16_t background_colour;
} world_t;

void world_init(world_t *world,
                uint16_t width,
                uint16_t height,
                uint16_t background_colour);

#endif /* WORLD_H */
