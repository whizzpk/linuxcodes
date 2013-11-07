#!/bin/sh
modprobe cns3xxx

#COUNTER=20
#         until [  $COUNTER -lt 10 ]; do
             #SDA using GPIO 10
		SDA=`echo direct output 10 1 > /proc/cns3xxx/gpio`
		sethighSDA=`echo set value 10 1 > /proc/cns3xxx/gpio`

		#SCK using GPIO 11
		SCK=`echo direct output 11 1 > /proc/cns3xxx/gpio` 
		sethighSCK=`echo set value 11 1 > /proc/cns3xxx/gpio`

		#Delay 100ms
		for i in `seq 1 3`;
			do
				echo $i
			done   

		#turning SDA low
		SDA=`echo direct output 10 0 > /proc/cns3xxx/gpio`
		setlowSDA=`echo set value 10 0 > /proc/cns3xxx/gpio`
		for i in `seq 1 3`;
			do
				echo $i
			done  
 #            let COUNTER+=1
  #       done

	


#test=`echo ` 
#state=`dmesg | tail -n 1 | cut -d= -f 3`
#tmp='0'

#echo $tmp
#echo $state
#if [ $state = $tmp ];
#then echo ""
#else echo ""
#fi  

