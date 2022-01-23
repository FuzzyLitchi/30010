#include <stdio.h>

void clrscr() {
    printf("\x1B[2J\x1b[H");
}

void gotoxy(int x, int y) {
    printf("\x1B[%d;%df", y, x);
}

void home_cursor() {
	printf("\x1B[H");
}

void hide_cursor() {
	printf("\x1B[?25l");
}

int set_colors(char fg, char bg) {
	return printf("\x1B[%d;%dm", fg, bg);
}

int set_color(char color) {
	return printf("\x1B[%dm", color);
}
