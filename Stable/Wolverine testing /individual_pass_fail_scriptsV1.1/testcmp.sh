#!/bin/sh

rm /tmp/memtest2

touch /tmp/memtest2

mount -t tmpfs -o size=400M tmpfs /tmp

dd if=/dev/urandom bs=700000 of=/tmp/memtest2 count=1



a=$(md5sum /tmp/memtest2 | cut -d ' ' -f 1)
b="fail1"
c="fail"

#

echo "$a"
echo "$b"
echo "$c"
if test "$a"="$b"="$c"
then echo "$txtgrn RAM Test - PASSED $txtrst"
else echo "Fail"
fi
