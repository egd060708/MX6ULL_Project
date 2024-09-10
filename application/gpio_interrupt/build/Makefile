# 编译器(如果未赋值则赋值)
CROSS_COMPILE 	?= arm-linux-gnueabihf-
# 编译目标
TARGET		  	?= gpio_interrupt

# 编译（后定义的值不生效）
CC 				:= $(CROSS_COMPILE)gcc
# 链接
LD				:= $(CROSS_COMPILE)ld
# 转换可执行文件
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
# 反编
OBJDUMP 		:= $(CROSS_COMPILE)objdump

# 全部包含路径
INCDIRS 		:= ../include \
				   ../../../my_lib/clk \
				   ../../../my_lib/gpio \
				   ../../../my_lib/tools \
				   ../../../my_lib/board \
				   ../../../my_lib/interrupt \
				   ../../../my_lib/key

# 全部源文件路径			   			   
SRCDIRS			:= ../src \
				   ../../../my_lib/clk \
				   ../../../my_lib/gpio \
				   ../../../my_lib/tools \
				   ../../../my_lib/interrupt \
				   ../../../my_lib/key
				   
# 编译包含命令，把所有包含路径前加上-I			   
INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

# 源文件索引，对每一个目录逐个索引
sFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
# 获取无目录文件名称
sFILENDIR		:= $(notdir  $(sFILES))
SFILENDIR		:= $(notdir  $(SFILES))
CFILENDIR		:= $(notdir  $(CFILES))
# 把原文件名替换成依赖文件名
sOBJS			:= $(patsubst %, %, $(sFILENDIR:.s=.o))
SOBJS			:= $(patsubst %, %, $(SFILENDIR:.S=.o))
COBJS			:= $(patsubst %, %, $(CFILENDIR:.c=.o))
OBJS			:= $(sOBJS) $(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)

.PHONY: clean
	
$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

# 目标+依赖，后面的依赖全部替换
$(sOBJS) : %.o : %.s
	$(CC) -Wall -nostdlib -c -O2  $(INCLUDE) -o $@ $<

$(SOBJS) : %.o : %.S
	$(CC) -Wall -nostdlib -c -O2  $(INCLUDE) -o $@ $<

$(COBJS) : %.o : %.c
	$(CC) -Wall -nostdlib -c -O2  $(INCLUDE) -o $@ $<
	
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)

	
