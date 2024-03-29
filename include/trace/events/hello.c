#undef TRACE_SYSTEM
#define TRACE_SYSTEM subsys

#if !defined(_TRACE_SUBSYS_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_SUBSYS_H

#include <linux/tracepoint.h>
#ifdef CONFIG_HAVE_SYSCALL_TRACEPOINTS

DECLARE_TRACE(sys_hello,
	   TP_PROTO(struct pt_regs *regs, long ret),
           TP_ARGS(regs, ret));
#endif /* _TRACE_SUBSYS_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
