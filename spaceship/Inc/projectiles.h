#ifndef _PROJECTILES_H_
#define _PROJECTILES_H_
#include "graphics.h"
#include "fixedpoint.h"

#define MAX_PROJECTILES 50

typedef struct {
	vector_t position;
	vector_t velocity;
	char color;
} projectile_t;

typedef struct {
	projectile_t projectiles[MAX_PROJECTILES];
	uint8_t count;
} projectiles_state_t;

projectiles_state_t projectiles_init();

void projectiles_add(
	projectiles_state_t* projectiles_state,
	projectile_t projectile
);

void projectiles_remove(projectiles_state_t* projectiles_state, int index);

void projectiles_update(projectiles_state_t* projectiles_state);

void projectiles_draw(
	projectiles_state_t* projectiles_state,
	graphics_state_t* graphics_state
);

#endif
