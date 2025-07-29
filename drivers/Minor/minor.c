#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

dev_t driver=0;
static int __init minor(void)
{
	if((alloc_chrdev_region(&driver,0,1,"Embetronix-driver"))< 0)
	{
		printk(KERN_INFO "Cannot allocate major number for device");
		return -1;
	}

	printk(KERN_INFO "MAJOR :%d and MINOR : %d \n",MAJOR(driver),MINOR(driver));
	printk(KERN_INFO "driver inserted succesfully\n");

	return 0;
}
module_init(minor);

void __exit stop(void)
{
	unregister_chrdev_region(driver,1);
	printk(KERN_INFO "Driver Removed Succesfully");
}
module_exit(stop);

MODULE_LICENSE("GPL");
MODULE_VERSION("1:3.0");
MODULE_AUTHOR("NAGURBEE");
MODULE_DESCRIPTION("DYNAMIC ALLOCATION PROCESS FOR MAJOR NUMBER");




	

	
