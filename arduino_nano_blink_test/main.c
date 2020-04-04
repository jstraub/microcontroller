#include <avr/io.h>
#include <util/delay.h>

int main(void) {

  DDRB |= (1<<PB5) | (1<<PB4);

  while(42) { 
    PORTB ^= (1<<PB5);
    PORTB ^= (1<<PB4);
    _delay_ms(100);
  }
}
