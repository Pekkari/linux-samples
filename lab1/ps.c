#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

struct task_struct *p;

static int __init ps_init(void)
{
    pr_info("Loading ps module");
    for_each_process(p) {
        pr_info("PID: %d; state: %ld; flags: %d; cpu: %d; cmd: %s\n",
            p->tgid,
            p->state,
            p->flags,
            p->on_cpu,
            p->comm
        );
    }
    return 0;
}

static void __exit ps_exit(void)
{
    pr_info("Unloading ps module");
    return;
}

module_init(ps_init);
module_exit(ps_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
