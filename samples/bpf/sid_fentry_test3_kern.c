#include <bpf/bpf_helpers.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <bpf/bpf_tracing.h>



SEC("fentry/bpf_get_current_pid_tgid")
int fentry_test3(void *ctx){
	
	bpf_printk("Inside fentry test3 function\n");
    
    int x = bpf_get_current_pid_tgid();

    bpf_printk("The value of bpf_get_current_pid_tgid() in fentry_test3: %d\n", x);
	return 0;
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
