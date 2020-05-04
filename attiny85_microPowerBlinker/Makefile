MCU=attiny85
F_CPU=1000000
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c

all:
	        ${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
					        ${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	        avrdude -p ${MCU} -c usbtiny -U flash:w:${TARGET}.hex:i

clean:
	        rm -f *.bin *.hex

