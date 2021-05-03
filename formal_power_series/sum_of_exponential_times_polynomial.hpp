#pragma once
#include "lagrange_interpolation.hpp"
#include "sum_of_exponential_times_polynomial_limit.hpp"
#include <cassert>
#include <vector>

// CUT begin
// $d$ 次以下の多項式 $f(x)$ と定数 $r$ について，
// $\sum_{i=0}^{N-1} r^i f(i)$ の値を $[f(0), ..., f(d - 1), f(d)]$ の値から $O(d)$ で計算．
// Reference:
// - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial
// - https://min-25.hatenablog.com/entry/2015/04/24/031413
template <typename MODINT>
MODINT sum_of_exponential_times_polynomial(MODINT r, const std::vector<MODINT> &init, long long N) {
    if (N <= 0) return 0;
    if (init.size() == 1) return init[0] * (r == 1 ? MODINT(N) : (1 - r.pow(N)) / (1 - r));

    std::vector<MODINT> S(init.size() + 1);
    MODINT rp = 1;
    for (int i = 0; i < int(init.size()); i++) {
        S[i + 1] = S[i] + init[i] * rp;
        rp *= r;
    }
    if (N < (long long)S.size()) return S[N];

    if (r == 1) return interpolate_iota<MODINT>(S, N);

    const MODINT Sinf = sum_of_exponential_times_polynomial_limit<MODINT>(r, init);
    MODINT rinv = r.inv(), rinvp = 1;
    for (int i = 0; i < int(S.size()); i++) {
        S[i] = (S[i] - Sinf) * rinvp;
        rinvp *= rinv;
    }
    return interpolate_iota<MODINT>(S, N) * r.pow(N) + Sinf;
};
