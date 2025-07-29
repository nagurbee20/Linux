#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/fs.h>

dev_t dev = MKDEV(23,0);

static int __init major(void)
{
	 register_chrdev_region(dev,1,"embetronix-driver");

	printk(KERN_INFO "MAjor module inserted sucessfully");
	printk(KERN_INFO " MAJOR NUMBER IS %d and MINOR NUMBER IS :%d ", MAJOR(dev),MINOR(dev));

	return 0;
}
module_init(major);
 
void __exit stop(void)
{
	 unregister_chrdev_region(dev,1);

	printk(KERN_INFO "major module removed successfully");

}
module_exit(stop);
MODULE_LICENSE("GPL");
MODULE_VERSION("1:3.0");
MODULE_DESCRIPTION("MAJOR AND MINOR NUMBER");
MODULE_AUTHOR("NAGURBEE");

