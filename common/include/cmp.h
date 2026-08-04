#pragma once

#define CMP_H_DEF_MINMAX(ty, suffix)                                           \
    static inline ty min##suffix(ty _x, ty _y) {                               \
        if (_x < _y)                                                           \
            return _x;                                                         \
        else                                                                   \
            return _y;                                                         \
    }                                                                          \
    static inline ty max##suffix(ty _x, ty _y) {                               \
        if (_x > _y)                                                           \
            return _x;                                                         \
        else                                                                   \
            return _y;                                                         \
    }

CMP_H_DEF_MINMAX(int, )
CMP_H_DEF_MINMAX(unsigned, u)
CMP_H_DEF_MINMAX(long, l)
CMP_H_DEF_MINMAX(unsigned long, ul)
CMP_H_DEF_MINMAX(long long, ll)
CMP_H_DEF_MINMAX(unsigned long long, ull)

#ifdef __SIZEOF_INT128__
CMP_H_DEF_MINMAX(__int128, i128)
CMP_H_DEF_MINMAX(unsigned __int128, u128)
#endif

#define _cmph_min_max(_op, _x, _y)                                             \
    _Generic((_x),                                                             \
        char: (char)((_op)((_x), (_y))),                                       \
        signed char: (signed char)((_op)((_x), (_y))),                         \
        unsigned char: (unsigned char)((_op##u)((_x), (_y))),                  \
        short: (short)((_op)((_x), (_y))),                                     \
        unsigned short: (unsigned short)((_op##u)((_x), (_y))),                \
        int: ((_op)((_x), (_y))),                                              \
        unsigned: ((_op##u)((_x), (_y))),                                      \
        long: ((_op##l)((_x), (_y))),                                          \
        unsigned long: ((_op##ul)((_x), (_y))),                                \
        long long: ((_op##ll)((_x), (_y))),                                    \
        unsigned long long: ((_op##ull)((_x), (_y))),                          \
        signed _BitInt(8): (signed _BitInt(8))((_op)((_x), (_y))),             \
        unsigned _BitInt(8): (unsigned _BitInt(8))((_op##u)((_x), (_y))),      \
        _BitInt(16): (_BitInt(16))((_op)((_x), (_y))),                         \
        unsigned _BitInt(16): (unsigned _BitInt(16))((_op##u)((_x), (_y))),    \
        _BitInt(32): (_BitInt(32))((_op)((_x), (_y))),                         \
        unsigned _BitInt(32): (unsigned _BitInt(32))((_op##u)((_x), (_y))),    \
        _BitInt(64): (_BitInt(64))((_op##ll)((_x), (_y))),                     \
        unsigned _BitInt(64): (_BitInt(64))((_op##ull)((_x), (_y))))

#define min(_x, _y) _cmph_min_max(min, (_x), (_y))
#define max(_x, _y) _cmph_min_max(max, (_x), (_y))
