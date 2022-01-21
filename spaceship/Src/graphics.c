#include "30010_io.h"
#include "graphics.h"
#include "ansi.h"

#define GRAPHICS_TRANSPARENT 0

graphics_state_t graphics_init() {
	graphics_state_t ctx = {
		.background_color = 90 // Grey
	};
	graphics_clear(&ctx);
	return ctx;
}

// Sets every pixel to be the background color
void graphics_clear(graphics_state_t* graphics_state) {
	for (int x = 0; x < GRAPHICS_WIDTH; x++) {
		for (int y = 0; y < GRAPHICS_HEIGHT; y++) {
			graphics_state->buffer[x][y] = graphics_state->background_color;
		}
	}
}

// Turns the buffer into commands and sends it over USART
int graphics_show(graphics_state_t* ctx) {
	// Store how many bytes we send for debug reasons.
	int total_bytes = 3; // home_cursor is 3 bytes.

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
			} else if (bg == previous_bg_color) {
				total_bytes += set_color(fg);
			} else if (fg == previous_fg_color) {
				total_bytes += set_color(bg + 10);
			} else {
				total_bytes += set_colors(fg, bg + 10);
			}
			uart_put_char('\xDC');
			total_bytes++;

			previous_bg_color = bg;
			previous_fg_color = fg;
		}
		uart_put_char('\r');
		uart_put_char('\n');
		total_bytes += 2;
	}

	return total_bytes;
}

int min(int a, int b) {
    return a<b ? a : b;
}

int max(int a, int b) {
    return a>b ? a : b;
}

// Draws the sprite within the area, but only the visible part of the sprite.
// If a sprite is on the boundary as such:
//
//    +---------------+
//    |               |
//  OO|XXXX           |
//   O|XXXXXX         |
//   O|XXXXXX         |
//  OO|XXXX           |
//    |               |
//    +---------------+
//
// We still draw the X part of the sprite.
void graphics_draw_sprite(graphics_state_t* ctx, sprite_t sprite, int x, int y) {
	int cutoff_dx = max(-x, 0);
	int cutoff_dy = max(-y, 0);

	int visible_width = min(sprite.width, GRAPHICS_WIDTH-x);
	int visible_height = min(sprite.height, GRAPHICS_HEIGHT-y);

	for (int dx = cutoff_dx; dx < visible_width; dx++) {
		for (int dy = cutoff_dy; dy < visible_height; dy++) {
			char byte = *(sprite.data + sprite.width * dy + dx);
			if (byte != GRAPHICS_TRANSPARENT) {
				ctx->buffer[x+dx][y+dy] = byte;
			}
		}
	}
}

