
TOP=..


include $(TOP)/make.cfg

SRCS=interrupts.c debug.c debugmon.c \
	ksleep.c \
	neon.c \
	mmu-simple.c \
	pmon.c \
	syscalls.c 
#ASM=exceptions.S  memset.S memcpy.S context.S
#ASM=exceptions.S  
OBJS=$(SRCS:.c=.o) $(ASM:.S=.o)

all:: libomap.a

libomap.a: $(OBJS)
	$(AR) cvq $@ $^

clean::
	-rm *.o
	-rm *.a

