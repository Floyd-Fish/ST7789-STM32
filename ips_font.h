#ifndef __IPS_FONT_H
#define __IPS_FONT_H

#include "stdint.h"

typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;


extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

extern uint8_t ST7789_32[];
extern uint8_t ST7789_16[];
extern const uint16_t saber[][128];

#endif