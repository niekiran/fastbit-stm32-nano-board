# 010_Flappy_Bird

This project implements the classic Flappy Bird game on an STM32 Nano board. The player controls a bird sprite to navigate through obstacles displayed on a Nano LCD display using an MPU6050 accelerometer.*

## Gameplay

1. Start the game: Press the user button to start the game.
2. Control the bird: Tilt the microcontroller to control the bird's flight. Tilting the device upwards makes the bird flap its wings and ascend, while tilting downwards allows it to descend.
3. Navigate through obstacles: Guide the bird through the gaps between the obstacles by tilting the microcontroller carefully.
4. Scoring: Each successful passage through a gap increases the score by 1.
5. Game over: If the bird collides with an obstacle or the ground, the game ends. Press the user button to restart the game.

Note: We have utilized the GC4901A LCD TFT(SPI) display for the Flappy Bird game.
