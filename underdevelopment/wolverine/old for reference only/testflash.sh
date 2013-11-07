# set file size below
size="100" #[MB]
txtgrn=$(tput setaf 2)
txtred=$(tput setaf 1)
txtrst=$(tput sgr0)
txtblu=$(tput setaf 4)
bold=$(tput bold)



cd /media
df -h | grep "/dev/sd*"
echo "$txtblu $bold Reference above to select the drive to copy to (Ctrl+c to exit):$txtrst "
echo "$txtgrn $bold THIS IS DESIGNED FOR A SMALL CAPACITY DRIVE$txtrst"

select drive in *; 
do

dd if=/dev/zero of=/tmp/$size''MB bs=1M count=$size
z=$(echo $?)
if test $z -eq 0
then
cd /tmp 
for i in {1..5}; do cp $size''MB /media/$drive/$size''MB_$i; done

wait
cd /tmp
a=$(md5sum $size''MB | cut -d ' ' -f 1)
b=$(md5sum /media/$drive/$size''MB_1 | cut -d ' ' -f 1)
c=$(md5sum /media/$drive/$size''MB_2 | cut -d ' ' -f 1)
d=$(md5sum /media/$drive/$size''MB_3 | cut -d ' ' -f 1)
e=$(md5sum /media/$drive/$size''MB_4 | cut -d ' ' -f 1)
f=$(md5sum /media/$drive/$size''MB_5 | cut -d ' ' -f 1) 
echo $a

echo $b
if test $a=$b
then echo "$txtgrn MATCH $txtrst"
else echo "MISMATCH"
fi
echo $c
if test $a=$c
then echo "$txtgrn MATCH $txtrst"
else echo "MISMATCH"
fi
echo $d
if test $a=$d
then echo "$txtgrn MATCH $txtrst"
else echo "MISMATCH"
fi
echo $e
if test $a=$e
then echo "$txtgrn MATCH $txtrst"
else echo "MISMATCH"
fi
echo $f
if test $a=$f
then echo "$txtgrn MATCH $txtrst"
else echo "MISMATCH"
fi

diff $size''MB /media/$drive/$size''MB_1 -s
g=$(echo $?)
diff $size''MB /media/$drive/$size''MB_2 -s
h=$(echo $?)
diff $size''MB /media/$drive/$size''MB_3 -s
j=$(echo $?)
diff $size''MB /media/$drive/$size''MB_4 -s
k=$(echo $?)
diff $size''MB /media/$drive/$size''MB_5 -s
l=$(echo $?)


		if test $a=$b,$c,$d,$e,$f
		then echo $txtgrn$bold"MD5 PASS $txtrst"
		else echo $txtred$bold"MD5 FAIL $txtrst"
		fi
		if test $g=$h,$j,$k,$l
		then echo $txtgrn$bold"Diff PASS $txtrst"
		else echo $txtred$bold"Diff FAIL $txtrst"
		fi
else
echo"$txtred $bold RUN AS ROOT$txtrst"
fi
	
df -h | grep "/dev/sd*"
echo "$txtblu $bold Reference above to select the drive to copy to (Ctrl+c to exit):$txtrst "
echo "$txtgrn $bold THIS IS DESIGNED FOR A SMALL CAPACITY DRIVE$txtrst"
cd /media
ls
done




