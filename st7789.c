#include "st7789.h"


//#include "bmp.h"
uint16_t BACK_COLOR = 0x0000;    //用户自定义背景色

//选择
static void ST7789_Select() {
  HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_RESET);
}

//取消选择
static void ST7789_Unselect() {
  HAL_GPIO_WritePin(ST7789_CS_PORT, ST7789_CS_PIN, GPIO_PIN_SET);
}

//复位
static void ST7789_Reset() {
    HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(ST7789_RST_PORT, ST7789_RST_PIN, GPIO_PIN_SET);  
}

//写命令
static void ST7789_WriteCommand(uint8_t cmd) {
	//ST7789_Select();
    HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&ST7789_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
	//ST7789_UnSelect();
}

//写数据，8bit
static void ST7789_WriteData(uint8_t* buff, size_t buff_size) {
	//ST7789_Select();
    HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_SET);

    // split data in small chunks because HAL can't send more then 64K at once
    while(buff_size > 0) {
        uint16_t chunk_size = buff_size > 32768 ? 32768 : buff_size;
        HAL_SPI_Transmit(&ST7789_SPI_PORT, buff, chunk_size, HAL_MAX_DELAY);
        buff += chunk_size;
        buff_size -= chunk_size;
    }
		//ST7789_UnSelect();
}

//设置显示地址窗
static void ST7789_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	//ST7789_Select();
		if(USING_HORIZONAL == 0) {
			// column address set
			ST7789_WriteCommand(0x2A); { // CASET
					uint8_t data[] = { ((x0+52) >> 8) & 0xFF , (x0+52) & 0xFF, ((x1+52) >> 8) & 0xFF, (x1+52) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// row address set
			ST7789_WriteCommand(0x2B); {// RASET
					uint8_t data[] = { ((y0+40) >> 8) & 0xFF, (y0+40) & 0xFF, ((y1+40) >> 8) & 0xFF, (y1+40) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// write to RAM
			ST7789_WriteCommand(0x2C); // RAMWR
		}
		else if (USING_HORIZONAL == 1) {
			// column address set
			ST7789_WriteCommand(0x2A); { // CASET
					uint8_t data[] = { ((x0+52) >> 8) & 0xFF , (x0+52) & 0xFF, ((x1+52) >> 8) & 0xFF, (x1+52) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// row address set
			ST7789_WriteCommand(0x2B); {// RASET
					uint8_t data[] = { ((y0+40) >> 8) & 0xFF, (y0+40) & 0xFF, ((y1+40) >> 8) & 0xFF, (y1+40) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// write to RAM
			ST7789_WriteCommand(0x2C); // RAMWR
		}
		else if (USING_HORIZONAL == 2) {
			// column address set
			ST7789_WriteCommand(0x2A); { // CASET
					uint8_t data[] = { ((x0+40) >> 8) & 0xFF , (x0+40) & 0xFF, ((x1+40) >> 8) & 0xFF, (x1+40) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// row address set
			ST7789_WriteCommand(0x2B); {// RASET
					uint8_t data[] = { ((y0+53) >> 8) & 0xFF, (y0+53) & 0xFF, ((y1+53) >> 8) & 0xFF, (y1+53) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// write to RAM
			ST7789_WriteCommand(0x2C); // RAMWR
		}
		else {
			// column address set
			ST7789_WriteCommand(0x2A); { // CASET
					uint8_t data[] = { ((x0+40) >> 8) & 0xFF , (x0+40) & 0xFF, ((x1+40) >> 8) & 0xFF, (x1+40) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// row address set
			ST7789_WriteCommand(0x2B); {// RASET
					uint8_t data[] = { ((y0+52) >> 8) & 0xFF, (y0+52) & 0xFF, ((y1+52) >> 8) & 0xFF, (y1+52) & 0xFF };
					ST7789_WriteData(data, sizeof(data));
			}
			// write to RAM
			ST7789_WriteCommand(0x2C); // RAMWR
		}
		//ST7789_UnSelect();
}

//初始化函数
void ST7789_Init(void)
{

  ST7789_Select();
  //ST7789_Reset();
	ST7789_RST_Clr();
	HAL_Delay(10);
	ST7789_RST_Set();
	HAL_Delay(10); 
  ST7789_WriteCommand(0x36);

    if (USING_HORIZONAL == 0) {
			uint8_t data[] = {0x00};
			ST7789_WriteData(data, sizeof(data));
		}
			
    else if (USING_HORIZONAL == 1) {
			uint8_t data[] = {0xC0};
			ST7789_WriteData(data, sizeof(data));
		}
    else if (USING_HORIZONAL == 2) {
			uint8_t data[] = {0x70};
			ST7789_WriteData(data, sizeof(data));
		}
    else {
			uint8_t data[] = {0xA0};
			ST7789_WriteData(data, sizeof(data));
		}


  ST7789_WriteCommand(0x3A);
	{
		uint8_t data[] = {0x05};
		ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0xB2);
	{
		uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
		ST7789_WriteData(data, sizeof(data));
	}
	
  ST7789_WriteCommand(0xB7);
	{
		uint8_t data[] = {0x35};
		ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0xBB);
	{
		uint8_t data[] = {0x19};
		ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0xC0);
	{
		uint8_t data[] = {0x2C};
		ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0xC2);
	{
		uint8_t data[] = {0x01};
		ST7789_WriteData(data, sizeof(data));
	}
	
  ST7789_WriteCommand(0xC3);
	{
		uint8_t data[] = {0x12};
		ST7789_WriteData(data, sizeof(data));
	}
	
  ST7789_WriteCommand(0xC4);
	{
		uint8_t data[] = {0x20};
		ST7789_WriteData(data, sizeof(data));
	}
  
  ST7789_WriteCommand(0xC6);
	{
		uint8_t data[] = {0x0F};
		ST7789_WriteData(data, sizeof(data));
	} 

  ST7789_WriteCommand(0xD0);
	{
		uint8_t data[] = {0xA4, 0xA1};
			ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0xE0);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
			ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0xE1);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
		ST7789_WriteData(data, sizeof(data));
	}

  ST7789_WriteCommand(0x21);
  ST7789_WriteCommand(0x11);
  ST7789_WriteCommand(0x29);
}

//纯色填充
void ST7789_Fill_Color(uint16_t color)
{
	//ST7789_Select();
  uint16_t i, j;
  ST7789_SetAddressWindow(0, 0, ST7789_WIDTH-1, ST7789_HEIGHT-1);
  for (i = 0; i < ST7789_WIDTH; i++)
    for(j = 0; j < ST7789_HEIGHT; j++)
		{
			uint8_t data[] = {color >> 8, color & 0xFF};
			ST7789_WriteData(data, sizeof(data));
		}
		//ST7789_UnSelect();
}

//画像素点
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	//ST7789_Select();
  ST7789_SetAddressWindow(x, y, x, y);
	uint8_t data[] = {color >> 8, color & 0xFF};
	ST7789_WriteData(data, sizeof(data));
	//ST7789_UnSelect();
}

//选定区域填充纯色
void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color)
{
	//ST7789_Select();
  uint16_t i, j;
  ST7789_SetAddressWindow(xSta, ySta, xEnd, yEnd);
  for(i = ySta; i <= yEnd; i++)
    for(j = xSta; j <= xEnd; j++)
	{
    uint8_t data[] = {color >> 8, color & 0xFF};
		ST7789_WriteData(data, sizeof(data));
	}
	//ST7789_UnSelect();
}

//画4px的像素点
void ST7789_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color)
{
	//ST7789_Select();
  ST7789_Fill(x-1, y-1, x+1, y+1, color);
	//ST7789_UnSelect();
}

//画线
void ST7789_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	//ST7789_Select();
  uint16_t t;
  int xerr = 0, yerr = 0, delta_x, delta_y, distance;
  int incx, incy, uRow, uCol;

  delta_x = x2 - x1;
  delta_y = y2 - y1;

  uRow = x1;
  uCol = y1;

  if (delta_x > 0)
    incx = 1;
  else if (delta_x == 0)
    incx = 0;
  else 
  {
    incx = -1;
    delta_x = -delta_x;
  }

  if (delta_y > 0)
    incy = 1;
  else if (delta_y == 0)
    incy = 0;
  else 
  {
    incy = -1;
    delta_y = -delta_x;
  }
  if (delta_x > delta_y)
    distance = delta_x;
  else 
    distance = delta_y;

  for(t = 0; t <= distance; t++)
  {
    ST7789_DrawPixel(uRow, uCol, color);
    xerr += delta_x;
    yerr += delta_y;
    if (xerr > distance)
    {
      xerr -= distance;
      uRow += incx;
    }
    if (yerr > distance)
    {
      yerr -= distance;
      uCol += incy;
    }
  }
	//ST7789_UnSelect();
}

//画空心矩形
void ST7789_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	//ST7789_Select();
  ST7789_DrawLine(x1,y1,x2,y1,color);
  ST7789_DrawLine(x1,y1,x1,y2,color);
  ST7789_DrawLine(x1,y2,x2,y2,color);
  ST7789_DrawLine(x2,y1,x2,y2,color);
	//ST7789_UnSelect();
}

//显示汉字
//index ->汉字的序号，需要在字库查找
//size ->字号, 16/32
void ST7789_ShowChinese(uint16_t x, uint16_t y, uint8_t index, uint8_t size, uint16_t color)	
{  
	//ST7789_Select();
	uint8_t i,j;
	uint8_t *temp,size1;
	if(size==16)
		temp=ST7789_16;//选择字号
	
	if(size==32)
		temp=ST7789_32;
	
  ST7789_SetAddressWindow(x,y,x+size-1,y+size-1); //设置一个汉字的区域
  size1=size*size/8;//一个汉字所占的字节
	temp+=index*size1;//写入的起始位置
	for(j=0;j<size1;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((*temp&(1<<i))!=0)//从数据的低位开始读
			{
				uint8_t data[] = {color >> 8, color & 0xFF};
				ST7789_WriteData(data, sizeof(data));//点亮
			}
			else
			{
				uint8_t data[] = { BACK_COLOR >> 8, BACK_COLOR & 0xFF};
				ST7789_WriteData(data, sizeof(data));//不点亮
			}
		}
		temp++;
	 }
	//ST7789_UnSelect();
}

//画个圆
void ST7789_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
	//ST7789_Select();
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    ST7789_DrawPixel(x0, y0 + r, color);
    ST7789_DrawPixel(x0, y0 - r, color);
    ST7789_DrawPixel(x0 + r, y0, color);
    ST7789_DrawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST7789_DrawPixel(x0 + x, y0 + y, color);
        ST7789_DrawPixel(x0 - x, y0 + y, color);
        ST7789_DrawPixel(x0 + x, y0 - y, color);
        ST7789_DrawPixel(x0 - x, y0 - y, color);

        ST7789_DrawPixel(x0 + y, y0 + x, color);
        ST7789_DrawPixel(x0 - y, y0 + x, color);
        ST7789_DrawPixel(x0 + y, y0 - x, color);
        ST7789_DrawPixel(x0 - y, y0 - x, color);
			}
	//ST7789_UnSelect();
}

//画个图
void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data)
{
   if((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT)) return;
   if((x + w - 1) >= ST7789_WIDTH) return;
   if((y + h - 1) >= ST7789_HEIGHT) return;

   //ST7789_Select();
   ST7789_SetAddressWindow(x, y, x+w-1, y+h-1);
   ST7789_WriteData((uint8_t*)data, sizeof(uint16_t)*w*h);
   //ST7789_Unselect();	
}

//反色
void ST7789_InvertColors(uint8_t invert) {
    //ST7789_Select();
    ST7789_WriteCommand(invert ? 0x21 /* INVON */ : 0x20 /* INVOFF */);
    //ST7789_Unselect();
}

//写字符
static void ST7789_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;
	//ST7789_Select();
    ST7789_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8_t data[] = { color >> 8, color & 0xFF };
                ST7789_WriteData(data, sizeof(data));
            } else {
                uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
                ST7789_WriteData(data, sizeof(data));
            }
        }
    }
	//ST7789_UnSelect();
}

//写字符串
void ST7789_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor)
{
	//ST7789_Select();
	while(*str)
	{
		if(x + font.width >= ST7789_WIDTH) {
    x = 0;
    y += font.height;
			if(y + font.height >= ST7789_HEIGHT) {
				break;
			}

			if(*str == ' ') {
			// skip spaces in the beginning of the new line
				str++;
				continue;
			}
		}
		ST7789_WriteChar(x, y, *str, font, color, bgcolor);
		x += font.width;
		str++;
	}
	//ST7789_UnSelect();
}

//画实心纯色矩形
void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) 
{
	uint8_t i;
	
	/* Check input parameters */
	if (
		x >= ST7789_WIDTH ||
		y >= ST7789_HEIGHT
	) {
		/* Return error */
		return;
	}
	
	/* Check width and height */
	if ((x + w) >= ST7789_WIDTH) {
		w = ST7789_WIDTH - x;
	}
	if ((y + h) >= ST7789_HEIGHT) {
		h = ST7789_HEIGHT - y;
	}
	
	/* Draw lines */
	for (i = 0; i <= h; i++) {
		/* Draw lines */
		ST7789_DrawLine(x, y + i, x + w, y + i, color);
	}
}

//画三角形
void ST7789_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color) 
{
	/* Draw lines */
	ST7789_DrawLine(x1, y1, x2, y2, color);
	ST7789_DrawLine(x2, y2, x3, y3, color);
	ST7789_DrawLine(x3, y3, x1, y1, color);
}

//画实心三角形
void ST7789_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
	curpixel = 0;
	
	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay){
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		ST7789_DrawLine(x, y, x3, y3, color);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void ST7789_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    ST7789_DrawPixel(x0, y0 + r, color);
    ST7789_DrawPixel(x0, y0 - r, color);
    ST7789_DrawPixel(x0 + r, y0, color);
    ST7789_DrawPixel(x0 - r, y0, color);
    ST7789_DrawLine(x0 - r, y0, x0 + r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST7789_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        ST7789_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

        ST7789_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
        ST7789_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
    }
}

void ST7789_Test(void)
{
	ST7789_Fill_Color(CYAN);
		HAL_Delay(500);
		ST7789_Fill_Color(RED);
		HAL_Delay(500);
		ST7789_Fill_Color(BLUE);
		HAL_Delay(500);
		ST7789_Fill_Color(WHITE);
		ST7789_WriteString(10, 20, "Hello Steve!", Font_7x10, RED, GREEN);
		HAL_Delay(500);
		ST7789_Fill_Color(RED);
		ST7789_DrawRectangle(20, 20, 200, 80, WHITE);
		HAL_Delay(500);
		ST7789_Fill_Color(BLACK);
		ST7789_ShowChinese(10, 10, 0, 16, CYAN);
		ST7789_ShowChinese(30, 10, 1, 16, RED);
		ST7789_ShowChinese(50, 10, 2, 16, GREEN);
		ST7789_ShowChinese(70, 10, 3, 16, YELLOW);
		ST7789_ShowChinese(90, 10, 4, 16, BLUE);
		
		ST7789_WriteString(20, 30, "->", Font_11x18, RED, BLACK);
		ST7789_ShowChinese(50, 30, 5, 16, CYAN);
		ST7789_ShowChinese(70, 30, 6, 16, CYAN);
		
		
		HAL_Delay(1000);
		ST7789_Fill_Color(WHITE);
		//HAL_Delay(500);
		ST7789_DrawImage(0, 0, 128, 128, (uint16_t*)saber);
		HAL_Delay(3000);
}





