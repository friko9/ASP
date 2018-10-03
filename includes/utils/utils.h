#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

static constexpr int primes[] = { 1, 1, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381, 32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393, 67108859, 134217689, 268435399, 536870909, 1073741789, 2147483647 };

static constexpr
uint32_t floor_log2_1(uint32_t x)
{
    uint32_t r1 = x>>16 != 0;
    r1 = r1*16;
    x >>=r1;
    uint32_t r2 = x>>8 != 0;
    r2 = r2*8;
    x >>=r2;
    uint32_t r3 = x>>4 != 0;
    r3 = r3*4;
    x >>= r3;
    uint32_t r4 = x>>2 != 0;
    r4 = r4*2;
    x >>= r4;
    uint32_t r5 = x>>1 != 0;
    return r1+r2+r3+r4+r5;
}

static constexpr
uint32_t floor_log2_3(uint32_t x)
{
    uint32_t res = (x>>16 != 0)? x>>=16,16 : 0;
    res += (x>>8 != 0)? x>>=8,8 : 0;
    res += (x>>4 != 0)? x>>=4,4 : 0;
    res += (x>>2 != 0)? x>>=2,2 : 0;
    res += x >> 1;
    return res;
}

inline uint32_t floor_log2(uint32_t x)
{
    return floor_log2_3(x);
}

template<typename T>
struct TestPlug
{ };

#endif /*UTILS_H*/
