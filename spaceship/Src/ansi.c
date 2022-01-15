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

//static char powers_of_ten[] = {1, 10, 100};
//
// This function expects 4 bytes of buffer, and returns the
// amount of bytes written.
//char radix(char n, char* buffer) {
//	char bytes_written = 0;
//	for (int i = 2; i >= 0; i--) {
//		char digit = (n / powers_of_ten[i]) % 10;
//		if (digit || bytes_written) {
//			*buffer = '0' + digit;
//			buffer++;
//			bytes_written++;
//		}
//	}
//	*buffer = '\0';
//
//	return bytes_written;
//}

void set_colors(char fg, char bg) {
//	char buffer[4];

	printf("\x1B[%d;%dm", fg, bg);

	// I was trying to optimize the code, but it wasn't faster
//    uart_put_string("\x1B[");
//	radix(fg, (char*) &buffer);
//	uart_put_string((char*) &buffer);
//	uart_put_char(';');
//	radix(bg, (char*) &buffer);
//	uart_put_string((char*) &buffer);
//	uart_put_char('m');
}
