#ifndef _DEATHSCREEN_H_
#define _DEAHTSCREEN_H_
#include "graphics.h"
#include "random.h"

typedef struct {
	int time_until_on;
	int time_until_blink;
	int blink_count;
	sprite_t sprite;
	int x;
	int y;
} letter_t ;

#define LETTER_COUNT 8

typedef struct {
	letter_t letters[LETTER_COUNT];
} deathscreen_state_t ;

static const char G_DATA[] = {
	 0, 97, 97, 97, 97,
	97, 97,  0,  0,  0,
	97, 97,  0, 97, 97,
	97, 97,  0,  0, 97,
	 0, 97, 97, 97,  0
};

static const sprite_t G_sprite = {
	.data = (char*) &G_DATA,
	.width = 5,
	.height = 5
};

static const char A_DATA[] = {
	 0, 97, 97, 97,  0,
	97, 97,  0, 97, 97,
	97, 97,  0, 97, 97,
	97, 97, 97, 97, 97,
	97, 97,  0, 97, 97
};

static const sprite_t A_sprite = {
	.data = (char*) &A_DATA,
	.width = 5,
	.height = 5
};

static const char M_DATA[] = {
	97, 97,  0,  0,  0,  0, 97, 97,
	97, 97, 97,  0,  0, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97,  0, 97, 97,  0, 97, 97,
	97, 97,  0, 97, 97,  0, 97, 97
};

static const sprite_t M_sprite = {
	.data = (char*) &M_DATA,
	.width = 8,
	.height = 5
};

static const char E_DATA[] = {
	97, 97, 97, 97, 97,
	97, 97,  0,  0,  0,
	97, 97, 97, 97,  0,
	97, 97,  0,  0,  0,
	97, 97, 97, 97, 97
};

static const sprite_t E_sprite = {
	.data = (char*) &E_DATA,
	.width = 5,
	.height = 5
};

static const char O_DATA[] = {
	 0, 97, 97, 97,  0,
	97, 97,  0, 97, 97,
	97, 97,  0, 97, 97,
	97, 97,  0, 97, 97,
	 0, 97, 97, 97,  0
};

static const sprite_t O_sprite = {
	.data = (char*) &O_DATA,
	.width = 5,
	.height = 5
};

static const char V_DATA[] = {
	97, 97,  0, 97, 97,
	97, 97,  0, 97, 97,
	97, 97,  0, 97, 97,
	 0, 97, 97, 97,  0,
	 0, 97, 97, 97,  0
};

static const sprite_t V_sprite = {
	.data = (char*) &V_DATA,
	.width = 5,
	.height = 5
};

static const char R_DATA[] = {
	97, 97, 97, 97,  0,
	97, 97,  0, 97, 97,
	97, 97, 97, 97, 97,
	97, 97,  0, 97,  0,
	97, 97,  0, 97, 97
};

static const sprite_t R_sprite = {
	.data = (char*) &R_DATA,
	.width = 5,
	.height = 5
};

deathscreen_state_t deathscreen_enter(
	graphics_state_t* graphics_state,
	random_state_t* random_state
);

void deathscreen_update(
	deathscreen_state_t* deathscreen_state,
	random_state_t* random_state
);

void deathscreen_draw(
	deathscreen_state_t* deathscreen_state,
	graphics_state_t* graphics_state
);

#endif
