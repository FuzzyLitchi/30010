// Shamelessly stolen (and modified) from: https://en.wikipedia.org/wiki/Xorshift
// It's Creative Commons! So it's legal. But I still say it because then it's not plagiat, I hope.
// Xorshift is a simple algorithm, and this implementation will only repeat after 2^64-1 calls.
// For our pseudo-random purposes this is fine. However, we still need a seed. If we had a constant
// as a seed we would always see the same behavior, which would be pretty boring gameplay wise.
// (and completely defeat the purpose of a PRNG). Therefore we read the lower bits of the ADC upon
// initialization to create a random seed.

#include "random.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f30x.h"
#include "gpio.h"

uint64_t xorshift64(random_state_t *state) {
	uint64_t x = state->a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return state->a = x;
}

// Everything after this is my own code.
random_state_t random_init() {
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A

    set_input(GPIOA, 0);
    set_input(GPIOA, 1);

	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);

	// We take 1 bit per measurement and construct a random 64 bit value.
	uint64_t seed = 0;
	for (int i = 0; i < 64; i++) {
		ADC_StartConversion(ADC1);
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
		uint16_t analog_value = ADC_GetConversionValue(ADC1); // Read the ADC value

		// Move everything left
		seed <<= 1;
		// Set least significant bit of seed to least significant bit of the
		// analog value
		seed |= analog_value & 1;
	}

	random_state_t state = {
		.a = seed,
	};

	return state;
}

// Generates a random number from 0 to the bound excluding the bound.
uint64_t random_u64_up_to(random_state_t *state, uint64_t bound) {
	// In order to assure randomness, we sometimes have to throw numbers out.
	// For example, if we had a PRNG give us a number between 0 and 9 (inlcuding both),
	// and we did n % 3 to limit the number to 0, 1 and 2 we'd have a higher chance of
	// geting 0 than the rest.
	//
	// (0, 3, 6, 9) => 0, (1, 4, 7) => 1, (2, 5, 8) => 2
	//
	// If we imagine the random numbers we can get as a string that the PRNG selects from
	// we simply cut off the last period of our numbers.
	// 0 1 2 0 1 2 0 1 2|0
	//                  ^ Everything after | is discarded. If our PRNG selects it, we simply reroll.

	// What we're doing is 2**64 - (2**64 % max) but we can't use that number because it's too big.
	// uint64_t extended_max = 0 - (UINT64_MAX % max + 1) % max);
	// Apparently underflow is undefined behavior in C, so I'll give up on this for now.
	
	// while (1) {
	// 	uint64_t n = xorshift64(state);
	// 	if (n < extended_max) {
	// 		return n % max;

	// 	}
	// 	// Try with new number
	// }
	return xorshift64(state) % bound;
}

// min has to be smaller than max.
int32_t random_i32_between(random_state_t *state, int32_t min, int32_t max) {
	return min + (int32_t) random_u64_up_to(state, max - min);
}

int random_bool(random_state_t* state) {

}
