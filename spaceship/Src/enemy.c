#include "enemy.h"
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"
#include "random.h"
#include "player.h"

static char data[] = {
	 0,  0,  0, 95, 95,  0,
	 0, 95, 95, 35, 35, 35,
	95, 35, 35, 35, 95, 95,
	 0, 35, 35, 35, 35, 35,
	 0,  0,  0, 35, 35,  0,
};

#define ENEMY_WIDTH 6
#define ENEMY_HEIGHT 5

#define ENEMY_SPEED FP_FROM_WHOLE(15)
#define ENEMY_FRICTION_INV 50

#define BULLET_SPEED FP_FROM_WHOLE(25)

// If enemies go outside this area they vanish
const rectangle_t ENEMY_AREA = {
	FP_FROM_WHOLE(-10),
	FP_FROM_WHOLE(-10),
	FP_FROM_WHOLE(GRAPHICS_WIDTH+10),
	FP_FROM_WHOLE(GRAPHICS_HEIGHT+10)
};

static sprite_t enemy_sprite = {
	.width = 6,
	.height = 5,
	.data = (char*) &data,
};

enemy_state_t enemy_init() {
	enemy_state_t enemy_state = {
		.count = 0,
		.enemies = {}
	};

	return enemy_state;
}

void enemy_add(
	enemy_state_t* enemy_state,
	enemy_t enemy
) {
	if (enemy_state->count >= MAX_ENEMIES) {
		return;
	}

	enemy_state->enemies[enemy_state->count] = enemy;
	enemy_state->count++;
}

void enemy_remove(enemy_state_t* enemy_state, int index) {
	// Move enemies i + 1 to enemy_state->enemy back by 1
	for (int i = index; i < enemy_state->count - 1; i++) {
		enemy_state->enemies[i] = enemy_state->enemies[i+1];
	}
	enemy_state->count--;
}

void enemy_handle_damage(enemy_state_t* enemy_state, int index, int damage) {
	enemy_t* enemy = &enemy_state->enemies[index];
	enemy->health -= damage;
	if (enemy->health <= 0) {
		// It's dead
		enemy_remove(enemy_state, index);
	} else if (enemy->health == 1) {
		// If we're on our last sliver of health, run away
		enemy->action = ACTION_FLEEING;
		enemy->time_until_next_action = 2*30; // 2 secs
	}

	// We could show the damage taken by flashing here or something.
}

void enemy_update(
	enemy_state_t* enemy_state,
	projectiles_state_t* projectile_state,
	player_state_t* player_state,
	random_state_t* random_state
) {
	if (enemy_state->count < MAX_ENEMIES && random_u64_up_to(random_state, 100) == 0) {
		enemy_t new_enemy = {
			.sprite = enemy_sprite,
			.velocity = vector_from_whole(0, 0),
			.health = 3,
			.time_until_next_action = random_i32_between(random_state, 30, 90),
			.action = ACTION_APPROACHING
		};

		new_enemy.position.x = FP_FROM_WHOLE(GRAPHICS_WIDTH);
		new_enemy.position.y = random_i32_between(random_state, 0, FP_FROM_WHOLE(GRAPHICS_HEIGHT));
		enemy_add(enemy_state, new_enemy);
	}

	// Update each enemy
	for (int i = enemy_state->count - 1; i >= 0; i--) {
		enemy_t* enemy = &enemy_state->enemies[i];

		if (enemy->time_until_next_action <= 0) {
			switch (enemy->action) {
			case ACTION_APPROACHING:
				// We always shoot after approaching
				enemy->action = ACTION_SHOOTING;
				enemy->time_until_next_action = random_i32_between(random_state, 15*2, 15*5);
				break;
			case ACTION_SHOOTING:
				// After shooting we give the player a break by either moving or drifting.
				enemy->action = random_u64_up_to(random_state, 1) ? ACTION_IDLE : ACTION_APPROACHING;
				enemy->time_until_next_action = random_i32_between(random_state, 30, 3*30);
				break;
			case ACTION_IDLE:
				// After giving the player a break we either shoot now, or shoot after approaching
				enemy->action = random_u64_up_to(random_state, 1) ? ACTION_SHOOTING : ACTION_APPROACHING;
				if (enemy->action == ACTION_SHOOTING) {
					enemy->time_until_next_action = random_i32_between(random_state, 15*2, 15*5);
				} else {
					enemy->time_until_next_action = random_i32_between(random_state, 30, 3*30);
				}
				break;
			case ACTION_FLEEING:
				// Roll to be brave!
				// One in six chance
				enemy->action = random_u64_up_to(random_state, 6) ? ACTION_FLEEING : ACTION_APPROACHING;
				enemy->time_until_next_action = 60;
				break;
			}
		}

		vector_t acceleration = vector_from_whole(0, 0);

		vector_t direction;

		switch (enemy->action) {
		case ACTION_APPROACHING:
			direction = vector_sub(&player_state->position, &enemy->position);
			vector_set_length(&direction, ENEMY_SPEED);
			acceleration.x += direction.x;
			acceleration.y += direction.y;
			break;
		case ACTION_SHOOTING:
			// Only shoot 2 times per second
			if (enemy->time_until_next_action % 15 == 0) {
				direction = vector_sub(&player_state->position, &enemy->position);
				vector_set_length(&direction, BULLET_SPEED);

				projectile_t projectile = {
					.position = enemy->position,
					.velocity = direction,
					.color = 95,
					.grace_frames = 7
				};
				// Offset the position
				projectile.position.x += FP_FROM_WHOLE(ENEMY_WIDTH) / 2;
				projectile.position.y += FP_FROM_WHOLE(ENEMY_HEIGHT) / 2;

				projectiles_add(projectile_state, projectile);
				acceleration.x -= enemy->velocity.x;
				acceleration.y -= enemy->velocity.y;
			}
			break;
		case ACTION_IDLE:
			break;
		case ACTION_FLEEING:
			direction = vector_sub(&enemy->position, &player_state->position);
			vector_set_length(&direction, ENEMY_SPEED);
			acceleration.x += direction.x;
			acceleration.y += direction.y;
			break;
		}

		// Friction
		fixedpoint_t length = vector_get_length(&enemy->velocity);
		acceleration.x -= fp_mul(enemy->velocity.x, length) / ENEMY_FRICTION_INV;
		acceleration.y -= fp_mul(enemy->velocity.y, length) / ENEMY_FRICTION_INV;

		// Apply acceleration
		enemy->velocity.x += acceleration.x / 30;
		enemy->velocity.y += acceleration.y / 30;

		// Update position
		enemy->position.x += enemy->velocity.x / 30;
		enemy->position.y += enemy->velocity.y / 30;

		// If enemies are too far away we remove them
		if (!rectangle_contains(ENEMY_AREA, enemy->position)) {
			enemy_remove(enemy_state, i);
		}

		enemy->time_until_next_action -= 1;
	}
}

void enemy_draw(
	enemy_state_t* enemy_state,
	graphics_state_t* graphics_state
) {
	for (int i = 0; i < enemy_state->count; i++) {
		enemy_t* enemy = &enemy_state->enemies[i];

		int x = fp_round(enemy->position.x);
		int y = fp_round(enemy->position.y);
		graphics_draw_sprite(
			graphics_state,
			enemy->sprite,
			x,
			y
		);
	}
}
