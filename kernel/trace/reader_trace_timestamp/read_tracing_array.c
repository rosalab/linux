#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

// Declaration of the exported array from timestamp_to_array.c
extern u64 my_tracing_array[6];

static void read_times_tracing_timestamps(void) {
    int i;
    for (i = 0; i < 6; ++i) {
        printk(KERN_INFO "Element %d: %llu\n", i, 2*my_tracing_array[i]);
    }
}

static int __init read_tracing_array_init(void)
{
    printk(KERN_INFO "Initializing read_tracing_array module\n");
    read_times_tracing_timestamps();
    return 0;
}

static void __exit read_tracing_array_exit(void)
{
    printk(KERN_INFO "Exiting read_tracing_array module\n");
}

module_init(read_tracing_array_init);
module_exit(read_tracing_array_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to read my_tracing_array from timestamp_to_array");
