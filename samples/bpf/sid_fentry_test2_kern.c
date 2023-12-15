#include <bpf/bpf_helpers.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <bpf/bpf_tracing.h>

#define SIZE_OF_STACK 400 

SEC("fentry/bpf_get_current_pid_tgid")
int fentry_test2(void *ctx){
	
	bpf_printk("Inside fentry test2 function\n");
    
    unsigned char stack_space[SIZE_OF_STACK] = {0};
    /* 8 byte */
    unsigned long int i = 0;
    bpf_printk("value of i: %d, address of stack_space[i]: %llu\n", i,(unsigned long long) &stack_space[i]);

    for(i = 0; i < SIZE_OF_STACK; i++) {
        stack_space[i] = i % 255;
    }   

    bpf_printk("value of i: %d, address of stack_space[i]: %llu\n", i,(unsigned long long) &stack_space[i]);
    int x = bpf_get_current_pid_tgid();

    bpf_printk("The value of bpf_get_current_pid_tgid() in fentry_test2: %d\n", x);
	return 0;
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
