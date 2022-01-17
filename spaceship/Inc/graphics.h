#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define GRAPHICS_WIDTH 80
// Height must be an even number
#define GRAPHICS_HEIGHT 64

// Black
#define BACKGROUND_COLOR 90

typedef struct {
	char buffer[GRAPHICS_WIDTH][GRAPHICS_HEIGHT];
} graphics_state_t;

typedef struct {
	char width;
	char height;
	char* data;
} sprite_t ;

graphics_state_t graphics_init();
void graphics_clear(graphics_state_t* ctx);
void graphics_show(graphics_state_t* ctx);

void graphics_draw_sprite(graphics_state_t* ctx, sprite_t sprite, int x, int y);

#endif // _GRAPHICS_H_
