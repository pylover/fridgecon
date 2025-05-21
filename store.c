#include "config.h"
#include "store.h"


#define _MAGIC 0xc9
#define _LIMITS_EEPROMADDR 5


void
limits_load(struct limits *out) {
    out->magic = eeprom_read(_LIMITS_EEPROMADDR);
    if (out->magic != _MAGIC) {
        out->low = DEFAULT_LT;
        out->high = DEFAULT_HT;
        limits_save(out);
        return;
    }
    out->low = (signed char)eeprom_read(_LIMITS_EEPROMADDR + 1);
    out->high = (signed char)eeprom_read(_LIMITS_EEPROMADDR + 2);
}


void
limits_save(struct limits *out) {
    out->magic = _MAGIC;
    eeprom_write(_LIMITS_EEPROMADDR, out->magic);
    eeprom_write(_LIMITS_EEPROMADDR + 1, (char)out->low);
    eeprom_write(_LIMITS_EEPROMADDR + 2, (char)out->high);
}
