MCU=atmega328p
F_CPU=16000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -Wl,-u,vfprintf -lprintf_flt -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c adc.c serial.c

all:
	        ${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
					        ${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	        avrdude -p ${MCU} -c arduino -U flash:w:${TARGET}.hex:i -P /dev/ttyUSB0 -b 57600

clean:
	        rm -f *.bin *.hex

