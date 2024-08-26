/*
 * sd_card.c
 *
 *  Created on: Jul 11, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

/**
 * @brief  Write data to SD card file.
 * @param  data: Data to write.
 * @retval None
 */
#include "sd_card.h"
#include "ff.h"
#include "main.h"
#include <string.h>

extern FATFS fs;
extern FIL file;
extern const char *filename ;
/**
 * @brief  Check SD card insertion status.
 * @retval true if SD card is inserted, false otherwise.
 */
uint8_t check_sd_card_status(void) {
  HAL_Delay(10);
  SD_status status = HAL_GPIO_ReadPin(SD_DET_GPIO_Port, SD_DET_Pin);

  /* Check if SD card is inserted or not */
  if (status == SD_CARD_INSERTED) {
    return true;
  }
  return false;
}

/**
 * @brief  Sets the global filename variable.
 * @param  new_filename: New filename to set.
 * @retval None
 */
void set_filename(const char *new_filename) {
  filename = new_filename;
}

/**
 * @brief  Writes data to a file on the SD card using the global filename.
 * @param  data: Pointer to the data buffer to write.
 * @param  length: Length of data to write in bytes.
 * @retval None
 */
void write_to_sd_card(const char *data, uint16_t length) {
  FRESULT res;
  UINT bytes_written;
  FIL file;

  res = f_mount(&fs, "", 0);
  if (res != FR_OK) {
    printmsg("Failed to mount file system. Error code: %d\r\n", res);
    return;
  }

  res = f_open(&file, filename, FA_OPEN_ALWAYS | FA_WRITE);
  if (res == FR_OK) {
    // Move to the end of the file
    f_lseek(&file, f_size(&file));
    // Write data to file
    res = f_write(&file, data, length, &bytes_written);

    if (res != FR_OK) {
      printmsg("Failed to write to SD card. Error code: %d\r\n", res);
    }

    f_close(&file);
  } else {
    printmsg("Failed to open SD card file. Error code: %d\r\n", res);
  }
  printmsg("\r\n");
  printmsg("Continue SD card write or\r\n");
  printmsg("press the user button to read from the SD card.\r\n");
  printmsg("\r\n");
  f_mount(NULL, "", 0);
}


/**
 * @brief  Reads and transmits the content of a file from the SD card over UART using the global filename.
 * @retval None
 */
void read_sd_card_file(void) {
  FRESULT res;
  char buffer[30];
  UINT bytes_read;
  FIL file;

  res = f_mount(&fs, "", 0);
  if (res != FR_OK) {
    printmsg("Failed to mount file system. Error code: %d\r\n", res);
    return;
  }

  res = f_open(&file, filename, FA_READ);
  if (res == FR_OK) {
    printmsg("\r\n");

    printmsg("Read data from '%s':\r\n", filename);
    while (f_read(&file, buffer, sizeof(buffer) - 1, &bytes_read) == FR_OK && bytes_read > 0) {
      buffer[bytes_read] = '\0'; // Null-terminate the buffer
      //HAL_UART_Transmit(&huart1, (uint8_t *)buffer, bytes_read, HAL_MAX_DELAY);
      printmsg("%s",buffer );
    }

    f_close(&file);
  } else {
    printmsg("Failed to open SD card file. Error code: %d\r\n", res);
  }
  printmsg("\r\n");

  f_mount(NULL, "", 0);
}


/**
  * @brief  Store data received via UART in SD card.
  * @retval None
  */
void store_received_data(void) {
  if (data_received == true) {
    write_to_sd_card((const char *)processing_buff, strlen((const char *)processing_buff));
    data_received = false;
  }
}

/**
  * @brief  display stored data.
  * @retval None
  */
void display_stored_data(void) {
  if (button_press == true) {
    read_sd_card_file();
    button_press = false;
  }
}
