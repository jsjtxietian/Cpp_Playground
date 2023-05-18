#pragma once

#include <stdint.h>
#include <bit>
#include <functional>

inline size_t bit_floor(size_t i)
{
    constexpr int num_bits = sizeof(i) * 8;
    return size_t(1) << (num_bits - std::countl_zero(i) - 1);
}
inline size_t bit_ceil(size_t i)
{
    constexpr int num_bits = sizeof(i) * 8;
    return size_t(1) << (num_bits - std::countl_zero(i - 1));
}

template<typename It, typename T, typename Cmp>
It branchless_lower_bound(It begin, It end, const T & value, Cmp && compare)
{
    std::size_t length = end - begin;
    if (length == 0)
        return end;
    std::size_t step = bit_floor(length);
    if (step != length && compare(begin[step], value))
    {
        length -= step + 1;
        if (length == 0)
            return end;
        step = bit_ceil(length);
        begin = end - step;
    }
    for (step /= 2; step != 0; step /= 2)
    {
        if (compare(begin[step], value))
            begin += step;
    }
    return begin + compare(*begin, value);
}

template<typename It, typename T>
It branchless_lower_bound(It begin, It end, const T & value)
{
    return branchless_lower_bound(begin, end, value, std::less<>{});
}

// https://orlp.net/blog/bitwise-binary-search/
template<typename It, typename T, typename Cmp>
It lower_bound(It begin, It end, const T& value, Cmp comp) {
    size_t n = end - begin;
    if (n == 0) return begin;

    size_t two_k = size_t(1) << (std::bit_width(n) - 1);
    size_t b = comp(begin[n / 2], value) ? n - two_k : -1;
    for (size_t bit = two_k >> 1; bit != 0; bit >>= 1) {
        if (comp(begin[b + bit], value)) b += bit;
    }
    return begin + (b + 1);
}