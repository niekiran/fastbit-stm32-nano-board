**012_USB_HID_Mouse**

This project is a simple mouse emulator based on a nano board with an MPU6050 sensor placed on the board. The MCU USB is configured in FS-Mode as an HID-Class Device, sending a mouse report every 2 ms. The report is based on data from the gyroscope, transmitted via I2C, and the state of GPIO pins used as the mouse's left and right buttons.

**1.Yaw Control:** Changing the yaw angle of the board moves the cursor horizontally (negative - left, positive - right).
**2.Pitch Control:** Changing the pitch angle of the board moves the cursor vertically (negative - down, positive - up).
**3.Buttons:** The left and right buttons on the mouse are emulated using GPIO pins.