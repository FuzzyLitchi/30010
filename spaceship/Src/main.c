#include <ansi.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "joystick.h"
#include "graphics.h"
#include "input.h"

// We pick to run our game at 30 Hz, which means each frame is 33.33 ms
#define FRAME_DURATION 33
// Run using debug features
#define DEBUG_GAME_INFO

volatile int32_t milliseconds = 0;

// Timer 2's interupt
void TIM2_IRQHandler() {
    milliseconds++;

    TIM2->SR &= ~0x0001;
}

void print_formated_centiseconds(int32_t now) {
    char centis = now % 100;
    char seconds = (now / 100) % 60;
    char minutes = (now / 6000) % 60;
    char hours = (now / 360000) % 24;
    printf("%02d:%02d:%02d.%03d\n", hours, minutes, seconds, centis);
}

void timer_init() {
    // Set up clock with 100Hz frequency
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2
    // No remapping, No clock division, Not buffered, Edge-aligned, Up-counting mode,
    // One-pulse mode disabled, Any update request source, update events disabled
    TIM2->CR1 = 0x0000;
    TIM2->ARR = 64000 - 1;
    TIM2->PSC = 0;
    // Enable interrupt
    TIM2->DIER |= 0x0001;
    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Enable timer
    TIM2->CR1 = 0x0001;
}

void print_binary(int16_t value) {
	for (char i = 0; i < 16; i++) {
		if ((value >> i) & 1) {
			uart_put_char('1');
		} else {
			uart_put_char('0');
		}
	}
}

int main(void) {
    uart_init(1024000);
    timer_init();

    clrscr();
    hide_cursor();

    graphics_data_t graphics_state = graphics_init();
    input_data_t input_state = input_init();

    // The current frame we're on
    int frame = 0;
    while(1) {
    	// Get input
    	if (frame % 2) {
    		// PuTTY doesn't send the keys very fast so we have to update the input slowly
    		input_update(&input_state);
    	}

    	// Update world
    	// TODO

    	// Render world (into buffer)
    	// TODO
    	graphics_state.buffer[1][0] = 31;
    	graphics_state.buffer[2][1] = 31;

    	graphics_state.buffer[12][12] = 31;
    	graphics_state.buffer[13][13] = 31;
    	graphics_state.buffer[14][14] = 31;
    	graphics_state.buffer[15][15] = 31;

    	// Send rendered world over USART
    	graphics_show(&graphics_state);

    	// Clean (get ready for next frame)
    	frame++;
    	graphics_clear(&graphics_state);

#ifdef DEBUG_GAME_INFO
    	// Debug info
    	set_colors(32, 40);
    	printf("Frame number: %d\n", frame-1);
    	printf("ms left: %ld\n", (frame)*FRAME_DURATION - milliseconds);
    	printf("This frame: ");
    	print_binary(input_state.current_frame);
    	printf("\nLast frame: ");
    	print_binary(input_state.last_frame);
    	uart_put_char('\n');
#endif

    	// wait until next frame
    	while (milliseconds < frame * FRAME_DURATION) {

    	}
    }
}

