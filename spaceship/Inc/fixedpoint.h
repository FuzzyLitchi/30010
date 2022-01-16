#ifndef _FIXEDPOINT_H_
#define _FIXEDPOINT_H_
#include <stdint.h>

// 14 decimal bits, 17 whole part bits, and 1 sign bit.
#define FP_DECIMAL_BITS 14
#define FP_WHOLE_BITS 17
#define FP_TOTAL_BITS 32

// Get the whole or the fracitonal part
#define FP_WHOLE(n) ((int32_t) (n >> FP_DECIMAL_BITS))
#define FP_FRACTIONAL(n) (n & ((1 << FP_DECIMAL_BITS)-1))

// Create a new fixed point value from a whole number
#define FP_FROM_WHOLE(n) (n << FP_DECIMAL_BITS)

typedef int32_t fixedpoint_t;

typedef struct {
	fixedpoint_t x;
	fixedpoint_t y;
} vector_t;

// fp stands for fixed-point
fixedpoint_t fp_mul(fixedpoint_t a, fixedpoint_t b);
int32_t fp_round(fixedpoint_t n);

void fp_print(fixedpoint_t n);

vector_t vector_from_whole(int16_t x, int16_t y);

#endif
