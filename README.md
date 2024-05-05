# BPF transactions
=========================================
Support a tx_begin() and tx_end() helper to mark a code section as a transaction in a BPF program. 
Currently, transaction is modelled towards BPF map write operations i.e. any writes done in the current
tx block needs to be reverted if the program failed for some reason. The list of reasons could be : 
deadlock related failure of a helper function, async termination request or a synchronous exception
raised by a programmer upon getting an unexpected return value from a function call. 

Typical scenario : 

```C
BPF_PROG(sample_program, "fentry/map_push_stack"){
	// some operations

	/* tx block 1 */
	tx_begin();
	map_read(map1, key);
	map_write(map1, key, value); // w1
	map_write(map2, key- value2); // w2
	tx_end();

	// other operations

	/* tx block 2 */
	tx_begin();
	// some other map R/W
	tx_end();

}
```
If execution is within tx block 1, say performing W#2, a failure due to a deadlock, or async termination request
should lead to rollback to the older state prior to W#1. 
In case of sync failure, such as for exception handling, the scenario will be : 

```C
BPF_PROG(sample_program, "fentry/map_push_stack"){
	// some operations

	/* tx block 1 */
	tx_begin();
	map_write(map1, key, value); // w1
	map_write(map2, key- value2); // w2
	if (failed)
		bpf_throw(); 
	tx_end();

}
```
For above example, bpf_throw needs to be configured to first identify a tx_block, and then perform rollbacks.
This differs from the default case, where only locks and refcnts are released by the bpf_throw functionality.  


## Reference 

 * In [1](https://www.kernel.org/doc/html/v5.9/powerpc/transactional_memory.html), is a kernel doc on transactional
   memory support in POWERPC arch essentially using _tbegin_ and _tend_ CPU insns. 

## TODOs : 
 * How transaction is efficiently down in MySQL and other dbs? 
 * How is XDP rolling back an skb modification? 

