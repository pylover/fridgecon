
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

// GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
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


#include "config.h"


static int adcval = 0;
static long temp = 44;


static signed char templ = DEFAULT_TL;
static signed char temph = DEFAULT_TH;
static bool motor_must = OFF;
static bool motor_safe = NO;
static unsigned long tmr1_ms = 0;
static unsigned long tmr1_us = 0;
// #define TMR1MAX_US 524288
// #define TMR1MAX_US 262144
#define TMR1MAX_US 131072
// #define TMR1MAX_US 65536


const unsigned short tmr1_initial = 65536 - 50000;


#define TMR1_START() \
    TMR1IE = 1; \
    TMR1ON = 1; \
    TMR1_RESET()


#define TMR1_STOP() \
    TMR1IE = 0; \
    TMR1ON = 0; \
    TMR1_RESET()


#define TMR1_RESET() \
    TMR1IF = 0; \
    TMR1H = (unsigned char)(tmr1_initial >> 8); \
    TMR1L = (unsigned char)(tmr1_initial << 8)


#define MOTOR_FORCE(s) \
    RELAY_SET(s); \
    LED_SET(s)


static void
motor_on() {
    motor_must = ON;
    if (motor_safe) {
        MOTOR_FORCE(ON);
    }
}


static void
motor_off() {
    motor_must = OFF;
    if (RELAY_IS(ON)) {
        motor_safe = NO;
        RELAY_SET(OFF);
        LED_SET(OFF);
        TMR1_START();
    }
}


void __interrupt()
isr(void) {
    if (ADIF) {
        adcval = ADRESH << 8;
        adcval += ADRESL;
        temp = adcval;
        temp *= VREF_MV;
        temp /= ADC_MAX;
        temp -= ADC_OFFSET;
        ADIF = 0;
    }
    if (TMR1IF) {
        tmr1_us += TMR1MAX_US;
        TMR1IF = 0;
        if (tmr1_us >= MOTORON_DELAY) {
            tmr1_us = 0;
            TMR1_STOP();
            motor_safe = YES;
            if (motor_must == ON) {
                MOTOR_FORCE(ON);
            }
        }
        else {
            TMR1_RESET();
            LED_SET(!LED);
        }
    }
    if (GPIF) {
        if (TBTN) {
            TLED_SET(ON);
            motor_off();
        }
        else {
            TLED_SET(OFF);
        }
        GPIF = 0;
    }
}


static void
sample() {
    if (temp < templ) {
        motor_off();
    }
    else if (temp > temph) {
        motor_on();
    }
}


void
main(void) {
    /* Callibrate the 4MHZ internal oscilator */
    OSCCAL = 0b01001000;

    /* comprator off */
    CMCON = 0b00000111;
    VRCON = 0b00000000;

    /* timer1 config
     *   7: unused
     *   6: disable external enable pin gate
     * 5~4: prescale to 1/4
     *   3: LP oscilator off
     *   2: no sync
     *   1: internal clock source (Fosc/4)
     *   0: Timr on
     */
    T1CON = 0b00010001;
    TMR1_START();

    /* option reg
     * 7. enable global pull up control active low: GPPU
     * 6. interrupt on falling edge of GP2, default.
     * internal clock
     * prescaler is assigned to tmr0 module
     * prescaller rate 1/8
     */
    OPTION_REG = 0b01000011;

    /* GP2, 1 and 3 as input */
    TRISIO = 0b00001110;

    /* GP3 weak pullup */
    WPU = 0b00001000;

    /* interrrupt on change GP3 */
    IOC = 0b00001000;

    /* adc configuration
     *   7. right justified result format
     *   6. vref pin enabled
     * 3:2. analog channel selection: ch 10
     *   0. ADON enable ADC module
     */
    ADCON0 = 0b11001001;

    /* enable analog input for GP2/AN2
     * ADC clock drived from internal clock < 500KH */
    ANSEL = 0b00110100;

    /* interrupt control
     * 7. GIE: Enables all unmasked interrupts
     * 6. enable all unmasked peripheral interrupts
     * 5. disable the TMR0 interrupt
     * 4. disable the GP2/INT external interrupt
     * 3. enable the GPIO port change interrupt
     * 2. TMR0 register did not overflow
     * 1. clear INTF
     * 0. GPIF None of the GP5:GP0 pins have changed state
     */
    INTCON = 0b11001000;

    ADIE = 1;
    ADIF = 0;

    // TLED_SET(ON);
    RELAY_SET(OFF);
    TLED_SET(ON);
    GO_nDONE = 1;   // ADC enable
    long d = 0;
    while (1) {
        if (GO_nDONE == 1){
            continue;
        }
        sample();
        _delaywdt(SECS(1));
        // LED_SET(!LED);
        // _delaywdt(50463240);
        GO_nDONE = 1;           // ADC enable
    }
}
