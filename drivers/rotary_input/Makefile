obj-m += hello.o

KDIR := /home/sp/Documents/projects/cyberdeck/buildroot_build_dir/build/linux-custom
ARCH := arm64
CROSS_COMPILE := /home/sp/Documents/projects/cyberdeck/buildroot_build_dir/host/bin/aarch64-cybit-linux-uclibc-

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

#obj-m += hello.o

#all:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

#clean:
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
