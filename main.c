
// PIC12F675 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

// BEGIN CONFIG
#pragma config FOSC =  INTRCIO   // Oscillator Selection bits (RC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN)
#pragma config WDTE =  OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
// END CONFIG

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "max7219.h"


#define INTERVAL 300000


#define SECOND  1000000
#define RANGE   (RISK_TEMP - LOW_TEMP)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


static int adcval = 0;


void __interrupt()
isr(void) {
    if (ADIF) {
        adcval = ADRESH << 8;
        adcval += ADRESL;
        ADIF = 0;
    }
}


void
main(void) {
    float f;
    TRISIO = 0b00000100;        // GP2: IN
    ANSEL = 0b00110100;         // GP2->AN2

    OPTION_REG = 0b11010011;
    CMCON = 0b00000111;
    ADCON0 = 0b10001001;        // ADON, AN2, VDD
    VRCON = 0b00000000;

    GIE = 1;
    ADIE = 1;
    PEIE = 1;
    ADIF = 0;
    TMR0 = 0;

    max7219_init(4);

    GO_nDONE = 1;   // ADC enable
    long d = 0;
    while (1) {
        if (GO_nDONE == 1){
            continue;
        }
        f = (float) adcval;
        max7219_display(left, adcval, 1);
        max7219_display(right, adcval, 1);
        GO_nDONE = 1;           // ADC enable
        _delaywdt(INTERVAL);

    }
}
