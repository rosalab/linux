/*
 * Contains the struct definition and linked list operations for dealing 
 * with abrupt termination of eBPF programs
 */
#ifndef UNWIND_LIST_H
#define UNWIND_LIST_H

#include<linux/list.h>
#include<linux/percpu.h>
#include<linux/slab.h>
#include<linux/spinlock.h>



struct unwind_list_obj{
	struct list_head  entry;
	
	bool is_reference; // true if this helper/kfunc takes/leaves reference
	bool is_lock; // true if takes/releases locks
	unsigned long stored_ip; // the ip within the BPF bytecode where this function is called 
	unsigned long func_addr; // symbol address of the function in concern
	unsigned long obj_addr; // address of the lock object or the referenced object
};

/* 
 * We can't have a linked list for each BPF invocation as :
	* As objects are to be added from within a helper call, it might not 
	  be easy to identify which BPF program called it. Thus, we init 
	  a linked list for each CPU. We know that each CPU will run an eBPF
	  program to completion, thus a single list per cpu will be enough. 
	
	* Initializing the linked list for every BPF invocation will mean 
	  overheads.  
 */



//  init/de-init
int pcpu_init_unwindlist(void); 
// clear off all elems from current CPU's list 
void pcpu_reset_unwindlist(void);
//  push/pop 
void pcpu_push_unwindlist(struct unwind_list_obj *); 
//void pcpu_destroy_unwindlist(void);


//struct unwind_list* pcpu_pop_unwind_list();

#endif // UNWIND_LIST_H
