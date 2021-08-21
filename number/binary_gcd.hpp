#pragma once

// CUT begin
template <typename Int> Int binary_gcd(Int x_, Int y_) {
    unsigned long long x = x_ < 0 ? -x_ : x_, y = y_ < 0 ? -y_ : y_;
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
