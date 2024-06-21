#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include "../read_write_to_heaps.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Uddhav P. Gautam");
MODULE_DESCRIPTION("Kernel module to read my_tracing_array");

static int __init read_tracing_array_init(void)
{
    printk(KERN_INFO "Initializing read_tracing_array module\n");
    read_times();
    return 0;
}

static void __exit read_tracing_array_exit(void)
{
    printk(KERN_INFO "Exiting read_tracing_array module\n");
}

module_init(read_tracing_array_init);
module_exit(read_tracing_array_exit);
