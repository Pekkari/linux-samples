#include <linux/module.h>
#include <linux/init.h>

void call_me_in(void)
{
    pr_info("Cross called function called");
    return;
}

static int __init first_init(void)
{
    pr_info("Loading first module");
    return 0;
}

static void __exit first_exit(void)
{
    pr_info("Unloading first module");
    return;
}

EXPORT_SYMBOL(call_me_in);
module_init(first_init);
module_exit(first_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
