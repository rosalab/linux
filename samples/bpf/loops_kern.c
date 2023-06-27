#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <uapi/linux/bpf.h>

#define __ksym __attribute__((section(".ksyms")))
struct task_struct *bpf_task_acquire(struct task_struct *p) __ksym;
void bpf_task_release(struct task_struct *p) __ksym;

SEC("tp_btf/task_newtask")
int trace_sys_connect(struct pt_regs *ctx)
{	
	bpf_printk("Testing task_struct kfuncs\n");
	
	struct task_struct *current, *acquired;

	current = bpf_get_current_task_btf();
	acquired = bpf_task_acquire(current);
	bpf_task_release(acquired);
	return 0;	
}


char _license[] SEC("license") = "GPL";
 
