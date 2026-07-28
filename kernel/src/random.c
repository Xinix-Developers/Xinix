
#include <keccack.h>
#include <random.h>

int rand_init(random_generator* restrict _gen) {
    uint8_t buf[16];
    int res = rand_slow_get_entropy(buf);
    if(res < 0)
        return res;

  sha3_absorb(&_gen->_state, buf, 128);
  return 0;
}

void rand_poll(random_generator *restrict _gen,
               uint8_t _output[static restrict 16]) {
  sha3_squeeze(&_gen->_state, _output, 128);
}
