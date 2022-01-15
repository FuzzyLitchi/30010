#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "graphics.h"
#include "input.h"

typedef struct {
	sprite_t sprite;
	int x;
	int y;
} player_data_t;


player_data_t player_init();

void player_update(
	player_data_t* player_state,
	input_data_t* input_state
);

void player_draw(
	player_data_t* player_state,
	graphics_data_t* graphics_state
);

#endif
