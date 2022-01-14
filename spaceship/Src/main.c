#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "cli.h"
#include "joystick.h"

volatile int32_t centiseconds = 0;

// Timer 2's interupt
void TIM2_IRQHandler() {
    centiseconds++;

    TIM2->SR &= ~0x0001;
}

int print_formated_centiseconds(int32_t now) {
    char centis = now % 100;
    char seconds = (now / 100) % 60;
    char minutes = (now / 6000) % 60;
    char hours = (now / 360000) % 24;
    printf("%02d:%02d:%02d.%03d\n", hours, minutes, seconds, centis);
}

int main(void) {
    lcd_init();
    uart_init(9600);
    init_joystick();

    clrscr();

    uint8_t buffer[512];
    for (int i = 0; i < 512; i++) {
        buffer[i] = (uint8_t) i;
    }

    lcd_push_buffer(&buffer);

    // Set up clock with 100Hz frequency
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2
    // No remapping, No clock division, Not buffered, Edge-aligned, Up-counting mode,
    // One-pulse mode disabled, Any update request source, update events disabled
    TIM2->CR1 = 0x0000;
    TIM2->ARR = 640000 - 1;
    TIM2->PSC = 0;
    // Enable interrupt
    TIM2->DIER |= 0x0001;
    NVIC_SetPriority(TIM2_IRQn, 2);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Enable timer
    TIM2->CR1 = 0x0001;

    int32_t split1_acc = 0;
    int32_t split2_acc = 0;

    int32_t split1_offset = 0;
    int32_t split2_offset = 0;

    // 0 is no one selected, 1 is split 1, 2 is split 2
    char selected = 0;

    while(1){
        int input = read_joystick();

        if (input == 0b10000) {
            TIM2->CR1 ^= 0x0001;
        } else if (input & 0b0100) {
            // Split time 1
            if (selected == 2) {
                split2_acc += centiseconds - split2_offset;
            }

            if (selected != 1) {
                split1_offset = centiseconds;
            }
            selected = 1;
        } else if (input & 0b1000) {
            // Split time 2
            if (selected == 1) {
                split1_acc += centiseconds - split1_offset;
            }

            if (selected != 2) {
                split2_offset = centiseconds;
            }
            selected = 2;
        } else if (input & 0b0010) {
            // Stop clock and set time to 0:00
            TIM2->CR1 = 0x0000;
            centiseconds = 0;
            split1_acc = 0;
            split2_acc = 0;
            selected = 0;
        }

        // Roughly every second we print the current time
        if (centiseconds % 10 == 0) {
            gotoxy(1,1);
            printf("Time:    ");
            print_formated_centiseconds(centiseconds);

            printf("Split 1: ");
            if (selected == 1) {
                print_formated_centiseconds(split1_acc + centiseconds - split1_offset);
            } else {
                print_formated_centiseconds(split1_acc);
            }

            printf("Split 2: ");
            if (selected == 2) {
                print_formated_centiseconds(split2_acc + centiseconds - split2_offset);
            } else {
                print_formated_centiseconds(split2_acc);
            }
        }
    }
}
