# fastbit_nano_board_test

## Project Overview
Despite the name, the current firmware in this project is **the Flappy Bird game** — functionally identical to `010_Flappy_Bird_SPI`/`016_Flappy_Bird_8bit_Parallel` (same `main.c` flow, `player`/`obstacle`/`background`/`text_mssg` modules, and IMU-driven tilt control). The player tilts the board to fly a bird through gaps in scrolling obstacles, displayed on the round TFT LCD.

## ⚠️ Known gap: `nano_mfg_host.py` doesn't match this firmware
This directory also contains `nano_mfg_host.py`, a Python manufacturing-test host script that expects the board to run a serial command menu over UART (single-character commands `m`/`d`/`a`/`1`-`4`/`p`/`s`/`q` for LED/button/oscillator/MPU6050/LCD tests, replying with a `TEST:`/`RESULT:PASS|FAIL`/`DONE` line protocol, logged to `nano_mfg_log.csv`). **The actual `main.c` in this project does not implement any of that** — it's pure Flappy Bird with no serial command handling at all. If you run `nano_mfg_host.py` against a board flashed with this firmware, it will time out waiting for a menu response. Either the test-menu firmware hasn't been written yet, or it needs to be merged into this project — flagging this now so it isn't a surprise later.

## Features (of the firmware that's actually here)
- **Platform**: STM32 Nano board.
- **Input**: Onboard IMU (accelerometer-derived pitch) to control the bird's altitude.
- **Display**: Fastbit 1.28" TFT LCD with CTP for game graphics and touch input (start/restart).
- **IMU support**: Builds for either board revision — **MPU6050** (Nano v2.0) or **BMI270** (Nano v2.1) — selected at compile time via `NANO_BOARD_V2_0`/`NANO_BOARD_V2_1` in `Core/Inc/main.h`.

## Gameplay Instructions
1. **Starting the Game**: Tap the **START** icon on the TFT LCD.
2. **Controlling the Bird**: Tilt the board up/down to make the bird ascend/descend.
3. **Navigating Obstacles**: Guide the bird through gaps; colliding with an obstacle or the ground ends the run.
4. **Scoring**: Each gap passed increases the score by 1.
5. **Game Over**: Tap **RESTART** to play again.

## How to Run
1. Flash the STM32 Nano board with the provided code, having selected the correct `NANO_BOARD_V2_x` macro for your hardware revision.
2. Ensure the TFT LCD is properly connected.
3. Tap **START** on the TFT LCD to begin playing.
