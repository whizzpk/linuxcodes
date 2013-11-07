#!/bin/sh
#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 

#
#memory test
memtester 1 1 
dmesg | grep Memory | cut -d ] -f 2 >> results.dat
#memory test

#running c applications now
./passfailtest memorycontrol.dat
rm results.dat
