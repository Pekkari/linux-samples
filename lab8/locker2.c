#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/init.h>

extern struct mutex lock;

static int __init locker2_init(void)
{
    pr_info("Loading locker2 module");
    request_module("mutex");
    if (mutex_trylock(&lock))
        pr_info("Mutex locked! Yay!");
    else
        pr_info("Mutex blocked! Fuuu!");
    return 0;
}

static void __exit locker2_exit(void)
{
    pr_info("Unloading locker2 module");
    mutex_unlock(&lock);
    return;
}

module_init(locker2_init);
module_exit(locker2_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
