#include <avr/eeprom.h>
void writePacked10bit(uint8_t* p, uint16_t a, uint16_t b) {
  // TODO debug
  uint8_t buf[3];
  buf[0] = a >> 6;
  buf[1] = (b >> 8) & (a << 2);
  buf[2] = b;
  eeprom_update_block(buf, p, 3);
}
void readPacked10bit(uint8_t* p, uint16_t* a, uint16_t* b) {
  // TODO debug
  uint8_t buf[3];
  eeprom_read_block(buf, p, 3);
  *b = buf[2];
  *b &= (buf[1] & 0x03) << 8;
  *a = (buf[1] & 0xfc) >> 2;
  *a &= buf[2] << 6;
}

void eraseEeprom() {
  const uint16_t* eepMax = (uint16_t*) 0x0400;
  uint16_t* eepAdr = 0;
  while (eepAdr < eepMax) {
    eeprom_update_word(eepAdr++, 0xffff);
  }
}

