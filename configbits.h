#ifndef CONFIGBITS_H_
#define CONFIGBITS_H_

// PIC12F675 Configuration Bit Settings
// 'C' source line config statements


// BEGIN CONFIG
// 100 = INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN
// #pragma config FOSC = INTRCIO
//
/*
111 = RC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN
110 = RC oscillator: I/O function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN
101 = INTOSC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN
100 = INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN
011 = EC: I/O function on GP4/OSC2/CLKOUT pin, CLKIN on GP5/OSC1/CLKIN
010 = HS oscillator: High speed crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN
001 = XT oscillator: Crystal/resonator on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN
000 = LP oscillator: Low-power crystal on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN
*/
#pragma config FOSC = 4

// Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTE = ON

// Power-Up Timer Enable bit (PWRT disabled)
#pragma config PWRTE = ON

// GP3/MCLR pin function select (GP3/MCLR pin function is R)
#pragma config MCLRE = OFF

// Brown-out Detect Enable bit (BOD enabled)
#pragma config BOREN = OFF

// Code Protection bit (Program Memory code protection is disabled)
#pragma config CP = OFF

// Data Code Protection bit (Data memory code protection is disabled)
#pragma config CPD = OFF
// END CONFIG

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#endif  // CONFIGBITS_H_
