#include "30010_io.h"
#include "input.h"

 // Checks if the specified key is down in the specified frame.
char _is_down(uint16_t pressed, char key) {
	return (pressed >> key) & 1;
}

char is_down(input_state_t* state, char key) {
	return _is_down(state->current_frame, key);
}

char just_pressed(input_state_t* state, char key) {
	return !_is_down(state->last_frame, key) && _is_down(state->current_frame, key);
}

input_state_t input_init() {
	input_state_t state = {0, 0};
	return state;
}

void input_update(input_state_t* state) {
	state->last_frame = state->current_frame;
	uint16_t current = 0;

	while (1) {
		uint8_t c = uart_get_char();
		switch (c) {
		case 'W':
		case 'w':
			current |= 1 << KEY_W;
			break;
		case 'A':
		case 'a':
			current |= 1 << KEY_A;
			break;
		case 'S':
		case 's':
			current |= 1 << KEY_S;
			break;
		case 'D':
		case 'd':
			current |= 1 << KEY_D;
			break;
		case ' ':
			current |= 1 << KEY_SPACE;
			break;
		// Up =    "\x1b[A"
		// Down =  "\x1b[B"
		// Right = "\x1b[C"
		// Left =  "\x1b[D"
		case '\x1b':
			// The arrow keys are more complicated, so we have to parse more than
			// one byte. We assume the second byte is '['.
			uart_get_char();
			switch (uart_get_char()) {
			case 'A':
				current |= 1 << KEY_UP;
				break;
			case 'B':
				current |= 1 << KEY_DOWN;
				break;
			case 'C':
				current |= 1 << KEY_RIGHT;
				break;
			case 'D':
				current |= 1 << KEY_LEFT;
				break;
			default:
				//Ignore.
				break;
			}
			break;
		default:
			// Ignore.
			break;
		case 0:
			// No more characters
			state->current_frame = current;
			return;
		}
	}
}
