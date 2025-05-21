#include "config.h"
#include "timer.h"


static void *_state;
static timercb_t _cb;
static unsigned short _initial;
static unsigned int _count;


#define _RESET() \
    TMR1IF = 0; \
    TMR1H = (unsigned char)(_initial >> 8); \
    TMR1L = (unsigned char)(_initial << 8)


void
timer_init() {
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
    TMR1IE = 1;
    _count = 0;
    _cb = NULL;
    _state = NULL;
}


void
timer_async(unsigned int count, unsigned int interval_ms, timercb_t cb,
        void *state) {
    _count = count;
    _cb = cb;
    _state = state;

    unsigned short v = interval_ms / TMR1_INTERVAL_MS;
    _initial = (unsigned short)65536 - v;
    _initial += 9000;
    _RESET();
    TMR1ON = 1;
}


void
timer_tick() {
    _count--;
    if (_cb) {
        _cb(_count, _state);
    }

    if (_count == 0) {
        TMR1ON = 0;
        return;
    }

    _RESET();
}
