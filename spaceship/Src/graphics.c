#include "30010_io.h"
#include "graphics.h"
#include "ansi.h"

graphics_data_t graphics_init() {
	graphics_data_t ctx;
	graphics_clear(&ctx);
	return ctx;
}

// Sets every pixel to be the background color
void graphics_clear(graphics_data_t* ctx) {
	for (int x = 0; x < GRAPHICS_WIDTH; x++) {
		for (int y = 0; y < GRAPHICS_HEIGHT; y++) {
			ctx->buffer[x][y] = BACKGROUND_COLOR;
		}
	}
}

// Turns the buffer into commands and sends it over USART
void graphics_show(graphics_data_t* ctx) {
	// Set to some value that represents no color
	char previous_bg_color = 255;
	char previous_fg_color = 255;

	home_cursor();
	for (int y = 0; y < GRAPHICS_HEIGHT; y += 2) {
		for (int x = 0; x < GRAPHICS_WIDTH; x++) {
			char bg = ctx->buffer[x][y];
		    char fg = ctx->buffer[x][y+1];
			if (bg == previous_bg_color && fg == previous_fg_color) {
				uart_put_char('\xDC');
			} else {
				printf("\x1B[%d;%dm\xDC", bg + 10, fg);
			}

			previous_bg_color = bg;
			previous_fg_color = fg;
		}
		uart_put_char('\n');
		uart_put_char('\r');
	}
}

