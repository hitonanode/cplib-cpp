#pragma once
#include <algorithm>
#include <type_traits>

// Solve x^2 == a (MOD p) for prime p
// If no solution exists, return -1
template <class Int> Int sqrt_mod(Int a, Int p) {
    using Long =
        std::conditional_t<std::is_same_v<Int, int>, long long,
                           std::conditional_t<std::is_same_v<Int, long long>, __int128, void>>;

    auto pow = [&](Int x, long long n) {
        Int ans = 1, tmp = x;
        while (n) {
            if (n & 1) ans = (Long)ans * tmp % p;
            tmp = (Long)tmp * tmp % p, n /= 2;
        }
        return ans;
    };
    if (a == 0) return 0;

    a = (a % p + p) % p;
    if (p == 2) return a;
    if (pow(a, (p - 1) / 2) != 1) return -1;

    int b = 1;
    while (pow(b, (p - 1) / 2) == 1) ++b;

    int e = 0;
    Int m = p - 1;
    while (m % 2 == 0) m /= 2, ++e;

    Int x = pow(a, (m - 1) / 2), y = (Long)x * x % p * a % p;
    x = (Long)x * a % p;
    Int z = pow(b, m);
    while (y != 1) {
        int j = 0;
        Int t = y;
        while (t != 1) t = (Long)t * t % p, ++j;
        z = pow(z, 1LL << (e - j - 1));
        x = (Long)x * z % p;
        z = (Long)z * z % p;
        y = (Long)y * z % p;
        e = j;
    }
    return std::min(x, p - x);
}
