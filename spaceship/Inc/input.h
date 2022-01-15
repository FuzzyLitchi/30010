#ifndef _INPUT_H_
#define _INPUT_H_
#include <stdint.h>

#define KEY_SPACE 8
#define KEY_W 7
#define KEY_A 6
#define KEY_S 5
#define KEY_D 4
#define KEY_UP 3
#define KEY_LEFT 2
#define KEY_DOWN 1
#define KEY_RIGHT 0

 // This value contains whether each button we care about is pressed.
 // Each bit represents whether the key Shift, W, A, S, D, Up, Left, Down or Right is pressed.
typedef struct {
	uint16_t last_frame;
	uint16_t current_frame;
} input_data_t;

char is_down(input_data_t* state, char key);

char just_pressed(input_data_t* state, char key);

input_data_t input_init();
void input_update(input_data_t* state);

#endif
