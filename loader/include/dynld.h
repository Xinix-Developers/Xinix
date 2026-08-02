#pragma once

#include <elf.h>
#include <got.h>
#include <auxv.h>

typedef void elf_init_t(char**, char**, auxv_t*);
typedef void elf_fini_t(void);