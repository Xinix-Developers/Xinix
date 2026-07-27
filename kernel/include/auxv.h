#pragma once

#include <bits/feat_test.h>
#include <stddef.h>

typedef struct {
  unsigned long a_type;
  union auxval_t{
    long a_val;
    void *a_ptr;
    void (*a_fnc)();
  } a_un;
} auxv_t;

// a_type values
#define AT_NULL 0               // end of list
#define AT_IGNORE 1             // no-op entry

#define AT_PAGESZ 6
#define AT_BASE 7
#define AT_PLATFORM 8

#define AT_RANDOM 26

// Xinix specific region begins at 64

#define AT_XINIX_MAX_USER 95
// Xinix Kernel region begins at 96
#define AT_KXINIX_FRAMEBUFFER 96 // framebuffer structure


#define AT_XINIX_MAX_KERNEL 127 

union auxval_t getauxval(unsigned long a_type) _ATTRIBUTE_UNSEQ;