#include <stdio.h>
#include <math.h>
#include "30010_io.h"

void clrscr() {
    printf("\x1B[2J\x1b[H");
}

void clreol() {
    printf("\x1B[0K");
}

void gotoxy(int x, int y) {
    printf("\x1B[%d;%df", y, x);
}

void underline(int enable) {
    if (enable) {
        printf("\x1B[4m");
    } else {
        printf("\x1B[24m");
    }
}

void blink(int enable) {
    if (enable) {
        printf("\x1B[5m");
    } else {
        printf("\x1B[25m");
    }
}

void inverse(int enable) {
    if (enable) {
        printf("\x1B[7m");
    } else {
        printf("\x1B[27m");
    }
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
