#ifndef BLINK_H_
#define BLINK_H_


#include "timer.h"


typedef void (* volatile blinkcb_t)(void *state);


struct blink {
    blinkcb_t cb;
    void *state;
};


void
blink(unsigned int count, unsigned int interval_ms, blinkcb_t cb,
        void *state);


#endif  // BLINK_H_
