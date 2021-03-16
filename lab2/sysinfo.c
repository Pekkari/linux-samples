#include <linux/module.h>
#include <linux/init.h>
#include <linux/utsname.h>

struct new_utsname *uname;

static int __init sysinfo_init(void)
{
    pr_info("Loading sysinfo module");
    uname = init_utsname();
    pr_info(
        "Sys: %s\n Node: %s\n Release: %s\n Version: %s\n Machine: %s\n Domain: %s\n",
        uname->sysname,
        uname->nodename,
        uname->release,
        uname->version,
        uname->machine,
        uname->domainname
    );
    return 0;
}

static void __exit sysinfo_exit(void)
{
    pr_info("Unloading sysinfo module");
    return;
}

module_init(sysinfo_init);
module_exit(sysinfo_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
