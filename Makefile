obj-m += hello.o
obj-m += chenillard.o
obj-m += gpio-leds.o
obj-m += timer.o

KERNEL_SOURCE = ../linux-socfpga
CFLAGS_MODULE = -fno-pic
EXTRA_CFLAGS += -fno-pic

all:
	make -C $(KERNEL_SOURCE) M=$(PWD) modules

clean:
	make -C $(KERNEL_SOURCE) M=$(PWD) clean

install:
	make -C $(KERNEL_SOURCE) M=$(PWD) modules install
