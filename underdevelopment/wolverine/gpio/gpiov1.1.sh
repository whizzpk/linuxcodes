#!/bin/sh



#GPIO LED TESTS

## Setting all GPIO driven LEDs to High
gpio0_sethigh=`echo direct output 0 1 > /proc/cns3xxx/gpio` 
gpio1_getstate=`echo get value 0 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='1'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi

gpio1_sethigh=`echo direct output 1 0 > /proc/cns3xxx/gpio` 
gpio1_getstate=`echo get value 1 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='0'
tmp2=
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi


gpio8_sethigh=`echo direct output 8 1 > /proc/cns3xxx/gpio` 
gpio8_getstate=`echo get value 8 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='1'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi

gpio

gpio10_sethigh=`echo direct output 10 0 > /proc/cns3xxx/gpio` 
gpio10_getstate=`echo get value 10 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='0'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi


gpio11_sethigh=`echo direct output 11 1 > /proc/cns3xxx/gpio` 
gpio11_getstate=`echo get value 11 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='1'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi


gpio12_sethigh=`echo direct output 12 1 > /proc/cns3xxx/gpio` 
gpio12_getstate=`echo get value 12 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='1'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi


gpio13_sethigh=`echo direct output 13 0 > /proc/cns3xxx/gpio` 
gpio1_getstate=`echo get value 13 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='0'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi

gpio14_sethigh=`echo direct output 14 1 > /proc/cns3xxx/gpio` 
gpio14_getstate=`echo get value 14 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='1'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi


gpio52_sethigh=`echo direct output 52 1 > /proc/cns3xxx/gpio` 
gpio52_getstate=`echo get value 52 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='1'
boolchk='1'
echo $tmp
echo $state
if [ $state = $tmp ];
	then 
	boolchk=1
	else boolchk=0
fi


if [ $boolchk = $tmp ];
	then 
	echo "GPIO TEST - PASSED"
	else echo "GPIO TEST - FAILED"
fi
