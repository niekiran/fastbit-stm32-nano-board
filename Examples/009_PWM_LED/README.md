# 009_PWM_LED

This project implements a fading LED pattern using Pulse Width Modulation (PWM) on the STM32 nano board. The brightness of each LED gradually fades in and out, one by one, in a continuous cycle.

## Overview

The program uses the microcontroller's Timer hardware to generate PWM signals for controlling the brightness of three LEDs. Each LED is connected to a different Timer output channel, and the PWM duty cycle is varied to achieve the gradual fade effect.

## LED Pattern Generation

The LED fade pattern follows this sequence:

- **LED 1 (Blue)** fades in gradually, then fades out.
- **LED 2 (Red)** fades in gradually, then fades out.
- **LED 3 (Green)** fades in gradually, then fades out.

This pattern repeats continuously, creating a smooth and sequential fading effect across the LEDs.

<img src="009_PWM_LED.gif" alt="009_PWM_LED" width="550">
