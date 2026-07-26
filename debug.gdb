target remote localhost:1234
add-symbol-file kernel/target/kernel
set disassemble-next-line on
set disassembly-flavor intel
break pkmain
continue
