#!/bin/sh



a="0000:00:00.0 PCI bridge: Cavium Networks Device 3400\
0000:00:01.0 PCI bridge: PLX Technology, Inc. Device 8603 (rev ab)\
0000:02:01.0 PCI bridge: PLX Technology, Inc. Device 8603 (rev ab)\
0000:02:02.0 PCI bridge: PLX Technology, Inc. Device 8603 (rev ab)\
0001:00:00.0 PCI bridge: Cavium Networks Device 3400\
0001:00:01.0 PCI bridge: PLX Technology, Inc. PEX8112 x1 Lane PCI Express-to-PCI Bridge (rev aa)"
b=`lspci`




#
tmp='aa_aa'

setpci=`setpci -d 168c:001b 0x3C.B=aa`

current=`setpci -d 168c:001b 0x3C.B | tr -d ' '`
current=$(echo $current | tr ' ' _ | tr \" ' ')

if [ xx$axx = xx$bxx ];
then 
	echo "*************$'\n' *********PCI read/write Test - Passed******** $'\n' *********************"
	if [ "$current" = "$tmp" ];
	then 
	     echo "$txtgrn PCI ENUMERATION - PASSED $txtrst"
	else echo "*************$'\n' *********PCI read/write Test - Failed******** $'\n' *********************"
	fi  
	
else echo "******** $'\n' *********************PCI ENUMERATION - FAILED******** $'\n' *********************"
fi


