// Shamelessly stolen (and modified) from: https://en.wikipedia.org/wiki/Xorshift
// It's Creative Commons! So it's legal. But I still say it because then it's not plagiat, I hope.

#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <stdint.h>

typedef struct {
  uint64_t a;
} random_state_t;

uint64_t xorshift64(random_state_t *state);

// Everthing after this is my code.
random_state_t random_init();
uint64_t random_u64_up_to(random_state_t *state, uint64_t max);
int32_t random_i32_between(random_state_t *state, int32_t min, int32_t max);

#endif
