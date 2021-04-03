#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/debugfs.h>

struct dentry *folder;
struct dentry *file;

static ssize_t debugfs_read(
    struct file *file,
    char *buffer,
    size_t buffer_size,
    loff_t *ppos
)
{
    pr_info("Dumb reading debugfs");
    return 0;
}

static ssize_t debugfs_write(
    struct file *file,
    const char *buffer,
    size_t buffer_size,
    loff_t *ppos
)
{
    pr_info("Fake writing to debugfs");
    return buffer_size;
}

static const struct file_operations debugfs_fops = {
    .owner = THIS_MODULE,
    .read = debugfs_read,
    .write = debugfs_write
};

static int __init debugfs_var_init(void)
{
    pr_info("Loading debugfs_var module");
    folder = debugfs_create_dir(
        "custom", 
        NULL
    );
    file = debugfs_create_file(
        "hello",
        0x644,
        folder,
        NULL,
        &debugfs_fops
    );
    return 0;
}

static void __exit debugfs_var_exit(void)
{
    pr_info("Unloading debugfs_var module");
    debugfs_remove(file);
    debugfs_remove(folder);
    return;
}

module_init(debugfs_var_init);
module_exit(debugfs_var_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
