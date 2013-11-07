#!/bin/sh

#modprobes
modprobe i2c-cns3xxx
modprobe ehci-hcd
umount /proc/bus/usb
mount -t usbfs none /proc/bus/usb 
modprobe cns3xxx
ifconfig eth0 192.168.0.111

tftp -l passfailtest -r passfailtest -g 192.168.0.102
tftp -l usbcontrol.dat -r sdhcicontrol.dat -g 192.168.0.102
#
#md5test on mmc
modprobe sdhci-cns3xxx
modprobe mmc-block 
mkdir /mnt/mmc
mount /dev/mmcblk0p1 /mnt/mmc
touch test.vim
md5sum test.vim > t.md5
cp test.vim /mnt/mmc/test.vim
cd /mnt/mmc
md5sum -c ../../t.md5 >>/results.dat
cd /
#

#running c applications now
./passfailtest sdhcicontrol.dat
rm results.dat
