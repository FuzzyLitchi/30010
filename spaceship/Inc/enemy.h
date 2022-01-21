#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"
#include "random.h"

#define MAX_ENEMIES 5

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
	int health;

	// AI State Machine
	action_t action;
	int time_until_next_action;
} enemy_t ;


typedef struct {
	int count;
	enemy_t enemies[MAX_ENEMIES];
} enemy_state_t;


// I have to move some of the includes down here, because there's a circular
// dependency between the types for the methods. I really feel like C compilers
// shouldn't be having this problem with modern compilers, but there's probably
// some arcane reason they can't modify the header parser to lazily parse type
// names. My solution to this problem is inspired by:
// https://stackoverflow.com/questions/46150724/circular-dependency-between-c-header-files
#include "player.h"

enemy_state_t enemy_init();

void enemy_add(enemy_state_t* enemy_state, enemy_t enemy);
void enemy_remove(enemy_state_t* enemy_state, int index);

void enemy_handle_damage(enemy_state_t* enemy_state, int index, int damage);

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
