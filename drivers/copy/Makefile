#Makefile to build modules

KDIR := /lib/modules/$(shell uname -r)/build

#module name
MODULE := param

#sourece files

obj-m := $(MODULE).o


#default target

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
