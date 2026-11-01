obj-m += rotary_cybit.o
rotary_cybit-y := hello.o

KDIR := /home/sp/Documents/projects/cyberdeck/buildroot_build_dir/build/linux-custom
ARCH := arm64
CROSS_COMPILE := /home/sp/Documents/projects/cyberdeck/buildroot_build_dir/host/bin/aarch64-cybit-linux-uclibc-
DRIVER_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
ROOTFS_OVERLAY_DIR := $(DRIVER_DIR)/../../board/raspberrypizero2w-64/rootfs-overlay
KERNEL_VERSION := $(shell $(MAKE) -s -C $(KDIR) kernelrelease)
MODULE_DEST := $(ROOTFS_OVERLAY_DIR)/lib/modules/$(KERNEL_VERSION)/extra/rotary_cybit.ko

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	mkdir -p $(dir $(MODULE_DEST))
	rm -f $(MODULE_DEST)
	cp $(PWD)/rotary_cybit.ko $(MODULE_DEST)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

#obj-m += hello.o

#all:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

#clean:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
