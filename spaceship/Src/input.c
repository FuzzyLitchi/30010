// #define KEY_SHIFT 8
// #define KEY_W 7
// #define KEY_A 6
// #define KEY_S 5
// #define KEY_D 4
// #define KEY_UP 3
// #define KEY_LEFT 2
// #define KEY_DOWN 1
// #define KEY_RIGHT 0

// // This value contains whether each button we care about is pressed.
// // Each bit represents whether the key Shift, W, A, S, D, Up, Left, Down or Right is pressed.
// typedef struct {
//     uint16_t last_frame;
//     uint16_t current_frame;
// } input_system_state_t;

// // Checks if the specified key is down in the specified frame.
// char is_down(uint16_t pressed, char key) {
//     return (pressed >> key) & 1;
// }

// char just_pressed(input_system_state_t state, char key) {
//     return !is_down(state.last_frame, key) && is_down(state.current_frame, key);
// }