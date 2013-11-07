#!/bin/sh

maincheck=1
#interfacetest


#move results cont

## video card gpio test
interfacetest=`echo direct input 60 > /proc/cns3xxx/gpio` 
interfacetest=`echo get value 60 > /proc/cns3xxx/gpio` 
state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='0'
echo $tmp
echo $state
if [ $state = $tmp ];
then echo "*********\n**********Interface board detection Test - Passed**********\n**********************"
else echo "*********\n**********Interface board detection Test - Failed*********\n**********"
     maincheck=0
fi  

#ehci
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
		     maincheck=0
	     fi
fi
	   


rm /mnt/usb/test.vim

umount /mnt/usb
rmdir /mnt/usb





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
		maincheck=0
fi

#ramtest
rm /tmp/memtest2

touch /tmp/memtest2

mount -t tmpfs -o size=400M tmpfs /tmp

dd if=/dev/urandom bs=700000 of=/tmp/memtest2 count=1



a=$(md5sum /tmp/memtest2 | cut -d ' ' -f 1)
b=$(md5sum /tmp/memtest2 | cut -d ' ' -f 1)
c=$(md5sum /tmp/memtest2 | cut -d ' ' -f 1)

#


if [ $a = $b ];
 then if [ $a = $c ];
	then echo " RAM Test - PASSED "
	else echo "Fail"
	     maincheck=0
      fi  
 
fi

#sdhci
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
if test $a=$b
then echo "SDHCI Test - Passed"
else echo "SDHCI Test - Failed"
     maincheck=0
fi

#videocard



## video card gpio test
vidtest=`echo direct input 12 > /proc/cns3xxx/gpio` 
vidtest=`echo get value 12 > /proc/cns3xxx/gpio` 
  state=`dmesg | tail -n 1 | cut -d= -f 3`
tmp='0'
echo $tmp
echo $state
if [ $state = $tmp ];
then echo "videocard board detection Test - Passed"
else echo "videocard board detection Test - Failed"
     maincheck=0
     #checking if maincheck == 0 if not add to list and intiialize 
fi

#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#################  


if [ $? = 0 ];
then echo "Sim Card - Passed"
else echo "Sim Card - Failed"
maincheck=0
     
fi
#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
################# 
#################		
#################			
#		#		
#		#		
#		#
#		#
#		#
#		#
#################		
#		#
#		#
#		#
#		#
#		#
#		#
#################  


if [ $? = 0 ];
then echo "Rs485 - Passed"
else echo "Rs485 - Failed"
maincheck=0
     
fi
#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#################  

#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#################  

./rs232v1.1
if [ $? = 0 ];
then echo "Rs232 - Passed"
else echo "Rs232 - Failed"
	maincheck=0
     
fi
#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
################# 
if [ $maincheck = 0 ];
then
 echo "#######################"	
 echo "####board - Failed#####"
 echo "#######################"	
else 
echo "#######################"	
echo "#####board - Passed####"
echo "#######################"	     
fi

#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#############
#		#           #  
#		#           #
#		#           #########
#		#           #       #
#		#           #       #
#		#           #       #
#		#           #       #
####################################################
###################################################		   
##################################################			
#################################################		
#		                               #
#		                              #
#		                             #
#		                            #
#		                           #
#		                          #
#		                         #
#		                        #
#		                       #
#		                      #
#		                     #
##################################### 
#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
################# 
#################		
#		#	
#		#		
#		#		
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
#		#
################# 
