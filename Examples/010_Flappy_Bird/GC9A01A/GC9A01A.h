/*
 * GC9A01A.h
 *
 *  Created on: Jan 12, 2024
 *      Author: BHARATI SOFT
 */

#ifndef SRC_GC9A01A_H_
#define SRC_GC9A01A_H_

#include "main.h"

#include "../GC9A01A/font.h"

#define GC9A01A_TFTWIDTH 			240  		///< Display width in pixels
#define GC9A01A_TFTHEIGHT		  240 		///< Display height in pixels

#define GC9A01A_SWRESET 			0x01   		///< Software Reset (maybe, not documented)
#define GC9A01A_RDDID     		0x04     	///< Read display identification information
#define GC9A01A_RDDST 				0x09     	///< Read Display Status
#define GC9A01A_SLPIN			    0x10   		 ///< Enter Sleep Mode
#define GC9A01A_SLPOUT 				0x11   		 ///< Sleep Out
#define GC9A01A_PTLON 				0x12    	 ///< Partial Mode ON
#define GC9A01A_NORON 				0x13     	///< Normal Display Mode ON
#define GC9A01A_INVOFF 				0x20    	///< Display Inversion OFF
#define GC9A01A_INVON 				0x21     	///< Display Inversion ON
#define GC9A01A_DISPOFF 			0x28   		///< Display OFF
#define GC9A01A_DISPON 				0x29    	///< Display ON
#define GC9A01A_CASET 				0x2A     	///< Column Address Set
#define GC9A01A_RASET 				0x2B     	///< Row Address Set
#define GC9A01A_RAMWR 				0x2C     	///< Memory Write
#define GC9A01A_PTLAR 				0x30    	///< Partial Area
#define GC9A01A_VSCRDEF 			0x33   		///< Vertical Scrolling Definition
#define GC9A01A_TEOFF 				0x34     	///< Tearing Effect Line OFF
#define GC9A01A_TEON 					0x35    	///< Tearing Effect Line ON
#define GC9A01A_MADCTL 				0x36    	///< Memory Access Control
#define GC9A01A_VSCRSADD 			0x37  		///< Vertical Scrolling Start Address
#define GC9A01A_IDLEOFF 			0x38   		///< Idle mode OFF
#define GC9A01A_IDLEON 				0x39    	///< Idle mode ON
#define GC9A01A_COLMOD 				0x3A    	///< Pixel Format Set
#define GC9A01A_CONTINUE 			0x3C  		///< Write Memory Continue
#define GC9A01A_TEARSET 			0x44   		///< Set Tear Scanline
#define GC9A01A_GETLINE 			0x45   		///< Get Scanline
#define GC9A01A_SETBRIGHT 		0x51 			///< Write Display Brightness
#define GC9A01A_SETCTRL 			0x53   		///< Write CTRL Display
#define GC9A01A1_POWER7 			0xA7   		///< Power Control 7
#define GC9A01A_TEWC 					0xBA      ///< Tearing effect width control
#define GC9A01A1_POWER1 			0xC1   		///< Power Control 1
#define GC9A01A1_POWER2 			0xC3   		///< Power Control 2
#define GC9A01A1_POWER3 			0xC4   		///< Power Control 3
#define GC9A01A1_POWER4 			0xC9   		///< Power Control 4
#define GC9A01A_RDID1 				0xDA     	///< Read ID 1
#define GC9A01A_RDID2 				0xDB     	///< Read ID 2
#define GC9A01A_RDID3 				0xDC     	///< Read ID 3
#define GC9A01A_FRAMERATE 		0xE8 		 	///< Frame rate control
#define GC9A01A_SPI2DATA 			0xE9  		///< SPI 2DATA control
#define GC9A01A_INREGEN2 			0xEF  		///< Inter register enable 2
#define GC9A01A_GAMMA1 				0xF0    	///< Set gamma 1
#define GC9A01A_GAMMA2 				0xF1    	///< Set gamma 2
#define GC9A01A_GAMMA3 				0xF2    	///< Set gamma 3
#define GC9A01A_GAMMA4 				0xF3    	///< Set gamma 4
#define GC9A01A_IFACE 				0xF6     	///< Interface control
#define GC9A01A_INREGEN1 			0xFE  		///< Inter register enable 1


#define GC9A01A_DISPLAY_FUN_CTRL  		 0xB6
#define GC9A01A_COLMOD_FIXEL_FORMAT_SET  0x3A


// Color definitions
#define GC9A01A_BLACK 				0x0000      ///<   0,   0,   0
#define GC9A01A_NAVY 					0x000F      ///<   0,   0, 123
#define GC9A01A_DARKGREEN 		0x03E0  		///<   0, 125,   0
#define GC9A01A_DARKCYAN 			0x03EF   	 	///<   0, 125, 123
#define GC9A01A_MAROON 				0x7800      ///< 123,   0,   0
#define GC9A01A_PURPLE 				0x780F      ///< 123,   0, 123
#define GC9A01A_OLIVE 				0x7BE0      ///< 123, 125,   0
#define GC9A01A_LIGHTGREY 		0xC618   		///< 198, 195, 198
#define GC9A01A_DARKGREY 			0x7BEF   	 	///< 123, 125, 123
#define GC9A01A_BLUE 					0x001F      ///<   0,   0, 255
#define GC9A01A_GREEN 				0x07E0      ///<   0, 255,   0
#define GC9A01A_CYAN 					0x07FF      ///<   0, 255, 255
#define GC9A01A_RED 					0xF800      ///< 255,   0,   0
#define GC9A01A_MAGENTA 			0xF81F      ///< 255,   0, 255
#define GC9A01A_YELLOW 				0xFFE0      ///< 255, 255,   0
#define GC9A01A_WHITE 				0xFFFF      ///< 255, 255, 255
#define GC9A01A_ORANGE 				0xFD20      ///< 255, 165,   0
#define GC9A01A_GREENYELLOW 	0xAFE5 			///< 173, 255,  41
#define GC9A01A_PINK 					0xFC18      ///< 255, 130, 198


#define MADCTL_MY 	0x80  ///< Bottom to top
#define MADCTL_MX 	0x40  ///< Right to left
#define MADCTL_MV 	0x20  ///< Reverse Mode
#define MADCTL_ML 	0x10  ///< LCD refresh Bottom to top
#define MADCTL_RGB 	0x00 	///< Red-Green-Blue pixel order
#define MADCTL_BGR 	0x08 	///< Blue-Green-Red pixel order
#define MADCTL_MH 	0x04  ///< LCD refresh right to left


//for hw reset
#define LCD_RESX_HIGH()				HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
#define LCD_RESX_LOW()				HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);


//cs
#define LCD_CSX_HIGH()				HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
#define LCD_CSX_LOW()					HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);


//DCX
#define LCD_DCX_HIGH()				HAL_GPIO_WritePin(LCD_RS_A0_GPIO_Port, LCD_RS_A0_Pin, GPIO_PIN_SET);
#define LCD_DCX_LOW()					HAL_GPIO_WritePin(LCD_RS_A0_GPIO_Port, LCD_RS_A0_Pin, GPIO_PIN_RESET);



#define LCD_HW_RESET_DELAY_MS    50


 typedef struct{
 	uint16_t x1;
 	uint16_t x2;
 	uint16_t y1;
 	uint16_t y2;
 }lcd_area_t;

 struct bsp_lcd;

 typedef void (*bsp_lcd_dma_cplt_cb_t)(struct bsp_lcd*);
 typedef void (*bsp_lcd_dma_err_cb_t)(struct bsp_lcd*);

 typedef struct{
 	uint8_t orientation;
 	uint8_t pixel_format;
 	uint8_t * draw_buffer1;
 	uint8_t * draw_buffer2;
 	uint32_t write_length;
 	uint8_t *buff_to_draw;
 	uint8_t *buff_to_flush;
 	lcd_area_t area;
 	uint32_t db_size;
 	bsp_lcd_dma_cplt_cb_t dma_cplt_cb;
 	bsp_lcd_dma_err_cb_t dma_err_cb;
 }bsp_lcd_t;

#define	BSP_LCD_PIXEL_FMT_L8 		1
#define	BSP_LCD_PIXEL_FMT_RGB565	2
#define BSP_LCD_PIXEL_FMT_RGB666    3
#define	BSP_LCD_PIXEL_FMT_RGB888	4
#define BSP_LCD_PIXEL_FMT 			BSP_LCD_PIXEL_FMT_RGB565

 /*Select orientation*/
 #define PORTRAIT  0
 #define LANDSCAPE 1
 #define BSP_LCD_ORIENTATION   LANDSCAPE

#if(BSP_LCD_ORIENTATION == PORTRAIT)
	#define  BSP_LCD_ACTIVE_WIDTH 			GC9A01A_TFTWIDTH
	#define  BSP_LCD_ACTIVE_HEIGHT  		GC9A01A_TFTHEIGHT
#elif(BSP_LCD_ORIENTATION == LANDSCAPE)
	#define  BSP_LCD_ACTIVE_WIDTH 			GC9A01A_TFTHEIGHT
	#define  BSP_LCD_ACTIVE_HEIGHT 			GC9A01A_TFTWIDTH
#endif


void gc9a01a_config(void);
void gc9a01a_config2(void);
void gc9a01a_hw_reset();
void gc9a01a_set_display_area(lcd_area_t *area);
void gc9a01a_set_orientation(uint8_t orientation);
void bsp_lcd_fill_rect(bsp_lcd_t *hlcd, uint32_t rgb888, uint32_t x_start, uint32_t x_width,uint32_t y_start,uint32_t y_height);
void bsp_lcd_set_background_color(bsp_lcd_t *hlcd, uint32_t rgb888);
void bsp_lcd_send_cmd_mem_write(void);
void bsp_lcd_write(uint8_t *buffer, uint32_t nbytes);

/********************************************************************************/
void gc9a01a_write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void bsp_lcd_fill_image(bsp_lcd_t *hlcd, uint16_t *image_data, uint16_t x_start, uint16_t x_width,uint16_t y_start,uint16_t y_height);
/********************************************************************************/
#endif /* SRC_GC9A01A_H_ */
