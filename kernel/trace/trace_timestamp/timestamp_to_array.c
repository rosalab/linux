// timestamp_to_array.c

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include "timestamp_to_array.h"

u64 my_tracing_array[6];

// Export the symbol to other GPL modules
EXPORT_SYMBOL_GPL(my_tracing_array);

//comment 1
/*static void write_times_tracing_timestamps(void) {
    int i;
    u64 value = 10;  // Starting value to write

    for (i = 0; i < 6; ++i) {
        my_tracing_array[i] = value;
        printk(KERN_INFO "Element %d: %llu\n", i, my_tracing_array[i]);
        value++;  // Increment value for next element
    }
}*/


void write_times_tracing_timestamps(int index, u64 current_time) {
    my_tracing_array[index] = current_time;
}

static int __init read_tracing_array_init(void)
{
    printk(KERN_INFO "Initializing timestamp_to_array module\n");
    //comment 1
    //write_times_tracing_timestamps();
    return 0;
}

static void __exit read_tracing_array_exit(void)
{
    printk(KERN_INFO "Exiting timestamp_to_array module\n");
}

module_init(read_tracing_array_init);
module_exit(read_tracing_array_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Uddhav P. Gautam");
MODULE_DESCRIPTION("Kernel module to read timestamp_to_array");

