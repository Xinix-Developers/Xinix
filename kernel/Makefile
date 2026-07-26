.SUFFIXES:

.PHONY: all clean clobber

override CFLAGS += \
	-g \
	-MMD \
	-ffreestanding \
	-Wall \
	-std=c23 \
	--target=x86_64-unknown-none-elf

override CPPFLAGS += \
	-I include \
	-I $(EXTERNALS)/Flanterm/src

override LDFLAGS += \
	-m elf_x86_64 \
	-nostdlib \
	-static \
	-z max-page-size=0x1000 \
	--gc-sections \
	-T $(LDSCRIPT)

override LIBS = $(PREKERNEL) $(EXTERNALS)/flanterm-build/target/flanterm.a

CC := clang

srcfiles := $(patsubst src/%,%,$(shell find src -type f -name '*.c'))
objs := $(srcfiles:%.c=target/%.o)
depfiles := $(srcfiles:%.c=target/%.d)
output := target/kernel

all: $(output)

-include $(depfiles)

clean:
	rm -f $(objs) $(depfiles)

clobber: clean
	rm -f $(output)

target/kernel: $(objs)
	$(LD) $(LDFLAGS) -o $@ $(objs) $(LIBS)

target/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
