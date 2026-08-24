# 021_Nano_watch_ui

## Project Overview
This project is a **work-in-progress skeleton** for a smartwatch-style UI on the STM32 Nano board. Despite the project name, the current source only brings up two status LEDs — it does not yet drive the round LCD, handle touch input, or render a watch face.

## Current Behaviour
- `app_init()` configures PA1 (blue LED) and PA2 (green LED) as push-pull GPIO outputs.
- `app_run()` toggles both LEDs together every 1000 ms in an infinite loop.

That is the entire runtime behaviour today.

## Present but unused
The project tree already includes the pieces a real watch UI would need, but none of them are wired up yet in `main.c`/`app.c`:
- `CST816S.c/.h` — capacitive touch panel driver.
- `font.c/.h` — bitmap font renderer.
- `assets/ball_1.png`, `assets/ball_2.png` — leftover sprite assets copied from `020_Bouncy_Ball`, not referenced by any code here.

## Components
- **STM32 Nano board**: Microcontroller platform.
- **Fastbit 1.28" round TFT LCD with CTP**: Present on the board and wired in the `.ioc`, but not yet initialized or drawn to by this firmware.

## How to Run
1. Flash the STM32 Nano board with the provided code.
2. Observe the blue and green LEDs toggling together once per second.

## Status
This is a starting point for a future watch-face UI, not a finished demo. If you're picking this project up to build the actual watch UI, `015_Nano_LCD_TP` (LCD init + touch handling) and `020_Bouncy_Ball` (LCD init + drawing) are the closest working references in this repo — note that `020_Bouncy_Ball` also carries unused `CST816S.c/.h` files, so its touch driver isn't wired up either; `015_Nano_LCD_TP` is the one with working touch.
