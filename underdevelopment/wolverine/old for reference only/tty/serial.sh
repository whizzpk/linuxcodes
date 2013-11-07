#!/bin/bash
modprobe sdhci-cns3xxx
modprobe mmc-block 
mkdir /mnt/mmc
mount /dev/mmcblk0p1 /mnt/mmc
cd /mnt/mmc
chmod 777 serial.sh
for (( ; ; ))
do
   sudo echo "1" > /dev/ttyS1 
   sudo echo "2" > /dev/ttyS2 
   
done
