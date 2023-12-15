#include <bpf/bpf_helpers.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <bpf/bpf_tracing.h>


SEC("fentry/__sys_socket")
int fentry_test1(void *ctx){
	
	bpf_printk("Inside fentry test1 function\n");
    
    int family = *((int *) ctx); 
    int type= *((int *) ctx + 2); 
    int protocol= *((int *) ctx + 4); 

    bpf_printk("family: %d", family);
    bpf_printk("type: %d", type);
    bpf_printk("protocol: %d", protocol);

	return 0;
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
