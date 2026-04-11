#pragma once
#include <cassert>
#include <type_traits>

template <class Int> Int pow_mod(Int x, long long n, Int md) {
    using Long =
        std::conditional_t<std::is_same_v<Int, int>, long long,
                           std::conditional_t<std::is_same_v<Int, long long>, __int128, void>>;
    assert(n >= 0 and md > 0);
    if (md == 1) return 0;
    if (n == 0) return 1;

    x = (x % md + md) % md;
    Int ans = 1;
    while (n > 0) {
        if (n & 1) ans = (Long)ans * x % md;
        x = (Long)x * x % md;
        n >>= 1;
    }
    return ans;
}
