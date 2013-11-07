#!/bin/sh

#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx

#
#md5test on USB
modprobe ehci-hcd

mkdir /mnt/usb

mount /dev/sda1 /mnt/usb
touch test.vim
md5sum test.vim > t.md5
cp test.vim /mnt/usb/test.vim
cd /mnt/usb
md5sum -c ../../t.md5 >>/ehcihcdcontrol.dat


cd /
#




