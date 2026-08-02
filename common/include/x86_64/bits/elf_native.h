// #pragma once Intentionally omitted


#ifdef ELF_WANT_NATIVE_MACHINE
EM_NATIVE = EM_X86_64,
#else 
#error Cannot include this header directly. Include <elf.h> instead.
#endif