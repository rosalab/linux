BPF termination
============

In `samples/bpf/loops_kern.c`, it is a BPF program with two helper calls (other than the debug print calls).
The `bpf_get_numa_node_id()` is modified to sleep for 5-10 seconds to simulate a long running helper ultimately
leading to a long running BPF program. 

In this commit, using the `bpftool prog terminate <prog-ID>` command, an IPI will be sent to the CPU currently
running the BPF program.
The IPI will be handled by bpf_die defined in `kernel/bpf/syscall.c` which will just change the execution state
from the original BPF program to the termination copy, which is prepared at load time itself (check `patch_generator`).
In order to change the execution state, there are two cases : 
 * Case 1 : BPF is currently running a helper that could further be inside another kernel function. 
	- In this case, we do not want to change the saved Instruction Pointer. 
 * Case 2 : The Instruction Pointer indicates that the last running code before the IPI was in BPF text itself. 
	- Thus, we can directly change the saved pt_reg's IP to point to the termination copy of the original 
	  BPF program. 

In both the cases, we still want to modify the stack to avoid returning to stale BPF instructions and rather
return to the new termination copy we want to execute. 

Example : A sample stack state seen from bpf_die i.e. interrupt context : 
Top of stack --><a kernel return address>
		<another kernel address>
		<a BPF return address>
		<another BPF address>
		<pre-BPF kernel address>
		.
		.
Bottom       -->.

Because the BPF code is now at a new location (with modified instructions), we want all locations in the stack
which are pointing to old BPF return address, to now point to new BPF return address. 

The modified stack will look like : 	

Top of stack --><a kernel return address>
		<another kernel address>
		<new BPF return address> // Modified
		<new another BPF address>// Modified
		<pre-BPF kernel address>
		.
		.
Bottom       -->.

All non-BPF return address will be left untouched. 

When the interrupt handler returns and gives back execution to the helper function, or the kernel function
runnning before the interrupt came in, that function will continue.
After all the necessary returns, the execution will finally try to return to the BPF address and this time
will find the new BPF code's location and will jump there. 


## Demo 
 * Compile the kernel using the working_config.config (`cp working_config.config .config`)
	* To verify, check .config to have `CONFIG_HAVE_BPF_TERMINATION=y`
 * Goto the linux sample bpf directory : `cd sample/bpf/`
 * Install the bpf program : `./loops &`
 * In another shell, find the prog id of this BPF program as : `bpftool prog show`
 * Trigger the installed BPF program as : `./trigger_loops`
 * Again in the 2nd window, use the program ID obtained previously to run the termination command : `bpftool prog terminate <prog_ID>`
 * The BPF program should not make you wait for the 2nd `bpf_get_numa_node_id()` helper call because due to the binary patch, 
   the helper will get stubbed out leading to a quick termination. 

Refer the screenshot for expected results : ![Screenshot showing the termination results](https://github.com/rosalab/linux/blob/74e29a4ce457046d58c61a71d9647a97c4aa2732/termination_ss.png?raw=true)
