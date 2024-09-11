/*
 * btn_handler.c
 *
 *  Created on: Jun 15, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "btn_handler.h"
#include "usbd_cdc_if.h"
#include <string.h>
#include <stdio.h>
extern RTC_HandleTypeDef hrtc;

/**
  * @brief  Debounce handler for button input.
  * @param  btn_value: Raw input value of the button (non-zero if pressed, zero if not pressed).
  * @retval Debounced button value (non-zero if debounced as pressed, zero otherwise).
  */
uint8_t handle_user_btn(uint8_t btn_value) {
  static button_state_t btn_sm_state = NOT_PRESSED;
  static uint32_t curr_time = 0;
  uint32_t new_time = HAL_GetTick();

  switch (btn_sm_state) {
    case NOT_PRESSED:
      if (btn_value) {
        btn_sm_state = BOUNCE;
        curr_time = new_time;
      }
      break;
    case BOUNCE:
      if ((new_time - curr_time) >= 100) {
        if (btn_value) {
          btn_sm_state = PRESSED;
          return btn_value;
        } else {
          btn_sm_state = NOT_PRESSED;
        }
      }
      break;
    case PRESSED:
      if (!btn_value) {
        btn_sm_state = BOUNCE;
        curr_time = new_time;
      }else {
        return btn_value;
      }
      break;
  }
  return 0;
}

/**
  * @brief  Read button state.
  * @param  GPIOx: GPIO port.
  * @param  GPIO_Pin: GPIO pin.
  * @retval Button state
  */
uint8_t read_btn_state(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
 return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/**
  * @brief  Converts a numerical representation of the day of the week to its string equivalent.
  * @param  number: Numerical representation of the day of the week (1 for Monday, 2 for Tuesday, etc.).
  * @retval Pointer to a string representing the day of the week.
  */
char* getDayofweek(uint8_t number)
{
  char *weekday[] = { "Monday", "TuesDay", "Wednesday","Thursday","Friday","Saturday","Sunday"};

  return weekday[number-1];
}

/**
  * @brief  Processes the button press and outputs the current time and date via USB.
  * @param  hrtc: Pointer to the RTC handle.
  * @retval None
  */
void process_button_press(RTC_HandleTypeDef *hrtc) {
  RTC_TimeTypeDef RTC_TimeRead;
  RTC_DateTypeDef RTC_DateRead;

  HAL_RTC_GetTime(hrtc, &RTC_TimeRead, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(hrtc, &RTC_DateRead, RTC_FORMAT_BIN);

  printmsg("Current Time is : %02d:%02d:%02d %s\r\n",\
          RTC_TimeRead.Hours,\
          RTC_TimeRead.Minutes,RTC_TimeRead.Seconds,\
         (RTC_TimeRead.TimeFormat == RTC_HOURFORMAT12_AM) ? "PM" : "AM");
  printmsg("Current Date is : %02d-%2d-%2d  <%s> \r\n",\
          RTC_DateRead.Date,\
          RTC_DateRead.Month,\
          2000 + RTC_DateRead.Year,
          getDayofweek(RTC_DateRead.WeekDay));
}

