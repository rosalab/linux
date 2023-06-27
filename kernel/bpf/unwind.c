/*
  * Internal functions to be used by BPF helpers to keep track 
  * of referenced objects or acquired locks. This information 
  * will be used during a runtime termination request to clean-up.
  */

#include "unwind_list.h"


int pcpu_init_unwindlist(){
	int cpu;
	unwind_list->entry = alloc_percpu(struct list_head);	
	if (!s->entry)
		return -ENOMEM;
	for_each_possible_cpu(cpu){
		struct unwind_list *node = list_entry(
						per_cpu_ptr(unwind_list->entry, cpu), 
						struct unwind_list, entry);
		// Both is_reference and is_lock won't be false 
		// unless its a boundary case 
		node->is_reference = node->is_lock = false;
	}
	return 0;
}

// remove all elements  
void pcpu_reset_unwindlist(){
	// untill list exists and is non empty, call pop 
	struct list_head *tmp, *node;
	struct list_head *head ;
	head = get_cpu_ptr(unwind_list->entry);
	
	list_for_each_safe(pos, tmp, head){ // tmp is used internally by list_for_each_safe macro
		node = list_entry(pos, struct unwind_list, entry);
		list_del(node);
		free(node);
	}
}

void pcpu_destroy_unwindlist(){
	free_percpu(unwind_list->entry);
}

/*
//  push the element to the linked list belonging to this cpu
void pcpu_push_unwindlist(struct unwind_list *node){
	struct list_head *head = get_cpu_ptr(unwind_list->entry);
	list_add(&node->entry, &unwind_entry->entry);	
}

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
