#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // set LED pin PB5 and PB4 to output
  DDRB |= (1<<PB5) | (1<<PB5);

  while(true) {
    // toggle the LED pin PB5 and PB4 and hence the LED
    PORTB ^= (1<<PB5);
    PORTB ^= (1<<PB4);
    // use build in delay function to delay for 100ms
    _delay_ms(100);
  }
}
