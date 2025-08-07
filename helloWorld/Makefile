obj-m += helloworld.o		# 生成模块helloworld.ko，必须和helloworld.c文件名字严格匹配
KERNELDIR ?= /lib/modules/$(shell uname -r)/build  # 内核源码路径
PWD := $(shell pwd)          # 当前目录

# -C $(KERNELDIR) 切换到内核目录进行构建
# M=$(PWD) 告知内核构建系统，模块源码位于当前目录

# modules 内核构建参数，表示构建一个模块；clean 也是，删除所有构建生成的文件

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean