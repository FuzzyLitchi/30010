#include "player.h"
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"

static char data[] = {
	36, 96, 96,  0,  0,
	 0, 36, 36, 36, 36,
	 0, 36, 36, 36, 36,
	36, 36, 36,  0,  0
};

static sprite_t player_sprite = {
	.width = 5,
	.height = 4,
	.data = (char*) &data,
};


player_data_t player_init() {
	player_data_t player_state = {
		.sprite = player_sprite,
		.position = vector_from_whole(5, 32),
		.velocity = vector_from_whole(0, 0),
	};
	return player_state;
}

void player_update(
	player_data_t* player_state,
	input_data_t* input_state
) {
	vector_t acceleration = vector_from_whole(0, 0);

	if (is_down(input_state, KEY_W)) {
		acceleration.y -= FP_FROM_WHOLE(20);
	}
	if (is_down(input_state, KEY_A)) {
		acceleration.x -= FP_FROM_WHOLE(20);
	}
	if (is_down(input_state, KEY_S)) {
		acceleration.y += FP_FROM_WHOLE(20);
	}
	if (is_down(input_state, KEY_D)) {
		acceleration.x += FP_FROM_WHOLE(20);
	}

	if (
		!is_down(input_state, KEY_W)
		&& !is_down(input_state, KEY_A)
		&& !is_down(input_state, KEY_S)
		&& !is_down(input_state, KEY_D)
	) {
		// If we're not going anywhere, deccelerate.
		acceleration.x -= player_state->velocity.x;
		acceleration.y -= player_state->velocity.y;
	}

	// Apply acceleration
	player_state->velocity.x += acceleration.x / 30;
	player_state->velocity.y += acceleration.y / 30;

	// Update position
	player_state->position.x += player_state->velocity.x / 30;
	player_state->position.y += player_state->velocity.y / 30;
}

void player_draw(
	player_data_t* player_state,
	graphics_data_t* graphics_state
) {
	int x = fp_round(player_state->position.x);
	int y = fp_round(player_state->position.y);
	graphics_draw_sprite(
		graphics_state,
		player_state->sprite,
		x,
		y
	);
}
