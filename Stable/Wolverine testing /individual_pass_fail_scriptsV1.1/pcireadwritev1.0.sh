#!/bin/sh


tmp='aa_aa'

setpci=`setpci -d 168c:001b 0x3C.B=aa`

current=`setpci -d 168c:001b 0x3C.B | tr -d ' '`
current=$(echo $current | tr ' ' _ | tr \" ' ')

echo $current
echo $tmp
if [ "$current" = "$tmp" ];
then echo "PCI read/write Test - Passed"
else echo "PCI read/write Test - Failed"
fi  




