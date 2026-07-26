#pragma once

typedef struct {
  int a_type;
  union {
    long a_val;
    void *a_ptr;
    void (*a_fnc)();
  } a_un;
} auxv_t;

// a_type values
#define AT_NULL 0               // end of list
#define AT_IGNORE 1             // no-op entry

// Xinix specific region begins at 64

#define AT_XINIX_MAX_USER 95
// Xinix Kernel region begins at 96
#define AT_KXINIX_FRAMEBUFFER 96 // framebuffer structure


#define AT_XINIX_MAX_KERNEL 127 
