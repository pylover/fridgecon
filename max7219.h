#ifndef MAX7219_H_
#define MAX7219_H_


#include <xc.h>


#define MAX7219_DATA   GP0
#define MAX7219_LOAD   GP5
#define MAX7219_CLOCK  GP1


#define right 0
#define left 1


void
max7219_display(uint8_t pos, int number, unsigned char dp);


// void
// max7219_displayfloat(enum max7219_position pos, float v);


void
max7219_init(unsigned char intensity);


#endif  // MAX7219_H_
