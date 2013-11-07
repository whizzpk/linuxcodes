#!/bin/sh

#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111
#
#md5test on mmc
modprobe sdhci-cns3xxx
modprobe mmc-block 
mkdir /mnt/mmc
mount /dev/mmcblk0p1 /mnt/mmc
tftp -l test.vim -r test.vim -g 192.168.0.102
md5sum *.vim > t.md5
cp test.vim /mnt/mmc/test.vim
cd /mnt/mmc
md5sum -c ../../t.md5 >>results.dat
#

#running c applications now
./passfailtest sdhcicontrol