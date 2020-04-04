#!/usr/bin/env bash

# setup the baud rate
stty -F /dev/ttyUSB0 115200
# output the received data to the terminal
cat /dev/ttyUSB0 | tee log.log
