#!/bin/sh
modprobe i2c-cns3xxx


#move results cont

## video card gpio test
 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='0'
echo $tmp
echo $state
if [ $state = $tmp ];
then echo "Interface board detection Test - Passed"
else echo "Interface board detection Test - Failed"
fi  

