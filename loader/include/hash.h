#pragma once

#include <stddef.h>
#include <stdint.h>

static inline uint32_t gnu_hash(const uint8_t *name) {
  uint32_t h = 5381;

  for (; *name; name++) {
    h = (h << 5) + h + *name;
  }

  return h;
}

static inline uint32_t svr4_hash(const uint8_t *name) {
  uint32_t h = 0, g;
  for (; *name; name++) {
    h = (h << 4) + *name;
    if ((g = (h & 0xf0000000))) {
      h ^= g >> 24;
    }
    h &= ~g;
  }
  return h;
}

struct dt_hash {
  uint32_t nbucket;
  uint32_t nchain;
  uint32_t tail[];
};

struct dt_gnu_hash {
  uint32_t nbuckets;
  uint32_t symoffset;
  uint32_t bloom_size;
  uint32_t bloom_shift;
  union {
    size_t bloom_entry;
    uint32_t bucket_or_chain[sizeof(size_t) / sizeof(uint32_t)];
  } tail[];
};

#if INTPTR_WIDTH == 64
#define HASH_GNU_IMPL_MASK 1
#define HASH_GNU_IMPL_SHIFT 1
#elif INTPTR_WIDTH == 32
#define HASH_GNU_IMPL_MASK 0
#define HASH_GNU_IMPL_SHIFT 0
#endif

static inline uint32_t gnu_hash_get_bucket(const struct dt_gnu_hash *hash,
                                           uint32_t bucket) {
  auto *arr = &hash->tail[hash->bloom_size];
  return arr[bucket >> HASH_GNU_IMPL_SHIFT]
      .bucket_or_chain[bucket & HASH_GNU_IMPL_MASK];
}

static inline uint32_t gnu_hash_get_chain(const struct dt_gnu_hash *hash,
                                          uint32_t chain) {
  return gnu_hash_get_bucket(hash, chain + hash->nbuckets);
}
