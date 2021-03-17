#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

#define DEVICE_NAME "ioctl"

static dev_t device;
static struct cdev *ioctl_device;
static int major = 500, minor = 1, count = 1;

static int ioctl_open(struct inode *inode, struct file *file) {
    pr_info("Opening device: %s\n", DEVICE_NAME);
    return 0;
}

static int ioctl_release(struct inode *inode, struct file *file) {
    pr_info("Releasing device: %s\n", DEVICE_NAME);
    return 0;
}

static long int ioctl_ioctl(struct file *file, unsigned int ioctl_req,  long unsigned int args_size)
{
    pr_info("Calling ioctl of device: %s\n", DEVICE_NAME);
    return 0;
}

static const struct file_operations ioctl_fops = {
    .owner = THIS_MODULE,
    .open = ioctl_open,
    .release = ioctl_release,
    .unlocked_ioctl = ioctl_ioctl,
};

static int __init ioctl_init(void)
{
    pr_info("Loading ioctl module");
    device = MKDEV(major, minor);
    register_chrdev_region(device, count, DEVICE_NAME);
    ioctl_device = cdev_alloc();
    cdev_init(ioctl_device, &ioctl_fops);
    cdev_add(ioctl_device, device, count);
    pr_info("Character device registered!\n");
    return 0;
}

static void __exit ioctl_exit(void)
{
    pr_info("Unloading ioctl module");
    cdev_del(ioctl_device);
    unregister_chrdev_region(device, count);
    pr_info("Character device unregistered!\n");

    return;
}

module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
