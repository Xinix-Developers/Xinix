.PHONY: all clean

BOOTLOADER := limine

all:
	@mkdir -p target
	make -C $(BOOTLOADER)
	cp $(BOOTLOADER)/target/prekernel.a $(BOOTLOADER)/target/link.ld target/

clean:
	make -C $(BOOTLOADER) clean
	rm -f target/*
