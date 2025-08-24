#pragma once
#include <cassert>
#include <cmath>
#include <functional>
#include <unordered_set>

// Solve min_n f^n s = t (0 <= n <= max_search)
// baby = f, giant = f^giant_stride
// If solution is not found, return -1.
// https://maspypy.com/%e3%83%a2%e3%83%8e%e3%82%a4%e3%83%89%e4%bd%9c%e7%94%a8%e3%81%ab%e9%96%a2%e3%81%99%e3%82%8b%e9%9b%a2%e6%95%a3%e5%af%be%e6%95%b0%e5%95%8f%e9%a1%8c
template <class S, class F, class Container>
long long
DiscreteLogarithm(const F &baby, const F &giant, const S &s, const S &t,
                  const std::function<S(F, S)> &mapping, long long max_search, int giant_stride) {
    if (s == t) return 0;
    if (max_search <= 0) return -1;

    Container ys;
    // ys.reserve(giant_stride); // if unordered_set
    {
        auto yt = t;
        for (int i = 0; i < giant_stride; ++i) {
            ys.emplace(yt);
            yt = mapping(baby, yt);
        }
    }

    int num_fails = 0;
    S cur = s;

    for (long long k = 1;; ++k) {
        if (const S nxt = mapping(giant, cur); ys.count(nxt)) {
            for (int i = 1; i <= giant_stride; ++i) {
                cur = mapping(baby, cur);
                if (cur == t) {
                    long long ret = (k - 1) * giant_stride + i;
                    return (ret <= max_search) ? ret : -1;
                }
            }
            ++num_fails;
        } else {
            cur = nxt;
        }

        if (num_fails >= 2 or k * giant_stride > max_search) return -1;
    }
}

// Solve min_n f^n s = t (0 <= n <= max_search) f \in F, s \in S, t \in S
// mapping: (F, S) -> S
// composition: (F, F) -> F
template <class S, class F, class Container>
long long
DiscreteLogarithm(const F &f, const S &s, const S &t, const std::function<S(F, S)> &mapping,
                  const std::function<F(F, F)> &composition, long long max_search) {
    const int giant_stride = ceil(sqrtl(max_search));
    F giant = f, tmp = f;
    for (int n = giant_stride - 1; n; n >>= 1) {
        if (n & 1) giant = composition(giant, tmp);
        tmp = composition(tmp, tmp);
    }
    return DiscreteLogarithm<S, F, Container>(f, giant, s, t, mapping, max_search, giant_stride);
}

// Solve min_n x^n = y (1 <= n <= max_search)
template <class S, class Container>
long long DiscreteLogarithmNonzero(const S &x, const S &y, const std::function<S(S, S)> &op,
                                   long long max_search) {
    long long res = DiscreteLogarithm<S, S, Container>(x, x, y, op, op, max_search);
    if (res < 0 or res >= max_search) return -1;
    return res + 1;
}

// Solve min_n x^n = y mod md (n >= 0) or return -1 if infeasible
template <class Int> Int DiscreteLogarithmMod(Int x, Int y, Int md) {
    x %= md, y %= md;
    if (x < 0) x += md;
    if (y < 0) y += md;
    // You may change __int128 to long long, but be careful about overflow.
    auto f = [&](Int a, Int b) -> Int { return __int128(a) * b % md; };
    return DiscreteLogarithm<Int, Int, std::unordered_set<Int>>(x, Int{1} % md, y, f, f, md);
}

// Solve min_n x^n = y mod md (n >= 1) or return -1 if infeasible
template <class Int> Int DiscreteLogarithmModNonzero(Int x, Int y, Int md) {
    x %= md, y %= md;
    if (x < 0) x += md;
    if (y < 0) y += md;
    // You may change __int128 to long long, but be careful about overflow.
    auto f = [&](Int a, Int b) -> Int { return __int128(a) * b % md; };
    return DiscreteLogarithmNonzero<Int, std::unordered_set<Int>>(x, y, f, md);
}
