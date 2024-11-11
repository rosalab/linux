#include <linux/ptrace.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <uapi/linux/in6.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

#if defined(CONFIG_FUNCTION_TRACER)
#define CC_USING_FENTRY
#endif

#define MAX_DICT_SIZE 1000 
#define MAX_DICT_VAL  10000

struct 
{
    __uint(type, BPF_MAP_TYPE_LRU_HASH);
    __uint(max_entries, MAX_DICT_SIZE);
    __type(key, int);
    __type(value,int);
} 
my_map SEC(".maps");

void populate_map()
{
	bpf_printk("Hello world ;)\n");
}

SEC("tracepoint/syscalls/sys_exit_saterm_test")
int tracepoint_exit_saterm_connect1(struct pt_regs *ctx)
{
	populate_map();
	return 0;
}

