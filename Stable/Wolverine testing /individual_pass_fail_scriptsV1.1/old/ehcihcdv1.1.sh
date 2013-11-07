#!/bin/sh



mkdir /mnt/usb

mount /dev/sda1 /mnt/usb
touch test.vim
md5sum test.vim > t.md5
cp test.vim /mnt/usb/test.vim
cd /mnt/usb
md5sum -c ../../t.md5 >>/results.dat
cd /
#

#running c applications now
./passfailtest ehcihcdcontrol.dat
rm results.dat



