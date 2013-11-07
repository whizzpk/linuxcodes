#!/bin/sh
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
tftp -l passfailtest -r passfailtest -g 192.168.0.102
tftp -l usbcontrol.dat -r usbcontrol.dat -g 192.168.0.102

#move results control file to board root

#
chmod 777 passfailtest

lsusb >> results.dat

#running c applications now
./passfailtest usbcontrol.dat

rm results.dat
