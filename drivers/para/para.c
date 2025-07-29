#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>

int valueETX,valueARRAY[5];
char *nameETX;
int value_cb =0;

module_param(valueETX,int,S_IWUSR|S_IRUSR);
module_param(nameETX,charp,S_IWUSR|S_IRUSR);
module_param_array(valueARRAY,int,NULL,S_IWUSR|S_IRUSR);

static int notify(const char *val,const struct kernel_param *kp)
{
	int res = param_set_int(val,kp);
	if (res == 0)
	{
		printk(KERN_INFO " value_cb is being changed");
		printk(KERN_INFO "value_cb is :%d",value_cb);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param =
{
	
	.set = &notify,
	.get = &param_get_int,
};
module_param_cb(value_cb,&my_param,&value_cb,S_IRUGO|S_IWUSR);

static int __init param(void)
{
	int i;
	printk(KERN_INFO "the value of ValueETX is : %d\n",valueETX);
	printk(KERN_INFO "nameETX :%s\n ",nameETX);
	printk(KERN_INFO "value_cb : %d\n",value_cb);

	for( i =0;i < (sizeof valueARRAY /sizeof(int));i++)
	{
		printk(KERN_INFO "%d  ",valueARRAY[i]);
	}

	printk(KERN_INFO "kernel module inserted succesfully");

	return 0;
	}
	module_init(param);

static void __exit stop(void)
{
printk("Kernel Module removed succcessfully");

}
module_exit(stop);

MODULE_AUTHOR("NAGURBEE <NAGURBEEY@GMAIL.COM>");
MODULE_LICENSE("GPL");
MODULE_VERSION("1:1.2");
MODULE_DESCRIPTION("SIMPE CODE ON MODULE PARAMTERES");

