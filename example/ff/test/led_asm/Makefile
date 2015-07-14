led.bin:led.o
	arm-linux-gnueabi-objcopy -O binary -S led.o led.bin
led.o:led.asm
	arm-linux-gnueabi-as led.asm -o led.o
clean:
	rm led.o led.bin
