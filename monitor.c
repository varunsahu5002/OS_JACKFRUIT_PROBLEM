#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "container_monitor"

static int major;

static int device_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    return 0;
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
};

static int __init monitor_init(void)
{
    printk(KERN_INFO "monitor: init\n");

    major = register_chrdev(0, DEVICE_NAME, &fops);

    if (major < 0)
    {
        printk(KERN_ALERT "monitor: register failed\n");
        return major;
    }

    printk(KERN_INFO "monitor loaded major=%d\n", major);
    return 0;
}

static void __exit monitor_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "monitor unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
