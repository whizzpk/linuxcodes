#!/bin/sh
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
tftp -l passfailtestlocal -r passfailtestlocal -g 192.168.0.102

#move results control file to board root

#
chmod 777 passfailtestlocal
lspci >> results.dat
lsusb >> results.dat

#running c applications now
./passfailtestlocal results.dat

rm results.dat
