/*
 * GC9A01A.h
 *
 *  Created on: Jun 27, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_GC9A01A_H_
#define INC_GC9A01A_H_

#include <font.h>
#include <stdbool.h>

#define GC9A01A_WIDTH   240
#define GC9A01A_HEIGHT  240

#define PORTRAIT        0
#define LANDSCAPE       1

#if(BSP_LCD_ORIENTATION == PORTRAIT)
    #define  BSP_LCD_ACTIVE_WIDTH           GC9A01A_WIDTH
    #define  BSP_LCD_ACTIVE_HEIGHT          GC9A01A_HEIGHT
#elif(BSP_LCD_ORIENTATION == LANDSCAPE)
    #define  BSP_LCD_ACTIVE_WIDTH           GC9A01A_HEIGHT
    #define  BSP_LCD_ACTIVE_HEIGHT          GC9A01A_WIDTH
#endif

/********************** GC9A01A commands **********************/
#define GC9A01A_NOP             0x00  ///< No operation
#define GC9A01A_SWRESET         0x01  ///< Software Reset (maybe, not documented)
#define GC9A01A_RDDID           0x04  ///< Read display identification information
#define GC9A01A_RDDST           0x09  ///< Read Display Status

#define GC9A01A_SLPIN           0x10  ///< Enter Sleep Mode
#define GC9A01A_SLPOUT          0x11  ///< Sleep Out
#define GC9A01A_PTLON           0x12  ///< Partial Mode ON
#define GC9A01A_NORON           0x13  ///< Normal Display Mode ON

#define GC9A01A_INVOFF          0x20  ///< Display Inversion OFF
#define GC9A01A_INVON           0x21  ///< Display Inversion ON
#define GC9A01A_DISPOFF         0x28  ///< Display OFF
#define GC9A01A_DISPON          0x29  ///< Display ON

#define GC9A01A_CASET           0x2A  ///< Column Address Set
#define GC9A01A_RASET           0x2B  ///< Row Address Set
#define GC9A01A_RAMWR           0x2C  ///< Memory Write

#define GC9A01A_MADCTL          0x36  ///< Memory Access Control
#define GC9A01A_COLMOD          0x3A  ///< Pixel Format Set

#define GC9A01A1_POWER1         0xC1  ///< Power Control 1
#define GC9A01A1_POWER2         0xC3  ///< Power Control 2
#define GC9A01A1_POWER3         0xC4  ///< Power Control 3
#define GC9A01A1_POWER4         0xC9  ///< Power Control 4
#define GC9A01A1_POWER7         0xA7  ///< Power Control 7

#define GC9A01A_FRAMERATE       0xE8  ///< Frame rate control

#define GC9A01A_INREGEN1        0xFE  ///< Inter register enable 1
#define GC9A01A_INREGEN2        0xEF  ///< Inter register enable 2

#define GC9A01A_GAMMA1          0xF0  ///< Set gamma 1
#define GC9A01A_GAMMA2          0xF1  ///< Set gamma 2
#define GC9A01A_GAMMA3          0xF2  ///< Set gamma 3
#define GC9A01A_GAMMA4          0xF3  ///< Set gamma 4

#define GC9A01A_TEOFF           0x34  ///< Tearing Effect Line OFF
#define GC9A01A_TEON            0x35  ///< Tearing Effect Line ON

#define GC9A01A_DISP_CTRL       0xB6  ///<Display Function Control

#define MADCTL_MY               0x80  ///< Bottom to top
#define MADCTL_MX               0x40  ///< Right to left
#define MADCTL_MV               0x20  ///< Reverse Mode
#define MADCTL_ML               0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB              0x00  ///< Red-Green-Blue pixel order
#define MADCTL_BGR              0x08  ///< Blue-Green-Red pixel order
#define MADCTL_MH               0x04  ///< LCD refresh right to left


/********************** Color definitions **********************/
#define VIOLET                  0x801F  ///< RGB: 148, 0, 211
#define INDIGO                  0x480F  ///< RGB: 75, 0, 130
#define BLUE                    0x001F  ///< RGB: 0, 0, 255
#define GREEN                   0x07E0  ///< RGB: 0, 255, 0
#define YELLOW                  0xFFE0  ///< RGB: 255, 255, 0
#define ORANGE                  0xFC00  ///< RGB: 255, 165, 0
#define RED                     0xF800  ///< RGB: 255, 0, 0
#define WHITE                   0xFFFF  ///< RGB: 255, 255, 255
#define BLACK                   0x0000  ///< RGB: 0, 0, 0
#define NAVY                    0x000F  ///< RGB: 0, 0, 128
#define DARKGREEN               0x03E0  ///< RGB: 0, 128, 0
#define DARKCYAN                0x03EF  ///< RGB: 0, 128, 128
#define MAROON                  0x7800  ///< RGB: 128, 0, 0
#define PURPLE                  0x780F  ///< RGB: 128, 0, 128
#define OLIVE                   0x7BE0  ///< RGB: 128, 128, 0
#define LIGHTGREY               0xC618  ///< RGB: 192, 192, 192
#define DARKGREY                0x7BEF  ///< RGB: 128, 128, 128
#define CYAN                    0x07FF  ///< RGB: 0, 255, 255
#define MAGENTA                 0xF81F  ///< RGB: 255, 0, 255
#define GREENYELLOW             0xAFE5  ///< RGB: 173, 255, 47
#define PINK                    0xF81F  ///< RGB: 255, 0, 255
#define GC9A01A_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))


#define GC9A01A_BL_ON           HAL_GPIO_WritePin(BL_A_GPIO_Port, BL_A_Pin, GPIO_PIN_SET)

#define GC9A01A_DC_CMD          HAL_GPIO_WritePin(DCX_GPIO_Port, DCX_Pin, GPIO_PIN_RESET)
#define GC9A01A_DC_DATA         HAL_GPIO_WritePin(DCX_GPIO_Port, DCX_Pin, GPIO_PIN_SET)

#define GC9A01A_CS_LOW          HAL_GPIO_WritePin(LCD_CSX_GPIO_Port, LCD_CSX_Pin, GPIO_PIN_RESET)
#define GC9A01A_CS_HIGH         HAL_GPIO_WritePin(LCD_CSX_GPIO_Port, LCD_CSX_Pin, GPIO_PIN_SET)

#define GC9A01A_RST_LOW         HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET)
#define GC9A01A_RST_HIGH        HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET)

#define GC9A01A_RD_LOW          HAL_GPIO_WritePin(LCD_RDX_GPIO_Port, LCD_RDX_Pin, GPIO_PIN_RESET)
#define GC9A01A_RD_HIGH         HAL_GPIO_WritePin(LCD_RDX_GPIO_Port, LCD_RDX_Pin, GPIO_PIN_SET)
#define GC9A01A_RD_STROBE       { GC9A01A_RD_LOW;  GC9A01A_RD_HIGH; }

#define GC9A01A_WR_LOW          HAL_GPIO_WritePin(WRD_GPIO_Port, WRD_Pin, GPIO_PIN_RESET)
#define GC9A01A_WR_HIGH         HAL_GPIO_WritePin(WRD_GPIO_Port, WRD_Pin, GPIO_PIN_SET)
#define GC9A01A_WR_STROBE       { GC9A01A_WR_LOW;  GC9A01A_WR_HIGH; }

#define GC9A01A_TE_LOW          HAL_GPIO_WritePin(LCD_TE_GPIO_Port, LCD_TE_Pin, GPIO_PIN_RESET)

#define GC9A01A_WRITE_8BIT(d)   { \
  HAL_GPIO_WritePin(BD0_GPIO_Port, BD0_Pin, (d& (1 << 0)) >> 0);\
  HAL_GPIO_WritePin(BD1_GPIO_Port, BD1_Pin, (d& (1 << 1)) >> 1);\
  HAL_GPIO_WritePin(BD2_GPIO_Port, BD2_Pin, (d& (1 << 2)) >> 2);\
  HAL_GPIO_WritePin(BD3_GPIO_Port, BD3_Pin, (d& (1 << 3)) >> 3);\
  HAL_GPIO_WritePin(BD4_GPIO_Port, BD4_Pin, (d& (1 << 4)) >> 4);\
  HAL_GPIO_WritePin(BD5_GPIO_Port, BD5_Pin, (d& (1 << 5)) >> 5);\
  HAL_GPIO_WritePin(BD6_GPIO_Port, BD6_Pin, (d& (1 << 6)) >> 6);\
  HAL_GPIO_WritePin(BD7_GPIO_Port, BD7_Pin, (d& (1 << 7)) >> 7);\
  GC9A01A_WR_STROBE; \
}

void bsp_lcd_init(void);
void gc9a01a_set_orientation(uint8_t orientation);
void gc9a01a_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void gc9a01a_set_address_window(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);
void gc9a01a_write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void gc9a01a_fill_rect(uint16_t x, uint16_t w, uint16_t y, uint16_t h, uint16_t color);
void gc9a01a_fill_screen(uint16_t color);
void gc9a01a_draw_image(uint16_t x, uint16_t w, uint16_t y, uint16_t h, const uint16_t* data);
void gc9a01a_lcd_fill_image(const uint16_t* data);
void gc9a01a_invert_colors(bool invert);

#endif /* INC_GC9A01A_H_ */
