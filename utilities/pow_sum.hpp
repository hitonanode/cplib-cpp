#pragma once
#include <algorithm>
#include <utility>

// CUT begin
// {x^n, x^0 + ... + x^(n - 1)} for n >= 1
// Verify: ABC212H
template <typename T, typename Int> std::pair<T, T> pow_sum(T x, Int n) {
    T sum = 1, p = x; // ans = x^0 + ... + x^(len - 1), p = x^len
    for (int d = std::__lg(n) - 1; d >= 0; d--) {
        sum = sum * (p + 1);
        p *= p;
        if ((n >> d) & 1) {
            sum += p;
            p *= x;
        }
    }
    return {p, sum};
}
