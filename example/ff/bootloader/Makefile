ARCH		:=arm
CROSS_COMPILE	:=arm-linux-gnueabi-
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
AS		= $(CROSS_COMPILE)as
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
OBJ = lowlevel_init.o start.o cpu_init.o loader.o
loader.out:$(OBJ)
	arm-linux-gnueabi-ld -Tboot.lds -O $(OBJ) -o loader.out

loader.bin:loader.out
	arm-linux-gnueabi-objcopy -O binary -S loader.out loader.bin

sd:loader.bin
	../tools/write.sh loader.bin
hcsd:loader.bin
	../tools/write_hcsd.sh loader.bin
	
clean:
	rm *.o loader.out loader.bin
