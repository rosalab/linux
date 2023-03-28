#include <unistd.h>
#include <linux/unistd.h>

int main(void)
{
	// triggers the tracepoint syscalls/sys_enter_dup
        return syscall(__NR_dup, 1);
}
