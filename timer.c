#include "config.h"
#include "timer.h"


static timercb_t _cb;
static unsigned int _count;
static volatile unsigned long _ticks;
static unsigned long _interval_us;


void
timer_init() {
    /* timer1 config
     *   7: unused
     *   6: disable external enable pin gate
     * 5~4: prescale to 1/8
     *   3: LP oscilator off
     *   2: no sync
     *   1: internal clock source (Fosc/4)
     *   0: Timr on
     */
    T1CON = 0b00110001;
    TMR1IE = 1;
    _count = 0;
    _cb = NULL;
}


inline void
reset() {
    unsigned short v;
    if (_ticks > TMR1_MAX) {
        v = (unsigned short)_ticks;
    }
    else {
        v = TMR1_MAX;
    }
    _ticks -= v;
    v = TMR1_MAX - v;
    TMR1IF = 0;
    TMR1H = (unsigned char)(v >> 8);
    TMR1L = (unsigned char)(v << 8);
}


void
timer_async(unsigned int count, unsigned long interval_ms, timercb_t cb) {
    _count = count;
    _cb = cb;
    _interval_us = interval_ms * 1000;

    _ticks = _interval_us / TMR1_INTERVAL_US;
    reset();
    TMR1ON = 1;
}


void
timer_tick() {
    if (_ticks) {
        reset();
        return;
    }

    if (_cb) {
        _cb(_count - 1);
    }

    if (_count == 1) {
        TMR1ON = 0;
        TMR1IF = 0;
        return;
    }

    _count--;
    _ticks = _interval_us / TMR1_INTERVAL_US;
    reset();
}
