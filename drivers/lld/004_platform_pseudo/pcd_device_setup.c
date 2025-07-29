#include<linux/module.h>
#include<linux/platform_device.h>
#include "platform.h"

#undef pr_fmt
#define pr_fmt(fmt) "%s : "fmt,__func__

void pcdev_release(struct device *dev)
{
pr_info("device release\n");
}

/* create teo platform data */

struct pcdev_platform_data pcdev_pdata[2] = {
	[0] = {.size=512,.perm = RDWR,.serial_number = "PCDEV1BC1111"},
	[1] = {.size = 1024,.perm = RDWR,.serial_number = "PCDEVXYZ222"}
};

/*create two platform devices*/

struct platform_device platform_pcdev1 = {

	.name = "pseudo-char-device",
	.id = 0,
	.dev = {
		.platform_data = &pcdev_pdata[0],
		.release = pcdev_release
	}
};

struct platform_device platform_pcdev2 = {
.name = "pseudo-char-device",
        .id = 1,
	.dev = {
		.platform_data = &pcdev_pdata[1],
		.release = pcdev_release
	}
};

static int __init pcdev_platform_init(void)
{
	/*REGIster platform device */
	platform_device_register(&platform_pcdev1);
	platform_device_register(&platform_pcdev2);
	
	pr_info("Device set-up Module Loaded succesfully\n");
	return 0;
}
static void __exit pcdev_platform_exit(void)
{
	 platform_device_unregister(&platform_pcdev1);
	 platform_device_unregister(&platform_pcdev2);
	 pr_info("set-up device Module UNLOADED successfully\n");

}
module_init(pcdev_platform_init);
module_exit(pcdev_platform_exit);


MODULE_AUTHOR("NAGURBEE");
MODULE_DESCRIPTION("PLATFORM DEVICE SETUP");
MODULE_LICENSE("GPL");



