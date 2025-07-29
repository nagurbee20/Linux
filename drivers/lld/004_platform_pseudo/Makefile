
KDIR := /lib/modules/$(shell uname -r)/build

obj-m := pcd_device_setup.o pcd_platform_driver.o

#TDIR:= 

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

#target:
#	make -C 

