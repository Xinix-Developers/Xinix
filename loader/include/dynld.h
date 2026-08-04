#pragma once

#include <auxv.h>
#include <elf.h>
#include <got.h>

typedef void elf_init_t(char **, char **, auxv_t *);
typedef void elf_fini_t(void);
