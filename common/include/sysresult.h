#pragma once

#include <stddef.h>

typedef long sysresult_t;

#if __has_include(<bits/sysresult2_def.h>)
#include <bits/sysresult2_def.h>
#else
struct _sysresult_2 {
    sysresult_t _code;
    union {
        void* _value;
        unsigned char _uninit[sizeof(void*)];
    };
};

typedef struct _sysresult_2 sysresult2_t;

#define SYSRESULT2_CODE(val) ((val)._code)
#define SYSRESULT2_VALUE(val, T) ((T)((val)._value))

#define SYSRESULT2_ERROR(val) ((sysresult2_t)((struct _sysresult_2){._code = val}))
#define SYSRESULT2_OK(val) ((sysresult2_t)((struct _sysresult_2){._code = 0, ._value = (void*)val}))
#endif