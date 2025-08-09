#include <linux/module.h>
#include <linux/time.h>

static int num = 5;
static struct timespec64 start_time;

module_param(num, int, S_IRUGO);    // num参数可指定

static int __init hello_init(void)
{
    ktime_get_real_ts64(&start_time);   // 保存时间
    pr_info("Hello world init\n");  // printk(KERN_INFO, xxx)的简写，推荐这种用法
    pr_info("num = %d\n", num);
    return 0;
}

static void __exit hello_exit(void)
{
    struct timespec64 end_time;
    ktime_get_real_ts64(&end_time);
    pr_info("Hello world exit, running total time: %lld seconds\n",
        end_time.tv_sec - start_time.tv_sec);
}

module_init(hello_init);    // 指定模块加载时的回调
module_exit(hello_exit);    // 指定模块卸载时的回调

MODULE_LICENSE("GPL");      // 指定许可证GPL
MODULE_AUTHOR("cai");
MODULE_DESCRIPTION("This is a print out Hello World module");

