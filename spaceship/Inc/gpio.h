#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f30x_conf.h"

// Turns the GPIO pin into an input
void set_input(GPIO_TypeDef *gpio, char pin);

char read_input(GPIO_TypeDef *gpio, char pin);

// Turns the GPIO pin into an output
void set_output(GPIO_TypeDef *gpio, char pin);

void write_output(GPIO_TypeDef *gpio, char pin, char value);

// Order is Middle, Right, Left, Down, Up
// 0bMRLDU
char read_joystick();

void init_joystick();

#endif /* _GPIO_H_ */
