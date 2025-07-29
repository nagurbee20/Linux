#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h> /* for copy_to_user and copy_from_user */

#undef pr_fmt
#define pr_fmt(fmt) "%s: "fmt,__func__


#define MEM_SIZE_MAX_PCDDEV1 1024
#define MEM_SIZE_MAX_PCDDEV2 512
#define MEM_SIZE_MAX_PCDDEV3 1024
#define MEM_SIZE_MAX_PCDDEV4 512

#define NO_OF_DEVICES 4

char device_buffer_pcdev1[MEM_SIZE_MAX_PCDDEV1];
char device_buffer_pcdev2[MEM_SIZE_MAX_PCDDEV2];
char device_buffer_pcdev3[MEM_SIZE_MAX_PCDDEV3];
char device_buffer_pcdev4[MEM_SIZE_MAX_PCDDEV4];

#define RDONLY 0x01
#define WRONLY 0x10
#define RDWR   0x11

/* Device Private Data */
struct pcdev_private_data
{
        unsigned size;
        const char * serial_number;
        char *buffer;
        int perm;
        struct cdev cdev;
};
/*Driver private Data */
struct pcdrv_private_data
{
	int total_devices;
	/*This holds the device number */
	dev_t device_number;

	struct class *class_pcd;

	struct device *device_pcd;
	struct pcdev_private_data pcdev_data[NO_OF_DEVICES];
};

struct pcdrv_private_data pcdrv_data =
{
	.total_devices = NO_OF_DEVICES,
	.pcdev_data = {
		
		[0] = {
			.buffer        = device_buffer_pcdev1,
			.size          = MEM_SIZE_MAX_PCDDEV1,
			.serial_number = "PCDEV1XYZ123",
		       	.perm = RDONLY/*RDONLY*/
		},

		 [1] = {
                        .buffer        = device_buffer_pcdev2,
                        .size          = MEM_SIZE_MAX_PCDDEV2,
                        .serial_number = "PCDEV2XYZ123",
                        .perm = WRONLY/*WRONLY*/
                },
		 [2] = {
                        .buffer        = device_buffer_pcdev3,
                        .size          = MEM_SIZE_MAX_PCDDEV3,
                        .serial_number = "PCDEV3XYZ123",
                        .perm = RDWR/*RDWR*/
                },
		 [3] = {
                        .buffer        = device_buffer_pcdev4,
                        .size          = MEM_SIZE_MAX_PCDDEV4,
                        .serial_number = "PCDEV4XYZ123",
                        .perm = RDWR/*RDWR*/
                }
	}
};	


loff_t pcd_lseek (struct file *filp, loff_t offset, int whence)
{

	struct pcdev_private_data *pcdev_data = (struct pcdev_private_data*)filp->private_data;
        int max_size = pcdev_data->size;

	loff_t temp;
	pr_info("lseek of pcd\n");
	pr_info("current file position = %lld\n",filp->f_pos); 

	switch(whence)
	{
		case SEEK_SET:
			if((offset > max_size) || (offset < 0))
				return -EINVAL;
			filp->f_pos = offset;
			break;
		case SEEK_CUR:
			temp = filp->f_pos + offset;
			if((temp > max_size) || (temp < 0))
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

	struct pcdev_private_data *pcdev_data = (struct pcdev_private_data*)filp->private_data;

	int max_size = pcdev_data->size;


	pr_info("read requested for %zu bytes \n",count);
	pr_info("intially the file-position is %lld\n",*f_pos);
	/*1.check count value with dev_mem-size*/

	if((*f_pos + count) > max_size)
		count = max_size - *f_pos;

	/*2.copy to user*/
	if(copy_to_user(buff,pcdev_data->buffer+(*f_pos),count)){
		return -EFAULT;
	}

	/*3. update the current file position*/
	*f_pos += count;	
	

	pr_info("number of bytes succesfuuly read = %zu\n",count);
	pr_info("updated the file-position is %lld\n",*f_pos);
	/*return number of bytes succesfully read */
	return count;

	return 0;
}
ssize_t pcd_write (struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	struct pcdev_private_data *pcdev_data = (struct pcdev_private_data*)filp->private_data;

        int max_size = pcdev_data->size;

	pr_info("write requested for %zu bytes \n",count);
        pr_info("intially the file-position is %lld\n",*f_pos);
        /*1.check count value with dev_mem-size*/

        if((*f_pos + count) > max_size)
                count = max_size - *f_pos;
	if(!count)
		return -ENOMEM;

        /*2.copy from user*/
        if(copy_from_user(&pcdev_data->buffer+(*f_pos),buff,count)){
                return -EFAULT;
        }

        /*3. update the current file position*/
        *f_pos += count;


        pr_info("number of bytes succesfuuly write = %zu\n",count);
        pr_info("updated the file-position is %lld\n",*f_pos);
        /*return number of bytes succesfully read */
        return count;

	return -ENOMEM;
}

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

int pcd_open (struct inode *inode, struct file *filp)
{

	int ret;
	int minor_n;

	struct pcdev_private_data *pcdev_data;

	/* to know which device has to open*/
	minor_n =MINOR(inode->i_rdev);

	pr_info("MINOR number is %d \n",minor_n);

	/*get the d3evice private data*/
	pcdev_data = container_of(inode->i_cdev,struct pcdev_private_data,cdev);

	/* to give device data to other memthos*/

	filp->private_data = pcdev_data;

	ret = check_permission(pcdev_data->perm,filp->f_mode);
	class_destroy(pcdrv_data.class_pcd);


	(!ret)?pr_info("open requested for pcd\n"):pr_info("open was unsuccessfull\n");
	
	return ret;
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

static int __init pcd_driver_init(void)
{

	int ret;
	int i;
	/*1.Dynamically allocating device_number"*/
	ret = alloc_chrdev_region(&pcdrv_data.device_number,0,1,"pcd_devices");
	if(ret <0)
	{
		 pr_err("allocation of chrdev failed\n");
		goto out;
	}

	 /*4.create dveice class under /sys/class/ */
                //class_pcd = class_create(THIS_MODULE,"pcd_class");
               pcdrv_data.class_pcd = class_create("pcd_class");
                if(IS_ERR(pcdrv_data.class_pcd))
                {
                        pr_err("class creation failed\n");
                        ret = PTR_ERR(pcdrv_data.class_pcd);
                        goto unreg_chrdev;
                }

	for(i = 0;i< NO_OF_DEVICES;i++)
	{

		pr_info("Device number <major>:<minor> is %d : %d ",MAJOR(pcdrv_data.device_number+i),MINOR(pcdrv_data.device_number+i));
		/*2.cdev intialization*/
		cdev_init(&pcdrv_data.pcdev_data[i].cdev,&pcd_fops);

		/*3. register cdev structure with VFS*/
		pcdrv_data.pcdev_data[i].cdev.owner = THIS_MODULE;
		ret = cdev_add(&pcdrv_data.pcdev_data[i].cdev,pcdrv_data.device_number+1,1);
		
		if(ret < 0)
		{
			pr_err("cdev add failed\n");
			goto cdev_del;
		}

		/*5.populate the sysfs with device information */
		pcdrv_data.device_pcd = device_create(pcdrv_data.class_pcd,NULL,pcdrv_data.device_number+i,NULL,"pcdev-%d",i+1);
		if(IS_ERR(pcdrv_data.device_pcd)){
			pr_err("device create failure\n");
			ret = PTR_ERR(pcdrv_data.device_pcd);
			goto class_del;
		}
	}

	pr_info("Module init was successfull\n");
	return 0;
cdev_del:
class_del:
	for(;i>0;i--){
		device_destroy(pcdrv_data.class_pcd,pcdrv_data.device_number);
		cdev_del(&pcdrv_data.pcdev_data[i].cdev);
	}
	class_destroy(pcdrv_data.class_pcd);

unreg_chrdev:
	unregister_chrdev_region(pcdrv_data.device_number,NO_OF_DEVICES);

out:
	pr_err("Modile isertion failed\n");
	return ret;

}


static void __exit pcd_driver_cleanup(void)
{
#if 0
//	unregister_chrdev_region();
	device_destroy(class_pcd,device_number);
	class_destroy(class_pcd);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(device_number,1);
#endif
}
module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_DESCRIPTION("A PUSEDO for N number of  DEVICEs DRIVER\n");
MODULE_AUTHOR("NAGURBEE");
MODULE_LICENSE("GPL");
MODULE_VERSION("1:0");
