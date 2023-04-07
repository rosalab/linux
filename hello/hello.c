
#include<linux/kernel.h>
#include<linux/bpf.h>
#include<linux/filter.h>
#include<linux/syscalls.h>
#include <linux/interrupt.h>
#include <linux/kprobes.h> // for registering kprobes

char shellcode[] = {0xf3,0x0f ,0x1e ,0xfa ,0x55 ,0x48 ,0x89 ,0xe5, 0xb8, 0x00, 0x00, 0x00,0x00, 0x5d ,0xc3};

/*static int tester(void){
	printk("Inside tester function for addresses\n");
	return 0;
}*/
static int __kprobes handler_pre(struct kprobe* p, struct pt_regs *regs)
{
        printk("[$$$] Inside kprobe pre handler for address : 0x%x\n", (unsigned int)*p->addr);
        regs->ax = 0xdeadbeef;
	return 0;
 }

static void loop(void){
	volatile unsigned long rxx; // for fetching registers and saving later on
	int i=0;

	while(1){
		printk("Looping before.. %d\n",i);// Attaching kprobe here to atleast print "Looping" once. 
		asm volatile("\t mov %%rax , %0": "=m"(rxx) :: "%rax");	
		if(rxx == 0xdeadbeef)
			return;
		printk("Looping after.. %d\n",i);// Attaching kprobe here to atleast print "Looping" once. 
		i++;
	}

}

static void test_kprobes(void){

	struct kprobe *kp;
        kp = kzalloc(sizeof(struct kprobe), GFP_KERNEL);
        kp->addr = (kprobe_opcode_t *)(loop);
        kp->offset = 0x123 - 0xef ;
        kp->pre_handler = handler_pre ;	
	unsigned long ret = register_kprobe(kp);
	if(ret!=0){
		printk("Failed at register kprobe. Error : 0x%lx\n", ret);
		return;
	}
	loop();
}

SYSCALL_DEFINE0(hello){
	//struct bpf_prog *prog;
	//prog = bpf_prog_by_id(prog_id);
	//int cpu_id = prog->saved_state->cpu_id;

	//for (i = 0; i < prog->aux->func_cnt; i++)
	//      info.jited_prog_len += prog->aux->func[i]->jited_len;

	/* Commented on : 06 Feb, 2023
	   printk("--- Address of tester function : %llx\n", (unsigned long)tester);
	//printk("--- Size of jited program : %d\n", prog->jited_len);

	printk("calling tester function\n");
	tester();

	printk("Calling SET_NX function %llx\n",(PAGE_MASK));
	printk("Masked address : %llx\n", (unsigned long)tester & PAGE_MASK);
	set_memory_nx((unsigned long)tester & PAGE_MASK, 10 );

	printk("calling tester function after NX\n");
	tester();
	 */ 

	/* Commented on : 30 March, 2023 
	int (*dest)(void) = NULL;
	//dest = mmap(NULL, 4096, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE | MAP_ANON, -1,0);
	dest = vmalloc(4096);
	if(dest==NULL){
		printk("Mapping Failed");
		return -1;
	}

	memcpy(dest, shellcode, sizeof(shellcode));
	set_memory_x(dest,1);

	__builtin___clear_cache (dest, dest + sizeof(dest));
	printk("bytecode returned : %d\n", dest());

	if(0!=mprotect(dest, sizeof(shellcode), PROT_READ|PROT_WRITE)){
		perror("mprotect failed");
		return -1;
	}

	
	set_memory_nx(dest, 1);
	set_memory_rw(dest,1);
	
	printk("nonexecutable bytecode returned : %d\n", dest());

	int err = munmap(dest, 4069);
	if(err!=0){
		perror("Unmapping Failed");
		return -1;
	}
	
	vfree(dest);
	*/

	test_kprobes();	
	printk("Exiting from sys_hello!\n");
	return 0;
}
