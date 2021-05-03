#pragma once
#include <vector>

// CUT begin
// $d$ 次以下の多項式 $f(x)$ と定数 $r$ について，
// $\sum_{i=0}^\infty r^i f(i)$ の値を $[f(0), ..., f(d - 1), f(d)]$ の値から $O(d)$ で計算．
// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
template <typename MODINT> MODINT sum_of_exponential_times_polynomial_limit(MODINT r, std::vector<MODINT> init) {
    auto &bs = init;
    if (bs.empty()) return 0;
    const int d = int(bs.size()) - 1;
    if (d == 0) { return 1 / (1 - r); }
    MODINT rp = 1;
    for (int i = 1; i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];
    MODINT ret = 0;
    rp = 1;
    for (int i = 0; i <= d; i++) {
        ret += bs[d - i] * MODINT(d + 1).nCr(i) * rp;
        rp *= -r;
    }
    return ret / MODINT(1 - r).pow(d + 1);
};
