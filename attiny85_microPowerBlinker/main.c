#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


void initWatchdog() {
  cli();
  MCUSR = 0x00;
  // needed in safety level 1
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // enable watchdog AND watchdog timer interrupt 
  // and set prescaler to 1Hz frequency at 5V
  WDTCR = (1<<WDIE) | (1<<WDP2) | (1<<WDP1); 
  sei();
}

void initPowerSave() {
  DDRB = (1<<PB0); // only leave PB0 on for LED, rest is input
  PORTB = 0;
  ADCSRA &= ~(1<<ADEN); // disable the ADC
  PRR = (1<<PRADC) | (1<<PRUSI) | (1<<PRTIM0) | (1<<PRTIM1); // disable all other modules
}

// following
// https://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html#ga3775b21f297187752bcfc434a541209a
void sleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();
  sleep_enable();
  sleep_bod_disable();
  sei();
  sleep_cpu();
}

// watchdog interrupt is the only time the micro-controller is not in power save
// mode
ISR(WDT_vect) {
  PORTB |= (1<<PB0);
  _delay_ms(1);
  PORTB &= ~(1<<PB0);
  sleep(); // back to sleep
}


int main(void) {
  initPowerSave();
  initWatchdog();
  sleep(); // start sleeping; 
  sleep_disable(); // this is never reached since the watchdog interrupt always puts the microcontroller back to sleep.
}
