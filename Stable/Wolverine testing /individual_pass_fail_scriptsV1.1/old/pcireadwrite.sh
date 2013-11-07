#!/bin/sh



current=`setpci -d 168c:001b 0x3C.B`
setpci=`setpci -d 168c:001b0x3C.B=aa`
echo $setpci



