#include "config.h"
#include "store.h"


#define _MAGIC 0xc9
#define _LIMITS_EEPROMADDR 5


void
limits_load(struct limits *out) {
    unsigned char magic = eeprom_read(_LIMITS_EEPROMADDR);
    if (magic != _MAGIC) {
        out->low = DEFAULT_LT;
        limits_save(out);
        return;
    }
    out->low = (signed char)eeprom_read(_LIMITS_EEPROMADDR + 1);
}


void
limits_save(struct limits *out) {
    eeprom_write(_LIMITS_EEPROMADDR, _MAGIC);
    eeprom_write(_LIMITS_EEPROMADDR + 1, (char)out->low);
}
