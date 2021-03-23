#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>

DEFINE_SEMAPHORE(lock);
EXPORT_SYMBOL(lock);

static int __init semaphore_module_init(void)
{
    pr_info("Loading semaphore module");
    return 0;
}

static void __exit semaphore_module_exit(void)
{
    pr_info("Unloading semaphore module");
    return;
}

module_init(semaphore_module_init);
module_exit(semaphore_module_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
