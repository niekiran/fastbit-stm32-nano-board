
# 017_SD_Card_Read_Write

This project demonstrates how to use the Fastbit STM32 Nano board to read from and write to an SD card. Data is received via UART, written to the SD card, and read back when the user button is pressed.


## Overview

**1. SD Card Detection:** Checks if the SD card is connected and prompts the user if it is not.

*Note: You can use any serial monitor to view data transmission and reception. I am using Hercules  SETUP utility.*

![alt text](media/Sd\_card\_not\_connected.png)

**2. Data Entry and Storage:** Receives data from the UART interface, writes it to the SD card.

File Setup: Set the filename in main.c where data will be stored:

```bash
   set_filename("write.txt");
```


set_filename("write.txt");

![alt text](media/write\_sd\_card.png)

**3. Data Transmission:** Upon user button press, the stored data is transmitted over UART.

![alt text](media/read\_sd\_card.png)