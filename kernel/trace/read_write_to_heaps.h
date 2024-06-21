#ifndef READ_WRITE_TO_HEAPS_H
#define READ_WRITE_TO_HEAPS_H

#include <linux/types.h>
#include <linux/ktime.h>

static u64 my_tracing_array[10]; // Declare the tracing array as extern

static inline void write_times(int index, u64 current_time) {
    my_tracing_array[index] = current_time;
}

static inline void read_times(void) {
    int i;
    for (i = 0; i < 10; ++i) {
        printk(KERN_INFO "Element %d: %llu\n", i, my_tracing_array[i]);
    }
}

#endif /* READ_WRITE_TO_HEAPS_H */
