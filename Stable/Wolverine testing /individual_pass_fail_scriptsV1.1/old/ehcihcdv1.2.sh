#!/bin/sh
mkdir /mnt/usb

mount /dev/sda1 /mnt/usb
touch test.vim
a=$(md5sum test.vim | cut -d ' ' -f 1)
md5sum test.vim > t.md5
cp test.vim /mnt/usb/test.vim
b=$(md5sum /mnt/usb/test.vim | cut -d ' ' -f 1)


#
echo $a

echo $b
if test $a=$b
then echo "Ehcihcd test - Passed"
else echo "Ehcihcd test - Failed"
fi

umount /dev/sda1
rmdir /mnt/usb



