
#!/bin/bash
modprobe i2c-cns3xxx
echo run tests?
read val

if [ "x$val" = "xyes" ] ; then
echo -n "usb pci"
lspci
 ./mytest&
echo -n "usb listing"
 ./mytest&
 echo -n "pci listing"
 lscpi&
wait

mychk="yes"
until [ "x$mychk" == "yes"  ]
do
    echo -n "enter parameters for i2c read write"
    read params
    ./crosscompiledi2cinfocast $params
    echo -n "continue i2c checks [yes] [no]"
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









