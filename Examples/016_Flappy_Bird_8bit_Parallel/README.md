# 016_Flappy_Bird_8bit_Parallel

## Project Overview
This project is an implementation of the classic **Flappy Bird** game on an STM32 Nano board, utilizing the **onboard MPU6050 accelerometer** for player control. The game is displayed on a 1.28" TFT LCD. The player must control a bird sprite to navigate through obstacles by tilting the microcontroller.

## Features
- **Platform**: STM32 Nano board.
- **Input**: Onboard MPU6050 accelerometer to control the bird's movement.
- **Display**: Fastbit 1.28" TFT LCD with CTP for game graphics and touch input.
- **Gameplay**: Classic Flappy Bird mechanics, where tilting the board controls the bird's altitude.

## Components
- **STM32 Nano board**: Microcontroller platform running the game logic.
- **Fastbit 1.28" TFT LCD with CTP**: Displays the game graphics, including the bird, obstacles, and score. The capacitive touch panel is used as the start/restart button.

## Gameplay Instructions
1] **Starting the Game**:
   * Tap the **START** icon on TFT LCD to start a new game.
   
2] **Controlling the Bird**:
   - **Tilt the Microcontroller Upwards**: The bird ascends by flapping its wings.
   - **Tilt the Microcontroller Downwards**: The bird descends.

3] **Navigating Obstacles**:
   - Tilt the STM32 Nano board to guide the bird through gaps between the obstacles.
   - Careful and precise tilting is required to prevent collisions.

4] **Scoring**:
   - Each successful passage through a gap increases your score by 1.

5] **Game Over**:
   - The game ends if the bird collides with an obstacle or the ground.
   - Tap the **RESTART** icon to restart the game.

## How to Run
1] **Flash the STM32 Nano board with the provided code.**

2] **Ensure the TFT LCD is properly connected to the STM32 Nano board.**

3] **Tap the **START** icon on the TFT LCD to start playing.**

## 🔗 Product Links

[![product](https://img.shields.io/badge/fastbit_stm32_nano_board-1E90FF?style=for-the-badge&logo=data:image/png;base64,logoColor=white)](https://fastbitembedded.com/products/fastbit-stm32-nano-with-1-28-tft-lcd-display?pr_prod_strat=e5_desc&pr_rec_id=b4332f698&pr_rec_pid=9375081726239&pr_ref_pid=8999282901279&pr_seq=uniform)

![Flappy_bird](016_Flappy_bird.gif)

