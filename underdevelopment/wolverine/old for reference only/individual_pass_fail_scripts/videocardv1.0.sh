#!/bin/sh
modprobe i2c-cns3xxx


#move results control file to board root

#
chmod 777 passfailtestlocal

## video card gpio test
vidtest=`echo direct input 12 > /proc/cns3xxx/gpio` 
vidtest=`echo get value 12 > /proc/cns3xxx/gpio` 
dmesg | tail -n 1 | cut -d] -f 2 >> results.dat   
# video card gpio test

#running c applications now
./passfailtestlocal videocontrolresults.dat

#
rm results.dat
