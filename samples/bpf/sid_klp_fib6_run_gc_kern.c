#include <bpf/bpf_helpers.h>
#include <linux/version.h>
#include <uapi/linux/bpf.h>
#include <bpf/bpf_tracing.h>

/*
 * Here is the idea
 * when the function fib6_run_gc is triggered
 * fentry will be executed first and modify
 * function then fmod_ret will return 1 this
 * will skip the original function logic and
 * then fexit will do nothing for now
 */
SEC("fentry/ip6_dst_gc")
int fentry_func(void *ctxt) {
	bpf_printk("fentry_func: \n");
	return 0;
}

SEC("fmod_ret/ip6_dst_gc")
int fmod_ret_func(void *ctxt) {
	bpf_printk("fmod_ret_func: \n");
	return 1;
}

SEC("fexit/ip6_dst_gc")
int fexit_func(void *ctxt) {
	// Can be empty for now
	bpf_printk("fexit_func: \n");
	return 0;
}

char _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
