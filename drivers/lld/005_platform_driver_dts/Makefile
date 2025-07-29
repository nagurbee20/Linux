
KDIR := /lib/modules/$(shell uname -r)/build

obj-m := platform_driver_dtsi.o

#TDIR:= 

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

#target:
#	make -C 

