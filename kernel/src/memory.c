// Copied from the Limine sample:
// https://github.com/Limine-Bootloader/limine-c-template-x86-64/blob/trunk/kernel/src/memory.c
// And then malloc was added

#include <memory.h>
#include <stddef.h>
#include <stdint.h>

// GCC and Clang reserve the right to generate calls to the following
// 4 functions even if they are not directly called.
// They must be implemented as the C specification mandates.
// DO NOT remove or rename these functions, or stuff will eventually break!

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
  uint8_t *restrict pdest = dest;
  const uint8_t *restrict psrc = src;

  for (size_t i = 0; i < n; i++) {
    pdest[i] = psrc[i];
  }

  return dest;
}

void *memset(void *s, int c, size_t n) {
  uint8_t *p = s;

  for (size_t i = 0; i < n; i++) {
    p[i] = (uint8_t)c;
  }

  return s;
}

void *memmove(void *dest, const void *src, size_t n) {
  uint8_t *pdest = dest;
  const uint8_t *psrc = src;

  if ((uintptr_t)src > (uintptr_t)dest) {
    for (size_t i = 0; i < n; i++) {
      pdest[i] = psrc[i];
    }
  } else if ((uintptr_t)src < (uintptr_t)dest) {
    for (size_t i = n; i > 0; i--) {
      pdest[i - 1] = psrc[i - 1];
    }
  }

  return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const uint8_t *p1 = s1;
  const uint8_t *p2 = s2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] < p2[i] ? -1 : 1;
    }
  }

  return 0;
}

// end copied code

#define BUMP_HEAP_SIZE 8192000

char bump_heap[BUMP_HEAP_SIZE] = {};
size_t bump_heap_ptr = 0;

void *malloc(size_t size) {
  if (bump_heap_ptr + size >= BUMP_HEAP_SIZE) {
    return nullptr;
  } else {
    void *result = &bump_heap[bump_heap_ptr];
    size_t align = sizeof(max_align_t);
    bump_heap_ptr += (size + align - 1) / align * align;
    return result;
  }
}

void free(void *_ptr) {}
