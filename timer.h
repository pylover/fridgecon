#ifndef TIMER_H_
#define TIMER_H_


typedef void (*timercb_t) (unsigned int count, void *state);


void
timer_init(void);


void
timer_async(unsigned int count, unsigned long interval_ms, timercb_t cb,
        void *state);


void
timer_tick(void);


#endif  // TIMER_H_
