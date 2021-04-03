#include <linux/module.h>
#include <linux/init.h>
#include <linux/sysrq.h>

#define CODE_X 0x78

void sysrq_handler_x(int keycode)
{
    pr_info("Hello world from sysrq %d", keycode);
    return;
}

struct sysrq_key_op sysrq_x_op = {
    &sysrq_handler_x,
    "custom(x)",
    "Triggering the end of the world!",
    1
};

static int __init sysrq_x_init(void)
{
    pr_info("Loading sysrq module");
    register_sysrq_key(CODE_X, &sysrq_x_op);
    return 0;
}

static void __exit sysrq_x_exit(void)
{
    pr_info("Unloading sysrq module");
    unregister_sysrq_key(CODE_X, &sysrq_x_op);
    return;
}

module_init(sysrq_x_init);
module_exit(sysrq_x_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
