#!/bin/sh
var1="sudo setpci -s 00:02.0 f4.b | tr [:lower:] [:upper:]";
var2=$(echo "obase=16;ibase=16;${var1} + 48" |bc)
sudo setpci -s 00:02.0 f1.b=$var2
