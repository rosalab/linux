//
// Created by upgautamvt on 6/18/24.
//

#ifndef READ_WRITE_TO_HEAPS_H
#define READ_WRITE_TO_HEAPS_H

#include <linux/types.h>
#include <asm/atomic.h>
#include <linux/ktime.h>
#include <linux/slab.h> // Required for kmalloc/kfree
#include <linux/mutex.h> // Required for mutex

#define BUFFER_SIZE 1024 // Fixed size
#define HEAP_BUF_LEN (BUFFER_SIZE / sizeof(u64))

extern u64 *heap_buffer; // Declare heap_buffer as extern
extern struct mutex heap_buffer_lock; // Declare a mutex for thread-safe access

void init_heap_buffer(void);

static inline void write_times(int index, u64 current_time) {
	mutex_lock(&heap_buffer_lock);
	if (!heap_buffer) {
		printk(KERN_ERR "Heap buffer not allocated yet\n");
		return;
	}
	atomic64_set(&((atomic64_t *)heap_buffer)[index], current_time);
	mutex_unlock(&heap_buffer_lock);
}

static inline void read_times(void) {
	if (!heap_buffer) {
		printk(KERN_ERR "Heap buffer not allocated yet\n");
		return;
	}

	mutex_lock(&heap_buffer_lock);
	printk(KERN_INFO "trace_call_bpf Start Time: %llu nanoseconds, and Stop Time: %llu nanoseconds\n",
		atomic64_read((atomic64_t *)&heap_buffer[0]), atomic64_read((atomic64_t *)&heap_buffer[1]));
	printk(KERN_INFO "perf_call_bpf_enter Start Time: %llu nanoseconds, and Stop Time: %llu nanoseconds\n",
		atomic64_read((atomic64_t *)&heap_buffer[2]), atomic64_read((atomic64_t *)&heap_buffer[3]));
	mutex_unlock(&heap_buffer_lock);
}


#endif /* READ_WRITE_TO_HEAPS_H */

