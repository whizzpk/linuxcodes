#!/bin/sh
rmdir /mnt/mmc
umount /mnt/mmc
mkdir /mnt/mmc
mount /dev/mmcblk0p1 /mnt/mmc
touch test.vim
a=$(md5sum test.vim | cut -d ' ' -f 1)

cp test.vim /mnt/mmc/test.vim
b=$(md5sum /mnt/mmc/test.vim | cut -d ' ' -f 1)
cd /
#

echo $a

echo $b
if [ $a = $b ]
then echo "******** \n *********************SDHCI Test - Passed******** \n *********************"
else echo "******** \n *********************SDHCI Test - Failed******** \n *********************"
fi
rmdir /mnt/mmc


