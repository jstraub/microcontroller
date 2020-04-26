#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdbool.h>

#include "adc.h"
#include "serial.h"
#include "ring_buffer.h"
#include "pwm.h"

#include <avr/eeprom.h>

#define BUT0 PD2
#define LED0 PB5
#define LED1 PD3

#define LED0_OFF  PORTB &= ~(1<<PB5)
#define LED0_ON   PORTB |= (1<<PB5)

#define LED1_OFF  PORTD &= ~(1<<PD3)
#define LED1_ON   PORTD |= (1<<PD3)

void initPorts() {
  DDRD &= ~(1<<BUT0); // input for reset button
  PORTD |= (1<<BUT0); // pull-up on
  DDRD |= (1<<LED1); // green LED
  DDRB |= (1<<LED0) ; // red status LEDs
  LED1_OFF;
  LED0_OFF;
}

int main(void) {

  initPorts();
  initAdc1dot1Ref(); // init adc from 1.1V ref
  initSerial(); // init serial connection to 115200 baud, 8bit, 1 stop bit.
  initPwm();

  char buf[200];
  struct RingBuffer adcs;

  // turn off and let things settle
  OCR1A = 0;
  OCR1B = 0;
  _delay_ms(1000);
  LED1_ON;
  for (uint16_t r=0; r<1024; ++r) {
    OCR1A = r;
    OCR1B = r;
    // give capacitor time to reach steady state
    _delay_ms(200);
    // current set point
    float i = ((float)r/1024.f)*0.6f/100.f;
    // collect voltage averaged over 10 samples
    Init(&adcs);
    for (uint16_t i=0; i<10; ++i) {
      Insert(&adcs, readAdc(0));
      _delay_ms(10);
    }
    const float u_be = 0.7f;
    const float u_ce = 0.2f;
    float u = toVoltage(MeanFloat(&adcs), 6.27f);
    if (u < u_be + u_ce) 
      break;
    // send out over serial
    sprintf(buf, "%f\t%f\n", i, u);
    writeSerialStr(buf);
  }
  LED1_OFF;
  OCR1A = 0;
  OCR1B = 0;
}
