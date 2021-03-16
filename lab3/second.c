#include <linux/module.h>
#include <linux/kmod.h>
#include <linux/init.h>

extern void call_me_in(void);

static int __init second_init(void)
{
    pr_info("Loading second module");
    request_module("first");
    call_me_in();
    return 0;
}

static void __exit second_exit(void)
{
    pr_info("Unloading second module");
    return;
}

module_init(second_init);
module_exit(second_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
