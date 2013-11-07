#!/bin/sh
#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
#
#I2C switch

#To set lane  1 for pci plx switch

./setlane 0x74 0x1 >>results.dat

./getconfig 0x74 >>results.dat
#
#I2C switch

#To set lane  A for gps
./setlane 0x74 0xA >>results.dat
eeprog /dev/i2c-0 0x42 -x -r 0xff:2
#

#running c applications now
./passfailtest i2ccontrol