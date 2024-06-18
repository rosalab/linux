#include "read_write_to_heaps.h"

u64 *heap_buffer = NULL;
struct mutex heap_buffer_lock;

void init_heap_buffer(void) {
	if (!heap_buffer) {
		heap_buffer = kmalloc(BUFFER_SIZE * sizeof(u64), GFP_KERNEL);
		if (!heap_buffer) {
			printk(KERN_ERR "Failed to allocate heap buffer\n");
			return;
		}
		memset(heap_buffer, 0, BUFFER_SIZE * sizeof(u64));
		mutex_init(&heap_buffer_lock);
	}
}
