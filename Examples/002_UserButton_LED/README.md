# 002_UseButton_LED

This project control an LED based on the state of onboard user button on the STM32 nano board. The LED remains **ON** while the button is pressed and turns **OFF** when the button is released.

## Overview

The project includes a function `user_button_led()` (defined in the `user_button_led.c` file) that initializes the GPIO pins for both the user button and the LED. It continuously monitors the state of the user button and controls the LED accordingly.

## Functionality

### `user_button_led()`
- **LED Control**: 
  - The function checks the state of the user button.
  - If the button is **pressed**, the LED turns **ON**.
  - If the button is **released**, the LED turns **OFF**.

<img src="002_UserButton_LED.gif" alt="002_UserButton_LED" width="550">
