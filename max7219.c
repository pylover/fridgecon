//
// Use one MAX7219 to control 8-digit seven-segment display
// the display module: http://www.icshop.com.tw/product_info.php/products_id/20686
//
// MAX7219 datasheet: https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
//
#include "max7219.h"


// the MAX7219 address map (datasheet table 2)
#define MAX7219_DECODE_REG      (0x09)
#define MAX7219_INTENSITY_REG   (0x0A)
#define MAX7219_SCANLIMIT_REG   (0x0B)
#define MAX7219_SHUTDOWN_REG    (0X0C)
#define MAX7219_DISPLAYTEST_REG (0x0F)
#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)


// IOs
#define MAX7219_DATA   GP0
#define MAX7219_LOAD   GP5
#define MAX7219_CLOCK  GP1


// special chars
#define BLANK   0b00001111
#define DASH    0b00001010
#define DOT     0b10000000


enum state {
    DONE = 1,
    NEGATIVE = 2
};


static void
_shiftout(unsigned char data) {
	int i;
	for (i = 0; i < 8; i++) {
        MAX7219_DATA = !!(data & (1 << (7 - i)));
        MAX7219_CLOCK = 1;
        MAX7219_CLOCK = 0;
	}
}


// update the register value of MAX7219
static void
_setregister(unsigned char address, unsigned char value) {
    MAX7219_LOAD = 0;
    _shiftout(address);
    _shiftout(value);
    MAX7219_LOAD = 1;
}


void
max7219_display(uint8_t pos, int number, unsigned char dp) {
    unsigned char i;
    unsigned char digitvalue;
    unsigned char offset = (unsigned char)(pos * 4);
    unsigned char stat = 0b00;
    if (number < 0) {
        stat |= NEGATIVE;
        number = -number;
    }

    for (i = 0; i < 4; i++){
        digitvalue = (unsigned char)(number % 10);
        if ((stat & DONE) == DONE) {
            if ((stat & NEGATIVE) == NEGATIVE) {
                digitvalue |= DASH;
                stat &= DONE;
            }
            else {
                digitvalue |= BLANK;
            }
        }
        else if ((number < 10) && (i > 0)) {
            stat |= DONE;
        }

        if (dp == i) {
            digitvalue |= DOT;
        }

        _setregister((unsigned char)MAX7219_DIGIT_REG(offset + i), digitvalue);
        number /= 10;
    }
}


void
max7219_init(unsigned char intensity) {
    MAX7219_LOAD = 0;
    MAX7219_CLOCK = 0;
    MAX7219_DATA = 0;

    // disable test mode. datasheet table 10
    _setregister(MAX7219_DISPLAYTEST_REG, 0);
    // set medium intensity. datasheet table 7
    _setregister(MAX7219_INTENSITY_REG, intensity);
    // turn on display. datasheet table 3
    _setregister(MAX7219_SHUTDOWN_REG, 1);
    // drive 8 digits. datasheet table 8
    _setregister(MAX7219_SCANLIMIT_REG, 7);
    // decode mode for all positions. datasheet table 4
    _setregister(MAX7219_DECODE_REG, 0b11111111);
}
