# **012_USB_HID_Mouse**

This project is a simple mouse emulator using a Nano board with an MPU6050 sensor. The board connects via USB and acts as a mouse, using data from the gyroscope and buttons on the board to control mouse movements and clicks.

## **Overview**

### **1. Yaw Control**

Changing the yaw angle of the board moves the cursor horizontally:
- Negative yaw: Moves cursor left.
- Positive yaw: Moves cursor right.

### **2. Pitch Control**

Changing the pitch angle of the board moves the cursor vertically:
- Negative pitch: Moves cursor down.
- Positive pitch: Moves cursor up.

### **3. Buttons**

The left and right mouse buttons are emulated using GPIO pins on the board.
