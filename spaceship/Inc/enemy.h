#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"

typedef struct {
	sprite_t sprite;
	vector_t position;
	vector_t velocity;
} enemy_data_t;


enemy_data_t enemy_init();

void enemy_update(
	enemy_data_t* enemy_state
);

void enemy_draw(
	enemy_data_t* enemy_state,
	graphics_data_t* graphics_state
);

#endif
