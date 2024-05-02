#include <linux/ptrace.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <uapi/linux/in6.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "trace_common.h"


#define MAX_DICT_SIZE 10000 
#define MAX_DICT_VAL  10000



struct 
{
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __uint(max_entries, 3); // index 0 : total time, index 1 : total runs, index 3: id
    __type(key, int);
    __type(value,int);
} 
timer SEC(".maps");

struct 
{
    __uint(type, BPF_MAP_TYPE_LRU_HASH);
    __uint(max_entries, MAX_DICT_SIZE);
    __type(key, int);
    __type(value,int);
} 
my_map SEC(".maps");

struct 
{
        __uint(type, BPF_MAP_TYPE_PROG_ARRAY);
        __uint(key_size, sizeof(u32));
        __uint(value_size, sizeof(u32));
        __uint(max_entries, 8);
} 
jmp_table SEC(".maps");

struct {
 __uint(type, BPF_MAP_TYPE_LRU_HASH);
 __uint(max_entries, MAX_DICT_SIZE);
 __type(key, int);
 __type(value,int);
} my_map SEC(".maps");

void _populate_map()
{
	u64 start_time = bpf_ktime_get_ns();
       for(int i=0;i<MAX_DICT_SIZE;i++){
               int val = bpf_get_prandom_u32() % MAX_DICT_VAL;
               const int key=bpf_get_prandom_u32() % MAX_DICT_SIZE;
               bpf_map_update_elem(&my_map, &key, &val, BPF_ANY);
       }
	u64 time_delta = bpf_ktime_get_ns() - start_time; 
       bpf_printk("Map populate complete in time:%d\n", time_delta);
}

static int loop2(void){
	/*
	int key = bpf_get_prandom_u32() % MAX_DICT_VAL; 
	int *val;
	val = bpf_map_lookup_elem(&my_map, &key);
	*/
	bpf_printk("Printing from loop2");
	return 0;
}

static int loop1(void){
	u32 iter = (1<<10);	
	bpf_loop(iter, loop2, NULL, 0);

	/*
	bpf_spin_lock(&val->lock);
	val->cnt++;
	bpf_spin_unlock(&val->lock);
	*/

out:
	return 0;
}


SEC("tracepoint/syscalls/sys_exit_hello")
int trace_sys_connect1(struct pt_regs *ctx)
{	
	//bpf_printk("Inside trace_sys_connect\n");

	//bpf_printk("Inside trace_sys_connect\n");
	//u32 iter = (1<<2);	
	//bpf_printk("Loop iteration count: %dk\n",iter);
	//bpf_loop(iter, runner, NULL,0);
	//int id;
	int id = bpf_get_numa_node_id();
	bpf_printk("numa node run 1 : %d\nStarting another helper call", id);
	id = bpf_get_numa_node_id();
	//id = bpf_get_numa_node_id();
	//id = bpf_get_numa_node_id();
	//id = bpf_get_numa_node_id();
	bpf_printk("numa node run 2 : %d\n", id);
	//bpf_printk("BPF : at NUMA node : %d\n", id);
	//bpf_printk("Exiting trace_sys_connect\n");

/*
	const int t = 0;
	const int r = 1;
	const int id_index = 2;
	const int val = 0;
	int *total_time = bpf_map_lookup_elem(&timer, &t);
	int *total_run = bpf_map_lookup_elem(&timer, &r);
	bpf_map_update_elem(&timer, &id_index, &val, BPF_ANY);
	volatile int *id = bpf_map_lookup_elem(&timer, &id_index);
	if (!id)
		return 0;

	if (!total_time ){
		bpf_map_update_elem(&timer, &t, &val, BPF_ANY);
		total_time = bpf_map_lookup_elem(&timer, &t);
	}
	if(!total_time)
		return 0;

	if (!total_run ){
		bpf_map_update_elem(&timer, &r, &val, BPF_ANY);
		total_run = bpf_map_lookup_elem(&timer, &r);
	}

	if(!total_run)	
		return 0;

	bpf_printk("initial time : %d, initial run: %d", *total_time, *total_run);
	int start_time = bpf_ktime_get_ns();

	for(int i=0;i<120000; i++){
		bpf_printk("At %d", i);
	}

	int delta = bpf_ktime_get_ns() - start_time; 
	__sync_add_and_fetch(total_time,delta);
	__sync_add_and_fetch(total_run,1);
	bpf_printk("Total time : %d, total run : %d, id:%d\n", *total_time, *total_run,id);
*/
	return 0;	
}
/*
SEC("kprobe/__x64_sys_execve")
int kprobe_execve(struct pt_regs *ctx)
{
    void *ip = (void*)PT_REGS_IP(ctx);

    if (ip == &trace_sys_connect + 1) {
        // instruction after the marker
    	bpf_trace_printk("kprobe handler\n");
	} 
    //else if (ip == &trace_sys_connect + 3) {
        // instruction to probe
    //}

    return 0;
}
*/

/*
#define __ksym __attribute__((section(".ksyms")))
struct task_struct *bpf_task_acquire(struct task_struct *p) __ksym;
void bpf_task_release(struct task_struct *p) __ksym;

SEC("tp_btf/task_newtask")
int trace_sys_connect(struct pt_regs *ctx)
{	

	/*
	//_populate_map();

	u32 iter = (1<<20);	
	//bpf_printk("Loop iteration count: %dk\n",iter);
	u64 start_time = bpf_ktime_get_ns();
	bpf_loop(iter, loop1, NULL, 0);
	u64 time_delta = bpf_ktime_get_ns() - start_time; 
	*/	
	bpf_printk("BPF program : calling get_numa_node_id\n");
	bpf_get_numa_node_id();
	bpf_printk("BPF prog finished.\n" );
	return 0;	
}

*/

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
 
