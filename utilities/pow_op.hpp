#pragma once
#include <cassert>

// Calculate x^n
template <class S, class F> S pow_op(S x, long long n, F op) {
    assert(n > 0);
    S ans = x;
    --n;
    while (n) {
        if (n & 1) ans = op(ans, x);
        x = op(x, x);
        n >>= 1;
    }
    return ans;
}
