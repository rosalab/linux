#include <uapi/linux/bpf.h>
#include <uapi/linux/if_ether.h>
#include <uapi/linux/if_packet.h>
#include <uapi/linux/ip.h>
#include <uapi/linux/in.h>
#include <uapi/linux/tcp.h>
#include <uapi/linux/icmp.h>
#include <uapi/linux/filter.h>
#include <uapi/linux/pkt_cls.h>
#include <bpf/bpf_helpers.h>
#include "bpf_legacy.h"



SEC("ingress")
int sk_lookup_success_simple(struct __sk_buff *skb)
{
	struct bpf_sock_tuple tuple = {};
	struct bpf_sock *sk, *sk2,*sk3, *sk4, *sk5, *sk6;
	int x=0;
	sk = bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);
	x += 5;
	sk2 = bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);
	bpf_printk("Random stuff\n");

	sk3 = bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);

	sk4 = bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);
	
	sk5 = bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);

	sk6 = bpf_sk_lookup_tcp(skb, &tuple, sizeof(tuple), BPF_F_CURRENT_NETNS, 0);

	if (sk)
		bpf_sk_release(sk);
	if (sk2)
		bpf_sk_release(sk2);
	if (sk3)
		bpf_sk_release(sk3);
	if (sk4)
		bpf_sk_release(sk4);
	if (sk5)
		bpf_sk_release(sk5);

	if (sk6)
		bpf_sk_release(sk6);

	return 0;
}

char _license[] SEC("license") = "GPL";
