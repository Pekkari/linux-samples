#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>

extern struct semaphore lock;

static int __init locker2_init(void)
{
    pr_info("Loading locker2 module");
    request_module("sem");
    if (!down_trylock(&lock))
        pr_info("Sem locked! Yay!");
    else
        pr_info("Sem blocked! Fuuu!");
    return 0;
}

static void __exit locker2_exit(void)
{
    pr_info("Unloading locker2 module");
    up(&lock);
    return;
}

module_init(locker2_init);
module_exit(locker2_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
