#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdbool.h>

#include "adc.h"
#include "serial.h"
#include "eeprom.h"
#include "ring_buffer.h"
#include "delta_encoder.h"

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
  initAdc(); // init adc
  initSerial(); // init serial connection to 115200 baud, 8bit, 1 stop bit.

  char buf[200];
  uint16_t adc0=0;
  uint16_t adc1=0;
  struct RingBuffer adcs0;
  struct RingBuffer adcs1;
  Init(&adcs0);
  Init(&adcs1);

  struct DeltaEncoder del0;
  struct DeltaEncoder del1;

  uint16_t* eepAdr = 0;
  const uint16_t* eepMax = (uint16_t*) 0x0400;

  // show initial memory
  LED1_ON;
  adc0 = eeprom_read_word(eepAdr++);
  adc1 = eeprom_read_word(eepAdr++);
  sprintf(buf, "%f\t%f\n", toVoltage(adc0, 5.0f), toVoltage(adc1, 5.0f));
  writeSerialStr(buf);
  int16_t deltas = 0;
  int8_t delta0 = 0;
  int8_t delta1 = 0;
  while (adc0 < 1024 && adc1 < 1024) {
    deltas = eeprom_read_word(eepAdr++);
    // split 16bit into two 8bit deltas
    delta0 = 0x00ff & deltas;
    delta1 = (0xff00 & deltas) >> 8;
    adc0 += delta0;
    adc1 += delta1;
    if (adc0 < 1024 && adc1 < 1024) {
      sprintf(buf, "%f\t%f\n", toVoltage(adc0, 5.0f), toVoltage(adc1, 5.0f));
      writeSerialStr(buf);
    }
    if (eepAdr >= eepMax) {
      break;
    }
  }
  _delay_ms(1000);
  LED1_OFF;

  adc0 = 0;
  adc1 = 0;

  eepAdr = 0; // reset address
  uint32_t t = 0; // time in 1024ms increments.
  // 1k byte eeprom => 512 word => 510 samples
  // log every 1min: 4.3h
  // log every 5min: 21.3h
  // log every 675s: 48h
  uint32_t logEverySec = 169; // total of 48h;
  bool pressedPrev = false; //state of button press
  while(42) { 

    adc0 = readAdc(0);
    adc1 = readAdc(1);
    Insert(&adcs0, adc0);
    Insert(&adcs1, adc1);
    sprintf(buf, "%u\t%f\t%f\n", (unsigned int)t, toVoltage(MeanFloat(&adcs0), 5.0f), toVoltage(MeanFloat(&adcs1), 5.0f));
    writeSerialStr(buf);

    // wait for about 1s
    uint16_t i=0;
    while(i++ < 1000) {_delay_ms(1);}
    LED1_OFF;

    // simple state machine that finds when a button on PB4 is released
    // when that happens the memory is erased.
    if (!(PIND & (1<<BUT0))) {
      sprintf(buf, "pressed \n");
      writeSerialStr(buf);
      pressedPrev = true;
    } else {
      if (pressedPrev) {
        sprintf(buf, "releasing -> erasing \n");
        writeSerialStr(buf);
        LED1_ON;
        _delay_ms(100);
        LED1_OFF;
        eraseEeprom();
        eepAdr = 0; // reset address so that we start logging at the beginning
        t = 0; // reset time so that logging begins immediately.
        LED0_ON; // turn on on board LED to show we are in logging mode

        // write first two full values
        eeprom_update_word(eepAdr++, Mean(&adcs0)); 
        eeprom_update_word(eepAdr++, Mean(&adcs1)); 
        // initialize delta encoder from those values
        InitDeltaEncoder(&del0, Mean(&adcs0));
        InitDeltaEncoder(&del1, Mean(&adcs1));
      }
      pressedPrev = false;
    }

    // log every logEverySec seconds if there is still space in the eeprom.
    if (t++ % logEverySec == logEverySec-1 && eepAdr < eepMax) {
      uint16_t rd = eeprom_read_word(eepAdr);
      // if this is an unwritten field write to it
      if (rd == 0xffff) {
        LED1_ON;
        delta0 = UpdateDelta(&del0, Mean(&adcs0));
        delta1 = UpdateDelta(&del1, Mean(&adcs1));
        // combine 8bit deltas into a 16bit value
        deltas = (delta1<<8) | (delta0 & 0xff);
        eeprom_update_word(eepAdr++, deltas); 
        sprintf(buf, "t=%u -> logging %p: %d %d %d\n", (unsigned int)t, eepAdr, delta0, delta1, deltas);
        writeSerialStr(buf);

      } else {
        sprintf(buf, "t=%u -> not overwriting\t%p\n", (unsigned int)t, eepAdr);
        writeSerialStr(buf);
      }
    }
    if (eepAdr >= eepMax) {
        LED0_OFF; // turn off on board LED to show memory is full
    }
  }
}
