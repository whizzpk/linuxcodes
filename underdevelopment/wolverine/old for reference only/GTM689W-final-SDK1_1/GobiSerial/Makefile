obj-m := GobiSerial.o
KDIR := /home/mani/Desktop/remoteboard/cns3xxx-sdk/kernel/linux
PWD := $(shell pwd)

all: clean
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.* modules.order
