#include "fixedpoint.h"
#include <stdio.h>

// fp stands for fixed-point

// Multiplies two fixed point numbers with no loss of accuracy beyond necessary (I think)
fixedpoint_t fp_mul(fixedpoint_t a, fixedpoint_t b) {
	return (fixedpoint_t)((int64_t)a * (int64_t)b >> FP_DECIMAL_BITS);
}

fixedpoint_t fp_div(fixedpoint_t a, fixedpoint_t b) {
	return (fixedpoint_t)(((int64_t)a << FP_DECIMAL_BITS) / (int64_t)b);
}

fixedpoint_t fp_sqrt(fixedpoint_t n) {
	fixedpoint_t left = 0;
	fixedpoint_t right = n + 1;

	while (left != right - 1) {
		fixedpoint_t middle = (left + right) / 2;

		int64_t res = (int64_t)middle * (int64_t)middle >> FP_DECIMAL_BITS;
		if(res <= (int64_t)n) {
			left = middle;
		} else {
			right = middle;
		}
	}

	return left;
}

// Round to the neareast whole number, and return the value as an integer.
// Implements this algorithm: https://en.wikipedia.org/wiki/Rounding#Round_half_up
int32_t fp_round(fixedpoint_t n) {
	int32_t o = FP_WHOLE(n);
	if (FP_FRACTIONAL(n) >> (FP_DECIMAL_BITS - 1)) {
		o++;
	}

	return o;
}

// Debug print a fixed point value.
void fp_print(fixedpoint_t n) {
    if (n < 0) {
        putchar('-');
        // undo 2's compliment
        n = ~n + 1;
    }

    printf("%ld", FP_WHOLE(n));

    uint32_t number = FP_FRACTIONAL(n);
	if (number) {
		putchar('.');
	}

	while (number) {
		number *= 10;
		char digit = '0' + FP_WHOLE(number);
		putchar(digit);
		number = FP_FRACTIONAL(number);
	}
}

// Create a new vector from two whole numbers.
vector_t vector_from_whole(int16_t x, int16_t y) {
	vector_t vector = {
		FP_FROM_WHOLE(x),
		FP_FROM_WHOLE(y),
	};

	return vector;
}

vector_t vector_sub(vector_t* a, vector_t* b) {
	vector_t res;
	res.x = a->x - b->x;
	res.y = a->y - b->y;
	return res;
}

fixedpoint_t fp_min(fixedpoint_t a, fixedpoint_t b) {
    return a<b ? a : b;
}

fixedpoint_t fp_max(fixedpoint_t a, fixedpoint_t b) {
    return a>b ? a : b;
}

void clamp_vector(vector_t* vector, vector_t lower_bound, vector_t upper_bound) {
	fixedpoint_t x = vector->x;
	vector->x = fp_min(upper_bound.x, fp_max(lower_bound.x, x));

	fixedpoint_t y = vector->y;
	vector->y = fp_min(upper_bound.y, fp_max(lower_bound.y, y));
}

fixedpoint_t vector_get_length(vector_t* vector) {
	// sqrt(x**2 + y**2)
	return fp_sqrt(fp_mul(vector->x, vector->x) + fp_mul(vector->y, vector->y));
}

void vector_set_length(vector_t* vector, fixedpoint_t length) {
	fixedpoint_t current_length = vector_get_length(vector);
	vector->x = fp_mul(vector->x, fp_div(length, current_length));
	vector->y = fp_mul(vector->y, fp_div(length, current_length));
}

// Rectangles
rectangle_t rectangle_from_whole(int16_t x, int16_t y, int16_t w, int16_t h) {
	rectangle_t res = {
		.x = FP_FROM_WHOLE(x),
		.y = FP_FROM_WHOLE(y),
		.w = FP_FROM_WHOLE(w),
		.h = FP_FROM_WHOLE(h),
	};
	return res;
}

// Returns 1 if the rectangle does contain it, 0 otherwise.
int rectangle_contains(rectangle_t* rectangle, vector_t point) {
	return point.x > rectangle->x
	&& point.x < rectangle->x + rectangle->w
	&& point.y > rectangle->y
	&& point.y < rectangle->y + rectangle->h;
}
