#include "help_screen.h"
#include <stdio.h>
#include "ansi.h"

void help_screen_update(input_state_t* input_state, game_state_t* gamestate) {
	if (just_pressed(input_state, KEY_H)) {
		switch (*gamestate) {
		case PLAYING:
			*gamestate = HELP_SCREEN;
			break;
		case HELP_SCREEN:
			*gamestate = PLAYING;
			break;
		default:
			break;
		}
	}
}

void help_screen_draw(graphics_state_t* graphics_state) {
	set_colors(97, 40);
	gotoxy(23, 11);
	printf("Use the WASD keys or the joystick ");
	gotoxy(23, 12);
	printf("to move your spaceship.           ");
	gotoxy(23, 13);
	printf("Use the SPACE bar or press the    ");
	gotoxy(23, 14);
	printf("joystick to fire your weapon.     ");
	gotoxy(23, 15);
	printf("Enemy ships require multiple hits ");
	gotoxy(23, 16);
	printf("to go down, and so do you.        ");
	gotoxy(23, 17);
	printf("Try to avoid as much damage as you");
	gotoxy(23, 18);
	printf("can, as repairs are slow in space.");
	gotoxy(23, 19);
	printf("                                  ");
	gotoxy(23, 20);
	printf("                        Good luck.");
	gotoxy(0, 33);
}

// Use the WASD keys or the joystick
// to move your spaceship.
// Use the SPACE bar or press the
// joystick to fire your weapon.
// Enemy ships require multiple hits
// to go down, and so do you.
// Try to avoid as much damage as you
// can, as repairs are slow in space.
//
//                         Good luck.
