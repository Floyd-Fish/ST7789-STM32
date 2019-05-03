#ifndef __ST7789_H
#define __ST7789_H

#include "stm32f3xx_hal.h"

#include "ips_font.h"

#define ST7789_SPI_PORT hspi1
extern SPI_HandleTypeDef ST7789_SPI_PORT;

//引脚定义区
#define ST7789_RST_PORT GPIOB
#define ST7789_RST_PIN GPIO_PIN_10
#define ST7789_DC_PORT GPIOB
#define	ST7789_DC_PIN GPIO_PIN_0
#define ST7789_CS_PORT GPIOB
#define ST7789_CS_PIN GPIO_PIN_11

/*****Use if need backlight control*****
#define BLK_PORT
#define BLK_PIN
***************************************/

#define USING_HORIZONAL 2 // 0 & 1竖屏，2 & 3横屏

#define ABS(x)   ((x) > 0 ? (x) : -(x))

#if USING_HORIZONAL == 0 || USING_HORIZONAL == 1
#define ST7789_WIDTH 135
#define ST7789_HEIGHT 240

#else
#define ST7789_WIDTH 240
#define ST7789_HEIGHT 135
#endif


#define ST7789_RST_Clr() HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_RESET)
#define ST7789_RST_Set() HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_SET)

#define ST7789_DC_Clr() HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_RESET)
#define ST7789_DC_Set() HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_SET)

#define ST7789_CS_Clr() HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_RESET)
#define ST7789_CS_Set() HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_SET)

#define ST7789_CMD 0    //写命令
#define ST7789_DATA 1    //写数据




void ST7789_Init(void);
void ST7789_Fill_Color(uint16_t color);
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color);
void ST7789_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color);

void ST7789_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ST7789_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void ST7789_ShowChinese(uint16_t x, uint16_t y, uint8_t index, uint8_t size, uint16_t color);
void ST7789_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);
void ST7789_InvertColors(uint8_t invert);

void ST7789_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7789_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);

void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7789_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ST7789_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void ST7789_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

void ST7789_Test(void);

//画笔颜色
#define WHITE         	 0xFFFF	//白色
#define BLACK         	 0x0000	//黑色  
#define BLUE           	 0x001F //蓝色 
#define BRED             0XF81F	
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800	//红色
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0	//绿色
#define CYAN          	 0x7FFF	//青色
#define YELLOW        	 0xFFE0	//黄色
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif