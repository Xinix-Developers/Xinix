#pragma once

#include <stddef.h>
#include <stdint.h>

enum valloc_flags : uint32_t {
    PROT_NONE = 0,
    PROT_READ = 0x01,
    PROT_WRITE = 0x02,
    PROT_EXEC = 0x04,

    FLAG_UNINIT_MEM = 0x20,
};

void *valloc(size_t _page_count, enum valloc_flags _flags);

void *vprotect(void *_base, size_t _page_count, enum valloc_flags _prot_flags);
