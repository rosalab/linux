# Makefile for read_tracing_array kernel module

obj-m += read_tracing_array.o
obj-m += ../trace_timestamp/timestamp_to_array.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
