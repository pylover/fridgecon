#include "config.h"
#include "store.h"
#include "timer.h"


static __bit _blinking;
static __bit _tunning;
static volatile signed char temp;
static signed char _offtemp;
#define _RELAY GP4
#define _LED GP5
#define _TBTN GP3
#define MOTOR_SET(s) _RELAY = !(s)
#define LED_SET(s) _LED = (s)
#define LED_TOGGLE(s) _LED ^= 1
#define BLINKWAIT(n, i, c) \
    _blinking = true; \
    timer_async((n) * 2, TICKS(i), c); \
    while (_blinking) _delaywdt(MILI(50))


static void
_init() {
    /* Callibrate the 4MHZ internal oscilator */
    OSCCAL = 0b01001000;

    /* comprator off */
    CMCON = 0b00000111;
    VRCON = 0b00000000;

    /* option reg
     * 7. enable global pull up control active low: GPPU
     * 6. interrupt on falling edge of GP2, default.
     * 5. tmr0 uses internal clock
     * 4. Increment on low-to-high transition on GP2/T0CKI pin
     * 3. prescaler is assigned to wdt module
     * 2:0. prescale 1/128 for wdt.
     */
    OPTION_REG = 0b00001111;

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

    _offtemp = offtemp_load();
    timer_init();

    ADIE = 1;
}


void __interrupt()
isr(void) {
    unsigned short adcval;

    if (GPIF) {
        GPIF = 0;
        if (_tunning) {
            return;
        }
        TMR1ON = 0;
        _blinking = false;
        _tunning = true;
    }

    if (ADIF) {
        adcval = (unsigned short)ADRESH << 8;
        adcval += (unsigned short)ADRESL;
        temp = (signed char) (adcval / ADC_FACTOR);
        temp += ADC_OFFSET_CELSIUS;
        ADIF = 0;
    }

    if (TMR1IF) {
        timer_tick();
        TMR1IF = 0;
    }
}


static void
_blink(unsigned int countdown) {
    if (countdown > 20) {
        return;
    }
    LED_TOGGLE();
    if (countdown == 0) {
        _blinking = false;
    }
}


static void
_tune(unsigned int countdown) {
    LED_TOGGLE();
    if (countdown == 0) {
        _tunning = false;
    }
}


static int
_sample(void) {
    while (!_tunning) {
        GO_nDONE = 1;   // ADC enable
        while (GO_nDONE == 1){
            _delaywdt(100);
        }
        LED_TOGGLE();
        if (temp < _offtemp) {
            return 1;
        }
        else if (temp > ONTEMP) {
            MOTOR_SET(ON);
        }
        _delaywdt(MILI(1000));
    }
    return 0;
}


void
main(void) {
    _init();

normal:
    /* turn compressor off */
    MOTOR_SET(OFF);
    LED_SET(OFF);
    BLINKWAIT(MOTORON_DELAY_S * 10, MILI(100), _blink);
    if (_sample()) {
        goto normal;
    }

    /* tunning */
    _offtemp--;
    if (_offtemp < OFFTEMP_MIN) {
        _offtemp = OFFTEMP_MAX;
    }
    offtemp_save(_offtemp);
    LED_SET(OFF);
    BLINKWAIT(2, MILI(50), _blink);
    _delaywdt(MILI(700));
    timer_async((unsigned int)abs(_offtemp) * 2, TICKS(MILI(300)), _tune);
    while (_tunning) {
        _delaywdt(MILI(100));
    }
    goto normal;
}
