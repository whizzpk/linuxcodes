#!/bin/sh
#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
tftp -l passfailtest -r passfailtest -g 192.168.0.102
tftp -l memorycontrol.dat -r memorycontrol.dat -g 192.168.0.102
#
#memory test
memtester 1 1 
dmesg | grep Memory | cut -d ] -f 2 >> results.dat
#memory test

#running c applications now
./passfailtest memorycontrol.dat
rm results.dat
