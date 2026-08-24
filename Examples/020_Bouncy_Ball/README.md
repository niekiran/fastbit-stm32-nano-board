# 020_Bouncy_Ball

## Project Overview
This project is a tilt-controlled ball physics toy on the STM32 Nano board. A ball sprite rolls and bounces around inside a circular arena on the round TFT LCD, driven by the onboard IMU's gyroscope. There are no obstacles, no scoring, and no touch input — it's a small physics demo, not a game with a win/lose condition.

## Features
- **Platform**: STM32 Nano board.
- **Input**: Onboard IMU gyroscope (X/Y rotation rate) mapped to a 2D force applied to the ball.
- **Display**: Fastbit 1.28" round TFT LCD (GC9A01A) — the ball, a randomized "spilled paint" background, and occasional decorative paint splatters are rendered each frame.
- **IMU support**: Builds for either board revision — **MPU6050** (Nano v2.0) or **BMI270** (Nano v2.1) — selected at compile time (see below). Both are configured to the same ±2G / ±500dps ranges so the physics feel identical regardless of which sensor is fitted.

## Components
- **STM32 Nano board**: Runs the physics simulation and rendering loop at ~60 fps.
- **Fastbit 1.28" round TFT LCD**: Displays the ball and background; the capacitive touch controller is present on the board but not used by this project.

## Code layout
Unlike the older flat `Core/Src`/`Core/Inc` examples in this repo, this project organizes drivers by subsystem under `Core/drivers/`:
- `Core/drivers/imu/` — `mpu6050.c/.h` and `bmi270.c/.h`, a handle-based IMU driver API (`*_create/_init/_calibrate/_read_gyro`).
- `Core/drivers/display/` — `gc9a01a.c/.h`, the round LCD driver.
- `Core/drivers/gfx/` — `gfx.c/.h`, low-level drawing primitives.
- `Core/drivers/game/` — `game.c/.h`, `player.c/.h`, `world.c/.h`, `app.c/.h` — the physics/game loop itself.

## Board / IMU selection
`Core/Inc/main.h` selects the IMU driver at compile time:
```c
#define NANO_BOARD_V2_1   /* BMI270 -- default */
/* #define NANO_BOARD_V2_0 */   /* MPU6050 */
```
Define exactly one to match the board being built for; `game.c` picks the matching driver via `#ifdef IMU_MPU6050` / `#ifdef IMU_BMI270`.

## How to Run
1. Flash the STM32 Nano board with the provided code, having selected the correct `NANO_BOARD_V2_x` macro for your hardware revision.
2. Keep the board still for a moment after power-on — `game_init()` runs a ~200-sample accelerometer calibration pass.
3. Tilt the board to roll the ball around; it bounces off the circular arena boundary.
