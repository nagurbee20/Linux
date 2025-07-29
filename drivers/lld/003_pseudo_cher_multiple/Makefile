
KDIR := /lib/modules/$(shell uname -r)/build

obj-m := psd_n.o

#TDIR:= 

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

#target:
#	make -C 

