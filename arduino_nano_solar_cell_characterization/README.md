Recording characteristic U-I and U-P curve for small solar cells.

stty -F /dev/ttyUSB0 115200 && cat /dev/ttyUSB0 | tee test.csv 
python plot.py

more details at 
http://julianstraub.com/posts/arduino_solar_cell_characterization/
