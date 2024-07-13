#pragma once

#include <cassert>
#include <utility>
#include <vector>

// Rational approximation based on Stern–Brocot tree
// Input: N > 0, num >= 0, den >= 0 (num > 0 or den > 0)
// return {{p, q}, {r, s}} where p/q <= num/den <= r/s. Strictly,
// - p/q = max(n / d | n / d <= num / den, 0 <= n <= N, 1 <= d <= N)
// - r/s = min(n / d | num / den <= n / d, 0 <= n <= N, 1 <= d <= N)
template <class Int>
std::pair<std::pair<Int, Int>, std::pair<Int, Int>> rational_approximation(Int N, Int num, Int den) {
    assert(N >= 1);
    assert(num >= 0);
    assert(den >= 0);
    assert(num > 0 or den > 0);

    if (num == Int(0)) return {{Int(0), Int(1)}, {Int(0), Int(1)}}; // 0
    if (den == Int(0)) return {{Int(1), Int(0)}, {Int(1), Int(0)}}; // inf

    // p/q <= num/den <= r/s
    Int p = 0, q = 1, r = 1, s = 0;

    bool is_left = false;
    while (true) {
        Int max_steps = num / den;

        if (is_left) {
            // r + steps * p <= N
            // s + steps * q <= N

            if (p > Int(0)) max_steps = std::min(max_steps, (N - r) / p);
            max_steps = std::min(max_steps, (N - s) / q);

            r += max_steps * p;
            s += max_steps * q;
        } else {
            // p + steps * r <= N
            // q + steps * s <= N

            max_steps = std::min(max_steps, (N - p) / r);
            if (s > Int(0)) max_steps = std::min(max_steps, (N - q) / s);

            p += max_steps * r;
            q += max_steps * s;
        }

        if (is_left and !max_steps) break;

        num -= max_steps * den;

        if (num == Int(0)) {
            if (is_left) {
                return {{r, s}, {r, s}};
            } else {
                return {{p, q}, {p, q}};
            }
        }

        std::swap(num, den);
        is_left = !is_left;
    }

    return {{p, q}, {r, s}};
}
