/*
 * game.h
 *
 *  Created on: Mar 13, 2026
 *      Author: bhara
 */

#ifndef GAME_H
#define GAME_H

#include "error.h"

err_t game_init(void);
err_t game_update(float dt_s);
err_t game_render(void);

#endif /* GAME_H */
