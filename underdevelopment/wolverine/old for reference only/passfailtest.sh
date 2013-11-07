#!/bin/sh
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
tftp -l passfailtest -r passfailtest -g 192.168.0.102
chmod 777 passfailtest
lspci >> results.dat
lsusb >> results.dat
ifconfig eth0 | grep UP >> results.dat

./passfailtest

