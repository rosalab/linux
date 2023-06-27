#include<bpf/bpf_helpers.h>
#include<bpf/bpf_tracing.h>

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;


SEC("tracepoint/syscalls/sys_exit_hello")
int test_kfunc_main(struct pt_regs *ctx ){
	struct task_struct *ts;
	ts = bpf_task_from_pid(0xcafef00d);
	if(ts){
		bpf_task_release(ts);
		return 1;
	}
	return 0;
}
