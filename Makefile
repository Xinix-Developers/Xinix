.PHONY: all clean iso kernel limine

EXTERNALS := $(shell realpath ./externals)
IMAGE_NAME := xinix-dev

ARCH := x86_64

limine_bios_files := limine-bios.sys limine-bios-cd.bin limine-uefi-cd.bin
limine_efi_boot_files := BOOTX64.EFI BOOTIA32.EFI

all: iso

clean:
	rm -rf target/iso-root
	make -C loader clean
	make -C prekernel clean
	make -C externals/flanterm-build clean
	make -C kernel clean

iso: kernel limine limine.conf
	rm -rf target/iso-root
	mkdir -p target/iso-root/boot/limine
	cp -v kernel/target/kernel target/iso-root/boot/
	cp -v limine.conf $(limine_bios_files:%=externals/limine-binary/%) target/iso-root/boot/limine/
	mkdir -p target/iso-root/EFI/BOOT
	cp -v $(limine_efi_boot_files:%=externals/limine-binary/%) target/iso-root/EFI/BOOT
	xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
		-apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		target/iso-root -o target/$(IMAGE_NAME).iso
	externals/limine-binary/limine bios-install target/$(IMAGE_NAME).iso
	rm -rf target/iso-root

kernel:
	make -C loader EXTERNALS=$(EXTERNALS) ARCH=$(ARCH)
	make -C prekernel EXTERNALS=$(EXTERNALS) ARCH=$(ARCH)
	make -C externals/flanterm-build
	make -C kernel EXTERNALS=$(EXTERNALS) LDSCRIPT=$(shell realpath ./prekernel/target/link.ld) PREKERNEL=$(shell realpath ./prekernel/target/prekernel.a) ARCH=$(ARCH)

limine:
	make -C externals/limine-binary
