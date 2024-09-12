# 001_LED_Toggle

This project provides a basic template for programming STM32 nano board to toggle LEDs.

## Overview

The project demonstrates how to toggle LEDs connected to GPIO pins of an STM32 microcontroller. The main program, located in the `main.c` file, continuously toggles the LEDs in an infinite loop.

## Features

- **LED Toggle Functionality**: The project includes a dedicated function, `led_toggle()`, implemented in `led_toggle.c`, which handles the toggling of the LEDs.
- **LED Toggle Function Description**: The `led_toggle()` function toggles three LEDs (blue, green, and red) connected to the microcontrollers GPIO pins. The LEDs toggle sequentially, creating a cycling pattern.

<img src="001_LED_Toggle.gif" alt="001_LED_Toggle" width="550">
