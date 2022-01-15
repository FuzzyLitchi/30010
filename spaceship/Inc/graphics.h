#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define GRAPHICS_WIDTH 64
// Height must be an even number
#define GRAPHICS_HEIGHT 64

// Black
#define BACKGROUND_COLOR 90

typedef struct {
	char buffer[GRAPHICS_WIDTH][GRAPHICS_HEIGHT];
} graphics_data_t;

graphics_data_t graphics_init();
void graphics_clear(graphics_data_t* ctx);
void graphics_show(graphics_data_t* ctx);

#endif // _GRAPHICS_H_