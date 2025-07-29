
KDIR := /lib/modules/$(shell uname -r)/build

obj-m := pseudo.o

#TDIR:= 

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean

#target:
#	make -C 

