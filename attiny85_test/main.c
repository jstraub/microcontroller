#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // set LED pin PB0 
  DDRB |= (1<<PB0);

  while(42) {
    // toggle the LED pin PB0 and hence the LED
    PORTB ^= (1<<PB0);
    // use build in delay function to delay for 100ms
    _delay_ms(100);
  }
}
