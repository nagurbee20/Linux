#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h>
#include<linux/platform_device.h>
#include<linux/slab.h>

#include "platform.h"


#define MAX_DEVICES 10

#undef pr_fmt
#define pr_fmt(fmt) "%s : "fmt,__func__

/*Driver Private Data Strructure */

struct pcdrv_private_data{
	int total_devices;
	dev_t device_num_base;
	struct class *class_pcd;
	struct device *device_pcd;
};


/*device Private data */

struct pcdev_private_data{

	struct pcdev_platform_data pdata;
	char *buffer;
	dev_t dev_num;
	struct cdev cdev;
};
/* variable for driver data*/
struct pcdrv_private_data pcdrv_data;


int check_permission(int dev_perm,int acc_mode)
{
        if(dev_perm == RDWR)
                return 0;
        if((dev_perm == RDONLY) &&((acc_mode & FMODE_READ) && !(acc_mode &FMODE_WRITE)))
               return 0;
        if((dev_perm == WRONLY) &&((acc_mode & FMODE_WRITE) && !(acc_mode &FMODE_READ)))
               return 0;
        return -EPERM;
}

loff_t pcd_lseek (struct file *filp, loff_t off, int whence)
{

	return 0;
}

ssize_t pcd_read (struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}
ssize_t pcd_write (struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{

	return -ENOMEM;
}



int pcd_open (struct inode *inode, struct file *filp)
{

	return 0;
}

int pcd_release (struct inode *inode, struct file *filp)
{
	return 0;
}

struct file_operations pcd_fops ={
	.open = pcd_open,
	.release = pcd_release,
	.read = pcd_read,
	.write = pcd_write,
	.llseek = pcd_lseek,
	.owner = THIS_MODULE
};
/*gets called when matched platform device is found*/

int pcd_platfor_driver_probe(struct platform_device *pdev)
{
	int ret;
	struct pcdev_private_data *dev_data;

	struct pcdev_platform_data *pdata;
	/* 1.Get the Platform Data */
	//pdata = pdev->dev.platform_data;
	pdata = (struct pcdev_platform_data*)dev_get_platdata(&pdev->dev);
	if(!pdata){
		pr_info("No platform available \n");
		ret = -EINVAL;
		goto out;
	}

	/* 2. Dynamically Allocate memory for the device privata data */
	dev_data = kzalloc(sizeof(*dev_data),GFP_KERNEL);
	if(!dev_data)
	{
		pr_info("cannot allocate memory \n");
		ret = -ENOMEM;
		goto out;
	}

	
	
	dev_data->pdata.size = pdata->size;
	dev_data->pdata.perm = pdata->perm;
	dev_data->pdata.serial_number = pdata->serial_number;

	pr_info("Device serial number = %s\n",dev_data->pdata.serial_number);
	pr_info("Device permission = %d\n",dev_data->pdata.perm);
	pr_info("Device size = %d\n",dev_data->pdata.size);

	 /* 3. Dynamically allocate memory for device b usffer using size infornmato from platfor data */
	dev_data->buffer = kzalloc(dev_data->size,GFP_KERNEL);
        if(!dev_data->buffer)
        {
                pr_info("cannot allocate memory \n");
                ret = -ENOMEM;
                goto dev_data_free;
        }
	
	/* 3. get the device number*/
	dev_data->dev_num = pcdrv_data.device_num_base + pdev->id;

	/* 3. Do cdev int cdev add*/
	cdev_init(&dev_data->cdev,&pcd_fops);
	
	dev_data->cdev.owner = THIS_MODULE;
	ret = cdev_add(&dev_data->cdev,dev_data->dev_num,1);
	if(ret < 0){
		pr_err("CDEv add failed \n");
		goto buffer_free;

	/* 3. create device file for the detected platofm device*/
	

	/* 3. Eroor handling*/

	pr_info("Device is detetcted \n");
	return 0;
buffer_free:
	kfree(dev_data->buffer);
dev_data_free:
	kfree(dev_data);
out:
	pr_info("devie probe failde \n");
	return ret;
}

/* gets called when device is removed from the system*/

int pcd_platform_driver_remove(struct platform_device *pdev)
{
	pr_info("Device is removed \n");
	return 0;
}


struct platform_driver pcd_platform_driver = 
{
	.probe = pcd_platfor_driver_probe,
	.remove = pcd_platform_driver_remove,
	.driver = {
		.name = "pseudo-char-device"
	}
};


static int __init pcd_driver_init(void)
{
	int ret;
	/*1.dynamically allocate device number for MAX devices*/
	ret = alloc_chrdev_region(&pcdrv_data.device_num_base,0,MAX_DEVICES,"pcdevs");
	if(ret<0){
		pr_err("Alloc chrdev failed\n");
		return ret;
	}


	/*2. create device class under /sys/class */
	pcdrv_data.class_pcd = class_create("pcd_class");
	if(IS_ERR(pcdrv_data.class_pcd)){
		pr_err("class creation failed \n");
		ret = PTR_ERR(pcdrv_data.class_pcd);
		unregister_chrdev_region(pcdrv_data.device_num_base,MAX_DEVICES);

		return ret;
	}


	/*3.Register Platform driver */
	platform_driver_register(&pcd_platform_driver);
	pr_info("Driver inserted successfully \n");
	return 0;
}

void __exit pcd_driver_exit(void)

{
	/*unregitser platform driver*/
	platform_driver_unregister(&pcd_platform_driver);

	/*class destory */
	class_destroy(pcdrv_data.class_pcd);

	/*unregister device number */
	unregister_chrdev_region(pcdrv_data.device_num_base,MAX_DEVICES);
	pr_info("Driver removed successfully\n");

}

module_init(pcd_driver_init);
module_exit(pcd_driver_exit);
MODULE_AUTHOR("NAGURBEE\n");
MODULE_DESCRIPTION("PCD DRIVER\n ");
MODULE_LICENSE("GPL\n");
