#ifndef TIMER_H_
#define TIMER_H_


typedef void (*timercb_t) (unsigned int count);


#define TMR1_MAX ((short)65536)
#define TMR1_INTERVAL_US 8
#define TICKS(us) ((us) / TMR1_INTERVAL_US)


void
timer_init(void);


void
timer_async(unsigned int count, unsigned long ticks, timercb_t cb);


void
timer_tick(void);


#endif  // TIMER_H_
