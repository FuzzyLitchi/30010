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

#define ENEMY_SPEED FP_FROM_WHOLE(20)
#define ENEMY_FRICTION_INV 50

#define BULLET_SPEED FP_FROM_WHOLE(20)

static sprite_t enemy_sprite = {
	.width = 6,
	.height = 5,
	.data = (char*) &data,
};

enemy_state_t enemy_init() {
	enemy_state_t enemy_state = {
		.sprite = enemy_sprite,
		.position = vector_from_whole(60, 31),
		.velocity = vector_from_whole(0, 0),
		.time_until_next_action = 100,
		.action = ACTION_APPROACHING
	};
	return enemy_state;
}

void enemy_update(
	enemy_state_t* enemy_state,
	projectiles_state_t* projectile_state,
	player_state_t* player_state,
	random_state_t* random_state
) {
	if (enemy_state->time_until_next_action <= 0) {
		enemy_state->action = (action_t) random_u64_up_to(random_state, 4);
		enemy_state->time_until_next_action = random_i32_between(random_state, 30, 5*30);
	}

	vector_t acceleration = vector_from_whole(0, 0);

	vector_t direction;

	switch (enemy_state->action) {
	case ACTION_APPROACHING:
		direction = vector_sub(&player_state->position, &enemy_state->position);
		vector_set_length(&direction, ENEMY_SPEED);
		acceleration.x += direction.x;
		acceleration.y += direction.y;
		break;
	case ACTION_SHOOTING:
		// Only shoot 6 times per second
		if (enemy_state->time_until_next_action % 15 == 0) {
			direction = vector_sub(&player_state->position, &enemy_state->position);
			vector_set_length(&direction, BULLET_SPEED);

			projectile_t projectile = {
				.position = enemy_state->position,
				.velocity = direction,
				.color = 95
			};
			projectiles_add(projectile_state, projectile);
			acceleration.x -= enemy_state->velocity.x;
			acceleration.y -= enemy_state->velocity.y;
		}
		break;
	case ACTION_IDLE:
		break;
	case ACTION_FLEEING:
		direction = vector_sub(&enemy_state->position, &player_state->position);
		vector_set_length(&direction, ENEMY_SPEED);
		acceleration.x += direction.x;
		acceleration.y += direction.y;
		break;
	}

#define FRICTION_INV 3
	// Friction
	fixedpoint_t length = vector_get_length(&enemy_state->velocity);
	acceleration.x -= fp_mul(enemy_state->velocity.x, length) / ENEMY_FRICTION_INV;
	acceleration.y -= fp_mul(enemy_state->velocity.y, length) / ENEMY_FRICTION_INV;

	// Apply acceleration
	enemy_state->velocity.x += acceleration.x / 30;
	enemy_state->velocity.y += acceleration.y / 30;

	// Update position
	enemy_state->position.x += enemy_state->velocity.x / 30;
	enemy_state->position.y += enemy_state->velocity.y / 30;

	// Limit position
	clamp_vector(
		&enemy_state->position,
		vector_from_whole(0, 0),
		vector_from_whole(GRAPHICS_WIDTH-ENEMY_WIDTH, GRAPHICS_HEIGHT-ENEMY_HEIGHT)
	);
	enemy_state->time_until_next_action -= 1;
}

void enemy_draw(
	enemy_state_t* enemy_state,
	graphics_state_t* graphics_state
) {
	int x = fp_round(enemy_state->position.x);
	int y = fp_round(enemy_state->position.y);
	graphics_draw_sprite(
		graphics_state,
		enemy_state->sprite,
		x,
		y
	);
}
