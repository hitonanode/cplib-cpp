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
