GCCPARAMS = -m32  -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o

%.o: %.c
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

vjkernel.iso: vjkernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp vjkernel.bin iso/boot/vjkernel.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "VJs OS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/vjkernel.bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=vjkernel.iso iso
	rm -rf iso

run: vjkernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm 'VJs Operating System' &


vjkernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: vjkernel.bin
	sudo cp $< /boot/vjkernel.bin

