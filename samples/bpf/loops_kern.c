#define KBUILD_MODNAME "foo"
#include <linux/ptrace.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <uapi/linux/in6.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "trace_common.h"

#define MAX_DICT_SIZE 1000 
#define MAX_DICT_VAL  10000

struct {
    __uint(type, BPF_MAP_TYPE_LRU_HASH);
    __uint(max_entries, MAX_DICT_SIZE);
    __type(key, int);
    __type(value,int);
} my_map SEC(".maps");

struct {
        __uint(type, BPF_MAP_TYPE_PROG_ARRAY);
        __uint(key_size, sizeof(u32));
        __uint(value_size, sizeof(u32));
        __uint(max_entries, 8);
} jmp_table SEC(".maps");


void do_reg_lookup()
{
        int *result;
	for(int i=0;i<1000;i++){
		const int k = bpf_get_prandom_u32()%100;
        	int *result = bpf_map_lookup_elem(&my_map, &k);
		/*if (result ) 
			bpf_trace_printk("Found %d\n",sizeof("Found %d\n"), *result);
		else
			bpf_trace_printk("Not found\n", sizeof("Not found\n"));
		*/
	}
}

void _populate_map(){
	for(int i=0;i<10000;i++){
		int val = bpf_get_prandom_u32() % MAX_DICT_VAL;
		const int key=bpf_get_prandom_u32() % MAX_DICT_SIZE;
		bpf_map_update_elem(&my_map, &key, &val, BPF_ANY);
	}
	//bpf_printk("Map populate complete..\n");
}

static int runner(void* ctx){

	//populate the map with 1000 random numbers
	_populate_map();

	// look for 10 random element from the map to modify LRU.
	do_reg_lookup(); 	
	
	return 0;
}

static int runner2(void* ctx){

	bpf_loop(1000000, runner, NULL,0);
	return 0;

}


SEC("kprobe/__sys_connect")
int trace_sys_connect(struct pt_regs *ctx)
{
	bpf_printk("Inside trace_sys_connect_\n");
	long ret = bpf_loop(10000, runner2, NULL,0);
	//long ret = runner(ctx);	
	bpf_printk("Exiting trace_sys_connect_\n");
	return ret;	
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
 
