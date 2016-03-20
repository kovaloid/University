CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/misc
DEVPATH = /dev/ioctl

TARGET = chardev
obj-m  := $(TARGET).o

all: default ioctl

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

ioctl:	ioctl.h ioctl.c
	gcc ioctl.c -o ioctl

install:
	insmod $(TARGET).ko
	mknod -m0666 $(DEVPATH) c 200 0

uninstall:
	rmmod $(TARGET)
	rm -f $(DEVPATH)

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *.symvers *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions
	@rm -f *.ko
