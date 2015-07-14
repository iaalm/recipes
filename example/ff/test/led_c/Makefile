CC=arm-linux-gnueabi-gcc
CFLAGS=-I../../include
led.bin:led.o
	arm-linux-gnueabi-objcopy -O binary -S led.o led.bin
clean:
	rm led.o led.bin
sd:led.bin
	../../tools/write.sh led.bin
hcsd:led.bin
	../../tools/write_hcsd.sh led.bin
	
