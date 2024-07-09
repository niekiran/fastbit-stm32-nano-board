/*
 * mouse_handler.c
 *
 *  Created on: Jun 11, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "mouse_handler.h"
#include "main.h"

/**
  * @brief  Debounce handler for mouse button input.
  * @param  btn_value: Raw input value of the button (non-zero if pressed, zero if not pressed).
  * @retval Debounced button value (non-zero if debounced as pressed, zero otherwise).
  */
uint8_t handle_mouse_button(uint8_t btn_value) {
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
      if ((new_time - curr_time) >= 50) {
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
  * @brief  Updates the mouse HID buttons based on the button pad value.
  * @param  mouse_hid: Pointer to the mouse HID structure.
  * @param  btn_pad_value: Value representing the state of the buttons.
  *                        Bit 0 corresponds to the left button, and
  *                        bit 1 corresponds to the right button.
  * @retval None
  */
void update_btn_state(mouseHID *mouse_hid, uint8_t btn_pad_value)
{
  if (btn_pad_value & 0x01) {
      mouse_hid->button |= 0x01;
  } else {
      mouse_hid->button &= ~0x01;
  }

  if (btn_pad_value & 0x02) {
      mouse_hid->button |= 0x02;
  } else {
      mouse_hid->button &= ~0x02;
  }
}

/**
  * @brief  Update mouse movement based on gyroscope.
  * @param  gyroz: Gyroscope value for Z-axis.
  * @param  gyroy: Gyroscope value for Y-axis.
  * @param  mouse_hid: Pointer to the mouse HID structure.
  * @retval None
  */
void move_cursor(double gyroz, double gyroy, mouseHID *mouse_hid)
{
  int scaling_factor = 20;
  mouse_hid->mouse_x = -(gyroz / scaling_factor);
  mouse_hid->mouse_y = -(gyroy / scaling_factor);
}
