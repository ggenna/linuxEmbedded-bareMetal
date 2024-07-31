
TOP=..


include $(TOP)/make.cfg

SRCS= pwm_hw.c\
	pwm_drv.c \
	spi_hw.c \
	spi_drv.c    
		
#ASM=exceptions.S 

#OBJS=$(SRCS:.c=.o) $(ASM:.S=.o)
OBJS=$(SRCS:.c=.o) 

all:: libdriver.a

libdriver.a: $(OBJS)
	$(AR) cvq $@ $^

clean::
	-rm *.o
	-rm *.a

