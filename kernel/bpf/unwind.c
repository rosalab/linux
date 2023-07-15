/*
  * Internal functions to be used by BPF helpers to keep track 
  * of referenced objects or acquired locks. This information 
  * will be used during a runtime termination request to clean-up.
  */

#include <linux/unwind_list.h>

static __maybe_unused bool is_initialized; // Has init() been called even once
static  __maybe_unused struct list_head unwind_list[NR_CPUS];

DEFINE_SPINLOCK(init_lock);// Global lock to modify the is_initialized variable

__attribute__((__used__))
int pcpu_init_unwindlist(void){
#ifdef CONFIG_HAVE_BPF_TERMINATION
	/*int cpu;
	for_each_possible_cpu(cpu){
		unwind_list->entry = alloc_percpu(struct list_head);	
		if (!unwind_list->entry)
			return -ENOMEM;
		struct list_head *this_cpu_head;
		this_cpu_head = per_cpu_ptr(unwind_list->entry, cpu);
		struct unwind_list *node = list_entry(this_cpu_head, struct unwind_list, entry);
		// Both is_reference and is_lock won't be false 
		// unless its a boundary case 
		node->is_reference = node->is_lock = false;
	}
	*/
	if(likely(is_initialized))
		return 0;
	int i;
	spin_lock(&init_lock);		
	
	/* A process can be waiting when it saw is_initilized = false
	 * By the time it gets the lock, the last lock acquiring process 
	 * could have already initialized all list heads. Hence, another 
	 * check is required. 
	 */
	if(is_initialized) // 
		goto out;

	for(i=0;i<NR_CPUS;i++)
		INIT_LIST_HEAD(&unwind_list[i]);//[NR_CPUS];
	printk("pcpu_init_unwindlist complete\n");
	is_initialized = true;
out:
	spin_unlock(&init_lock);
#endif
	return 0;
}


// remove all elements from current CPU's unwind list
__attribute__((__used__))
void pcpu_reset_unwindlist(void){
#ifdef CONFIG_HAVE_BPF_TERMINATION
	// untill list exists and is non empty, call pop 
	/*struct list_head *tmp, *pos, *head;
	struct unwind_list *node ;
	//cpu_head = get_cpu_ptr(unwind_list->entry);
	int cpu;
	for(cpu=0;cpu<num_online_cpus();cpu++){
		head = unwind_list[cpu].entry;	
		list_for_each_safe(pos, tmp, head){ // tmp is used internally by list_for_each_safe macro
			node = list_entry(pos, struct unwind_list, entry);
			list_del(pos);
			kfree(node);
		}
	}
	*/
	int cpu = raw_smp_processor_id();
	printk("Before deleting linkedlist objexcts \n");
	struct unwind_list_obj *cursor, *temp;
	list_for_each_entry_safe(cursor, temp, &unwind_list[cpu], entry){
		printk("Deleting obj:0x%lx, helper:0x%lx\n", cursor->obj_addr, cursor->func_addr);
		list_del(&cursor->entry);
		kfree(cursor);
	}
#endif
}
/*
void pcpu_destroy_unwindlist(void){
	free_percpu(unwind_list->entry);
}
*/


//  push the element to the tail of linked list belonging to this cpu : act like a FIFO queue
__attribute__((__used__))
void pcpu_push_unwindlist(struct unwind_list_obj *node){
#ifdef CONFIG_HAVE_BPF_TERMINATION
	//struct list_head *head = get_cpu_ptr(unwind_list->entry);
	int cpu = raw_smp_processor_id();
	INIT_LIST_HEAD(&node->entry);
	list_add_tail(&node->entry, &unwind_list[cpu]);	
#endif
}
/*
// pop the element from this CPU's linked list
struct unwind_list* pcpu_pop_unwind_list(){
	// check if list exists and has an element
	struct unwind_list *node, *head;
	head = list_entry(
			get_cpu_ptr(unwind_list->entry),
			struct unwind_list, 
			entry);	
}

*/

EXPORT_SYMBOL_GPL(pcpu_init_unwindlist);
EXPORT_SYMBOL_GPL(pcpu_reset_unwindlist);
EXPORT_SYMBOL_GPL(pcpu_push_unwindlist);
