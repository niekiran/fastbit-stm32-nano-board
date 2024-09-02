# *011_USB_VCOM_Transmit*

***The USB_Vcom project displays RTC (Real-Time Clock) time using an STM32 nano board. It communicates the time over USB using the CDC (Communication Device Class) interface.***

## Description

* The main functionality of this project is to read the current RTC time and date and display it through a virtual COM port.
* The user button on the STM32 board is used to trigger this display.
* When the button is pressed, the code handles the button press and sends the current RTC time and date information to the USB virtual COM port.

## Edit RTC Time, Date, and Day

Open main.c and locate the MX_RTC_Init function.

```bash
hrtc.Instance = RTC;
hrtc.Init.HourFormat = RTC_HOURFORMAT_12;// Set hourforamt
hrtc.Init.AsynchPrediv = 127;
hrtc.Init.SynchPrediv = 255;
hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
if (HAL_RTC_Init(&hrtc) != HAL_OK)
{
  Error_Handler();
}

sTime.Hours = 0x5;                      // Set hour
sTime.Minutes = 0x30;                    // Set minutes 
sTime.Seconds = 0x0;                     // Set seconds to 0
sTime.TimeFormat = RTC_HOURFORMAT12_PM;  // Set 12-hour format with PM
sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;  
sTime.StoreOperation = RTC_STOREOPERATION_RESET;  

if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
{
  Error_Handler(); 
}

// Set the RTC date
sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;   // Set day 
sDate.Month = RTC_MONTH_JULY;            // Set month 
sDate.Date = 0x3;                        // Set date 
sDate.Year = 0x24;                       // Set year to 2024 (24 in BCD)
if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
{
  Error_Handler();  
}
```

