#include <linux/module.h>
/* 字符设备需要的头文件 */
#include <linux/cdev.h>
#include <linux/fs.h>

#define MY_MAJOR_NUM    (202)   // 主设备号

static struct cdev my_dev;

// 打开设备
static int my_dev_open(struct inode *inode, struct file *file)
{
    pr_info("my_dev_open() is called.\n");
    return 0;
}

// 关闭设备
static int my_dev_close(struct inode *inode, struct file *file)
{
    pr_info("my_dev_close() is called.\n");
    return 0;
}

// ioctl，用于复杂交互
static long my_dev_ioctl(struct file *file, unsigned int cmd /* 命令 */, unsigned long arg /* 输入/输出参数 */)
{
    pr_info("my_dev_ioctl() is called with cmd: %u, arg: %lu.\n", cmd, arg);
    return 0;
}

// file operations
static const struct file_operations my_dev_fops = {
    .owner = THIS_MODULE,   /* 该宏表示当前正在编译的模块 */
    .open = my_dev_open,
    .release = my_dev_close,
    .unlocked_ioctl = my_dev_ioctl,
};

static int __init hello_init(void)
{
    int ret = 0;
    dev_t dev = MKDEV(MY_MAJOR_NUM, 0); // 获得minor设备号0的设备
    
    pr_info("hello init");

    // 静态分配设备号
    ret = register_chrdev_region(dev, 1, "my_char_device");
    if(ret < 0)
    {
        pr_err("Failed to register char device region: %d\n", ret);
        return ret;
    }

    // 初始化设备，注册到内核
    cdev_init(&my_dev, &my_dev_fops);
    ret = cdev_add(&my_dev, dev, 1);
    if(ret < 0)
    {
        pr_err("Failed to add cdev: %d\n", ret);
        unregister_chrdev_region(dev, 1); // 失败时需要释放设备号
        return ret;
    }

    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("hello exit\n");
    cdev_del(&my_dev); // 删除字符设备
    unregister_chrdev_region(MKDEV(MY_MAJOR_NUM, 0), 1); // 释放设备号
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cai");
MODULE_DESCRIPTION("A simple character device driver");

/*
    TEST
    1. 加载后，cat /proc/devices 在字符设备中可以看到 202 my_char_device
    2. 此时 ls -l /dev 还看不到任何我们创建的202主设备号下的设备
    3. mknod /dev/mydev c 202 0 创建设备节点
    4. ls -l /dev 可以找到mydev
    5. 执行my_ioctl，dmesg | tail，可以看到相关打印
*/