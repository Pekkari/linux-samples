#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/init.h>

extern struct mutex lock;

static int __init locker1_init(void)
{
    pr_info("Loading locker1 module");
    request_module("mutex");
    if (mutex_trylock(&lock))
        pr_info("Mutex locked! Yay!");
    else
        pr_info("Mutex blocked! Fuuu!");
    return 0;
}

static void __exit locker1_exit(void)
{
    pr_info("Unloading locker1 module");
    mutex_unlock(&lock);
    return;
}

module_init(locker1_init);
module_exit(locker1_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
