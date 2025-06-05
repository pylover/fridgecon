#include <xc.h>

#include "userconfig.h"
#include "timer.h"


static timercb_t _cb;
static unsigned int _count;
static volatile unsigned long _initialticks;
static volatile unsigned long _ticks;


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
}


void
timer_async(unsigned int count, unsigned long ticks, timercb_t cb) {
    _count = count;
    _cb = cb;
    _initialticks = ticks;
    _ticks = ticks;
    TMR1H = 0xff;
    TMR1L = 0xff;
    TMR1ON = 1;
}


void
timer_tick() {
    unsigned short step;

    if (_ticks) {
        goto again;
    }

    if (_cb) {
        _cb(_count - 1);
    }

    if (_count == 1) {
        TMR1ON = 0;
        return;
    }

    _count--;
    _ticks = _initialticks;

again:
    step = _ticks > TMR1_MAX? (unsigned short)_ticks: TMR1_MAX;
    _ticks -= step;
    step = TMR1_MAX - step;
    TMR1H = (unsigned char)(step >> 8);
    TMR1L = (unsigned char)(step << 8);
}
