/*
 * GC9A01A.c
 *
 *  Created on: Jan 12, 2024
 *      Author: BHARATI SOFT
 */

#include "../GC9A01A/GC9A01A.h"

#include "../GC9A01A/font.h"

#define REG_WRITE(reg, val)   					((reg) = (val))
#define REG_READ(reg)         					((reg))
#define REG_SET_BIT(reg,pos)   					((reg) |=  (1U << (pos)))
#define REG_CLR_BIT(reg,pos)    				((reg) &= ~(1U << (pos)))
#define REG_READ_BIT(reg,pos)    				((reg) &   (1U << (pos)))
#define REG_CLR_VAL(reg,clrmask,pos)   			((reg) &= ~((clrmask) << (pos)))
#define REG_SET_VAL(reg,val,setmask,pos) 		do {\
														REG_CLR_VAL(reg,setmask,pos);\
														((reg) |= ((val) << (pos))); \
												}while(0)

#define REG_READ_VAL(reg,rdmask,pos)            ((REG_READ(reg) >> (pos)) & (rdmask))


#define __weak 			__attribute__((weak))

#define HIGH_16(x)     					((((uint16_t)x) >> 8U) & 0xFFU)
#define LOW_16(x)      					((((uint16_t)x) >> 0U) & 0xFFU)

#ifndef UNUSED
#define UNUSED(x)    (void)x
#endif

#define SPI SPI1

#define __disable_spi_ssm()           	REG_CLR_BIT(SPI->CR1,SPI_CR1_SSM_Pos)
#define __enable_spi_ssoe()				REG_SET_BIT(SPI->CR2,SPI_CR2_SSOE_Pos)
#define __spi_set_dff_8bit()  			REG_SET_VAL(SPI->CR2,0x7, 0xF,SPI_CR2_DS_Pos)
#define __spi_set_dff_16bit()			REG_SET_VAL(SPI->CR2,0xF, 0xF,SPI_CR2_DS_Pos)
#define __enable_spi()					REG_SET_BIT(SPI->CR1,SPI_CR1_SPE_Pos)
#define __disable_spi()					do{while(REG_READ_BIT(SPI->SR,SPI_SR_BSY_Pos));  REG_CLR_BIT(SPI->CR1,SPI_CR1_SPE_Pos);}while(0)

enum {FALSE,TRUE};

static void gc9a01a_write_cmd(uint8_t cmd);
static void gc9a01a_write_data(uint8_t *buffer, uint32_t len);
static uint32_t get_total_bytes(bsp_lcd_t *hlcd,uint32_t w , uint32_t h);
static void make_area(lcd_area_t *area,uint32_t x_start, uint32_t x_width,uint32_t y_start,uint32_t y_height);
static uint32_t copy_to_draw_buffer( bsp_lcd_t *hlcd,uint32_t nbytes,uint32_t rgb888);
static uint8_t* get_buff(bsp_lcd_t *hlcd);
static uint16_t convert_rgb888_to_rgb565(uint32_t rgb888);
static uint8_t is_lcd_write_allowed(bsp_lcd_t *hlcd);
static void lcd_flush(bsp_lcd_t *hlcd);
static uint32_t bytes_to_pixels(uint32_t nbytes, uint8_t pixel_format);
static uint32_t pixels_to_bytes(uint32_t pixels, uint8_t pixel_format);
static uint32_t copy_to_draw_buffer2( bsp_lcd_t *hlcd,uint16_t nbytes,uint16_t *image_data);
static void gc9a01a_write_char(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) ;
static void gc9a01a_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);


static void gc9a01a_write_cmd(uint8_t cmd) {
	LCD_CSX_LOW();
	LCD_DCX_LOW(); //DCX = 0 , for command
	HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
	LCD_DCX_HIGH();
	LCD_CSX_HIGH();
}


static void gc9a01a_write_data(uint8_t *buffer, uint32_t len) {
	LCD_CSX_LOW();
	HAL_SPI_Transmit(&hspi1, buffer, len, HAL_MAX_DELAY);
	LCD_CSX_HIGH();
}

void gc9a01a_set_orientation(uint8_t orientation)
{
	uint8_t params[4];
	if(orientation == LANDSCAPE) {
		gc9a01a_write_cmd(GC9A01A_RASET);
		params[0] = 0x00;
		params[1] = 0x00;
		params[2] = 0x00;
		params[3] = 0xf0;
		gc9a01a_write_data(params,4);

		gc9a01a_write_cmd(GC9A01A_CASET);
		params[0] = 0x00;
		params[1] = 0x00;
		params[2] = 0x00;
		params[3] = 0xf0;
		gc9a01a_write_data(params,4);

		params[0] = MADCTL_MV | MADCTL_BGR;
	} else if(orientation == PORTRAIT) {
		gc9a01a_write_cmd(GC9A01A_RASET);
		params[0] = 0x00;
		params[1] = 0x00;
		params[2] = 0x00;
		params[3] = 0xf0;
		gc9a01a_write_data(params,4);

		gc9a01a_write_cmd(GC9A01A_CASET);
		params[0] = 0x00;
		params[1] = 0x00;
		params[2] = 0x00;
		params[3] = 0xf0;
		gc9a01a_write_data(params,4);

		params[0] = MADCTL_MY | MADCTL_MX | MADCTL_BGR;
	}
	gc9a01a_write_cmd(GC9A01A_MADCTL);
	gc9a01a_write_data(params,1);
}

void gc9a01a_send_cmd_mem_write(void)
{
	gc9a01a_write_cmd(GC9A01A_RAMWR);
}


void gc9a01a_set_display_area(lcd_area_t *area)
{
	uint8_t params[4];

	/*Column address set(2Ah) */
	params[0] = HIGH_16(area->x1);
	params[1] = LOW_16(area->x1);
	params[2] = HIGH_16(area->x2);
	params[3] = LOW_16(area->x2);
	gc9a01a_write_cmd(GC9A01A_CASET);
	gc9a01a_write_data(params, 4);

	params[0] = HIGH_16(area->y1);
	params[1] = LOW_16(area->y1);
	params[2] = HIGH_16(area->y2);
	params[3] = LOW_16(area->y2);
	gc9a01a_write_cmd(GC9A01A_RASET);
	gc9a01a_write_data(params, 4);
}


void gc9a01a_config() {
	uint8_t params[15];

	gc9a01a_write_cmd(GC9A01A_INREGEN1);					///< Inter register enable 1
	gc9a01a_write_cmd(GC9A01A_INREGEN2);					///< Inter register enable 2

	params[0] = 0x00;
	params[1] = 0x00;
	gc9a01a_write_cmd(GC9A01A_DISPLAY_FUN_CTRL);			///<Display Function Control
	gc9a01a_write_data(params, 2);

#if 0
	params[0] = MADCTL_MX | MADCTL_BGR;
	gc9a01a_write_cmd(GC9A01A_MADCTL);						///< Memory Access Control
	gc9a01a_write_data(params, 1);
#endif

	params[0] = 0X5;
	gc9a01a_write_cmd(GC9A01A_COLMOD_FIXEL_FORMAT_SET); //16 bit	///< COLMOD: Pixel Format Set
	gc9a01a_write_data(params, 1);


	params[0] = 0X13;
	gc9a01a_write_cmd(GC9A01A1_POWER2);								///< Power Control 2
	gc9a01a_write_data(params, 1);

	params[0] = 0X13;
	gc9a01a_write_cmd(GC9A01A1_POWER3);								///< Power Control 3
	gc9a01a_write_data(params, 1);

	params[0] = 0X22;
	gc9a01a_write_cmd(GC9A01A1_POWER4);								///< Power Control 4
	gc9a01a_write_data(params, 1);

	params[0] = 0x45;
	params[1] = 0x09;
	params[2] = 0X08;
	params[3] = 0X08;
	params[4] = 0x26;
	params[5] = 0x2A;
	gc9a01a_write_cmd(GC9A01A_GAMMA1);								///< Set gamma 1
	gc9a01a_write_data(params, 6);

	params[0] = 0x43;
	params[1] = 0x70;
	params[2] = 0X72;
	params[3] = 0X36;
	params[4] = 0x37;
	params[5] = 0x6F;
	gc9a01a_write_cmd(GC9A01A_GAMMA2);								///< Set gamma 2
	gc9a01a_write_data(params, 6);

	params[0] = 0x45;
	params[1] = 0x09;
	params[2] = 0X08;
	params[3] = 0X08;
	params[4] = 0x26;
	params[5] = 0x2A;
	gc9a01a_write_cmd(GC9A01A_GAMMA3);							  	///< Set gamma 3
	gc9a01a_write_data(params, 6);

	params[0] = 0x43;
	params[1] = 0x70;
	params[2] = 0X72;
	params[3] = 0X36;
	params[4] = 0x37;
	params[5] = 0x6F;
	gc9a01a_write_cmd(GC9A01A_GAMMA4);								///< Set gamma 4
	gc9a01a_write_data(params, 6);

	params[0] = 0x34;
	gc9a01a_write_cmd(GC9A01A_FRAMERATE);							///< Frame rate control
	gc9a01a_write_data(params, 1);


	//gc9a01a_write_cmd(GC9A01A_TEON);
	//gc9a01a_write_cmd(GC9A01A_INVON); //??

	gc9a01a_write_cmd(GC9A01A_SLPOUT);								///< Sleep Out
	HAL_Delay(100);
	gc9a01a_write_cmd(GC9A01A_DISPON);								///< Display ON
}


void gc9a01a_config2() {
	uint8_t params[15];

	//LCD_RST = 1;
	//HAL_Delay(50);
	//LCD_RST = 0;
	//HAL_Delay(50);
	//LCD_RST = 1;
	//HAL_Delay(120);
	gc9a01a_write_cmd(0xFE);		///< Inter register enable 1
	gc9a01a_write_cmd(0xEF);		///< Inter register enable 2
#if 0
	params[0] = 0x14;
	gc9a01a_write_cmd(0xEB);
	gc9a01a_write_data(params,1);


	params[0] = 0x60;
	gc9a01a_write_cmd(0x84);
	gc9a01a_write_data(params,1); //40->60 0xb5 en  20200924  james

	params[0] = 0xFF;
	gc9a01a_write_cmd(0x85);
	gc9a01a_write_data(params,1);

	params[0] = 0xFF;
	gc9a01a_write_cmd(0x86);
	gc9a01a_write_data(params,1);

	params[0] = 0xFF;
	gc9a01a_write_cmd(0x87);
	gc9a01a_write_data(params,1);

	params[0] = 0xFF;
	gc9a01a_write_cmd(0x8E);
	gc9a01a_write_data(params,1);

	params[0] = 0xFF;
	gc9a01a_write_cmd(0x8F);
	gc9a01a_write_data(params,1);

	params[0] = 0x0A;
	gc9a01a_write_cmd(0x88);
	gc9a01a_write_data(params,1);

	params[0] = 0x23;
	gc9a01a_write_cmd(0x89);
	gc9a01a_write_data(params,1);  ///spi 2data reg en

	params[0] = 0x00;
	gc9a01a_write_cmd(0x8A);
	gc9a01a_write_data(params,1);

	params[0] = 0x80;
	gc9a01a_write_cmd(0x8B);
	gc9a01a_write_data(params,1);

	params[0] = 0x01;
	gc9a01a_write_cmd(0x8C);
	gc9a01a_write_data(params,1);

	params[0] = 0x03;
	gc9a01a_write_cmd(0x8D);
	gc9a01a_write_data(params,1);  //99 en
#endif

	params[0] = 0x08;
	params[1] = 0x09;
	params[2] = 0x14;
	params[3] = 0x08;
	gc9a01a_write_cmd(0xB5);
	gc9a01a_write_data(params,4); //08->09  james 20200924
	//正扫

	params[0] = 0x00;
	params[1] = 0x00;
	gc9a01a_write_cmd(0xB6);									///<Display Function Control
	gc9a01a_write_data(params,2);  //GS  SS  0x20


	params[0] = 0x48;
	gc9a01a_write_cmd(0x36);									///< Memory Access Control
	gc9a01a_write_data(params,1);

	params[0] = 0x05;
	gc9a01a_write_cmd(0x3A);									///< COLMOD: Pixel Format Set
	gc9a01a_write_data(params,1);

#if 0
	params[0] = 0x08;
	params[1] = 0x08;
	params[2] = 0x08;
	params[3] = 0x08;
	gc9a01a_write_cmd(0x90);
	gc9a01a_write_data(params,4);
#endif



	params[0] = 0x01;
	gc9a01a_write_cmd(0xBA);
	gc9a01a_write_data(params,1); ///TE width

#if 0
	params[0] = 0x06;
	gc9a01a_write_cmd(0xBD);
	gc9a01a_write_data(params,1);


	params[0] = 0x00;
	gc9a01a_write_cmd(0xBC);
	gc9a01a_write_data(params,1);


	params[0] = 0x60;
	params[2] = 0x01;
	params[3] = 0x04;
	gc9a01a_write_cmd(0xFF);
	gc9a01a_write_data(params,4);
#endif

	params[0] = 0x1a;
	gc9a01a_write_cmd(0xC3);								///< Power Control 2
	gc9a01a_write_data(params,1);

	params[0] = 0x1a;
	gc9a01a_write_cmd(0xC4);								///< Power Control 3
	gc9a01a_write_data(params,1);


	params[0] = 0x25;
	gc9a01a_write_cmd(0xC9);								///< Power Control 4
	gc9a01a_write_data(params,1);

#if 0
	params[0] = 0x11;
	gc9a01a_write_cmd(0xBE);
	gc9a01a_write_data(params,1);


	params[0] = 0x10;
	params[1] = 0x0E;
	gc9a01a_write_cmd(0xE1);
	gc9a01a_write_data(params,2);


	params[0] = 0x21;
	params[1] = 0x0c;
	params[2] = 0x02;
	gc9a01a_write_cmd(0xDF);
	gc9a01a_write_data(params,3);
#endif

	params[0] = 0x45;
	params[1] = 0x09;
	params[2] = 0x08;
	params[3] = 0x08;
	params[4] = 0x26;
	params[5] = 0x2A;
	gc9a01a_write_cmd(0xF0);										///< Set gamma 1
	gc9a01a_write_data(params,6);


	params[0] = 0x43;
	params[1] = 0x70;
	params[2] = 0x72;
	params[3] = 0x36;
	params[4] = 0x37;
	params[5] = 0x6F;
	gc9a01a_write_cmd(0xF1);										///< Set gamma 2
	gc9a01a_write_data(params,6);


	params[0] = 0x45;
	params[1] = 0x09;
	params[2] = 0x08;
	params[3] = 0x08;
	params[4] = 0x26;
	params[5] = 0x2A;
	gc9a01a_write_cmd(0xF2);										///< Set gamma 3
	gc9a01a_write_data(params,6);


	params[0] = 0x43;
	params[1] = 0x70;
	params[2] = 0x72;
	params[3] = 0x36;
	params[4] = 0x37;
	params[5] = 0x6F;
	gc9a01a_write_cmd(0xF3);										///< Set gamma 4
	gc9a01a_write_data(params,6);

#if 0
	params[0] = 0x1B;
	params[1] = 0x0B;
	gc9a01a_write_cmd(0xED);
	gc9a01a_write_data(params,2);



	params[0] = 0x77;
	gc9a01a_write_cmd(0xAE);
	gc9a01a_write_data(params,1);

	params[0] = 0x63;
	gc9a01a_write_cmd(0xCD);
	gc9a01a_write_data(params,1);


	params[0] = 0x07;
	params[1] = 0x07;
	params[2] = 0x04;
	params[3] = 0x0E;
	params[4] = 0x10;
	params[5] = 0x09;
	params[6] = 0x07;
	params[7] = 0x08;
	params[8] = 0x03;
	gc9a01a_write_cmd(0x70);
	gc9a01a_write_data(params,9);

#endif

	params[0] = 0x34;
	gc9a01a_write_cmd(0xE8);													///< Frame rate control
	gc9a01a_write_data(params,1);


	//gc9a01a_write_cmd(0xE9);
	//gc9a01a_write_data(0x08);///spi 2 data

#if 1
	//////////////////////undocumented commands - important///////////////////////

	params[0] = 0x38;
	params[1] = 0x0B;
	params[2] = 0x6D;
	params[3] = 0x6D;
	params[4] = 0x39;
	params[5] = 0xF0;
	params[6] = 0x6D;
	params[7] = 0x6D;
	gc9a01a_write_cmd(0x60);
	gc9a01a_write_data(params,8);


	params[0] = 0x38;
	params[1] = 0xF4;
	params[2] = 0x6D;
	params[3] = 0x6D;
	params[4] = 0x38;
	params[5] = 0xF7;//20200718
	params[6] = 0xF7;
	params[7] = 0x6D;
	params[8] = 0x6D;
	gc9a01a_write_cmd(0x61);
	gc9a01a_write_data(params,9);



	/////////////////////////////////////

	params[0] = 0x38;
	params[1] = 0x0D;
	params[2] = 0x71;
	params[3] = 0xED;
	params[4] = 0x70;
	params[5] = 0x70;
	params[6] = 0x38;
	params[7] = 0x0F;
	params[8] = 0x71;
	params[9] = 0xEF;
	params[10] = 0x70;
	params[11] = 0x70;
	gc9a01a_write_cmd(0x62);
	gc9a01a_write_data(params,12);



	params[0] = 0x38;
	params[1] = 0x11;
	params[2] = 0x71;
	params[3] = 0xF1;
	params[4] = 0x70;
	params[5] = 0x70;
	params[6] = 0x38;
	params[7] = 0x13;
	params[8] = 0x71;
	params[9] = 0xF3;
	params[10] = 0x70;
	params[11] = 0x70;
	gc9a01a_write_cmd(0x63);
	gc9a01a_write_data(params,12);


	///////////////////////////////////////////////////////

	params[0] = 0x28;
	params[1] = 0x29;
	params[2] = 0xF1;
	params[3] = 0x01;
	params[4] = 0xF1;
	params[5] = 0x00;
	params[6] = 0x07;
	gc9a01a_write_cmd(0x64);
	gc9a01a_write_data(params,7);


	//正扫
	params[0] = 0x3C;
	params[1] = 0x00;
	params[2] = 0xCD;
	params[3] = 0x67;
	params[4] = 0x45;
	params[5] = 0x45;
	params[6] = 0x10;
	params[7] = 0x00;
	params[8] = 0x00;
	params[9] = 0x00;
	gc9a01a_write_cmd(0x66);
	gc9a01a_write_data(params,10);


	params[0] = 0x00;
	params[1] = 0x3C;
	params[2] = 0x00;
	params[3] = 0x00;
	params[4] = 0x00;
	params[5] = 0x01;
	params[6] = 0x54;
	params[7] = 0x10;
	params[8] = 0x32;
	params[9] = 0x98;
	gc9a01a_write_cmd(0x67);
	gc9a01a_write_data(params,10);



	params[0] = 0x10;
	params[1] = 0x80;
	params[2] = 0x80;
	params[3] = 0x00;
	params[4] = 0x00;
	params[5] = 0x4E;
	params[6] = 0x00;
	gc9a01a_write_cmd(0x74);
	gc9a01a_write_data(params,7);


	params[0] = 0x3e;
	params[1] = 0x07;
	gc9a01a_write_cmd(0x98);
	gc9a01a_write_data(params,2);

#endif
	params[0] = 0x3e;
	params[1] = 0x07;
	gc9a01a_write_cmd(0x99);	//bvee 2x
	gc9a01a_write_data(params,2);


	params[0] = 0x00;
	gc9a01a_write_cmd(0x35);
	gc9a01a_write_data(params,1);

	gc9a01a_write_cmd(0x21);
	HAL_Delay(120);
	//--------end gamma setting--------------//

	gc9a01a_write_cmd(0x11);
	HAL_Delay(120);
	gc9a01a_write_cmd(0x29);



#if 1
	gc9a01a_write_cmd(0x2C);
#endif
}


void gc9a01a_sw_reset() {

}

void gc9a01a_hw_reset() {
	LCD_RESX_HIGH();
	HAL_Delay(LCD_HW_RESET_DELAY_MS);
	LCD_RESX_LOW();
	HAL_Delay(LCD_HW_RESET_DELAY_MS);
	LCD_RESX_HIGH();
	HAL_Delay(LCD_HW_RESET_DELAY_MS);
}

/*
 * Disc: Creates a rectangle and fills color
 * rgb888: Color value in RGB888 format
 * x_start : Horizontal start position of the rectangle ( 0 <= x_start < BSP_FB_WIDTH)
 * x_width : Width of the rectangle in number of pixels ( 1 <= x_width <= BSP_FB_WIDTH )
 * y_start : Vertical start position of the rectangle ( 0 <= y_start < BSP_FB_HEIGHT)
 * y_height : Height of the rectangle in number of pixels ( 1 <= y_height <= BSP_FB_HEIGHT )
 */
void bsp_lcd_fill_rect(bsp_lcd_t *hlcd, uint32_t rgb888, uint32_t x_start, uint32_t x_width,uint32_t y_start,uint32_t y_height)
{

	uint32_t total_bytes_to_write = 0;
	uint32_t bytes_sent_so_far = 0;
	uint32_t remaining_bytes = 0;
	uint32_t npix;
	uint32_t pixels_sent = 0;
	uint32_t x1,y1;
	uint32_t pixel_per_line = x_width;

	if((x_start+x_width) > BSP_LCD_ACTIVE_WIDTH) return;
	if((y_start+y_height) > BSP_LCD_ACTIVE_HEIGHT) return;

	//1. calculate total number of bytes written in to DB
	total_bytes_to_write = get_total_bytes(hlcd,x_width,y_height);
	remaining_bytes = total_bytes_to_write;
	while(remaining_bytes){
		x1 = x_start+(pixels_sent % pixel_per_line);
		y1 = y_start+(pixels_sent / pixel_per_line);

		make_area(&hlcd->area,x1,x_width,y1,y_height);
		//make_area(lcd_area_t *area,uint32_t x_start, uint32_t x_width,uint32_t y_start,uint32_t y_height)

		if(x1 != x_start){
			npix = x_start+x_width - x1;
		}else{
			npix = bytes_to_pixels(remaining_bytes,hlcd->pixel_format);
		}

		bytes_sent_so_far  +=  copy_to_draw_buffer(hlcd,pixels_to_bytes(npix,hlcd->pixel_format),rgb888);
		pixels_sent = bytes_to_pixels(bytes_sent_so_far,hlcd->pixel_format);
		remaining_bytes = total_bytes_to_write - bytes_sent_so_far;
		}
}


void bsp_lcd_set_background_color(bsp_lcd_t *hlcd, uint32_t rgb888)
{
	bsp_lcd_fill_rect(hlcd, rgb888,0,(BSP_LCD_ACTIVE_WIDTH),0,(BSP_LCD_ACTIVE_HEIGHT));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void bsp_lcd_fill_image(bsp_lcd_t *hlcd, uint16_t *image_data, uint16_t x_start, uint16_t x_width,uint16_t y_start,uint16_t y_height)
{
	uint16_t total_bytes_to_write = 0;
	uint16_t bytes_sent_so_far = 0;
	uint16_t remaining_bytes = 0;
	uint16_t npix;
	uint16_t pixels_sent = 0;
	uint16_t x1,y1;
	uint16_t pixel_per_line = x_width;

	if((x_start+x_width) > BSP_LCD_ACTIVE_WIDTH) return;
	if((y_start+y_height) > BSP_LCD_ACTIVE_HEIGHT) return;

	//1. calculate total number of bytes written in to DB
	total_bytes_to_write = get_total_bytes(hlcd,x_width,y_height);
	remaining_bytes = total_bytes_to_write;
	while(remaining_bytes){
		x1 = x_start+(pixels_sent % pixel_per_line);
		y1 = y_start+(pixels_sent / pixel_per_line);

		make_area(&hlcd->area,x1,x_width,y1,y_height);
		//make_area(lcd_area_t *area,uint32_t x_start, uint32_t x_width,uint32_t y_start,uint32_t y_height)

		if(x1 != x_start){
			npix = x_start+x_width - x1;
		}else{
			npix = bytes_to_pixels(remaining_bytes,hlcd->pixel_format);
		}

		bytes_sent_so_far  +=  copy_to_draw_buffer2(hlcd,pixels_to_bytes(npix,hlcd->pixel_format),image_data);

		pixels_sent = bytes_to_pixels(bytes_sent_so_far,hlcd->pixel_format);
		remaining_bytes = total_bytes_to_write - bytes_sent_so_far;
		}
}

static uint32_t copy_to_draw_buffer2( bsp_lcd_t *hlcd,uint16_t nbytes,uint16_t *image_data)
{
	uint16_t *fb_ptr = NULL;
	uint32_t npixels;
	hlcd->buff_to_draw = get_buff(hlcd);
	fb_ptr = (uint16_t*)hlcd->buff_to_draw;
	nbytes =  ((nbytes > hlcd->db_size)?hlcd->db_size:nbytes);
	npixels= bytes_to_pixels(nbytes,hlcd->pixel_format);
	if(hlcd->buff_to_draw != NULL){
		for(uint16_t i = 0 ; i < npixels ;i++){
			//*fb_ptr = convert_rgb888_to_rgb565(image_data[i]); //image_data[i]
			*fb_ptr = image_data[i];
			fb_ptr++;
		}
		hlcd->write_length = pixels_to_bytes(npixels,hlcd->pixel_format);
		while(!is_lcd_write_allowed(hlcd));
		hlcd->buff_to_flush = hlcd->buff_to_draw;
		hlcd->buff_to_draw = NULL;
		lcd_flush(hlcd);
		return pixels_to_bytes(npixels,hlcd->pixel_format);
	}

	return 0;
}


static void gc9a01a_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	// column address set
	gc9a01a_write_cmd(0x2A); // CASET
	{
		uint8_t data[] = { (x0 >> 8) & 0xFF, x0 & 0xFF, (x1 >> 8) & 0xFF, x1 & 0xFF };
		gc9a01a_write_data(data, sizeof(data));
	}

	// row address set
	gc9a01a_write_cmd(0x2B); // RASET
	{
		uint8_t data[] = { (y0 >> 8) & 0xFF, y0 & 0xFF, (y1 >> 8) & 0xFF, y1 & 0xFF };
		gc9a01a_write_data(data, sizeof(data));
	}

	// write to RAM
	gc9a01a_write_cmd(0x2C); // RAMWR
}

static void gc9a01a_write_char(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
	uint32_t i, b, j;

	gc9a01a_set_address_window(x, y, x+font.width-1, y+font.height-1);

	for(i = 0; i < font.height; i++) {
		b = font.data[(ch - 32) * font.height + i];
		for(j = 0; j < font.width; j++) {
			if((b << j) & 0x8000)  {
					uint8_t data[] = { color >> 8, color & 0xFF };
					gc9a01a_write_data(data, sizeof(data));
			} else {
					uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
					gc9a01a_write_data(data, sizeof(data));
			}
		}
	}
}

void gc9a01a_write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
	LCD_CSX_LOW();

	while(*str) {
		if(x + font.width >= BSP_LCD_ACTIVE_WIDTH) {
			x = 0;
			y += font.height;
			if(y + font.height >= BSP_LCD_ACTIVE_HEIGHT) {
				break;
			}

			if(*str == ' ') {
				// skip spaces in the beginning of the new line
				str++;
				continue;
			}
		}
		gc9a01a_write_char(x, y, *str, font, color, bgcolor);
		x += font.width;
		str++;
	}
	LCD_CSX_HIGH();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void bsp_lcd_send_cmd_mem_write(void)
{
	gc9a01a_write_cmd(GC9A01A_RAMWR);
}


void bsp_lcd_write(uint8_t *buffer, uint32_t nbytes)
{

	uint16_t *buff_ptr;

	__disable_spi();
	__spi_set_dff_16bit();
	__enable_spi();

	LCD_CSX_LOW();

	buff_ptr = (uint16_t*)buffer;
	while(nbytes){
		while(!REG_READ_BIT(SPI->SR,SPI_SR_TXE_Pos));
		REG_WRITE(SPI->DR,*buff_ptr);
		++buff_ptr;
		nbytes -= 2;
	}

	__disable_spi();
	LCD_CSX_HIGH();
	__spi_set_dff_8bit();
	__enable_spi();
}

static uint32_t get_total_bytes(bsp_lcd_t *hlcd,uint32_t w , uint32_t h)
{
	uint8_t bytes_per_pixel = 2;
	if(hlcd->pixel_format == BSP_LCD_PIXEL_FMT_RGB565){
		bytes_per_pixel = 2;
	}
	return (w * h * bytes_per_pixel);
}

static void make_area(lcd_area_t *area,uint32_t x_start, uint32_t x_width,uint32_t y_start,uint32_t y_height){

	uint16_t lcd_total_width,lcd_total_height;

	lcd_total_width =  BSP_LCD_ACTIVE_WIDTH-1;
	lcd_total_height = BSP_LCD_ACTIVE_HEIGHT -1;

	area->x1 = x_start;
	area->x2 = x_start + x_width -1;
	area->y1 = y_start;
	area->y2 = y_start + y_height -1;

	area->x2 = (area->x2 > lcd_total_width) ? lcd_total_width :area->x2;
	area->y2 = (area->y2 > lcd_total_height) ? lcd_total_height : area->y2;

}


static uint32_t bytes_to_pixels(uint32_t nbytes, uint8_t pixel_format)
{
	UNUSED(pixel_format);
	return nbytes/2;
}


static uint32_t pixels_to_bytes(uint32_t pixels, uint8_t pixel_format)
{
	UNUSED(pixel_format);
	return pixels * 2UL;
}

static uint32_t copy_to_draw_buffer( bsp_lcd_t *hlcd,uint32_t nbytes,uint32_t rgb888)
{
	uint16_t *fb_ptr = NULL;
	uint32_t npixels;
	hlcd->buff_to_draw = get_buff(hlcd);
	fb_ptr = (uint16_t*)hlcd->buff_to_draw;
	nbytes =  ((nbytes > hlcd->db_size)?hlcd->db_size:nbytes);
	npixels= bytes_to_pixels(nbytes,hlcd->pixel_format);
	if(hlcd->buff_to_draw != NULL){
		for(uint32_t i = 0 ; i < npixels ;i++){
			*fb_ptr = convert_rgb888_to_rgb565(rgb888); //image_data[i]
			fb_ptr++;
		}
		hlcd->write_length = pixels_to_bytes(npixels,hlcd->pixel_format);
		while(!is_lcd_write_allowed(hlcd));
		hlcd->buff_to_flush = hlcd->buff_to_draw;
		hlcd->buff_to_draw = NULL;
		lcd_flush(hlcd);
		return pixels_to_bytes(npixels,hlcd->pixel_format);
	}

	return 0;
}


static uint8_t* get_buff(bsp_lcd_t *hlcd)
{
	uint32_t buf1 = (uint32_t)hlcd->draw_buffer1;
	uint32_t buf2 = (uint32_t)hlcd->draw_buffer2;

	//__disable_irq();
	if(hlcd->buff_to_draw == NULL && hlcd->buff_to_flush == NULL){
		return  hlcd->draw_buffer1;
	}else if((uint32_t)hlcd->buff_to_flush == buf1 && hlcd->buff_to_draw == NULL ){
		return  hlcd->draw_buffer2;
	}else if ((uint32_t)hlcd->buff_to_flush == buf2 && hlcd->buff_to_draw == NULL){
		return  hlcd->draw_buffer1;
	}
	//__enable_irq();

	return NULL;
}

static uint16_t convert_rgb888_to_rgb565(uint32_t rgb888)
{
    uint16_t r,g,b;
	r = (rgb888 >> 19) & 0x1FU;
	g = (rgb888 >> 10) & 0x3FU;
	b = (rgb888 >> 3)  & 0x1FU;
	return (uint16_t)((r << 11) | (g << 5) | b);
}

static void lcd_flush(bsp_lcd_t *hlcd)
{
	gc9a01a_set_display_area(&hlcd->area);
	bsp_lcd_send_cmd_mem_write();
	bsp_lcd_write(hlcd->buff_to_flush,hlcd->write_length);
	hlcd->buff_to_flush = NULL;
}


static uint8_t is_lcd_write_allowed(bsp_lcd_t *hlcd)
{
	//__disable_irq();
	if(!hlcd->buff_to_flush)
		return TRUE;
	//__enable_irq();

	return FALSE;
}


