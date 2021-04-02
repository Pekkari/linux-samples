#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>

#define PROGRAM "/bin/cp"
#define ORIG "/tmp/xauth-1000-_1"
#define COPY "/tmp/copy_of_xauth-1000-_1"
#define CLEANUP_PROGRAM "/bin/rm"

static int __init usermode_init(void)
{
    char *cmdargs[] = {
        PROGRAM,
        ORIG,
        COPY,
        NULL,
    };
    pr_info("Loading usermode module");
    call_usermodehelper(PROGRAM, cmdargs, NULL, UMH_WAIT_PROC);
    return 0;
}

static void __exit usermode_exit(void)
{
    char *cmdargs[] = {
        CLEANUP_PROGRAM,
        COPY,
        NULL,
    };
    pr_info("Unloading usermode module");
    pr_info("Cleaning trash");
    call_usermodehelper(CLEANUP_PROGRAM, cmdargs, NULL, UMH_WAIT_PROC);
    return;
}

module_init(usermode_init);
module_exit(usermode_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
