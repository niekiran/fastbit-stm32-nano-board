# **007_Tilt_LED_Controller**

This program utilizes the onboard MPU6050 sensor of STM32 nano board to monitor orientation data and controls LEDs based on the sensor readings.

## **Overview**

The program reads the pitch (y-axis) and roll (x-axis) orientation data from the MPU6050 sensor and uses this information to control LEDs accordingly.

## **Functionality**

### **LED Control**

- The program monitors the pitch (y-axis) and roll (x-axis) orientation data from the MPU6050 sensor.
- **Pitch Control**:
  - If the pitch value is positive (indicating a forward tilt), LED 2 (green) turns on.
  - If the pitch value is negative (indicating a backward tilt), LED 3 (blue) turns on.
- **Roll Control**:
  - If the roll value is non-zero (indicating a tilt to the left or right), LED 1 (red) turns on.

<img src="007_Tilt_LED_Controller.gif" alt="007_Tilt_LED_Controller" width="450">



