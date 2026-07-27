#pragma once

#include <stdint.h>
#include <bits/feat_test.h>

#define X86_CPUID_DEFINE_FEATURE_ENUM(feat, idx, bit) _feature_## feat = ((idx << 6) | bit)

enum x86_feature_flags {
    X86_CPUID_DEFINE_FEATURE_ENUM(x87, 1, 0),
    X86_CPUID_DEFINE_FEATURE_ENUM(rdrand, 0, 30),
    X86_CPUID_DEFINE_FEATURE_ENUM(rdseed, 4, 18),
};

#undef X86_CPUID_DEFINE_FEATURE_ENUM

extern const uint32_t x86_feature_array[];

#define is_x86_feature_enabled(feature) (0) // TODO: Try to optimize this better, since it's important for optimized out feature checks

static inline bool _is_x86_feature_detected(enum x86_feature_flags _flag) _ATTRIBUTE_UNSEQ {
    return x86_feature_array[_flag >> 5] & (1 << (_flag & 31));
}


#define is_x86_feature_detected(feature) (is_x86_feature_enabled(feature) || (_is_x86_feature_detected(_feature_## feature)))