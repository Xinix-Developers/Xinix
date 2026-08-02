#pragma once

#include <elf.h>

union GotEntry {
    void * got_address;
    uintptr_t got_value;
};