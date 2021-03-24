#include <linux/module.h>
#include <linux/init.h>
#include <linux/percpu.h>

DEFINE_PER_CPU(int, cpu_variable) = 256;

static DEFINE_SPINLOCK(lock);
static int which_cpu(void)
{
        int cpu;
        spin_lock(&lock);
        cpu = smp_processor_id();
        spin_unlock(&lock);
        return cpu;
}

static int __init percpu_init(void)
{
    int cpu = which_cpu();
    int __percpu *dyncpuvar = alloc_percpu(int);

    pr_info("Loading percpu module");
    pr_info("Static cpuvar value: %d", get_cpu_var(cpu_variable));

    *per_cpu_ptr(dyncpuvar, cpu) = 512;
    put_cpu_var(dyncpuvar);
    pr_info("Dynamic cpuvar value: %d", *per_cpu_ptr(dyncpuvar, cpu));

    free_percpu(dyncpuvar);

    return 0;
}

static void __exit percpu_exit(void)
{
    pr_info("Unloading percpu module");
    return;
}

module_init(percpu_init);
module_exit(percpu_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
