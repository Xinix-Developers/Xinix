#pragma once

#include <stdint.h>

#define launder_pointer(_x) ((typeof(*(_x)) *)(uintptr_t)(_x))
