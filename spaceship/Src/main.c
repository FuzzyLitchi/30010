#include <ansi.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "joystick.h"
#include "graphics.h"

// We pick to run our game at 30 Hz, which means each frame is 33.33 ms
#define FRAME_DURATION 33

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

int main(void) {
    uart_init(1024000);
    timer_init();

    clrscr();
    hide_cursor();

    graphics_data_t graphics_ctx = graphics_init();

    // The current frame we're on
    int frame = 0;
    while(1) {
    	// Get input
    	// TODO

    	// Update world
    	// TODO

    	// Render world (into buffer)
    	// TODO
    	graphics_ctx.buffer[1][0] = 31;
    	graphics_ctx.buffer[2][1] = 31;

    	graphics_ctx.buffer[12][12] = 31;
    	graphics_ctx.buffer[13][13] = 31;
    	graphics_ctx.buffer[14][14] = 31;
    	graphics_ctx.buffer[15][15] = 31;

    	// Send rendered world over USART
    	graphics_show(&graphics_ctx);

    	// Clean (get ready for next frame)
    	printf("\x1B[32m%d", frame);
    	frame++;
    	graphics_clear(&graphics_ctx);

    	// wait until next frame
    	while (milliseconds < frame * FRAME_DURATION) {

    	}
    }
}

