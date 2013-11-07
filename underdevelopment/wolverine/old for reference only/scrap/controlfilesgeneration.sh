#!/bin/sh
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111


#pcicontrolfile generation

lspci >> pcicontrol.dat



#usbcontrolfile generation
lsusb >> usbcontrol.dat

#memorycontrolfile generation
memtester 1 1 
dmesg | grep Memory | cut -d ] -f 2 >> memorycontrol.dat
#memory test

#sdhcicontrolfile generation

#md5test on mmc
modprobe sdhci-cns3xxx
modprobe mmc-block 
mkdir /mnt/mmc
mount /dev/mmcblk0p1 /mnt/mmc
touch test.vim
md5sum test.vim > t.md5
cp test.vim /mnt/mmc/test.vim
cd /mnt/mmc
md5sum -c ../../t.md5 >>/sdhcicontrol.dat
cd /
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


