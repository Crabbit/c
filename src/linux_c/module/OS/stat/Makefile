# Makefile2.6

obj-m := my_stat.o 
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/kernels/2.6.32-279.el6.x86_64

all: 
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules 
clean: 
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean 
