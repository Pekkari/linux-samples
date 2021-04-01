#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/slab.h>

LIST_HEAD(thread_list);

struct thread_node {
    struct list_head list;
    struct task_struct *t;
};

int cpu_thread(void *args) {
    pr_info("Igniting kthread in cpu: %d\n", *((int *) args));
    do {
        msleep(1000);
    } while(!kthread_should_stop());
    return 0;
}

static int __init kthread_init(void)
{
    int cpu;
    pr_info("Loading kthread module");

    for_each_online_cpu(cpu) {
        struct thread_node *node = kmalloc(
            sizeof(struct thread_node),
            GFP_KERNEL
        );
        node->t = kthread_create(cpu_thread, &cpu, "cpu_thread/%d", cpu);
        kthread_bind(node->t, cpu);
        wake_up_process(node->t);
        list_add(&node->list, &thread_list);
    }
    return 0;
}

static void __exit kthread_exit(void)
{
    struct list_head * l;
    pr_info("Unloading kthread module");

    list_for_each(l, &thread_list) {
        struct thread_node *next = list_entry(
            l,
            struct thread_node,
            list
        );
        pr_info("Destroying thread %d\n", next->t->tgid);
        kthread_stop(next->t);
    }
    return;
}

module_init(kthread_init);
module_exit(kthread_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
