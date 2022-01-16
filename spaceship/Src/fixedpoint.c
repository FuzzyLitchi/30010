#include "fixedpoint.h"
#include <stdio.h>

// fp stands for fixed-point

// Multiplies two fixed point numbers with no loss of accuracy beyond necessary (I think)
fixedpoint_t fp_mul(fixedpoint_t a, fixedpoint_t b) {
	return (fixedpoint_t)((int64_t)a * (int64_t)b >> FP_DECIMAL_BITS);
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

    printf("%d", FP_WHOLE(n));

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
