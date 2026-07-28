#pragma once

#include <keccack.h>

#include <stdint.h>

typedef struct random_generator {
  sha3_state _state;
} random_generator;

int rand_slow_get_enthropy(uint8_t _output[static restrict 16]);

int rand_init(random_generator *_gen);

void rand_poll(random_generator *restrict _gen,
               uint8_t _output[static restrict 16]);
