#include <xc.h>

#include "userconfig.h"
#include "store.h"


#define _MAGIC 0xc9
#define _LIMITS_EEPROMADDR 5


// signed char
// offtemp_load() {
//     unsigned char magic = eeprom_read(_LIMITS_EEPROMADDR);
//     if (magic != _MAGIC) {
//         offtemp_save(OFFTEMP_DEFAULT);
//         return OFFTEMP_DEFAULT;
//     }
//     return (signed char)eeprom_read(_LIMITS_EEPROMADDR + 1);
// }
//
//
// void
// offtemp_save(signed char t) {
//     eeprom_write(_LIMITS_EEPROMADDR, _MAGIC);
//     eeprom_write(_LIMITS_EEPROMADDR + 1, (char)t);
// }
