#include "projectiles.h"
#include "graphics.h"
#include "fixedpoint.h"

projectiles_state_t projectiles_init() {
	projectiles_state_t projectiles_state = {
			.projectile_count = 0,
			.projectiles = {}
	};

	return projectiles_state;
}

void projectiles_add(
	projectiles_state_t* projectiles_state,
	projectile_t projectile
) {
	if (projectiles_state->projectile_count >= MAX_PROJECTILES) {
		return;
	}

	projectiles_state->projectiles[projectiles_state->projectile_count] = projectile;
	projectiles_state->projectile_count++;
}

void projectiles_update(projectiles_state_t* projectiles_state) {
	// Loop backwards so we can remove bullets easily
	for (int i = projectiles_state->projectile_count - 1; i >= 0; i--) {
		projectile_t* projectile = &projectiles_state->projectiles[i];
		projectile->position.x += projectile->velocity.x / 30;
		projectile->position.y += projectile->velocity.y / 30;

		// Check if colliding with a thing
		if (0) {
			// TODO: Damage
		}

		// Check if out of bounds
		if (0) {
			// TODO: Destroy bullets
		}
	}
}

void projectiles_draw(
	projectiles_state_t* projectiles_state,
	graphics_state_t* graphics_state
) {
	for (int i = 0; i < projectiles_state->projectile_count; i++) {
		projectile_t* projectile = &projectiles_state->projectiles[i];
		int32_t x = FP_WHOLE(projectile->position.x);
		int32_t y = FP_WHOLE(projectile->position.y);
		graphics_state->buffer[x][y] = projectile->color;
	}
}
