**003_Button_LED_Control**
This project demonstrates controlling LEDs based on button presses using an STM32 microcontroller.

**Overview:**

The main objective of this project is to toggle LEDs in a specific sequence upon button presses. 



**Functionality:**

- **Button Press Detection:** Upon detecting a button press, the program toggles the state of LEDs in a cyclic manner.
- **LED Control:** The LEDs (connected to GPIO pins) are controlled to switch on and off based on the button presses.
- **Debounce Mechanism:** A debounce mechanism is implemented to ensure reliable button press detection. A delay of 100 milliseconds is applied to avoid false triggers.
- **LED Initialization:** The LEDs are initially turned on upon program execution.

**How to Use:**

1. Connect the STM32 microcontroller board to your computer.
1. Open the project in your preferred IDE (e.g., STM32CubeIDE).
1. Build and flash the project onto the microcontroller.
1. Observe the behaviour:
- Upon startup, all LEDs are turned on.
- Press the button connected to GPIO pin PA0 to toggle the LEDs in a specific sequence.
- Each button press turns off one LED at a time (Red -> Green -> Blue). After turning off all LEDs, pressing the button again will turn them all on.
1. Customize or expand the functionality as needed.
