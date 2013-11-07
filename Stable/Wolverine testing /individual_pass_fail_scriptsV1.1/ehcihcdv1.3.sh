#!/bin/sh
mkdir /mnt/usb
umount /mnt/usb
mount /dev/sd*1 /mnt/usb
detection=$(mount | grep /mnt/usb | wc -l)
touch test.vim
a=$(md5sum test.vim | cut -d ' ' -f 1)
md5sum test.vim > t.md5
cp test.vim /mnt/usb/test.vim
b=$(md5sum /mnt/usb/test.vim | cut -d ' ' -f 1)


tmp='1'
#
echo $a

echo $b
echo $detection
echo $tmp
if [ $a = $b ]
	then if [ $detection = $tmp ]
		then echo "Ehcihcd test - Passed"
		else echo "Ehcihcd test - Failed"
	     fi
fi
	   


rm /mnt/usb/test.vim

umount /mnt/usb
rmdir /mnt/usb


