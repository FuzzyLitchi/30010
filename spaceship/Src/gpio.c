#include "stm32f30x_conf.h"

// Turns the GPIO pin into an input
void set_input(GPIO_TypeDef *gpio, char pin) {
    gpio->MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
    gpio->MODER |= (0x00000000 << (pin * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
    gpio->PUPDR &= ~(0x00000003 << (pin * 2)); // Clear push/pull register
    gpio->PUPDR |= (0x00000002 << (pin * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)
}

char read_input(GPIO_TypeDef *gpio, char pin) {
    return (gpio->IDR >> pin) & 1;
}

// Turns the GPIO pin into an output
void set_output(GPIO_TypeDef *gpio, char pin) {
    gpio->OSPEEDR &= ~(0x00000003 << (pin * 2)); // Clear speed register
    gpio->OSPEEDR |= (0x00000002 << (pin * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    gpio->OTYPER &= ~(0x0001 << (pin * 1)); // Clear output type register
    gpio->OTYPER |= (0x0000 << (pin * 1)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
    gpio->MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
    gpio->MODER |= (0x00000001 << (pin * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}

void write_output(GPIO_TypeDef *gpio, char pin, char value) {
    if (value) {
        gpio->ODR |= (1 << pin);
    } else {
        gpio->ODR &= ~(1 << pin);
    }
}

// Order is Center, Right, Left, Down, Up
// 0bRLDU

// UP LEFT DOWN RIGHT
char read_joystick() {
    return 0
    | (read_input(GPIOB, 5) << 4)
    | (read_input(GPIOA, 4) << 3)
    | (read_input(GPIOC, 1) << 2)
    | (read_input(GPIOB, 0) << 1)
    | (read_input(GPIOC, 0) << 0);
}

void init_joystick() {
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

    // Joystick
    // UP     => A2 => PA_4
    // DOWN   => A3 => PB_0
    // LEFT   => A4 => PC_1
    // RIGHT  => A5 => PC_0
    // CENTER => D5 => PB_5
    set_input(GPIOA, 4);
    set_input(GPIOB, 0);
    set_input(GPIOC, 1);
    set_input(GPIOC, 0);
    set_input(GPIOB, 5);
}
