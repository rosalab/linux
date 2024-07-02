/*
root@q:/moo-kernel/linux/bpf_trigger# insmod vmalloc_trigger_module.ko
[   86.528924][  T547] vmalloc_trigger_module: loading out-of-tree module taints kernel.
[   86.530267][  T547] Kernel Module Init
[   86.530876][  T547] Total end-to-end time is 76567 nanoseconds
        root@q:/moo-kernel/linux/bpf_trigger# cat /sys/kernel/debug/tracing/trace_pipe
*/



#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>     // For kmalloc, kfree
#include <linux/time.h>     // For time measurement
#include <linux/vmalloc.h>  // For vmalloc, vfree

#define VMALLOC_SIZE (1024 * 1024)

static void *vmalloc_buffer = NULL;

// Function prototypes
uint64_t measure_execution_time(void (*function)(void));
void alloc_vmap_area(void);
void free_vmap_area_noflush(void);
void purge_vmap_area_lazy(void);

// Function to measure execution time
uint64_t measure_execution_time(void (*function)(void)) {
    ktime_t begin, end;
    uint64_t time_ns;

    begin = ktime_get();
    function();
    end = ktime_get();

    time_ns = ktime_to_ns(ktime_sub(end, begin));
    return time_ns;
}

// Directory specific functions
void alloc_vmap_area(void) {
    vmalloc_buffer = vmalloc(VMALLOC_SIZE);
    if (!vmalloc_buffer) {
        printk(KERN_ERR "Failed to allocate vmap area\n");
        return;
    }
    memset(vmalloc_buffer, 0, VMALLOC_SIZE);
}

void free_vmap_area_noflush(void) {
    if (vmalloc_buffer) {
        vfree(vmalloc_buffer);
        printk(KERN_INFO "Freed vmap area\n");
    } else {
        printk(KERN_WARNING "No vmap area to free\n");
    }
}

void purge_vmap_area_lazy(void) {
    if (vmalloc_buffer) {
        vunmap(vmalloc_buffer);
        printk(KERN_INFO "Purged vmap area\n");
    } else {
        printk(KERN_WARNING "No vmap area to purge\n");
    }
}

static int cleanup_option = 1;  // Default to free_vmap_area_noflush

module_param(cleanup_option, int, 0644);  // Define a module parameter

static int __init kernel_module_init(void) {
    uint64_t execution_time;
    printk(KERN_INFO "Kernel Module Init\n");
    execution_time = measure_execution_time(alloc_vmap_area);
    printk("Total end-to-end time is %llu nanoseconds\n", execution_time);
    return 0;
}

static void __exit kernel_module_exit(void) {
    uint64_t execution_time;
    printk(KERN_INFO "Kernel Module Exit\n");

    if (cleanup_option == 1) {
        execution_time = measure_execution_time(free_vmap_area_noflush);
        printk("Total end-to-end time is %llu nanoseconds\n", (unsigned long long) execution_time);
    } else if (cleanup_option == 2) {
        execution_time = measure_execution_time(purge_vmap_area_lazy);
        printk("Total end-to-end time is %llu nanoseconds\n", execution_time);
    } else {
        printk(KERN_WARNING "Invalid cleanup option\n");
    }
}

module_init(kernel_module_init);
module_exit(kernel_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Uddhav P. Gautam");
MODULE_DESCRIPTION("VMalloc Kernel Module");
