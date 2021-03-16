#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>

LIST_HEAD(sample_list);

struct list_element {
    int val;
    struct list_head list;
};

static int __init list_init(void)
{
    int i;
    pr_info("Loading list module");
    for(i = 7; i > 0; i--) {
        struct list_element *elem = kmalloc(
            sizeof(struct list_element),
            GFP_KERNEL
        );
        elem->val = i;
        list_add(&elem->list, &sample_list);
        pr_info("Adding element %d\n", elem->val);
    }

    return 0;
}

static void __exit list_exit(void)
{
    struct list_head *l;
    pr_info("Unloading list module");
    if (list_empty(&sample_list))
        return;

    list_for_each(l, &sample_list) {
        struct list_element *elem = list_entry(
            l,
            struct list_element,
            list
        );
        pr_info("Freeing element %d\n", elem->val);
        kfree(elem);
    }
    return;
}

module_init(list_init);
module_exit(list_exit);

MODULE_AUTHOR("José Pekkarinen");
MODULE_LICENSE("GPL v2");
