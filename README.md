# ST7789-STM32
Using STM32's Hardware SPI to drive a ST7789 based IPS display.

## Supported Displays
- 135*240 resolution  
- 240*240 resolution  

If you like, you could customize it's resolution to drive different displays you prefer:D  
For more details, please refer to ST7789's datasheet.  
## How to use ?

Just as many other lib files for stm32 dev env.  
I suggest you mkdir a folder named 'st77889' and put these files in it.  
In keil MDK5 (I use this), add include path ./project-path/st7789  
And open them in project file tree.  

Include st7789.h in main.c
for a simple test, you could refer ST7789_Test() function in while(1).

## Developing...
So this repo is currently **UNSTABLE**, please wait for the stable version.  

I have tested this code on 135*240 screen made by ZhongJingYuan... but not on 240*240 yet  
**(Because of the 2019-ncov I have to stay at home with nothing to test :(  )**  

Test conditions:
- STM32F103  
- Keil MDK5  


# Special thanks to

#### Reference
- [ananevilya's Arduino-ST7789-Lib](https://github.com/ananevilya/Arduino-ST7789-Library)  
- [afiskon's stm32-st7735 lib](https://github.com/afiskon/stm32-st7735)

#### Contributer
- [JasonLrh](https://github.com/JasonLrh)  
- [ZiangCheng](https://github.com/ZiangCheng)  
