#include "config.h"
#include "timer.h"
#include "blink.h"


static volatile struct blink _blink;


static void
_cb(unsigned int countdown, struct blink *state) {
    LED_SET(!LED);
    if ((countdown == 0) && state->cb) {
        state->cb(state->state);
    };
}


void
blink(unsigned int count, unsigned int interval_ms, blinkcb_t cb,
        void *state) {
    _blink.cb = cb;
    _blink.state = state;
    timer_start(count * 2, interval_ms, (timercb_t)_cb, (void*)&_blink);
}
