#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h> /* for copy_to_user and copy_from_user */

#define DEV_MEM_SIZE 512

char device_buffer[DEV_MEM_SIZE];

/*cdev varialble*/
struct cdev pcd_cdev;

loff_t pcd_lseek (struct file *filp, loff_t offset, int whence)
{
	loff_t temp;
	pr_info("lseek of pcd\n");
	pr_info("current file position = %lld\n",filp->f_pos); 

	switch(whence)
	{
		case SEEK_SET:
			if((offset > DEV_MEM_SIZE) || (offset < 0))
				return -EINVAL;
			filp->f_pos = offset;
			break;
		case SEEK_CUR:
			temp = filp->f_pos + offset;
			if((temp > DEV_MEM_SIZE) || (temp < 0))
				return -EINVAL;
			filp->f_pos = temp;
			break;
		case SEEK_END:
			filp->f_pos = temp;
			break;
		default:
			return -EINVAL;
	}

	pr_info("updated file position = %lld\n",filp->f_pos);
	return filp->f_pos;
}

ssize_t pcd_read (struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{

	pr_info("read requested for %zu bytes \n",count);
	pr_info("intially the file-position is %lld\n",*f_pos);
	/*1.check count value with dev_mem-size*/

	if((*f_pos + count) > DEV_MEM_SIZE)
		count = DEV_MEM_SIZE - *f_pos;

	/*2.copy to user*/
	if(copy_to_user(buff,device_buffer[*f_pos],count)){
		return -EFAULT;
	}

	/*3. update the current file position*/
	*f_pos += count;	
	

	pr_info("number of bytes succesfuuly read = %zu\n",count);
	pr_info("updated the file-position is %lld\n",*f_pos);
	/*return number of bytes succesfully read */
	return count;
}
ssize_t pcd_write (struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("write requested for %zu bytes \n",count);
        pr_info("intially the file-position is %lld\n",*f_pos);
        /*1.check count value with dev_mem-size*/

        if((*f_pos + count) > DEV_MEM_SIZE)
                count = DEV_MEM_SIZE - *f_pos;
	if(!count)
		return -ENOMEM;

        /*2.copy from user*/
        if(copy_from_user(&device_buffer[*f_pos],buff,count)){
                return -EFAULT;
        }

        /*3. update the current file position*/
        *f_pos += count;


        pr_info("number of bytes succesfuuly write = %zu\n",count);
        pr_info("updated the file-position is %lld\n",*f_pos);
        /*return number of bytes succesfully read */
        return count;
}


int pcd_open (struct inode *inode, struct file *filp)
{
	pr_info("open requested for pcd\n");
	return 0;
}

int pcd_release (struct inode *inode, struct file *filp)
{
	pr_info("release requested for pcd\n");
	return 0;
}

//struct file_operations pcd_fops;

struct file_operations pcd_fops = {
	.open = pcd_open,
	.write = pcd_write,
	.read = pcd_read,
	.llseek = pcd_lseek,
	.release = pcd_release,
	.owner = THIS_MODULE
};

struct class *class_pcd;

struct device *device_pcd;

dev_t device_number;

static int __init pcd_driver_init(void)
{
	int ret;
	/*1.Dynamically allocating device_number"*/
	ret = alloc_chrdev_region(&device_number,0,1,"pcd_devices");
	if(ret <0)
	{
		 pr_err("allocation of chrdev failed\n");
		goto out;
	}

	pr_info("Device number <major>:<minor> is %d : %d ",MAJOR(device_number),MINOR(device_number));
	/*2.cdev intialization*/
	cdev_init(&pcd_cdev,&pcd_fops);

	/*3. register cdev structure with VFS*/
	pcd_cdev.owner = THIS_MODULE;
	ret = cdev_add(&pcd_cdev,device_number,1);
	if(ret < 0)
	{
		pr_err("cdev add failed\n");
		goto unreg_chrdev;
	}

	/*create dveice class under /sys/class/ */
	//class_pcd = class_create(THIS_MODULE,"pcd_class");
	class_pcd = class_create("pcd_class");
	if(IS_ERR(class_pcd))
	{
		pr_err("class creation failed\n");
		ret = PTR_ERR(class_pcd); 
		goto cdev_del;
	}


	/*populate the sysfs with device information */
	device_pcd = device_create(class_pcd,NULL,device_number,NULL,"pcd");
	if(IS_ERR(device_pcd)){
			pr_err("device create failure\n");
			ret = PTR_ERR(device_pcd);
			goto class_del;
			}

	pr_info("Module init was successfull\n");
	return 0;
class_del:
	class_destroy(class_pcd);

cdev_del:
	cdev_del(&pcd_cdev);

unreg_chrdev:
	unregister_chrdev_region(device_number,1);

out:
	pr_err("Modile isertion failed\n");
	return ret;

}


static void __exit pcd_driver_cleanup(void)
{
//	unregister_chrdev_region();
	device_destroy(class_pcd,device_number);
	class_destroy(class_pcd);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(device_number,1);
}
module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_DESCRIPTION("A PUSEDO DEVICE DRIVER\n");
MODULE_AUTHOR("NAGURBEE");
MODULE_LICENSE("GPL");
MODULE_VERSION("1:0");
