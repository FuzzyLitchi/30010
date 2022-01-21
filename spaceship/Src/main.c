#include <ansi.h>
#include <gpio.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "graphics.h"
#include "input.h"
#include "fixedpoint.h"
#include "random.h"
#include "player.h"
#include "enemy.h"
#include "projectiles.h"
#include "deathscreen.h"
#include "gamestate.h"

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

void print_binary(uint16_t value) {
	for (int i = 16; i > 0; i--) {
		if ((value >> i) & 1) {
			uart_put_char('1');
		} else {
			uart_put_char('0');
		}
	}
}

int main(void) {
    uart_init(2048000);
    timer_init();

    // Set the background color to black so that we clear with black.
    set_colors(37, 40);
    clrscr();
    hide_cursor();

    gamestate_t gamestate = PLAYING;
    gamestate_t previous_gamestate = PLAYING;

    random_state_t random_state = random_init();
    graphics_state_t graphics_state = graphics_init();
    input_state_t input_state = input_init();

    player_state_t player_state = player_init();
    enemy_state_t enemy_state = enemy_init();
    projectiles_state_t projectiles_state = projectiles_init();

    deathscreen_state_t deathscreen_state;

    // The current frame we're on
    int frame = 0;
    while(1) {
    	// Get input
		input_update(&input_state);

		switch (gamestate) {
		case PLAYING:
			// Update world
			player_update(
				&player_state,
				&input_state,
				&projectiles_state,
				&gamestate
			);
			enemy_update(&enemy_state, &projectiles_state, &player_state, &random_state);
			projectiles_update(&projectiles_state, &player_state, &enemy_state);

			// Render world (into buffer)
			enemy_draw(&enemy_state, &graphics_state);
			player_draw(&player_state, &graphics_state);
			projectiles_draw(&projectiles_state, &graphics_state);
			break;
		case DEATH_SCREEN:
			deathscreen_update(&deathscreen_state, &random_state);
			deathscreen_draw(&deathscreen_state, &graphics_state);
			break;
		case HELP_SCREEN:
			// TODO
			break;
		}

    	// Send rendered world over USART
    	int bytes_sent = graphics_show(&graphics_state);

    	// Clean (get ready for next frame)
    	frame++;
    	graphics_clear(&graphics_state);

    	// Check if we've switch gamestate
    	if (gamestate != previous_gamestate) {

    		// Call exit functions
    		switch (previous_gamestate) {
    		default:
    			break;
    		}

    		// Call enter functions
    		switch (gamestate) {
    		case DEATH_SCREEN:
    			deathscreen_state = deathscreen_enter(&graphics_state, &random_state);
    		default:
    			break;
    		}

    		previous_gamestate = gamestate;
    	}

#ifdef DEBUG_GAME_INFO
    	// Debug info
    	set_colors(32, 40);
    	printf("     Frame: %d\n", frame-1);
    	printf("   ms left: %ld \n", (frame)*FRAME_DURATION - milliseconds);
    	uart_put_string("This frame: ");
    	print_binary(input_state.current_frame);
    	uart_put_string("\n\rLast frame: ");
    	print_binary(input_state.last_frame);
    	uart_put_string("\n\r");
    	printf("Bytes sent: %d ", bytes_sent);
#endif

    	// wait until next frame
    	while (milliseconds < frame * FRAME_DURATION) {

    	}
    }
}
