#pragma once
#include <utility>

// \sum_{i=0}^{n-1} floor((ai + b) / m)
// 0 <= n < 2e32 (if Int is long long)
// 1 <= m < 2e32 (if Int is long long)
// 0 <= a, b < m
// Complexity: O(lg(m))
// (Int, Unsigned) = (long long, unsigned long long), (__int128_t, __uint128_t)
template <class Int, class Unsigned> Int floor_sum(Int n, Int m, Int a, Int b) {
    static_assert(-Int(1) < 0, "Int must be signed");
    static_assert(-Unsigned(1) > 0, "Unsigned must be unsigned");
    static_assert(sizeof(Unsigned) >= sizeof(Int), "Unsigned must be larger than Int");

    auto safe_mod = [](Int x, Int m) -> Int {
        x %= m;
        if (x < 0) x += m;
        return x;
    };
    auto floor_sum_unsigned = [](Unsigned n, Unsigned m, Unsigned a, Unsigned b) -> Unsigned {
        Unsigned ans = 0;
        while (true) {
            if (a >= m) {
                ans += n * (n - 1) / 2 * (a / m);
                a %= m;
            }
            if (b >= m) {
                ans += n * (b / m);
                b %= m;
            }

            Unsigned y_max = a * n + b;
            if (y_max < m) break;
            // y_max < m * (n + 1)
            // floor(y_max / m) <= n
            n = (Unsigned)(y_max / m);
            b = (Unsigned)(y_max % m);
            std::swap(m, a);
        }
        return ans;
    };

    Unsigned ans = 0;
    if (a < 0) {
        Unsigned a2 = safe_mod(a, m);
        ans -= Unsigned(1) * n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        Unsigned b2 = safe_mod(b, m);
        ans -= Unsigned(1) * n * ((b2 - b) / m);
        b = b2;
    }
    return ans + floor_sum_unsigned(n, m, a, b);
}
