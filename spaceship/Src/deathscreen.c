#include "deathscreen.h"

// Without optimization
// 8 letters = 7 ms.
// 7 letters = 9 ms.
// 6 letters = 9 ms.
// 5 letters = 11 ms.
// 4 letters = 12 ms.
// 1.2 ms per letter, 16.8 with no letters

// 0 letters = 18

// Update is free, all cost comes from drawing stuff.

deathscreen_state_t deathscreen_enter(
	graphics_state_t* graphics_state,
	random_state_t* random_state
) {
	graphics_state->background_color = 30; // Black
	graphics_clear(graphics_state);

	deathscreen_state_t deathscreen_state = {
		.letters = {
			{
				.sprite = G_sprite,
				.x = 27,
				.y = 26
			},
			{
				.sprite = A_sprite,
				.x = 33,
				.y = 26
			},
			{
				.sprite = M_sprite,
				.x = 39,
				.y = 26
			},
			{
				.sprite = E_sprite,
				.x = 48,
				.y = 26
			},
			{
				.sprite = O_sprite,
				.x = 29,
				.y = 32
			},
			{
				.sprite = V_sprite,
				.x = 35,
				.y = 32
			},
			{
				.sprite = E_sprite,
				.x = 41,
				.y = 32
			},
			{
				.sprite = R_sprite,
				.x = 47,
				.y = 32
			}
		}
	};

	for (int i = 0; i < LETTER_COUNT; i++) {
		letter_t* letter = &deathscreen_state.letters[i];
		// Half of the letters will turn on and stay on, and the other half
		// will blink on.
		if (random_i32_between(random_state, 0, 1)) {
			letter->time_until_on = random_i32_between(random_state, 40, 80);
			letter->time_until_blink = random_i32_between(random_state, 120, 1000);
		} else {
			letter->time_until_on = random_i32_between(random_state, 40, 80);
			letter->time_until_blink = letter->time_until_on;
		}
		letter->blink_count = random_i32_between(random_state, 1, 4);
	}

	return deathscreen_state;
}

void deathscreen_update(
	deathscreen_state_t* deathscreen_state,
	random_state_t* random_state
) {
	for (int i = 0; i < LETTER_COUNT; i++) {
		letter_t* letter = &deathscreen_state->letters[i];

		if (letter->time_until_on > 0) {
			letter->time_until_on--;
		}
		// If we're done blinking
		if (letter->time_until_blink + letter->blink_count * 4 < 0) {
			letter->time_until_blink = random_i32_between(random_state, 300, 1000);
			letter->blink_count = random_i32_between(random_state, 1, 4);
		}

		letter->time_until_blink--;
	}
}

int letter_is_on(letter_t* letter) {
	if (letter->time_until_on > 0) {
		// FIXME
		return 1;
		// Letter is off
		return 0;
	}
	if (letter->time_until_blink > 0) {
		// Letter is on, and we're not blinking
		return 1;
	}
	return 1;
	// Every second frame we're gonna blink
	return (letter->blink_count * 4 + letter->time_until_blink) / 2 % 2;
}

extern int32_t milliseconds;

void deathscreen_draw(
	deathscreen_state_t* deathscreen_state,
	graphics_state_t* graphics_state
) {
	// Draw the baground gradient
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 10; x++) {
			// Calculate bayer matrix index
			int limit = BAYER_MATRIX[(x % 4) + 4*(y % 4)];
			if (x > limit) {
				graphics_state->buffer[x][y] = 95;
			}
		}
	}
//	int before = milliseconds;
//	for (int x = 0; x < GRAPHICS_WIDTH; x++) {
//		for (int y = 0; y < GRAPHICS_HEIGHT; y++) {
//			graphics_state->buffer[x][y] = 30 + ((x&0b10000) >> 2);
//		}
//	}
//	int after = milliseconds;
//	int total = after - before;

	// Draw the letters
//	for (int i = 0; i < 0; i++) {
//		letter_t* letter = &deathscreen_state->letters[i];
//		if (letter_is_on(letter)) {
//			graphics_draw_sprite(
//				graphics_state,
//				letter->sprite,
//				letter->x,
//				letter->y
//			);
//		}
//	}
}
