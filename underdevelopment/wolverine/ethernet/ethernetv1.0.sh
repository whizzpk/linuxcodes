#!/bin/sh

a="5 packets transmitted, 5 packets received, 0% packet loss"
b=`ping -c 5 -q 192.168.1.103 | grep packets | cut -d ] -f 2`
c=`ping -I eth1 -c 5 -q 192.168.1.103 | grep packets | cut -d ] -f 2`
d=`ping -I eth2 -c 5 -q 192.168.1.103 | grep packets | cut -d ] -f 2`
if [ "$a" = "$b" ];
then  
	     echo "eth0 ETHERNET TEST - PASSED "
	
else echo "eth0 ETHERNET TEST - FAILED"
fi

if [ "$a" = "$c" ];
then  
	     echo "eth1 ETHERNET TEST - PASSED "
	
else echo "eth1 ETHERNET TEST - FAILED"
fi

if [ "$a" = "$d" ];
then  
	     echo "eth2 ETHERNET TEST - PASSED "
	
else echo "eth2 ETHERNET TEST - FAILED"
fi





