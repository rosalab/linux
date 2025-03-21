#include <linux/syscalls.h>
#include <linux/printk.h>
#include <linux/mutex.h>
#include <linux/memory.h>
#include <asm/set_memory.h>
#include <linux/bpf.h>

#define X86_64_REL_JMP_LEN 5

static noinline int __sys_test_poke2(void)
{
    pr_info("Poked! :D\n");
    return 1;
}

static noinline int __sys_test_text_poke(void)
{
    pr_info("Testing Text Poke\n");
    return 0;
}

static struct bpf_map *map;

extern int __sys_bpf(enum bpf_cmd cmd, bpfptr_t uattr, unsigned int size);

static void __test_map(void)
{
    if (map != NULL) {
        printk(KERN_INFO "Found map name %s\n", map->name);
        return;
    }

    union bpf_attr attr;
    bpfptr_t attr_ptr;
    attr_ptr.is_kernel = true;
    attr_ptr.kernel = &attr;

    attr.map_type = BPF_MAP_TYPE_ARRAY;
    attr.key_size = sizeof(unsigned int);
    attr.value_size = sizeof(unsigned int);
    attr.max_entries = 1;
    strncpy(attr.map_name, "test_map\0", 9);


	attr.btf_fd = 0;
	attr.btf_key_type_id = 0;
	attr.btf_value_type_id = 0;
	attr.btf_vmlinux_value_type_id = 0;
	attr.value_type_btf_obj_fd = 0;

	attr.inner_map_fd = 0;
	attr.map_flags = 0;
	attr.map_extra = 0;
	attr.numa_node = 0;
	attr.map_ifindex = 0;

	attr.map_token_fd = 0;


    int map_fd = __sys_bpf(BPF_MAP_CREATE, attr_ptr, offsetofend(union bpf_attr, map_token_fd));
    printk(KERN_INFO "Map fd is %d\n", map_fd);

    map = bpf_map_get(map_fd);
    printk(KERN_INFO "Map name is %s\n", map->name);

}


SYSCALL_DEFINE0(test_text_poke)
{
    __test_map();
    return 0;
}

//SYSCALL_DEFINE0(test_text_poke)
//{
//    __sys_test_text_poke();
//
//    mutex_lock(&text_mutex);
//    char * ptr = (char *)__sys_test_text_poke;
//
//    unsigned int op = 0xe9; // relative jump opcode
//    int diff = (int)((unsigned long)(__sys_test_poke2) - (unsigned long)__sys_test_text_poke) - X86_64_REL_JMP_LEN;  // RIP is instruction following JMP
//    //set_memory_rw(PAGE_ALIGN((unsigned long)__sys_test_text_poke), 1);
//    set_memory_rw((unsigned long)__sys_test_text_poke & PAGE_MASK, 1);
//
//    ptr[0] = op;
//
//    memcpy(ptr+1, &diff, 4);
//    mutex_unlock(&text_mutex);
//
//    set_memory_ro((unsigned long)__sys_test_text_poke & PAGE_MASK, 1);
//
//    __sys_test_text_poke();
//
//
//
//
//    //set_memory_ro((unsigned long)&__sys_test_text_poke, 1);
//    return 0;
//}
