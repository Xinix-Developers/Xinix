build:
    make

clean:
    make clean

run: build
    qemu-system-x86_64 \
        -M q35 \
        -cdrom target/xinix-dev.iso \
        -boot d \
        -m 2G

debug: build
    qemu-system-x86_64 \
        -M q35 \
        -cdrom target/xinix-dev.iso \
        -boot d \
        -m 2G \
        -s -S &
    gdb -x debug.gdb
