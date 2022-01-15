#include "30010_io.h"
#include "graphics.h"
#include "ansi.h"

#define GRAPHICS_TRANSPARENT 0

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
				// Do nothing :)
			} else {
				set_colors(fg, bg + 10);
			}
			uart_put_char('\xDC');

			previous_bg_color = bg;
			previous_fg_color = fg;
		}
		uart_put_char('\r');
		uart_put_char('\n');
	}
}

void graphics_draw_sprite(graphics_data_t* ctx, sprite_t sprite, int x, int y) {
	for (int dx = 0; dx < sprite.width; dx++) {
		for (int dy = 0; dy < sprite.height; dy++) {
			char byte = *(sprite.data + sprite.width * dy + dx);
			if (byte != GRAPHICS_TRANSPARENT) {
				ctx->buffer[x+dx][y+dy] = byte;
			}
		}
	}
}

