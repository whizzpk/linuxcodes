#!/bin/sh
insmod usbserial.ko
insmod GobiSerial.ko
./microcom -D/dev/ttyUSB0


