#include "hello1.h"

MODULE_AUTHOR("Rubanyk Hlib");
MODULE_DESCRIPTION("Lab4 Module hello2.c");
MODULE_LICENSE("Dual BSD/GPL");

static uint COUNTER = 1;
// 0444 = S_IRUGO
module_param(COUNTER, uint, 0444);
MODULE_PARM_DESC(COUNTER, "CONSOLE WRITING");

static int __init hello2_init(void)
{
    pr_emerg("Calling print_hello() from hello2...\n");
    print_hello(COUNTER);
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_emerg("Exiting module hello2...\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

