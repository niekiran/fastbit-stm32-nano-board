**005_UART_LED_Control_IT**

This embedded system program is designed to control LEDs via UART commands. 

**Overview:**

The program uses UART (Universal Asynchronous Receiver-Transmitter) communication to receive commands from an external device or terminal. Commands are parsed and processed to control LEDs connected to GPIO pins of the microcontroller.

**Functionality:**

The program transmits a menu of valid commands via UART. Users can interact with the program through a terminal emulator (e.g., Teraterm) or another device connected to the microcontroller's UART interface.

**Send Commands:** Commands are sent in the following format:

- **LEDON [1/2/3]:** Turn on the corresponding LED: red, green, or blue.
- **LEDOFF [1/2/3]:** Turn off the corresponding LED: red, green, or blue.
- **LEDTOGGLE [1/2/3] [delay]:** Toggle the corresponding LED: red, green, or blue with a specified delay in milliseconds.

**Feedback Messages:**

1. If an invalid command is entered, the UART transmits "Invalid Command".
2. If an invalid LED number (not 1, 2, or 3) is provided, the UART transmits "Invalid Argument".

Note: Ensure that the baud rate and other UART settings match the configuration specified in the code (38400 baud, 8 data bits, no parity, 1 stop bit).

