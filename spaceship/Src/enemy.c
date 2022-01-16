#include "enemy.h"
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"

static char data[] = {
	 0,  0,  0, 95, 95,  0,
	 0, 95, 95, 35, 35, 35,
	95, 35, 35, 35, 95, 95,
	 0, 35, 35, 35, 35, 35,
	 0,  0,  0, 35, 35,  0,
};

static sprite_t enemy_sprite = {
	.width = 6,
	.height = 5,
	.data = (char*) &data,
};


enemy_data_t enemy_init() {
	enemy_data_t enemy_state = {
		.sprite = enemy_sprite,
		.position = vector_from_whole(60, 31),
		.velocity = vector_from_whole(0, 0),
	};
	return enemy_state;
}

void enemy_update(
	enemy_data_t* enemy_state
) {
	vector_t acceleration = vector_from_whole(-10, 0);

	// Apply acceleration
	enemy_state->velocity.x += acceleration.x / 30;
	enemy_state->velocity.y += acceleration.y / 30;

	// Update position
	enemy_state->position.x += enemy_state->velocity.x / 30;
	enemy_state->position.y += enemy_state->velocity.y / 30;
}

void enemy_draw(
	enemy_data_t* enemy_state,
	graphics_data_t* graphics_state
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
