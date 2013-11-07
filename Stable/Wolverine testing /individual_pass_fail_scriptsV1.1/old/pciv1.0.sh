#!/bin/sh
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx

#move results control file to board root

#
chmod 777 passfailtest
lspci >> results.dat


#running c applications now
./passfailtest pcicontrol.dat

rm results.dat
