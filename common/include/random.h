#pragma once

#include <keccack.h>

#include <stdint.h>

typedef struct random_generator {
    sha3_state _state;
} random_generator;

/// Obtains 16 bytes of randomness that can be used for seeding a `random_generator`.
/// Quality for direct use as random bytes is not guaranteed, the result must be processed by a cryptographic hash function to produce uniform random bits of sufficient quality
/// Returns a negative error code on error or 0 on success. On error, `_output` is overwritten with 0 bytes.
///
/// ## Preconditions
/// The behaviour is undefined if `[_entropy, _entropy+16)` is not a valid range for writes
int rand_slow_get_entropy(uint8_t _output[static restrict 16]);

/// Inhitializes `gen` by calling `rand_slow_get_entropy`. Returns the error on error, and returns `0` on success
int rand_init(random_generator *_gen);

/// Injests 16 bytes of random data into `gen`
/// 
/// ## Preconditions
/// The behaviour is undefined if `_gen` and `_entropy` overlap, orif `[_entropy, _entropy+16)` is not a valid range for reads
void rand_injest(random_generator * restrict _gen, const uint8_t _entropy[static restrict 16]);

/// Polls _gen` into _output`, and fills `_output` with 16 bytes of uniform randomness.
///
/// ## Preconditions
/// The behaviour is undefined if `_gen` and `_entropy` overlap, or if `[_entropy, _entropy+16)` is not a valid range for writes
void rand_poll(random_generator *restrict _gen,
               uint8_t _output[static restrict 16]);
