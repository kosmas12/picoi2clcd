# picoi2clcd

A C library to control I2C LCD displays using the Rapsberry
Pi Pico (or really any board using the RP2040 microcontroller).

# License

All of the code in this repository is licensed under the
MIT license, read LICENSE for details.

# Notes

For example usage, check out the example directory.
Make sure to set your PICO_SDK_PATH if you haven't already
in case you want to compile the example and run it on your
Pico or other RP2040-powered board.

Currently only supports 16x2 LCDs. Being worked on.

A big part of the code is based off of the LCD example
located in the Raspberry Pi Foundation's pico-examples
repository, which can be found 
[here](https://github.com/raspberrypi/pico-examples).
