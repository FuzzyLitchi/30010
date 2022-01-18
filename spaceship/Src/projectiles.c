#include "projectiles.h"

const rectangle_t SCREEN = {
	FP_FROM_WHOLE(0),
	FP_FROM_WHOLE(0),
	FP_FROM_WHOLE(GRAPHICS_WIDTH),
	FP_FROM_WHOLE(GRAPHICS_HEIGHT)
};

projectiles_state_t projectiles_init() {
	projectiles_state_t projectiles_state = {
		.count = 0,
		.projectiles = {}
	};

	return projectiles_state;
}

void projectiles_add(
	projectiles_state_t* projectiles_state,
	projectile_t projectile
) {
	if (projectiles_state->count >= MAX_PROJECTILES) {
		return;
	}

	projectiles_state->projectiles[projectiles_state->count] = projectile;
	projectiles_state->count++;
}

void projectiles_remove(projectiles_state_t* projectiles_state, int index) {
	// Move prjectile i + 1 to projectiles_state->projectile_count back
	for (int i = index; i < projectiles_state->count - 1; i++) {
		projectiles_state->projectiles[i] = projectiles_state->projectiles[i+1];
	}
	projectiles_state->count--;
}

void projectiles_update(
	projectiles_state_t* projectiles_state,
	player_state_t* player_state,
	enemy_state_t* enemy_state
) {
	// Loop backwards so we can remove bullets easily
	for (int i = projectiles_state->count - 1; i >= 0; i--) {
		projectile_t* projectile = &projectiles_state->projectiles[i];
		// Update position
		projectile->position.x += projectile->velocity.x / 30;
		projectile->position.y += projectile->velocity.y / 30;

		// Check if we're colling with any enemy
		for (int j = 0; j < enemy_state->count; j++) {
			enemy_t* enemy = &enemy_state->enemies[j];
			rectangle_t collider_box = {
				.x = enemy->position.x,
				.y = enemy->position.y,
				.w = FP_FROM_WHOLE(enemy->sprite.width),
				.h = FP_FROM_WHOLE(enemy->sprite.height)
			};

			if (projectile->grace_frames == 0 && rectangle_contains(collider_box, projectile->position)) {
				// Hit! Apply damage and delete projectile
				enemy_remove(enemy_state, j); // TODO: Remove healh instead of instant death

				projectiles_remove(projectiles_state, i);
				goto outer_continue;
			}
		}
		// Check if we're colliding with the player
		rectangle_t collider_box = {
			.x = player_state->position.x,
			.y = player_state->position.y,
			.w = FP_FROM_WHOLE(player_state->sprite.width),
			.h = FP_FROM_WHOLE(player_state->sprite.height)
		};

		if (projectile->grace_frames == 0 && rectangle_contains(collider_box, projectile->position)) {
			// Hit! Apply damage and delete projectile
			player_state->health--; // 1 damage.

			projectiles_remove(projectiles_state, i);
			goto outer_continue;
		}

		// Check if out of bounds
		if (!rectangle_contains(SCREEN, projectile->position)) {
			projectiles_remove(projectiles_state, i);
		}

		if (projectile->grace_frames > 0) {
			projectile->grace_frames--;
		}

		outer_continue:;
	}
}

void projectiles_draw(
	projectiles_state_t* projectiles_state,
	graphics_state_t* graphics_state
) {
	for (int i = 0; i < projectiles_state->count; i++) {
		projectile_t* projectile = &projectiles_state->projectiles[i];
		int32_t x = FP_WHOLE(projectile->position.x);
		int32_t y = FP_WHOLE(projectile->position.y);
		graphics_state->buffer[x][y] = projectile->color;
	}
}
