
#include "sysresult.h"
#include <elf.h>
#include <got.h>

#include <dynld.h>

#include <hash.h>
#include <stdatomic.h>

struct DynLibraryEntry {
    ElfNative_Dyn *dylib_dynamic_section;
    size_t dylib_dynamic_size;
    ElfNative_Phdr *dylib_phdrs;
    size_t dylib_phdrs_size;
    ElfNative_Sym *dylib_symtab;
    union {
        struct dt_gnu_hash *dylib_gnu_hash;
        struct dt_hash *dylib_hash;
    };

    union GotEntry *dylib_pltgot;
    union {
        ElfNative_Rel *dylib_plt_rel;
        ElfNative_Rela *dylib_plt_rela;
    };
    enum Elf_DynTag dylib_hash_type;
    enum Elf_DynTag dylib_jmprel_type;
    const char *dylib_strtab;
    elf_init_t **dylib_init_array;
    size_t dylib_init_array_size;
    elf_fini_t **dylib_fini_array;
    size_t dylib_fini_array_size;
    const char *dylib_soname;
};

static constexpr size_t lock_bit = 0x80000000;

static constexpr size_t max_size = 8192;

struct DynldState {
    alignas(4096) struct DyldHeader {
        _Atomic(size_t) dynld_lock_and_offset;
        _Atomic(struct DynldState *) dynld_next;
        void *_pad[6];
    } header;

    struct DynLibraryEntry
        entries[(max_size / sizeof(struct DynLibraryEntry)) - 1];
};

struct DynldState dynld_state;

sysresult_t dynld_link(ElfNative_Dyn dyn[], ElfNative_Phdr *phdrs, size_t phnum,
                       const char *file_name) {
    ElfNative_Dyn *dynend = dyn;

    while (dynend->d_tag != DT_NULL) {

        dynend++;
    }
}
