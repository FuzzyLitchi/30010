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

// Axis-alligned rectabgle. Used for collision detection.
typedef struct {
	fixedpoint_t x;
	fixedpoint_t y;
	fixedpoint_t w;
	fixedpoint_t h;
} rectangle_t;

// Fixed-point
// fp stands for fixed-point
fixedpoint_t fp_mul(fixedpoint_t a, fixedpoint_t b);
fixedpoint_t fp_div(fixedpoint_t a, fixedpoint_t b);
fixedpoint_t fp_sqrt(fixedpoint_t n);
int32_t fp_round(fixedpoint_t n);
fixedpoint_t fp_min(fixedpoint_t a, fixedpoint_t b);
fixedpoint_t fp_max(fixedpoint_t a, fixedpoint_t b);

void fp_print(fixedpoint_t n);

// Vectors
vector_t vector_from_whole(int16_t x, int16_t y);
vector_t vector_sub(vector_t* a, vector_t* b);
void clamp_vector(vector_t* vector, vector_t lower_bound, vector_t upper_bound);

fixedpoint_t vector_get_length(vector_t* vector);
void vector_set_length(vector_t* vector, fixedpoint_t length);

// Rectangles
rectangle_t rectangle_from_whole(int16_t x, int16_t y, int16_t w, int16_t h);
int rectangle_contains(rectangle_t rectangle, vector_t point);

#endif
