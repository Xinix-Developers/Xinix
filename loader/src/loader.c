// Placeholder

#include <elf.h>
#include <stddef.h>
#include <stdint.h>

#include <sysresult.h>

extern ElfNative_Dyn _DYNAMIC[];

union GotEntry {
  void *address;
  uintptr_t value;
};

extern union GotEntry _GLOBAL_OFFSET_TABLE_[];

void *image_base_addr(void) {
  return (void *)((uintptr_t)(&_DYNAMIC) - _GLOBAL_OFFSET_TABLE_[0].value);
}

sysresult2_t loader_map_elf(Elf64_Ehdr* e_hdr) {
    SYSRESULT_TRY_SYSRESULT2(elf_validate_ident_native(&e_hdr->e_ident, ELFOSABINONE));

    return SYSRESULT2_OK(nullptr);
}
