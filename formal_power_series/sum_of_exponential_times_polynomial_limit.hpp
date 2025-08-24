#pragma once
#include <cassert>
#include <vector>

// CUT begin
// $d$ 次以下の多項式 $f(x)$ と定数 $r$ について，
// $\sum_{i=0}^\infty r^i f(i)$ の値を $[f(0), ..., f(d - 1), f(d)]$ の値から $O(d)$ で計算．
// Requirement: r != 1
// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
// Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
template <typename MODINT>
MODINT sum_of_exponential_times_polynomial_limit(MODINT r, std::vector<MODINT> init) {
    assert(r != 1);
    if (init.empty()) return 0;
    if (init.size() == 1) return init[0] / (1 - r);
    auto &bs = init;
    const int d = int(bs.size()) - 1;
    MODINT rp = 1;
    for (int i = 1; i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];
    MODINT ret = 0;
    rp = 1;
    for (int i = 0; i <= d; i++) {
        ret += bs[d - i] * MODINT::binom(d + 1, i) * rp;
        rp *= -r;
    }
    return ret / MODINT(1 - r).pow(d + 1);
};
