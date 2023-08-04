#pragma once
#include <cassert>

// lo <= (x xor v) < hi なる x の半開区間を列挙
// （lo 以上 hi 未満の各整数 と v の xor をとるとできる O(log(hi - lo)) 個の半開区間を全列挙）
// Verify: https://codeforces.com/contest/1849/problem/F
template <class Int, class F> void xor_of_interval(Int v, Int lo, Int hi, F f) {
    assert(0 <= lo);
    assert(0 <= v);

    for (int d = 0; lo < hi; lo /= 2, hi /= 2, v /= 2, ++d) {
        if (lo & 1) {
            f((lo ^ v) << d, ((lo ^ v) + 1) << d);
            ++lo;
        }
        if (hi & 1) {
            --hi;
            f((hi ^ v) << d, ((hi ^ v) + 1) << d);
        }
    }
}
