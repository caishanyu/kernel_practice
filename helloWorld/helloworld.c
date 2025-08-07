#include <linux/module.h>

static int __init hello_init(void)
{
    pr_info("Hello world init\n");  // printk(KERN_INFO, xxx)的简写，推荐这种用法
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Hello world exit\n");
}

module_init(hello_init);    // 指定模块加载时的回调
module_exit(hello_exit);    // 指定模块卸载时的回调

MODULE_LICENSE("GPL");      // 指定许可证GPL
MODULE_AUTHOR("cai");
MODULE_DESCRIPTION("This is a print out Hello World module");

