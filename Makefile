.PHONY: all clean iso kernel limine

EXTERNALS := $(shell realpath ./externals)
IMAGE_NAME := xinix-dev

all: iso

clean:
	rm -rf target/iso-root
	make -C prekernel clean
	make -C externals/flanterm-build clean
	make -C kernel clean

iso: kernel limine limine.conf
	rm -rf target/iso-root
	mkdir -p target/iso-root/boot/limine
	cp -v kernel/target/kernel target/iso-root/boot/
	cp -v limine.conf externals/limine-binary/{limine-bios.sys,limine-bios-cd.bin,limine-uefi-cd.bin} target/iso-root/boot/limine/
	mkdir -p target/iso-root/EFI/BOOT
	cp -v externals/limine-binary/{BOOTX64.EFI,BOOTIA32.EFI} target/iso-root/EFI/BOOT
	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		target/iso-root -o target/$(IMAGE_NAME).iso
	externals/limine-binary/limine bios-install target/$(IMAGE_NAME).iso
	rm -rf target/iso-root

kernel:
	make -C prekernel EXTERNALS=$(EXTERNALS)
	make -C externals/flanterm-build
	make -C kernel EXTERNALS=$(EXTERNALS) LDSCRIPT=$(shell realpath ./prekernel/target/link.ld) PREKERNEL=$(shell realpath ./prekernel/target/prekernel.a)

limine:
	make -C externals/limine-binary
