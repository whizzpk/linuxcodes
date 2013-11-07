#!/bin/sh


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
