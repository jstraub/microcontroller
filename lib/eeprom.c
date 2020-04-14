#include <avr/eeprom.h>

void eraseEeprom() {
  const uint16_t* eepMax = (uint16_t*) 0x0400;
  uint16_t* eepAdr = 0;
  while (eepAdr < eepMax) {
    eeprom_update_word(eepAdr++, 0xffff);
  }
}

