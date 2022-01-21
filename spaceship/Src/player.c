#include "player.h"

#define PLAYER_WIDTH 5
#define PLAYER_HEIGHT 4

#define PLAYER_SPEED 40
#define PLAYER_FRICTION_INV 10

static const char data[] = {
	36, 96, 96,  0,  0,
	 0, 36, 36, 36, 36,
	 0, 36, 36, 36, 36,
	36, 36, 36,  0,  0
};

static const sprite_t player_sprite = {
	.width = 5,
	.height = 4,
	.data = (char*) &data,
};


player_state_t player_init() {
	player_state_t player_state = {
		.sprite = player_sprite,
		.position = vector_from_whole(5, 32),
		.velocity = vector_from_whole(0, 0),
		.dead = 0,
		.health = 5
	};
	return player_state;
}

void player_update(
	player_state_t* player_state,
	input_state_t* input_state,
	projectiles_state_t* projectiles_state,
	gamestate_t* gamestate
) {
	vector_t acceleration = vector_from_whole(0, 0);

	if (is_down(input_state, KEY_W)) {
		acceleration.y -= FP_FROM_WHOLE(PLAYER_SPEED);
	}
	if (is_down(input_state, KEY_A)) {
		acceleration.x -= FP_FROM_WHOLE(PLAYER_SPEED);
	}
	if (is_down(input_state, KEY_S)) {
		acceleration.y += FP_FROM_WHOLE(PLAYER_SPEED);
	}
	if (is_down(input_state, KEY_D)) {
		acceleration.x += FP_FROM_WHOLE(PLAYER_SPEED);
	}

	// Apply friction
	fixedpoint_t length = vector_get_length(&player_state->velocity);
	acceleration.x -= fp_mul(player_state->velocity.x, length) / PLAYER_FRICTION_INV;
	acceleration.y -= fp_mul(player_state->velocity.y, length) / PLAYER_FRICTION_INV;


	// Apply acceleration
	player_state->velocity.x += acceleration.x / 30;
	player_state->velocity.y += acceleration.y / 30;

	// Update position
	player_state->position.x += player_state->velocity.x / 30;
	player_state->position.y += player_state->velocity.y / 30;

	// Limit position
	clamp_vector(
		&player_state->position,
		vector_from_whole(0, 0),
		vector_from_whole(GRAPHICS_WIDTH-PLAYER_WIDTH, GRAPHICS_HEIGHT-PLAYER_HEIGHT)
	);


	// Shooting
	if (just_pressed(input_state, KEY_SPACE)) {
		projectile_t projectile = {
			.color = 36,
			.position = player_state->position,
			.velocity = vector_from_whole(30, 0),
			.grace_frames = 10
		};
		// Offset the projectile
		projectile.position.x += FP_FROM_WHOLE(PLAYER_WIDTH) / 2;
		projectile.position.y += FP_FROM_WHOLE(PLAYER_HEIGHT) / 2;
		projectiles_add(projectiles_state, projectile);
	}

	// Health
	if (player_state->health <= 0) {
		// We're dead
		player_state->dead = 1;
		*gamestate = DEATH_SCREEN;
	}
}

void player_draw(
	player_state_t* player_state,
	graphics_state_t* graphics_state
) {
	if (!player_state->dead) {
		int x = fp_round(player_state->position.x);
		int y = fp_round(player_state->position.y);
		graphics_draw_sprite(
			graphics_state,
			player_state->sprite,
			x,
			y
		);
	}
}
