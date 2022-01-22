#ifndef _HELP_SCREEN_H_
#define _HELP_SCREEN_H_

#include "graphics.h"
#include "input.h"
#include "gamestate.h"

void help_screen_update(input_state_t* input_state, gamestate_t* gamestate);
void help_screen_draw(graphics_state_t* graphics_state);

#endif
