#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"

typedef struct {
	sprite_t sprite;
	vector_t position;
	vector_t velocity;
} player_state_t;


player_state_t player_init();

void player_update(
	player_state_t* player_state,
	input_state_t* input_state
);

void player_draw(
	player_state_t* player_state,
	graphics_state_t* graphics_state
);

#endif
