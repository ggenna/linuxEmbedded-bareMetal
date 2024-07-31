
TOP=..

include $(TOP)/make_u-boot.cfg

#CC=arm-none-eabi-gcc -DCONFIG_ARM

ASM=start.S
OBJS=$(ASM:.S=.o)


#all: start.o var.o
#all: start.o 

all: $(OBJS)

#start.o: start.S

#var.o: var.c

clean:
	-rm *.o
