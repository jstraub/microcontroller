#include <avr/io.h>

void initAdc() {
  // internal reference from VCC with capacitor
  ADMUX = (1<<REFS0);
  // enable and highest prescaler of 128 -> higher accuracy
  // 16MHz/128 = 125kHz
  ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

}

uint16_t readAdc(uint8_t adc) {
  ADMUX = (ADMUX & 0xF8) | (adc & 0x07);
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  return ADC;
}

float toVoltage(uint16_t adc, float maxVoltage) {
  return ((float)adc*maxVoltage)/1024.f;
}
