#ifndef CONFIG_H_
#define CONFIG_H_


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


#define MSECS(v) ((v) * 1000U)
#define SECS(v) ((v) * 1000000U)
#define MINS(m) SECS((m) * 60)


#define MOTORON_DELAY SECS(10)


#define RELAY GP4
#define LED GP5
#define TBTN GP3
#define RELAY_SET(s) RELAY = !(s)
#define RELAY_IS(s) (RELAY == !(s))
#define LED_SET(s) LED = (s)


#endif  // CONFIG_H_
