#include <avr/io.h>

void initPwm() {
  // PB1 = OC1A = D9
  // PB2 = OC1B = D10
  DDRB |= (1<<PB1) | (1<<PB2);
  PORTD &= ~((1<<PB1) | (1<<PB2));

  //phase correct 10bit PWM (own PWM cycle is 2x full 10bit counter)
  TCCR1A = (1<<WGM11) | (1<<WGM10);
  TCCR1A |= (1<<COM1A1) | (1<<COM1B1); // non-inverted operation

  // prescaler f = 16MHz/(x*2024) = 15.625 kHz /x
  // x = 1  : f=15.625 kHz
  // x = 8  : f=1.953 kHz
  // x = 64 : f=244 Hz
  // choose prescaler of 1
  TCCR1B = (1<<CS10);

  OCR1A = 0;
  OCR1B = 0;
}

