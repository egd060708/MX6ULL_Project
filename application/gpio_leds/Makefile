
buildDir = ./build

led.bin:led.s
	arm-linux-gnueabihf-gcc -g -c led.s -o $(buildDir)/led.o
	arm-linux-gnueabihf-ld -Ttext 0X87800000 $(buildDir)/led.o -o $(buildDir)/led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g $(buildDir)/led.elf $(buildDir)/led.bin
	arm-linux-gnueabihf-objdump -D led.elf > $(buildDir)/led.dis
clean:
	rm -rf $(buildDir)/*.o $(buildDir)/led.bin $(buildDir)/led.elf $(buildDir)/led.dis
	
	
