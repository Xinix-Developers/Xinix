#include "random.h"
#include "stdbit.h"

#include <cpuid.h>
#include <string.h>

int rand_slow_get_enthropy(uint8_t  _output[static restrict 16]) {
    uint64_t a[2];
    if (is_x86_feature_detected(rdseed)) {
        __asm__ volatile("2: rdseed %0\n\tjnc 2b\n\t2: rdseed %1\n\tjnc 2b": "=r"(a[0]), "=r"(a[1]));
    } else if(is_x86_feature_detected(rdrand)) {
        __asm__ volatile("2: rdrand %0\n\tjnc 2b\n\t2: rdrand %1\n\tjnc 2b": "=r"(a[0]), "=r"(a[1]));
    } else {
        for(size_t i = 0; i < 64; i+=2) {
            uint32_t r;
            __asm__ volatile("rdtsc\n\tsfence": "=a"(r) :: "edx");
            a[0] = stdc_rotate_right(a[0], 2) | (r & 3);
        }

        a[1] = ((((uint64_t)rand_slow_get_enthropy)<<20) & 0xFFFF'FFFF'0000'0000);
        for(size_t i = 0; i < 32; i+=2) {
            uint32_t r;
            __asm__ volatile("rdtsc\n\tsfence": "=a"(r) :: "edx");
            a[1] = stdc_rotate_right(a[1], 2) | (r & 3);
        }
    }

    memcpy(_output, a, 16);

    return 0;
}