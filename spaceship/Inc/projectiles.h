#ifndef _PROJECTILES_H_
#define _PROJECTILES_H_
#include "fixedpoint.h"
#include "graphics.h"

#define MAX_PROJECTILES 50

typedef struct {
	vector_t position;
	vector_t velocity;
	uint8_t color;
	// When spawning the projectile, it won't check for collisions
	// the first few frames. This way the projectile doesn't collide
	// with the person who fired it.
	uint8_t grace_frames;
} projectile_t;

typedef struct {
	projectile_t projectiles[MAX_PROJECTILES];
	uint8_t count;
} projectiles_state_t;

// I have to move some of the includes down here, because there's a circular
// dependency between the types for the methods. I really feel like C compilers
// shouldn't be having this problem with modern compilers, but there's probably
// some arcane reason they can't modify the header parser to lazily parse type
// names. My solution to this problem is inspired by:
// https://stackoverflow.com/questions/46150724/circular-dependency-between-c-header-files
#include "enemy.h"
#include "player.h"

projectiles_state_t projectiles_init();

void projectiles_add(
	projectiles_state_t* projectiles_state,
	projectile_t projectile
);

void projectiles_remove(projectiles_state_t* projectiles_state, int index);

void projectiles_update(
	projectiles_state_t* projectiles_state,
	player_state_t* player_state,
	enemy_state_t* enemy_state
);

void projectiles_draw(
	projectiles_state_t* projectiles_state,
	graphics_state_t* graphics_state
);

#endif
