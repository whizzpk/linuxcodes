#!/bin/sh

password="ges"

set_value_to=$(zenity --title="Brightness control" --scale --text="Adjust the     brightness value" --min-value=5 --max-value=95 --value=90)

echo $password | sudo -S setpci -s 00:02.0 f1.b=$set_value_to
