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

SEC("tracepoint/syscalls/sys_enter_hello")
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


char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
 
