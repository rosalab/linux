#undef TRACE_SYSTEM
#define TRACE_SYSTEM mm_fault

#if !defined(_TRACE_MM_FAULT_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MM_FAULT_H

#include <linux/types.h>
#include <linux/tracepoint.h>
#include <linux/mm_types.h>

TRACE_EVENT(handle_mm_fault,

	TP_PROTO(struct vm_area_struct *vma,
		unsigned long address, unsigned int flags),

	TP_ARGS(vma, address, flags),

	TP_STRUCT__entry(
		__field(	unsigned long,	vm_start		)
		__field(	unsigned long,	vm_end		)
		__field(	unsigned long,	address		)
		__field(	unsigned int,	flags	)
	),

	TP_fast_assign(
		__entry->vm_start	= vma->vm_start;
		__entry->vm_end		= vma->vm_end;
		__entry->address	= address;
		__entry->flags	= flags;
	),

	TP_printk("vm_start=0x%lx vm_end=0x%lx address=0x%lx flags=%d",
		__entry->vm_start, __entry->vm_end,
		__entry->address, __entry->flags)
);

DECLARE_EVENT_CLASS(mm_fault_class,
        TP_PROTO(struct vm_area_struct *vma, unsigned long address,
                 unsigned int flags, vm_fault_t fault_flags),
        TP_ARGS(vma, address, flags, fault_flags),
        TP_STRUCT__entry(
                __field(unsigned long, address)
                __field(unsigned long, vm_start)
                __field(unsigned long, vm_end)
                __field(unsigned int, flags)
                __field(vm_fault_t, fault_flags)
                __field(vm_flags_t, vma_flags)
                __field(unsigned long, pgoff)
        ),
        TP_fast_assign(
                __entry->address = address;
                __entry->vm_start = vma->vm_start;
                __entry->vm_end = vma->vm_end;
                __entry->flags = flags;
                __entry->fault_flags = fault_flags;
                __entry->vma_flags = vma->vm_flags;
                __entry->pgoff = (address - vma->vm_start) >> PAGE_SHIFT;
        ),
        TP_printk("address=0x%lx vm_start=0x%lx vm_end=0x%lx flags=0x%x "
                  "fault_flags=0x%x vma_flags=0x%lx pgoff=%lu",
                  __entry->address, __entry->vm_start, __entry->vm_end,
                  __entry->flags, __entry->fault_flags,
                  __entry->vma_flags, __entry->pgoff)
);DEFINE_EVENT(mm_fault_class, mm_account_fault,
        TP_PROTO(struct vm_area_struct *vma, unsigned long address,
                 unsigned int flags, vm_fault_t fault_flags),
        TP_ARGS(vma, address, flags, fault_flags)
);

// DECLARE_EVENT_CLASS(mm_fault_class,
//         TP_PROTO(struct mm_struct *mm, unsigned long address,
//                  unsigned int flags, vm_fault_t fault_flags),
//         TP_ARGS(mm, address, flags, fault_flags),
//         TP_STRUCT__entry(
//                 __field(unsigned long, address)
//                 __field(unsigned long, mmap_base)
//                 __field(unsigned int, flags)
//                 __field(vm_fault_t, fault_flags)
//         ),
//         TP_fast_assign(
//                 __entry->address = address;
//                 __entry->mmap_base = mm->mmap_base;
//                 __entry->flags = flags;
//                 __entry->fault_flags = fault_flags;
//         ),
//         TP_printk("address=0x%lx mmap_base=0x%lx flags=0x%x "
//                   "fault_flags=0x%x",
//                   __entry->address, __entry->mmap_base,
//                   __entry->flags, __entry->fault_flags)
// );
// DEFINE_EVENT(mm_fault_class, mm_account_fault,
//         TP_PROTO(struct mm_struct *mm, unsigned long address,
//                  unsigned int flags, vm_fault_t fault_flags),
//         TP_ARGS(mm, address, flags, fault_flags)
// );



#endif /* _TRACE_MM_FAULT_H */

#include <trace/define_trace.h>