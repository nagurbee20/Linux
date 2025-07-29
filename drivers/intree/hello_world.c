//#include<linux/kernel.h>
#include<linux/module.h>
//#include<linux/init.h>

static int __init hello_world_init(void)
{
        printk(KERN_INFO" WELCOME GUYS\n");
        printk(KERN_INFO "This is first code written by Nagurbee\n");
        printk(KERN_INFO "CODE INSERTED SUCCESfully\n");

        return 0;
}

static void __exit heloo_world_exit(void)
{
        printk(KERN_INFO "MODULE REMOVED SUCCESSFULLY\n");
}

module_init(hello_world_init);
module_exit(heloo_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NAGURBEE <nagurbeey20@gmail.com>");
MODULE_VERSION("1:1.0");
MODULE_DESCRIPTION("MY First Programm");
