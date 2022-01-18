#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"
#include "gamestate.h"

typedef struct {
	sprite_t sprite;
	vector_t position;
	vector_t velocity;
	// If it's 0, we're alive
	char dead;
	// A number representing how much health we have
	int health;
} player_state_t;


// I have to move some of the includes down here, because there's a circular
// dependency between the types for the methods. I really feel like C compilers
// shouldn't be having this problem with modern compilers, but there's probably
// some arcane reason they can't modify the header parser to lazily parse type
// names. My solution to this problem is inspired by:
// https://stackoverflow.com/questions/46150724/circular-dependency-between-c-header-files
#include "projectiles.h"

player_state_t player_init();

void player_update(
	player_state_t* player_state,
	input_state_t* input_state,
	projectiles_state_t* projectiles_state,
	gamestate_t* gamestate
);

void player_draw(
	player_state_t* player_state,
	graphics_state_t* graphics_state
);

#endif
