/*
 * GC9A01A.h
 *
 *  Created on: Jun 27, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 *      Version: v3.0 High-Speed Configurable Bus Layer
 */

#ifndef INC_GC9A01A_H_
#define INC_GC9A01A_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "main.h"
#include "font.h"

/* -------------------------------------------------------------------------- */
/*                              Display geometry                              */
/* -------------------------------------------------------------------------- */

#define GC9A01A_WIDTH                    240U
#define GC9A01A_HEIGHT                   240U

#define PORTRAIT                         0U
#define LANDSCAPE                        1U

#if (BSP_LCD_ORIENTATION == PORTRAIT)
    #define BSP_LCD_ACTIVE_WIDTH         GC9A01A_WIDTH
    #define BSP_LCD_ACTIVE_HEIGHT        GC9A01A_HEIGHT
#elif (BSP_LCD_ORIENTATION == LANDSCAPE)
    #define BSP_LCD_ACTIVE_WIDTH         GC9A01A_HEIGHT
    #define BSP_LCD_ACTIVE_HEIGHT        GC9A01A_WIDTH
#else
    #define BSP_LCD_ACTIVE_WIDTH         GC9A01A_WIDTH
    #define BSP_LCD_ACTIVE_HEIGHT        GC9A01A_HEIGHT
#endif

/* -------------------------------------------------------------------------- */
/*                         Interface / transfer config                         */
/* -------------------------------------------------------------------------- */

#define GC9A01A_IF_SPI                   1
#define GC9A01A_IF_PARALLEL              2

#ifndef GC9A01A_INTERFACE_MODE
#define GC9A01A_INTERFACE_MODE           GC9A01A_IF_SPI
#endif

#define GC9A01A_CS_MODE_TOGGLE           1
#define GC9A01A_CS_MODE_HOLD_LOW         2

#ifndef GC9A01A_CS_MODE
#define GC9A01A_CS_MODE                  GC9A01A_CS_MODE_HOLD_LOW
#endif

#ifndef GC9A01A_USE_DMA
#define GC9A01A_USE_DMA                  0
#endif

#ifndef GC9A01A_LINE_BUF_PIXELS
#define GC9A01A_LINE_BUF_PIXELS          240U
#endif

#ifndef GC9A01A_SPI_CHUNK_SIZE
#define GC9A01A_SPI_CHUNK_SIZE           65535U
#endif

/* -------------------------------------------------------------------------- */
/*                              GC9A01A commands                              */
/* -------------------------------------------------------------------------- */

#define GC9A01A_NOP                      0x00U
#define GC9A01A_SWRESET                  0x01U
#define GC9A01A_RDDID                    0x04U
#define GC9A01A_RDDST                    0x09U

#define GC9A01A_SLPIN                    0x10U
#define GC9A01A_SLPOUT                   0x11U
#define GC9A01A_PTLON                    0x12U
#define GC9A01A_NORON                    0x13U

#define GC9A01A_INVOFF                   0x20U
#define GC9A01A_INVON                    0x21U
#define GC9A01A_DISPOFF                  0x28U
#define GC9A01A_DISPON                   0x29U

#define GC9A01A_CASET                    0x2AU
#define GC9A01A_RASET                    0x2BU
#define GC9A01A_RAMWR                    0x2CU

#define GC9A01A_MADCTL                   0x36U
#define GC9A01A_COLMOD                   0x3AU

#define GC9A01A_DISP_CTRL                0xB6U

#define GC9A01A1_POWER1                  0xC1U
#define GC9A01A1_POWER2                  0xC3U
#define GC9A01A1_POWER3                  0xC4U
#define GC9A01A1_POWER4                  0xC9U
#define GC9A01A1_POWER7                  0xA7U

#define GC9A01A_FRAMERATE                0xE8U

#define GC9A01A_INREGEN1                 0xFEU
#define GC9A01A_INREGEN2                 0xEFU

#define GC9A01A_GAMMA1                   0xF0U
#define GC9A01A_GAMMA2                   0xF1U
#define GC9A01A_GAMMA3                   0xF2U
#define GC9A01A_GAMMA4                   0xF3U

#define GC9A01A_TEOFF                    0x34U
#define GC9A01A_TEON                     0x35U

/* -------------------------------------------------------------------------- */
/*                           MADCTL register bits                             */
/* -------------------------------------------------------------------------- */

#define MADCTL_MY                        0x80U
#define MADCTL_MX                        0x40U
#define MADCTL_MV                        0x20U
#define MADCTL_ML                        0x10U
#define MADCTL_BGR                       0x08U
#define MADCTL_MH                        0x04U
#define MADCTL_RGB                       0x00U

/* -------------------------------------------------------------------------- */
/*                              Color definitions                             */
/* -------------------------------------------------------------------------- */

#define BLACK                            0x0000U
#define NAVY                             0x000FU
#define DARKGREEN                        0x03E0U
#define DARKCYAN                         0x03EFU
#define MAROON                           0x7800U
#define PURPLE                           0x780FU
#define OLIVE                            0x7BE0U
#define LIGHTGREY                        0xC618U
#define DARKGREY                         0x7BEFU
#define BLUE                             0x001FU
#define GREEN                            0x07E0U
#define CYAN                             0x07FFU
#define RED                              0xF800U
#define MAGENTA                          0xF81FU
#define YELLOW                           0xFFE0U
#define WHITE                            0xFFFFU
#define ORANGE                           0xFC00U
#define GREENYELLOW                      0xAFE5U
#define PINK                             0xF81FU
#define VIOLET                           0x801FU
#define INDIGO                           0x480FU

#define GC9A01A_COLOR565(r, g, b) \
    ((((r) & 0xF8U) << 8) | (((g) & 0xFCU) << 3) | (((b) & 0xF8U) >> 3))

/* -------------------------------------------------------------------------- */
/*                              Pin configuration                             */
/* -------------------------------------------------------------------------- */

#define NEW

#ifdef OLD
    #define LCD_RST_Pin                  GPIO_PIN_3
    #define LCD_RST_GPIO_Port            GPIOA
    #define LCD_CSX_Pin                  GPIO_PIN_4
    #define LCD_CSX_GPIO_Port            GPIOA
    #define LCD_DCX_Pin                  GPIO_PIN_6
    #define LCD_DCX_GPIO_Port            GPIOA
#elif defined(NEW)
    #define LCD_RST_Pin                  GPIO_PIN_8
    #define LCD_RST_GPIO_Port            GPIOB
    #define LCD_CSX_Pin                  GPIO_PIN_3
    #define LCD_CSX_GPIO_Port            GPIOA
    #define LCD_DCX_Pin                  GPIO_PIN_1
    #define LCD_DCX_GPIO_Port            GPIOB
#endif

/* ---------------------------- Fast GPIO control ---------------------------- */
/* BSRR write is much faster than HAL_GPIO_WritePin() */

#define GC9A01A_DC_CMD()                 (LCD_DCX_GPIO_Port->BSRR = ((uint32_t)LCD_DCX_Pin << 16U))
#define GC9A01A_DC_DATA()                (LCD_DCX_GPIO_Port->BSRR = (uint32_t)LCD_DCX_Pin)

#define GC9A01A_CS_LOW()                 (LCD_CSX_GPIO_Port->BSRR = ((uint32_t)LCD_CSX_Pin << 16U))
#define GC9A01A_CS_HIGH()                (LCD_CSX_GPIO_Port->BSRR = (uint32_t)LCD_CSX_Pin)

#define GC9A01A_RST_LOW()                (LCD_RST_GPIO_Port->BSRR = ((uint32_t)LCD_RST_Pin << 16U))
#define GC9A01A_RST_HIGH()               (LCD_RST_GPIO_Port->BSRR = (uint32_t)LCD_RST_Pin)

/* -------------------------------------------------------------------------- */
/*                    Dummy parallel interface pin placeholders                */
/* -------------------------------------------------------------------------- */
/*
 * These are placeholders only.
 * If later you move to 8-bit parallel LCD mode, define real ports/pins here
 * and implement gc9a01a_bus_write_bytes() in .c for parallel protocol.
 */

#ifndef LCD_WR_Pin
#define LCD_WR_Pin                       GPIO_PIN_0
#endif
#ifndef LCD_WR_GPIO_Port
#define LCD_WR_GPIO_Port                 GPIOA
#endif

#ifndef LCD_RD_Pin
#define LCD_RD_Pin                       GPIO_PIN_0
#endif
#ifndef LCD_RD_GPIO_Port
#define LCD_RD_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D0_Pin
#define LCD_D0_Pin                       GPIO_PIN_0
#endif
#ifndef LCD_D0_GPIO_Port
#define LCD_D0_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D1_Pin
#define LCD_D1_Pin                       GPIO_PIN_1
#endif
#ifndef LCD_D1_GPIO_Port
#define LCD_D1_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D2_Pin
#define LCD_D2_Pin                       GPIO_PIN_2
#endif
#ifndef LCD_D2_GPIO_Port
#define LCD_D2_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D3_Pin
#define LCD_D3_Pin                       GPIO_PIN_3
#endif
#ifndef LCD_D3_GPIO_Port
#define LCD_D3_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D4_Pin
#define LCD_D4_Pin                       GPIO_PIN_4
#endif
#ifndef LCD_D4_GPIO_Port
#define LCD_D4_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D5_Pin
#define LCD_D5_Pin                       GPIO_PIN_5
#endif
#ifndef LCD_D5_GPIO_Port
#define LCD_D5_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D6_Pin
#define LCD_D6_Pin                       GPIO_PIN_6
#endif
#ifndef LCD_D6_GPIO_Port
#define LCD_D6_GPIO_Port                 GPIOA
#endif

#ifndef LCD_D7_Pin
#define LCD_D7_Pin                       GPIO_PIN_7
#endif
#ifndef LCD_D7_GPIO_Port
#define LCD_D7_GPIO_Port                 GPIOA
#endif

#define GC9A01A_WR_LOW()                 (LCD_WR_GPIO_Port->BSRR = ((uint32_t)LCD_WR_Pin << 16U))
#define GC9A01A_WR_HIGH()                (LCD_WR_GPIO_Port->BSRR = (uint32_t)LCD_WR_Pin)

#define GC9A01A_RD_LOW()                 (LCD_RD_GPIO_Port->BSRR = ((uint32_t)LCD_RD_Pin << 16U))
#define GC9A01A_RD_HIGH()                (LCD_RD_GPIO_Port->BSRR = (uint32_t)LCD_RD_Pin)

/* -------------------------------------------------------------------------- */
/*                              External handles                              */
/* -------------------------------------------------------------------------- */

extern SPI_HandleTypeDef hspi1;

/* -------------------------------------------------------------------------- */
/*                              Public API                                    */
/* -------------------------------------------------------------------------- */

void bsp_lcd_init(void);

void gc9a01a_set_orientation(uint8_t orientation);
void gc9a01a_set_address_window(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);

void gc9a01a_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void gc9a01a_fill_rect(uint16_t x, uint16_t w, uint16_t y, uint16_t h, uint16_t color);
void gc9a01a_fill_screen(uint16_t color);
void gc9a01a_fill_circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color);

void gc9a01a_write_string(uint16_t x,
                          uint16_t y,
                          const char *str,
                          FontDef font,
                          uint16_t color,
                          uint16_t bgcolor);

void gc9a01a_draw_image(uint16_t x,
                        uint16_t w,
                        uint16_t y,
                        uint16_t h,
                        const uint16_t *data);

void gc9a01a_lcd_fill_image(const uint16_t *data);
void gc9a01a_invert_colors(bool invert);

#ifdef __cplusplus
}
#endif

#endif /* INC_GC9A01A_H_ */
