KERNELDIR ?= /lib/modules/$(shell uname -r)/build  # 内核源码路径
MODULES := helloWorld

all: $(MODULES)

# -C $(KERNELDIR) 切换到内核目录进行构建
# M=$(PWD) 告知内核构建系统，模块源码位于当前目录

# modules 内核构建参数，表示构建一个模块；clean 也是，删除所有构建生成的文件

$(MODULES):
	$(MAKE) -C $(KERNELDIR) M=$(CURDIR)/$@ modules

# 清理所有模块
clean:
	for dir in $(MODULES); do \
		$(MAKE) -C $(KERNELDIR) M=$(CURDIR)/$$dir clean; \
	done

.PHONY: all clean $(MODULES)