# ST7789-STM32
Using STM32's Hardware SPI to drive a ST7789 based IPS display.

## Supported Displays
- 135*240 resolution  
- 240*240 resolution  

If you like, you could customize it's resolution to drive different displays you prefer. 
> For example, a 240x320 display is perfectly suited for st7789.  
> Just set all X_SHIFT and Y_SHIFT to 0, and set resolution to 240|320.  

For more details, please refer to ST7789's datasheet.  

## How to use ?

Include st7789.h in main.c
for a simple test, you could refer ST7789_Test() function in while(1).  
**Don't forget to refer `ST7789_Init();` before you use any functions...**


This code has been tested on 240x240 IPS screen. You can look into **demo** directory for details.  


Test conditions:
- STM32F103C8T6  
- Keil MDK5  

## **Important**

**Some display won't work, you should consider adding a pull-up resistor on SCLK(SCK) and SDA(MOSI) pin.**

The simplest way is to configure these 2 GPIO to `Pull-up` Mode manually in CubeMX(if supported) or in SPI initialization code.

# Special thanks to

#### Reference
- [ananevilya's Arduino-ST7789-Lib](https://github.com/ananevilya/Arduino-ST7789-Library)  
- [afiskon's stm32-st7735 lib](https://github.com/afiskon/stm32-st7735)

#### Contributor
- [JasonLrh](https://github.com/JasonLrh)  
- [ZiangCheng](https://github.com/ZiangCheng)  
