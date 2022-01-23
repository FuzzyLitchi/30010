#include "death_screen.h"

death_screen_state_t death_screen_enter(
	graphics_state_t* graphics_state,
	random_state_t* random_state
) {
	graphics_state->background_color = 30; // Black
	graphics_clear(graphics_state);

	death_screen_state_t deathscreen_state = {
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

void death_screen_update(
	death_screen_state_t* deathscreen_state,
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
		// Letter is off
		return 0;
	}
	if (letter->time_until_blink > 0) {
		// Letter is on, and we're not blinking
		return 1;
	}
	// Every second frame we're gonna blink
	return (letter->blink_count * 4 + letter->time_until_blink) / 2 % 2;
}

void death_screen_draw(
	death_screen_state_t* deathscreen_state,
	graphics_state_t* graphics_state
) {
	// Draw the letters
	for (int i = 0; i < LETTER_COUNT; i++) {
		letter_t* letter = &deathscreen_state->letters[i];
		if (letter_is_on(letter)) {
			graphics_draw_sprite(
				graphics_state,
				letter->sprite,
				letter->x,
				letter->y
			);
		}
	}
}
