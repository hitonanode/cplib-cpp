#pragma once
#include <cassert>
#include <vector>

// CUT begin
// Subset sum (fast zeta transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T> void subset_sum(std::vector<T> &f) {
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++)
            if (S & (1 << d)) f[S] += f[S ^ (1 << d)];
    }
}
// Inverse of subset sum (fast moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T> void subset_sum_inv(std::vector<T> &g) {
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++)
            if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];
    }
}

// Superset sum / its inverse (fast zeta/moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T> void superset_sum(std::vector<T> &f) {
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++)
            if (!(S & (1 << d))) f[S] += f[S | (1 << d)];
    }
}
template <typename T> void superset_sum_inv(std::vector<T> &g) {
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++)
            if (!(S & (1 << d))) g[S] -= g[S | (1 << d)];
    }
}

// Subset convolution
// h[S] = \sum_T f[T] * g[S - T]
// Complexity: O(N^2 2^N) for arrays of size 2^N
template <typename T> std::vector<T> subset_convolution(std::vector<T> f, std::vector<T> g) {
    const int sz = f.size(), m = __builtin_ctz(sz) + 1;
    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());

    std::vector<std::vector<T>> ff(m, std::vector<T>(sz)), fg(m, std::vector<T>(sz));
    for (int i = 0; i < sz; i++) {
        int pc = __builtin_popcount(i);
        ff[pc][i] += f[i], fg[pc][i] += g[i];
    }
    for (auto &vec : ff) subset_sum(vec);
    for (auto &vec : fg) subset_sum(vec);

    std::vector<std::vector<T>> fh(m, std::vector<T>(sz));
    for (int d = 0; d < m; d++) {
        for (int e = 0; d + e < m; e++) {
            for (int i = 0; i < sz; i++) fh[d + e][i] += ff[d][i] * fg[e][i];
        }
    }
    for (auto &vec : fh) subset_sum_inv(vec);
    std::vector<T> ret(sz);
    for (int i = 0; i < sz; i++) ret[i] = fh[__builtin_popcount(i)][i];
    return ret;
}

template <class T, class Function> void subset_func(std::vector<T> &f, const Function &func) {
    const int sz = f.size(), m = __builtin_ctz(sz) + 1;
    assert(__builtin_popcount(sz) == 1);
    std::vector<std::vector<T>> ff(m, std::vector<T>(sz));
    for (int i = 0; i < sz; i++) ff[__builtin_popcount(i)][i] += f[i];
    for (auto &vec : ff) subset_sum(vec);

    std::vector<T> p(m);
    for (int i = 0; i < sz; i++) {
        for (int d = 0; d < m; d++) p[d] = ff[d][i];
        p = func(p);
        for (int d = 0; d < m; d++) ff[d][i] = p[d];
    }

    for (auto &vec : ff) subset_sum_inv(vec);
    for (int i = 0; i < sz; i++) f[i] = ff[__builtin_popcount(i)][i];
}

template <class T> struct poly_log {
    int maxlen;
    std::vector<T> invs;
    poly_log(int maxlen) : maxlen(maxlen), invs(maxlen) {
        for (int d = 1; d < maxlen; d++) invs[d] = T(d).inv();
    }
    std::vector<T> operator()(const std::vector<T> &f) const {
        assert(f.at(0) == T(1));
        const int m = f.size();
        std::vector<T> finv(m);
        for (int d = 0; d < m; d++) {
            finv[d] = (d == 0);
            for (int e = 0; e < d; e++) finv[d] -= finv[e] * f[d - e];
        }
        std::vector<T> ret(m);
        for (int d = 1; d < m; d++) {
            for (int e = 0; d + e < m; e++) ret[d + e] += f[d] * d * finv[e] * invs[d + e];
        }
        return ret;
    }
};

// log(f(S)) for set function f(S), f(0) == 1
// https://atcoder.jp/contests/abc213/tasks/abc213_g
template <class T> void subset_log(std::vector<T> &f) {
    subset_func(f, poly_log<mint>(__builtin_ctz(f.size()) + 1));
}
