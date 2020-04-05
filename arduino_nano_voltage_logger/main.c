#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "adc.h"
#include "serial.h"

int main(void) {

  DDRB |= (1<<PB5) | (1<<PB4);
  PORTB &= ~(1<<PB4);

  initAdc();
  // init serial connection to 115200 baud, 8bit, 1 stop bit.
  initSerial();

  char buf[100];
  uint16_t adc=0;
  while(42) { 

    PORTB |= (1<<PB5);
    adc = readAdc0();
    float voltage = ((float)adc*5.f)/1024.f;
    sprintf(buf, "%d\t%f\n\r", adc, voltage);
    writeSerialStr(buf);

    // turn on proportional to adc
    uint16_t i=0;
    while(i++ < adc) {_delay_ms(1);}

    PORTB &= ~(1<<PB5);

    // turn off for the rest of 1024ms
    while(i++ < 1024) {_delay_ms(1);}
  }
}
