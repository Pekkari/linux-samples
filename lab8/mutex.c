#include <linux/module.h>
#include <linux/init.h>

DEFINE_MUTEX(lock);
EXPORT_SYMBOL(lock);

static int __init mutex_module_init(void)
{
    pr_info("Loading mutex module");
    return 0;
}

static void __exit mutex_module_exit(void)
{
    pr_info("Unloading mutex module");
    return;
}

module_init(mutex_module_init);
module_exit(mutex_module_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
