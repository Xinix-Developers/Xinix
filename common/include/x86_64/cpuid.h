#pragma once

#include <bits/feat_test.h>
#include <stdint.h>

/// Contains the feature cache in the following layout (with feature flags
/// related to unsupported state components masked out):
/// * [0]: cpuid[eax=1].ecx
/// * [1]: cpuid[eax=1].edx
/// * [2]: cpuid[eax=7,ecx=0].ecx
/// * [3]: cpuid[eax=7,ecx=0].edx
/// * [4]: cpuid[eax=7,ecx=0].ebx
/// * [5]: cpuid[eax=7,ecx=1].eax
/// * [6]: cpuid[eax=7,ecx=1].ecx
/// * [7]: cpuid[eax=7,ecx=1].edx
/// * [8]: cpuid[eax=7,ecx=1].ebx
/// * [9]: cpuid[eax=7,ecx=2].eax
/// * [10]: cpuid[eax=7,ecx=2].ecx
/// * [11]: cpuid[eax=7,ecx=2].edx
/// * [12]: cpuid[eax=7,ecx=2].ebx
/// * [13]: cpuid[eax=0x80000001].ecx (only non-redundant features)
/// * [14]: cpuid[eax=0x80000001].edx
/// * [15]:  reserved
/// * [16]: cpuid[eax=0x24,ecx=0].ebx
/// * [17]: cpuid[eax=0x24,ecx=1].ecx
/// * [18]..[31]: reserved
/// * [32]: cpuid[eax=0x0D,ecx=0].eax
/// * [33]: cpuid[eax=0x0D,ecx=0].edx
/// * [34]: cpuid[eax=0x0D,ecx=1].eax
/// * [35]: reserved
/// * [36]: cpuid[eax=0x0D,ecx=1].ecx
/// * [37]: cpuid[eax=0x0D,ecx=1].edx
extern const uint32_t x86_feature_array[];

#define X86_CPUID_DEFINE_FEATURE_ENUM(feat, idx, bit)                          \
    _feature_##feat = ((idx << 6) | bit)

enum x86_feature_flags {
    X86_CPUID_DEFINE_FEATURE_ENUM(x87, 1, 0),
    X86_CPUID_DEFINE_FEATURE_ENUM(rdrand, 0, 30),
    X86_CPUID_DEFINE_FEATURE_ENUM(rdseed, 4, 18),
};

#undef X86_CPUID_DEFINE_FEATURE_ENUM

#define is_x86_feature_enabled(feature)                                        \
    (0) // TODO: Try to optimize this better, since it's important for optimized
        // out feature checks

static inline bool
_is_x86_feature_detected(enum x86_feature_flags _flag) _ATTRIBUTE_UNSEQ {
    return x86_feature_array[_flag >> 5] & (1 << (_flag & 31));
}

#define is_x86_feature_detected(feature)                                       \
    (is_x86_feature_enabled(feature) ||                                        \
     (_is_x86_feature_detected(_feature_##feature)))
