# 003_UserButton_IT

This project controls multiple LEDs based on button presses using an STM32 microcontroller. The LEDs turn off one by one with each button press, and when all LEDs are off, pressing the button again turns them all back on, repeating the cycle.

## Overview

The project includes the `led_on()` function (located in the `led.c` file), which initially turns on all user LEDs. The `led_off()` function monitors button interrupts to control the LEDs, turning them off one by one with each button press until all LEDs are off.

## Functionality

- **LED Control**: 
  - The LEDs are connected to GPIO pins and are initially turned **ON**.
  - Each button press (detected via an interrupt) turns off one LED in sequence: **Red -> Green -> Blue**.
  - After all LEDs are off, the next button press turns them all back **ON**.

<img src="003_UserButton_IT.gif" alt="003_UserButton_IT" width="550">

