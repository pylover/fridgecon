#ifndef USERCONFIG_H_
#define USERCONFIG_H_


#include <stdbool.h>
#include "helpers.h"



/* ADC volatge refrence defined by D1 and pair of (R6, R7) voltage devider. */
#define VREF_MV 476


/* PIC12F675 ADC resolution is 10 bits. so 2 ^ 10 */
#define ADC_MAX 1024


/* ADC_MAX / VREF_MV */
#define ADC_FACTOR 22


/* temperature offset */
#define TEMP_OFFSET_CELSIUS -5


/* minimum/maximum allowed temperature to turn off the fridge compressor */
#define OFFTEMP_MIN -5
#define OFFTEMP_MAX -1
#define OFFTEMP_DEFAULT -1


/* temperature to turn the fridge compressor on */
#define ONTEMP 4


/* delay before turn the compressor on after power outage and etc. */
#define MOTORON_DELAY_S 30


#endif  // USERCONFIG_H_
