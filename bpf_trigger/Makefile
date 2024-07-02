# Kernel module filename (without the .c extension)
MODULE_NAME := vmalloc_trigger_module

# Kernel source tree path (assuming your module source is in linux/ directory)
#KERNEL_SRC := ../
KERNEL_SRC := /lib/modules/$(shell uname -r)/build

# Flags for the module compilation
ccflags-y := -I$(KERNEL_SRC)usr/include/ -I$(KERNEL_SRC)tools/lib/ -Wall -O0

# Define targets
obj-m += $(MODULE_NAME).o

# Default target
all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean

# Install the module
install:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules_install

# Uninstall the module
uninstall:
	sudo rmmod $(MODULE_NAME)

# Print information
info:
	@echo "KERNEL_SRC is $(KERNEL_SRC)"
	@echo "MODULE_NAME is $(MODULE_NAME)"
