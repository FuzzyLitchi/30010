The project description says I have to document the HAL. What is part of the HAL? If I write a function called `void set_pin_input(gpio, pin)` that sets a pin to be a specific input mode, is that part of the HAL?




# TODO:
- Finish Excerpts_STM32_Norris
- ~~and read the slides.~~

# Deadlines:
- 17/18th

Final versions of block diagram, flow charts, schedule and plan are expected

- 21st

Everything


# Other stuff
## CLI

This `openocd -f interface/stlink.cfg -f target/stm32f3x.cfg` works.
`arm-none-eabi-gdb -q -ex "target remote :3333" $BINARY` works.
Use `load` to flash the chip and `continue` to start it.

arm-none-eabi-gcc
arm-none-eabi-gdb

https://docs.rust-embedded.org/discovery/f3discovery/05-led-roulette/debug-it.html