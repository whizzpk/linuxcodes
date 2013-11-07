#!/bin/sh
#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
#
modprobe i2c-cns3xxx

ifconfig eth0 192.168.0.111
tftp -l passfailtest -r passfailtest -g 192.168.0.102
tftp -l i2ccontrol.dat -r i2ccontrol.dat -g 192.168.0.102
#I2C switch

#To set lane  1 for pci plx switch

./setconfig 0x74 0x2 >>results.dat

./getconfig 0x74 >>results.dat
#
#I2C switch

#To set lane  A for gps
./setconfig 0x74 0x10 >>results.dat 
eeprog /dev/i2c-0 0x42 -x -r 0xff:1 >>results.dat
#

#running c applications now
./passfailtest i2ccontrol.sh

rm results.dat
