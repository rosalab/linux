#include <linux/ptrace.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <uapi/linux/in6.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>
#include "trace_common.h"

#if defined(CONFIG_FUNCTION_TRACER)
#define CC_USING_FENTRY
#endif


static int cbck(void* ctx)
{
	return 	bpf_get_smp_processor_id()%2;

}

SEC("tracepoint/syscalls/sys_exit_hello")
int trace_sys_connect1(struct pt_regs *ctx)
{	
	bpf_printk("Inside trace_sys_connect\n");
	bpf_printk("processor id: %d\n", bpf_get_smp_processor_id());
	u32 iter = (1<<2);	
	bpf_printk("Loop iteration count: %dk\n",iter);
	bpf_loop(iter, cbck, NULL,0);

	int unique_id = bpf_test_acquire();
	bpf_printk("Add timer logs here");
	bpf_test_release(unique_id);

	return 0;	
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
 
