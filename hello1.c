#define DEBUG
#include <linux/module.h>
#include "hello1.h"

MODULE_AUTHOR("Rubanyk Hlib");
MODULE_DESCRIPTION("Lab4 Module hello1.c");
MODULE_LICENSE("Dual BSD/GPL");

struct myStruct {
    struct list_head list;
    ktime_t startTime;
    ktime_t finishTime;
};

static LIST_HEAD(myList);
int counter_sub;

int print_hello(uint COUNTER)
{
    BUG_ON(COUNTER > 10);

    if (COUNTER == 0 || (COUNTER <= 10 && COUNTER >= 5)) {
        pr_emerg("!!!WARNING!!!: %u\n", COUNTER);
    }

    counter_sub = 0;
    while (counter_sub != COUNTER) {
        struct myStruct *ptr;

        if (counter_sub == 5) {
            pr_emerg("Simulating kmalloc() failure for the 5th element.\n");
            ptr = NULL;
        } else {
            ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
        }

        if (!ptr) {
            pr_err("Memory allocation failed at iteration %d\n", counter_sub);
            return -ENOMEM;
        }

        ptr->startTime = ktime_get();
        pr_emerg("HELLO WORLD!!!\n");
        ptr->finishTime = ktime_get();
        list_add_tail(&ptr->list, &myList);
        counter_sub += 1;
    }
    return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    return 0;
}

static void __exit hello1_exit(void)
{
    struct myStruct *ptr, *next;

    pr_debug("Starting list traversal in hello1_exit...\n");

    list_for_each_entry_safe(ptr, next, &myList, list) {
        pr_debug("Time in nanoseconds: %lld\n", ptr->finishTime - ptr->startTime);
        list_del(&ptr->list);
        kfree(ptr);
    }

    pr_debug("Finished list traversal in hello1_exit...\n");
}


module_init(hello1_init);
module_exit(hello1_exit);

