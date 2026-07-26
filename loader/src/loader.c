// Placeholder

#include <elf.h>
#include <stddef.h>
#include <stdint.h>

extern ElfNative_Dyn _DYNAMIC[];

union GotEntry {
    void* address;
    uintptr_t value;
};

extern union GotEntry _GLOBAL_OFFSET_TABLE_[];

void* get_image_base_addr(void) {
    return (void*) ((uintptr_t)(&_DYNAMIC) - _GLOBAL_OFFSET_TABLE_[0].value);
}