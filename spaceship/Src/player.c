#include "player.h"
#include "graphics.h"
#include "input.h"

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
		.x = 5,
		.y = 32,
	};
	return player_state;
}

void player_update(
	player_data_t* player_state,
	input_data_t* input_state
) {
	if (is_down(input_state, KEY_W)) {
		player_state->y -= 1;
	}
	if (is_down(input_state, KEY_A)) {
		player_state->x -= 1;
	}
	if (is_down(input_state, KEY_S)) {
		player_state->y += 1;
	}
	if (is_down(input_state, KEY_D)) {
		player_state->x += 1;
	}
}
void player_draw(
	player_data_t* player_state,
	graphics_data_t* graphics_state
) {
	graphics_draw_sprite(
		graphics_state,
		player_state->sprite,
		player_state->x,
		player_state->y
	);
}
