obj-m += read_tracing_array.o
array_reader-objs := read_tracing_array.o ../read_write_to_heaps.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
