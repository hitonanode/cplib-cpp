#pragma once
#include <algorithm>
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

// https://hos-lyric.hatenablog.com/entry/2021/01/14/201231
template <class T, class Function> void subset_func(std::vector<T> &f, const Function &func) {
    const int sz = f.size(), m = __builtin_ctz(sz) + 1;
    assert(__builtin_popcount(sz) == 1);
    std::vector<std::vector<T>> ff(m, std::vector<T>(sz));
    for (int i = 0; i < sz; i++) ff[__builtin_popcount(i)][i] += f[i];
    for (auto &vec : ff) subset_sum(vec);

    std::vector<T> p(m);
    for (int i = 0; i < sz; i++) {
        for (int d = 0; d < m; d++) p[d] = ff[d][i];
        func(p);
        for (int d = 0; d < m; d++) ff[d][i] = p[d];
    }

    for (auto &vec : ff) subset_sum_inv(vec);
    for (int i = 0; i < sz; i++) f[i] = ff[__builtin_popcount(i)][i];
}

// log(f(x)) for f(x), f(0) == 1
// Requires inv()
template <class T> void poly_log(std::vector<T> &f) {
    assert(f.at(0) == T(1));
    static std::vector<T> invs{0};
    const int m = f.size();
    std::vector<T> finv(m);
    for (int d = 0; d < m; d++) {
        finv[d] = (d == 0);
        if (int(invs.size()) <= d) invs.push_back(T(d).inv());
        for (int e = 0; e < d; e++) finv[d] -= finv[e] * f[d - e];
    }
    std::vector<T> ret(m);
    for (int d = 1; d < m; d++) {
        for (int e = 0; d + e < m; e++) ret[d + e] += f[d] * d * finv[e] * invs[d + e];
    }
    f = ret;
}

// log(f(S)) for set function f(S), f(0) == 1
// Requires inv()
// Complexity: O(n^2 2^n)
// https://atcoder.jp/contests/abc213/tasks/abc213_g
template <class T> void subset_log(std::vector<T> &f) { subset_func(f, poly_log<T>); }

// exp(f(S)) for set function f(S), f(0) == 0
// Complexity: O(n^2 2^n)
// https://codeforces.com/blog/entry/92183
template <class T> void subset_exp(std::vector<T> &f) {
    const int sz = f.size(), m = __builtin_ctz(sz);
    assert(sz == 1 << m);
    assert(f.at(0) == 0);
    std::vector<T> ret{T(1)};
    ret.reserve(sz);
    for (int d = 0; d < m; d++) {
        auto c = subset_convolution({f.begin() + (1 << d), f.begin() + (1 << (d + 1))}, ret);
        ret.insert(ret.end(), c.begin(), c.end());
    }
    f = ret;
}

// sqrt(f(x)), f(x) == 1
// Requires inv of 2
// Compelxity: O(n^2)
template <class T> void poly_sqrt(std::vector<T> &f) {
    assert(f.at(0) == T(1));
    const int m = f.size();
    static const auto inv2 = T(2).inv();
    for (int d = 1; d < m; d++) {
        if (~(d & 1)) f[d] -= f[d / 2] * f[d / 2];
        f[d] *= inv2;
        for (int e = 1; e < d - e; e++) f[d] -= f[e] * f[d - e];
    }
}

// sqrt(f(S)) for set function f(S), f(0) == 1
// Requires inv()
// https://atcoder.jp/contests/xmascon20/tasks/xmascon20_h
template <class T> void subset_sqrt(std::vector<T> &f) { subset_func(f, poly_sqrt<T>); }

// exp(f(S)) for set function f(S), f(0) == 0
template <class T> void poly_exp(std::vector<T> &P) {
    const int m = P.size();
    assert(m and P[0] == 0);
    std::vector<T> Q(m), logQ(m), Qinv(m);
    Q[0] = Qinv[0] = T(1);
    static std::vector<T> invs{0};

    auto set_invlog = [&](int d) {
        Qinv[d] = 0;
        for (int e = 0; e < d; e++) Qinv[d] -= Qinv[e] * Q[d - e];
        while (d >= int(invs.size())) {
            int sz = invs.size();
            invs.push_back(T(sz).inv());
        }
        logQ[d] = 0;
        for (int e = 1; e <= d; e++) logQ[d] += Q[e] * e * Qinv[d - e];
        logQ[d] *= invs[d];
    };
    for (int d = 1; d < m; d++) {
        Q[d] += P[d] - logQ[d];
        set_invlog(d);
        assert(logQ[d] == P[d]);
        if (d + 1 < m) set_invlog(d + 1);
    }
    P = Q;
}

// f(S)^k for set function f(S)
// Requires inv()
template <class T> void subset_pow(std::vector<T> &f, long long k) {
    auto poly_pow = [&](std::vector<T> &f) {
        const int m = f.size();
        if (k == 0) f[0] = 1, std::fill(f.begin() + 1, f.end(), T(0));
        if (k <= 1) return;
        int nzero = 0;
        while (nzero < int(f.size()) and f[nzero] == T(0)) nzero++;
        int rem = std::max<long long>((long long)f.size() - nzero * k, 0LL);
        if (rem == 0) {
            std::fill(f.begin(), f.end(), 0);
            return;
        }
        f.erase(f.begin(), f.begin() + nzero);
        f.resize(rem);
        const T f0 = f.at(0), f0inv = f0.inv(), f0pow = f0.pow(k);
        for (auto &x : f) x *= f0inv;
        poly_log(f);
        for (auto &x : f) x *= k;
        poly_exp(f);
        for (auto &x : f) x *= f0pow;
        f.resize(rem, 0);
        f.insert(f.begin(), m - int(f.size()), T(0));
    };
    subset_func(f, poly_pow);
}
