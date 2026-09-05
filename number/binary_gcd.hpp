#pragma once
#include <type_traits>

// CUT begin
template <typename Int> Int binary_gcd(Int x_, Int y_) {
    using Uint = std::make_unsigned_t<Int>;
    auto magnitude = [](Int v) -> Uint {
        Uint u = static_cast<Uint>(v);
        return v < 0 ? Uint(0) - u : u;
    };
    unsigned long long x = magnitude(x_), y = magnitude(y_);
    if (!x or !y) return x + y;
    int n = __builtin_ctzll(x), m = __builtin_ctzll(y);
    x >>= n, y >>= m;
    while (x != y) {
        if (x > y) {
            x = (x - y) >> __builtin_ctzll(x - y);
        } else {
            y = (y - x) >> __builtin_ctzll(y - x);
        }
    }
    return x << (n > m ? m : n);
}
