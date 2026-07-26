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
	-I ../../kernel/include \
	-I $(EXTERNALS)/limine-protocol/include

CC := clang

srcfiles := $(patsubst src/%,%,$(shell find src -type f -name '*.c'))
objs := $(srcfiles:%.c=target/%.o)
depfiles := $(srcfiles:%.c=target/%.d)
outputs := target/prekernel.a target/link.ld

all: $(outputs)

-include $(depfiles)

clean:
	rm -f $(objs) $(depfiles)

clobber: clean
	rm -f $(output)

target/prekernel.a: $(objs)
	ar rcs $@ $(objs)

target/%.ld: src/%.ld
	cp $< $@

target/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
