#!/bin/bash
modprobe sdhci-cns3xxx
modprobe mmc-block 
mkdir /mnt/mmc
mount /dev/mmcblk0p1 /mnt/mmc/
cd /mnt/mmc/i2c_Econa

#./setconfig 0x74 $1
for (( ; ; ))

do
   eeprog -f /dev/i2c-0 $1 -r 0x00:1 
   
done
