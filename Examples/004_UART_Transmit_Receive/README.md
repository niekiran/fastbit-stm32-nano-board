**004_UART_Transmit_Receive** 

This project showcases UART communication on an STM32 microcontroller to transmit and receive data using a terminal emulator (e.g., Teraterm). Additionally, it includes functionality for decimal-to-binary conversion.

**Overview:** 

The primary goal of this project is to establish bidirectional communication between the microcontroller and a terminal emulator application, enabling transmission and reception of data. Moreover, it incorporates a feature for converting decimal numbers to binary representation.

**Functionality:**

- UART Configuration: The program configures UART communication to facilitate transmission and reception of data.
- Transmit Data: Predefined messages or prompts are transmitted from the microcontroller to the terminal emulator.
- Receive Data: The microcontroller listens for input from the terminal emulator and processes the received data accordingly.
- Decimal-to-Binary Conversion: Users can enter decimal numbers via the terminal emulator, and the microcontroller converts them to binary representation for display.


Note: Ensure that the baud rate and other UART settings match the configuration specified in the code (38400 baud, 8 data bits, no parity, 1 stop bit).

