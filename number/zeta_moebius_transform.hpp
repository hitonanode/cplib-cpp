#pragma once
#include "../number/sieve.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// f[n] に対して、全ての n の倍数 n*i に対する f[n*i] の和が出てくる 計算量 O(N loglog N)
// 素数p毎に処理する高速ゼータ変換
// 使用例 https://yukicoder.me/submissions/385043
template <class T> void multiple_zeta(std::vector<T> &f) {
    int N = int(f.size()) - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) {
        if (is_prime[p]) {
            for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
            for (int j = N / p; j > 0; --j) f[j] += f[j * p];
        }
    }
}

// inverse of multiple_zeta O(N loglog N)
// 使用例 https://yukicoder.me/submissions/385120
template <class T> void multiple_moebius(std::vector<T> &f) {
    int N = int(f.size()) - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) {
        if (is_prime[p]) {
            for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
            for (int j = 1; j * p <= N; ++j) f[j] -= f[j * p];
        }
    }
}

// f[n] に関して、全ての n の約数 m に対する f[m] の総和が出てくる 計算量 O(N loglog N)
template <class T> void divisor_zeta(std::vector<T> &f) {
    int N = int(f.size()) - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) {
        if (is_prime[p]) {
            for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
            for (int j = 1; j * p <= N; ++j) f[j * p] += f[j];
        }
    }
}
// inverse of divisor_zeta()
// Verified: https://codeforces.com/contest/1630/problem/E
template <class T> void divisor_moebius(std::vector<T> &f) {
    int N = int(f.size()) - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) {
        if (is_prime[p]) {
            for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
            for (int j = N / p; j > 0; --j) f[j * p] -= f[j];
        }
    }
}

// GCD convolution
// ret[k] = \sum_{gcd(i, j) = k} f[i] * g[j]
template <class T> std::vector<T> gcdconv(std::vector<T> f, std::vector<T> g) {
    assert(f.size() == g.size());
    multiple_zeta(f);
    multiple_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    multiple_moebius(f);
    return f;
}

// LCM convolution
// ret[k] = \sum_{lcm(i, j) = k} f[i] * g[j]
template <class T> std::vector<T> lcmconv(std::vector<T> f, std::vector<T> g) {
    assert(f.size() == g.size());
    divisor_zeta(f);
    divisor_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    divisor_moebius(f);
    return f;
}

// fast_integer_moebius の高速化（登場しない素因数が多ければ計算量改善）
// Requirement: f の key として登場する正整数の全ての約数が key として登場
// Verified: https://toph.co/p/height-of-the-trees
template <typename Int, typename Val>
void sparse_fast_integer_moebius(std::vector<std::pair<Int, Val>> &f, const Sieve &sieve) {
    if (f.empty()) return;
    std::sort(f.begin(), f.end());
    assert(f.back().first < Int(sieve.min_factor.size()));
    std::vector<Int> primes;
    for (auto p : f) {
        if (sieve.min_factor[p.first] == p.first) primes.push_back(p.first);
    }
    std::vector<std::vector<int>> p2is(primes.size());
    for (int i = 0; i < int(f.size()); i++) {
        Int a = f[i].first, pold = 0;
        int k = 0;
        while (a > 1) {
            auto p = sieve.min_factor[a];
            if (p != pold) {
                while (primes[k] != p) k++;
                p2is[k].emplace_back(i);
            }
            pold = p, a /= p;
        }
    }
    for (int d = 0; d < int(primes.size()); d++) {
        Int p = primes[d];
        for (auto i : p2is[d]) {
            auto comp = [](const std::pair<Int, Val> &l, const std::pair<Int, Val> &r) {
                return l.first < r.first;
            };
            auto itr = std::lower_bound(f.begin(), f.end(), std::make_pair(f[i].first / p, 0), comp);
            itr->second -= f[i].second;
        }
    }
}
