#include <avr/io.h>

void initSerial()
{
  // set baud rate to 115.2k
  uint16_t ubrr = 8; 
  UBRR0H = (uint8_t)(ubrr>>8);
  UBRR0L = (uint8_t)ubrr;
  // enable receiver and transmitter
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  // set frame format: 8data, 1stop bit
  UCSR0C = (3<<UCSZ00);
}

void writeSerial(uint8_t c) {
  while(! (UCSR0A & (1<<UDRE0)));
  UDR0 = c;
}

void writeSerialStr(char* s) {
  while(*s) {
    writeSerial(*s);
    s++;
  }
}

uint8_t readSerial() {
  while(! (UCSR0A & (1<<RXC0)));
  return UDR0;
}
