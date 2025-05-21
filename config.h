#ifndef CONFIG_H_
#define CONFIG_H_

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



#include <xc.h>
#include <stdbool.h>


enum {
    OFF = 0,
    ON = 1,
};


enum {
    NO = 0,
    YES = 1,
};

#define VREF_MV 476
#define ADC_MAX 1024
#define ADC_OFFSET 50

#define DEFAULT_TL -1
#define DEFAULT_TH 2


#define MILI(v) (((long)v) * 1000)
#define SECOND(v) ((v) * 1000000)
#define MINS(m) SECOND((m) * 60)


#define MOTORON_DELAY SECS(10)

#define TMR1_MAX ((short)65536)
#define TMR1_INTERVAL_US 8
#define RELAY GP4
#define LED GP5
#define TBTN GP3
#define RELAY_SET(s) RELAY = !(s)
#define RELAY_IS(s) (RELAY == !(s))
#define LED_SET(s) LED = (s)


#endif  // CONFIG_H_
