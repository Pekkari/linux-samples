#include <linux/module.h>
#include <linux/init.h>

static int __init tainted_init(void)
{
    struct module *mod = THIS_MODULE;
    struct list_head *l;
    pr_info("Loading tainted module");
    if (mod->taints > 0)
        pr_info(
            "Module %s, taints %ld times the kernel",
            mod->name,
            mod->taints
        );

    list_for_each(l, &mod->list) {
        struct module *next = list_entry(
            l,
            struct module,
            list
        );
        if (next->taints > 0)
            pr_info(
                "Module %s, taints %ld times the kernel",
                next->name,
                next->taints
            );
    }
    
    return 0;
}

static void __exit tainted_exit(void)
{
    pr_info("Unloading tainted module");
    return;
}

module_init(tainted_init);
module_exit(tainted_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
