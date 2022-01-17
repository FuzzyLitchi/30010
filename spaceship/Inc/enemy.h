#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"
#include "random.h"
#include "player.h"

typedef enum {
	ACTION_APPROACHING,
	ACTION_FLEEING,
	ACTION_SHOOTING,
	ACTION_IDLE
} action_t ;

typedef struct {
	sprite_t sprite;
	vector_t position;
	vector_t velocity;

	// AI State Machine
	action_t action;
	int time_until_next_action;
} enemy_state_t;


enemy_state_t enemy_init();

void enemy_update(
	enemy_state_t* enemy_state,
	projectiles_state_t* projectile_state,
	player_state_t* player_state,
	random_state_t* random_state
);

void enemy_draw(
	enemy_state_t* enemy_state,
	graphics_state_t* graphics_state
);

#endif
