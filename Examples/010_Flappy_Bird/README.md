# 010_Flappy_Bird

## Project Overview
This project is an implementation of the classic **Flappy Bird** game on an STM32 Nano board, utilizing the **onboard MPU6050 accelerometer** for player control. The game is displayed on a SPI based 1.28" TFT LCD. The player must control a bird sprite to navigate through obstacles by tilting the microcontroller.

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
   * Press the **UserButton** to start a new game.

   ![010_Flappy](media/010_Flappy.jpg)

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
   - 3] **Press the **UserButton** to restart the game.

## How to Run
1] **Flash the STM32 Nano board with the provided code.**

2] **Ensure the TFT LCD is properly connected to the STM32 Nano board.**

3] **Press the **UserButton** to start playing.**




