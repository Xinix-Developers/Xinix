// Placeholder

#include <elf.h>
#include <stddef.h>
#include <stdint.h>

extern ElfNative_Dyn _DYNAMIC[];

extern void* _GLOBAL_OFFSET_TABLE_[];

void* get_image_base_addr(void) {
    return (void*) ((uintptr_t)(&_DYNAMIC) - (uintptr_t)_GLOBAL_OFFSET_TABLE_[0]);
}