/*
 * GC9A01A.c
 *
 *  Created on: Jul 9, 2025
 *      Author: Shreyas Acharya, Fastbit Embedded
 *      Version: v3.0 High-Speed Configurable Bus Layer
 */

#include "gc9a01a.h"
#include "main.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* -------------------------------------------------------------------------- */
/*                             Build-time options                             */
/* -------------------------------------------------------------------------- */

#ifndef GC9A01A_IF_SPI
#define GC9A01A_IF_SPI                    1
#endif

#ifndef GC9A01A_IF_PARALLEL
#define GC9A01A_IF_PARALLEL               2
#endif

#ifndef GC9A01A_INTERFACE_MODE
#define GC9A01A_INTERFACE_MODE            GC9A01A_IF_SPI
#endif

#ifndef GC9A01A_CS_MODE_TOGGLE
#define GC9A01A_CS_MODE_TOGGLE            1
#endif

#ifndef GC9A01A_CS_MODE_HOLD_LOW
#define GC9A01A_CS_MODE_HOLD_LOW          2
#endif

#ifndef GC9A01A_CS_MODE
#define GC9A01A_CS_MODE                   GC9A01A_CS_MODE_HOLD_LOW
#endif

#ifndef GC9A01A_USE_DMA
#define GC9A01A_USE_DMA                   0
#endif

#ifndef GC9A01A_LINE_BUF_PIXELS
#define GC9A01A_LINE_BUF_PIXELS           240U
#endif

#ifndef GC9A01A_SPI_CHUNK_SIZE
#define GC9A01A_SPI_CHUNK_SIZE            65535U
#endif

/* -------------------------------------------------------------------------- */
/*                              Static storage                                */
/* -------------------------------------------------------------------------- */

static uint8_t s_line_buf[GC9A01A_LINE_BUF_PIXELS * 2U];
static uint8_t s_cs_held_low = 0U;

/* -------------------------------------------------------------------------- */
/*                          Internal low-level helpers                        */
/* -------------------------------------------------------------------------- */

static inline void gc9a01a_cs_low_internal(void)
{
#if (GC9A01A_CS_MODE == GC9A01A_CS_MODE_HOLD_LOW)
    if (s_cs_held_low == 0U) {
        GC9A01A_CS_LOW();
        s_cs_held_low = 1U;
    }
#else
    GC9A01A_CS_LOW();
#endif
}

static inline void gc9a01a_cs_high_internal(void)
{
#if (GC9A01A_CS_MODE == GC9A01A_CS_MODE_HOLD_LOW)
    /* Intentionally do nothing while bus is held active */
#else
    GC9A01A_CS_HIGH();
#endif
}

static inline void gc9a01a_dc_command(void)
{
    GC9A01A_DC_CMD();
}

static inline void gc9a01a_dc_data(void)
{
    GC9A01A_DC_DATA();
}

static inline void gc9a01a_begin_transaction(void)
{
    gc9a01a_cs_low_internal();
}

static inline void gc9a01a_end_transaction(void)
{
    gc9a01a_cs_high_internal();
}

static void gc9a01a_hw_reset(void)
{
    GC9A01A_RST_LOW();
    HAL_Delay(50);
    GC9A01A_RST_HIGH();
    HAL_Delay(120);
}

/* -------------------------------------------------------------------------- */
/*                              Bus primitives                                */
/* -------------------------------------------------------------------------- */

#if (GC9A01A_INTERFACE_MODE == GC9A01A_IF_SPI)

static void gc9a01a_bus_write_bytes(const uint8_t *data, size_t len)
{
    while (len > 0U) {
        uint16_t chunk;

        chunk = (len > GC9A01A_SPI_CHUNK_SIZE) ? (uint16_t)GC9A01A_SPI_CHUNK_SIZE : (uint16_t)len;

#if (GC9A01A_USE_DMA == 1)
        if (HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)data, chunk) != HAL_OK) {
            return;
        }

        while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY) {
        }
#else
        if (HAL_SPI_Transmit(&hspi1, (uint8_t *)data, chunk, HAL_MAX_DELAY) != HAL_OK) {
            return;
        }
#endif

        data += chunk;
        len  -= chunk;
    }
}

#elif (GC9A01A_INTERFACE_MODE == GC9A01A_IF_PARALLEL)

/*
 * Dummy parallel mode placeholder.
 * Replace this with real 8080/6800-style bus writes later.
 */
static void gc9a01a_bus_write_bytes(const uint8_t *data, size_t len)
{
    (void)data;
    (void)len;

    /*
     * Example future implementation idea:
     * 1. Put byte on D0..D7 pins
     * 2. Pulse WR low
     * 3. Repeat for all bytes
     */
}

#else
#error "Unsupported GC9A01A_INTERFACE_MODE"
#endif

static void gc9a01a_write_cmd_only(uint8_t cmd)
{
    gc9a01a_dc_command();
    gc9a01a_bus_write_bytes(&cmd, 1U);
}

static void gc9a01a_write_data_only(const uint8_t *buff, size_t buff_size)
{
    gc9a01a_dc_data();
    gc9a01a_bus_write_bytes(buff, buff_size);
}

static void gc9a01a_write_cmd(uint8_t cmd)
{
    gc9a01a_begin_transaction();
    gc9a01a_write_cmd_only(cmd);
    gc9a01a_end_transaction();
}

static void gc9a01a_write_data(const uint8_t *buff, size_t buff_size)
{
    gc9a01a_begin_transaction();
    gc9a01a_write_data_only(buff, buff_size);
    gc9a01a_end_transaction();
}

static void gc9a01a_write_u16_color(uint16_t color)
{
    uint8_t data[2];

    data[0] = (uint8_t)(color >> 8);
    data[1] = (uint8_t)(color & 0xFF);

    gc9a01a_begin_transaction();
    gc9a01a_write_data_only(data, sizeof(data));
    gc9a01a_end_transaction();
}

static void gc9a01a_prepare_color_line(uint16_t color, uint16_t pixels)
{
    uint8_t hi;
    uint8_t lo;

    if (pixels > GC9A01A_LINE_BUF_PIXELS) {
        pixels = GC9A01A_LINE_BUF_PIXELS;
    }

    hi = (uint8_t)(color >> 8);
    lo = (uint8_t)(color & 0xFF);

    for (uint16_t i = 0U; i < pixels; i++) {
        s_line_buf[(2U * i)]     = hi;
        s_line_buf[(2U * i) + 1] = lo;
    }
}

/* -------------------------------------------------------------------------- */
/*                           Address window control                           */
/* -------------------------------------------------------------------------- */

void gc9a01a_set_address_window(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
    uint8_t data[4];

    gc9a01a_begin_transaction();

    gc9a01a_write_cmd_only(GC9A01A_CASET);
    data[0] = (uint8_t)(x0 >> 8);
    data[1] = (uint8_t)(x0 & 0xFF);
    data[2] = (uint8_t)(x1 >> 8);
    data[3] = (uint8_t)(x1 & 0xFF);
    gc9a01a_write_data_only(data, sizeof(data));

    gc9a01a_write_cmd_only(GC9A01A_RASET);
    data[0] = (uint8_t)(y0 >> 8);
    data[1] = (uint8_t)(y0 & 0xFF);
    data[2] = (uint8_t)(y1 >> 8);
    data[3] = (uint8_t)(y1 & 0xFF);
    gc9a01a_write_data_only(data, sizeof(data));

    gc9a01a_write_cmd_only(GC9A01A_RAMWR);

    gc9a01a_end_transaction();
}

static void gc9a01a_set_address_window_stream(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
    uint8_t data[4];

    gc9a01a_write_cmd_only(GC9A01A_CASET);
    data[0] = (uint8_t)(x0 >> 8);
    data[1] = (uint8_t)(x0 & 0xFF);
    data[2] = (uint8_t)(x1 >> 8);
    data[3] = (uint8_t)(x1 & 0xFF);
    gc9a01a_write_data_only(data, sizeof(data));

    gc9a01a_write_cmd_only(GC9A01A_RASET);
    data[0] = (uint8_t)(y0 >> 8);
    data[1] = (uint8_t)(y0 & 0xFF);
    data[2] = (uint8_t)(y1 >> 8);
    data[3] = (uint8_t)(y1 & 0xFF);
    gc9a01a_write_data_only(data, sizeof(data));

    gc9a01a_write_cmd_only(GC9A01A_RAMWR);
}

/* -------------------------------------------------------------------------- */
/*                             LCD init sequence                              */
/* -------------------------------------------------------------------------- */

static void gc9a01a_init_sequence(void)
{
    uint8_t params[15];

    gc9a01a_begin_transaction();

    gc9a01a_write_cmd_only(GC9A01A_INREGEN1);
    gc9a01a_write_cmd_only(GC9A01A_INREGEN2);

    params[0] = 0x08; params[1] = 0x09; params[2] = 0x14; params[3] = 0x08;
    gc9a01a_write_cmd_only(0xB5);
    gc9a01a_write_data_only(params, 4);

    params[0] = 0x00; params[1] = 0x00;
    gc9a01a_write_cmd_only(GC9A01A_DISP_CTRL);
    gc9a01a_write_data_only(params, 2);

    params[0] = 0x48;
    gc9a01a_write_cmd_only(GC9A01A_MADCTL);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x05;
    gc9a01a_write_cmd_only(GC9A01A_COLMOD);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x01;
    gc9a01a_write_cmd_only(0xBA);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x1A;
    gc9a01a_write_cmd_only(GC9A01A1_POWER2);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x1A;
    gc9a01a_write_cmd_only(GC9A01A1_POWER3);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x25;
    gc9a01a_write_cmd_only(GC9A01A1_POWER4);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x45; params[1] = 0x09; params[2] = 0x08; params[3] = 0x08; params[4] = 0x26; params[5] = 0x2A;
    gc9a01a_write_cmd_only(GC9A01A_GAMMA1);
    gc9a01a_write_data_only(params, 6);

    params[0] = 0x43; params[1] = 0x70; params[2] = 0x72; params[3] = 0x36; params[4] = 0x37; params[5] = 0x6F;
    gc9a01a_write_cmd_only(GC9A01A_GAMMA2);
    gc9a01a_write_data_only(params, 6);

    params[0] = 0x45; params[1] = 0x09; params[2] = 0x08; params[3] = 0x08; params[4] = 0x26; params[5] = 0x2A;
    gc9a01a_write_cmd_only(GC9A01A_GAMMA3);
    gc9a01a_write_data_only(params, 6);

    params[0] = 0x43; params[1] = 0x70; params[2] = 0x72; params[3] = 0x36; params[4] = 0x37; params[5] = 0x6F;
    gc9a01a_write_cmd_only(GC9A01A_GAMMA4);
    gc9a01a_write_data_only(params, 6);

    params[0] = 0x34;
    gc9a01a_write_cmd_only(GC9A01A_FRAMERATE);
    gc9a01a_write_data_only(params, 1);

    params[0] = 0x38; params[1] = 0x0B; params[2] = 0x6D; params[3] = 0x6D; params[4] = 0x39; params[5] = 0xF0; params[6] = 0x6D; params[7] = 0x6D;
    gc9a01a_write_cmd_only(0x60);
    gc9a01a_write_data_only(params, 8);

    params[0] = 0x38; params[1] = 0xF4; params[2] = 0x6D; params[3] = 0x6D; params[4] = 0x38; params[5] = 0xF7; params[6] = 0xF7; params[7] = 0x6D; params[8] = 0x6D;
    gc9a01a_write_cmd_only(0x61);
    gc9a01a_write_data_only(params, 9);

    params[0] = 0x38; params[1] = 0x0D; params[2] = 0x71; params[3] = 0xED; params[4] = 0x70; params[5] = 0x70;
    params[6] = 0x38; params[7] = 0x0F; params[8] = 0x71; params[9] = 0xEF; params[10] = 0x70; params[11] = 0x70;
    gc9a01a_write_cmd_only(0x62);
    gc9a01a_write_data_only(params, 12);

    params[0] = 0x38; params[1] = 0x11; params[2] = 0x71; params[3] = 0xF1; params[4] = 0x70; params[5] = 0x70;
    params[6] = 0x38; params[7] = 0x13; params[8] = 0x71; params[9] = 0xF3; params[10] = 0x70; params[11] = 0x70;
    gc9a01a_write_cmd_only(0x63);
    gc9a01a_write_data_only(params, 12);

    params[0] = 0x28; params[1] = 0x29; params[2] = 0xF1; params[3] = 0x01; params[4] = 0xF1; params[5] = 0x00; params[6] = 0x07;
    gc9a01a_write_cmd_only(0x64);
    gc9a01a_write_data_only(params, 7);

    params[0] = 0x3C; params[1] = 0x00; params[2] = 0xCD; params[3] = 0x67; params[4] = 0x45; params[5] = 0x45; params[6] = 0x10; params[7] = 0x00; params[8] = 0x00; params[9] = 0x00;
    gc9a01a_write_cmd_only(0x66);
    gc9a01a_write_data_only(params, 10);

    params[0] = 0x00; params[1] = 0x3C; params[2] = 0x00; params[3] = 0x00; params[4] = 0x00; params[5] = 0x01; params[6] = 0x54; params[7] = 0x10; params[8] = 0x32; params[9] = 0x98;
    gc9a01a_write_cmd_only(0x67);
    gc9a01a_write_data_only(params, 10);

    params[0] = 0x10; params[1] = 0x80; params[2] = 0x80; params[3] = 0x00; params[4] = 0x00; params[5] = 0x4E; params[6] = 0x00;
    gc9a01a_write_cmd_only(0x74);
    gc9a01a_write_data_only(params, 7);

    params[0] = 0x3E; params[1] = 0x07;
    gc9a01a_write_cmd_only(0x98);
    gc9a01a_write_data_only(params, 2);

    params[0] = 0x3E; params[1] = 0x07;
    gc9a01a_write_cmd_only(0x99);
    gc9a01a_write_data_only(params, 2);

    params[0] = 0x00;
    gc9a01a_write_cmd_only(GC9A01A_TEON);
    gc9a01a_write_data_only(params, 1);

    gc9a01a_write_cmd_only(GC9A01A_INVON);

    gc9a01a_end_transaction();
    HAL_Delay(120);

    gc9a01a_begin_transaction();
    gc9a01a_write_cmd_only(GC9A01A_SLPOUT);
    gc9a01a_end_transaction();
    HAL_Delay(120);

    gc9a01a_begin_transaction();
    gc9a01a_write_cmd_only(GC9A01A_DISPON);
    gc9a01a_end_transaction();
    HAL_Delay(20);
}

/* -------------------------------------------------------------------------- */
/*                                Public APIs                                 */
/* -------------------------------------------------------------------------- */

void bsp_lcd_init(void)
{
#if (GC9A01A_CS_MODE == GC9A01A_CS_MODE_TOGGLE)
    GC9A01A_CS_HIGH();
#else
    GC9A01A_CS_LOW();
    s_cs_held_low = 1U;
#endif

    gc9a01a_hw_reset();
    gc9a01a_init_sequence();
    gc9a01a_set_orientation(LANDSCAPE);
}

void gc9a01a_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t data[2];

    if ((x >= BSP_LCD_ACTIVE_WIDTH) || (y >= BSP_LCD_ACTIVE_HEIGHT)) {
        return;
    }

    data[0] = (uint8_t)(color >> 8);
    data[1] = (uint8_t)(color & 0xFF);

    gc9a01a_begin_transaction();
    gc9a01a_set_address_window_stream(x, x, y, y);
    gc9a01a_write_data_only(data, sizeof(data));
    gc9a01a_end_transaction();
}

static void gc9a01a_write_char(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i;
    uint32_t j;
    uint32_t b;
    uint8_t fg[2];
    uint8_t bg[2];

    fg[0] = (uint8_t)(color >> 8);
    fg[1] = (uint8_t)(color & 0xFF);
    bg[0] = (uint8_t)(bgcolor >> 8);
    bg[1] = (uint8_t)(bgcolor & 0xFF);

    gc9a01a_set_address_window_stream(x, x + font.width - 1U, y, y + font.height - 1U);

    for (i = 0U; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for (j = 0U; j < font.width; j++) {
            if ((b << j) & 0x8000U) {
                gc9a01a_write_data_only(fg, sizeof(fg));
            } else {
                gc9a01a_write_data_only(bg, sizeof(bg));
            }
        }
    }
}

void gc9a01a_write_string(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
{
    if (str == NULL) {
        return;
    }

    gc9a01a_begin_transaction();

    while (*str != '\0') {
        if ((x + font.width) >= BSP_LCD_ACTIVE_WIDTH) {
            x = 0U;
            y += font.height;

            if ((y + font.height) >= BSP_LCD_ACTIVE_HEIGHT) {
                break;
            }

            if (*str == ' ') {
                str++;
                continue;
            }
        }

        gc9a01a_write_char(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

    gc9a01a_end_transaction();
}

void gc9a01a_fill_rect(uint16_t x, uint16_t w, uint16_t y, uint16_t h, uint16_t color)
{
    if ((x >= BSP_LCD_ACTIVE_WIDTH) || (y >= BSP_LCD_ACTIVE_HEIGHT)) {
        return;
    }

    if ((x + w) > BSP_LCD_ACTIVE_WIDTH) {
        w = BSP_LCD_ACTIVE_WIDTH - x;
    }

    if ((y + h) > BSP_LCD_ACTIVE_HEIGHT) {
        h = BSP_LCD_ACTIVE_HEIGHT - y;
    }

    if ((w == 0U) || (h == 0U)) {
        return;
    }

    gc9a01a_prepare_color_line(color, w);

    gc9a01a_begin_transaction();
    gc9a01a_set_address_window_stream(x, x + w - 1U, y, y + h - 1U);

    for (uint16_t row = 0U; row < h; row++) {
        gc9a01a_write_data_only(s_line_buf, (size_t)w * 2U);
    }

    gc9a01a_end_transaction();
}

void gc9a01a_fill_screen(uint16_t color)
{
    gc9a01a_fill_rect(0U, BSP_LCD_ACTIVE_WIDTH, 0U, BSP_LCD_ACTIVE_HEIGHT, color);
}

void gc9a01a_set_orientation(uint8_t orientation)
{
    uint8_t params[4];

    gc9a01a_begin_transaction();

    gc9a01a_write_cmd_only(GC9A01A_CASET);
    params[0] = 0x00; params[1] = 0x00; params[2] = 0x00; params[3] = 0xEF;
    gc9a01a_write_data_only(params, 4);

    gc9a01a_write_cmd_only(GC9A01A_RASET);
    gc9a01a_write_data_only(params, 4);

    if (orientation == LANDSCAPE) {
        params[0] = MADCTL_MV | MADCTL_BGR;
    } else {
        params[0] = MADCTL_MX | MADCTL_BGR;
    }

    gc9a01a_write_cmd_only(GC9A01A_MADCTL);
    gc9a01a_write_data_only(params, 1);

    gc9a01a_end_transaction();
}

void gc9a01a_draw_image(uint16_t x, uint16_t w, uint16_t y, uint16_t h, const uint16_t *data)
{
    uint8_t line_bytes[GC9A01A_LINE_BUF_PIXELS * 2U];

    if (data == NULL) {
        return;
    }

    if ((x >= GC9A01A_WIDTH) || (y >= GC9A01A_HEIGHT)) {
        return;
    }

    if ((x + w) > GC9A01A_WIDTH) {
        w = GC9A01A_WIDTH - x;
    }

    if ((y + h) > GC9A01A_HEIGHT) {
        h = GC9A01A_HEIGHT - y;
    }

    if ((w == 0U) || (h == 0U)) {
        return;
    }

    gc9a01a_begin_transaction();
    gc9a01a_set_address_window_stream(x, x + w - 1U, y, y + h - 1U);

    for (uint16_t row = 0U; row < h; row++) {
        for (uint16_t col = 0U; col < w; col++) {
            uint16_t pixel = data[(row * w) + col];
            line_bytes[(2U * col)]     = (uint8_t)(pixel >> 8);
            line_bytes[(2U * col) + 1] = (uint8_t)(pixel & 0xFF);
        }

        gc9a01a_write_data_only(line_bytes, (size_t)w * 2U);
    }

    gc9a01a_end_transaction();
}

void gc9a01a_invert_colors(bool invert)
{
    gc9a01a_begin_transaction();
    gc9a01a_write_cmd_only(invert ? GC9A01A_INVON : GC9A01A_INVOFF);
    gc9a01a_end_transaction();
}

void gc9a01a_lcd_fill_image(const uint16_t *data)
{
    gc9a01a_draw_image(0U, BSP_LCD_ACTIVE_WIDTH, 0U, BSP_LCD_ACTIVE_HEIGHT, data);
}

/* -------------------------------------------------------------------------- */
/*                         Extra primitive for player                         */
/* -------------------------------------------------------------------------- */

void gc9a01a_fill_circle(uint16_t x0, uint16_t y0, uint16_t radius, uint16_t color)
{
    int16_t x;
    int16_t y;
    int16_t err;

    x = (int16_t)radius;
    y = 0;
    err = 1 - x;

    while (x >= y) {
        if ((y0 + (uint16_t)y) < BSP_LCD_ACTIVE_HEIGHT) {
            uint16_t start_x = (x0 > (uint16_t)x) ? (x0 - (uint16_t)x) : 0U;
            uint16_t width   = (uint16_t)((2 * x) + 1);

            if ((start_x + width) > BSP_LCD_ACTIVE_WIDTH) {
                width = BSP_LCD_ACTIVE_WIDTH - start_x;
            }

            gc9a01a_fill_rect(start_x, width, y0 + (uint16_t)y, 1U, color);
        }

        if ((y0 >= (uint16_t)y) && ((y0 - (uint16_t)y) < BSP_LCD_ACTIVE_HEIGHT)) {
            uint16_t start_x = (x0 > (uint16_t)x) ? (x0 - (uint16_t)x) : 0U;
            uint16_t width   = (uint16_t)((2 * x) + 1);

            if ((start_x + width) > BSP_LCD_ACTIVE_WIDTH) {
                width = BSP_LCD_ACTIVE_WIDTH - start_x;
            }

            gc9a01a_fill_rect(start_x, width, y0 - (uint16_t)y, 1U, color);
        }

        if ((y0 + (uint16_t)x) < BSP_LCD_ACTIVE_HEIGHT) {
            uint16_t start_x = (x0 > (uint16_t)y) ? (x0 - (uint16_t)y) : 0U;
            uint16_t width   = (uint16_t)((2 * y) + 1);

            if ((start_x + width) > BSP_LCD_ACTIVE_WIDTH) {
                width = BSP_LCD_ACTIVE_WIDTH - start_x;
            }

            gc9a01a_fill_rect(start_x, width, y0 + (uint16_t)x, 1U, color);
        }

        if ((y0 >= (uint16_t)x) && ((y0 - (uint16_t)x) < BSP_LCD_ACTIVE_HEIGHT)) {
            uint16_t start_x = (x0 > (uint16_t)y) ? (x0 - (uint16_t)y) : 0U;
            uint16_t width   = (uint16_t)((2 * y) + 1);

            if ((start_x + width) > BSP_LCD_ACTIVE_WIDTH) {
                width = BSP_LCD_ACTIVE_WIDTH - start_x;
            }

            gc9a01a_fill_rect(start_x, width, y0 - (uint16_t)x, 1U, color);
        }

        y++;

        if (err < 0) {
            err += (2 * y) + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}
