#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>

extern struct semaphore lock;

static int __init locker1_init(void)
{
    pr_info("Loading locker1 module");
    request_module("sem");
    if (!down_trylock(&lock))
        pr_info("Sem locked! Yay!");
    else
        pr_info("Sem blocked! Fuuu!");
    return 0;
}

static void __exit locker1_exit(void)
{
    pr_info("Unloading locker1 module");
    up(&lock);
    return;
}

module_init(locker1_init);
module_exit(locker1_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
