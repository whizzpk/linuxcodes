#!/bin/sh
modprobe i2c-cns3xxx




mychk1="yes"
until [ "x$mychk" == "yes"  ]
do
	echo -n "type '0' for lane 0 '1' for lane one and press enter or 'test' to run 		pci enumeration and other tests."
	read val
    
	if [ "x$val" == "x0" ] ; then
	echo -n "testing lane 0"
	 lspci -s 0000:00:00.0
	fi

	if [ "x$val" == "x1" ] ; then
	echo "testing lane 0"
	lspci -s 0001:00:00.0
	fi
	echo "continue lane tests [yes] [no]"
    	read mychk1
    
done

if ["x$val" = "xtest" ] ; then
echo "pci enumeration"
lspci
 ./mytest
echo "usb listing"
 ./mytest
 echo "pci listing"
 lscpi
wait

mychk="yes"
until [ "x$mychk" == "yes"  ]
do
    echo "enter parameters for i2c read write"
    read params
    ./crosscompiledi2cinfocast $params
    echo "continue i2c checks [yes] [no]"
    read mychk
    
done



fi

pathremove () {
        local IFS=':'
       local NEWPATH
        local DIR
        local PATHVARIABLE=${2:-PATH}
        for DIR in ${!PATHVARIABLE} ; do
                if [ "$DIR" != "$1" ] ; then
                  NEWPATH=${NEWPATH:+$NEWPATH:}$DIR
                fi
        done
        export $PATHVARIABLE="$NEWPATH"
}

pathprepend () {
        pathremove $1 $2
        local PATHVARIABLE=${2:-PATH}
        export $PATHVARIABLE="$1${!PATHVARIABLE:+:${!PATHVARIABLE}}"
}

pathappend () {
        pathremove $1 $2
        local PATHVARIABLE=${2:-PATH}
        export $PATHVARIABLE="${!PATHVARIABLE:+${!PATHVARIABLE}:}$1"
}

pathredefine () {
	total read_directories $1 $2
	global path_variable=${}
}

exit









