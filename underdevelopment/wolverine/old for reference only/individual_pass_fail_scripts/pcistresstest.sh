#!/bin/sh
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
tftp -l passfailtest -r passfailtest -g 192.168.0.102
tftp -l pcistresstestcontrol.dat -r pcistresstestcontrol.dat -g 192.168.0.102

#move results control file to board root

#netperf for board
./netserver
#start pining server
./netperf -H 192.168.0.xxx

#running c applications now
./passfailtest





