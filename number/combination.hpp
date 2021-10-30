#pragma once
#include "bare_mod_algebra.hpp"
#include <utility>
#include <vector>

// nCr mod m = p^q (p: prime, q >= 1)
// Complexity: O(m) space (construction), O(log(n) + log(m)) (per query)
// https://ferin-tech.hatenablog.com/entry/2018/01/17/010829
struct combination_prime_pow {
    int p, q, m;
    std::vector<int> fac, invfac, ppow;

    long long _ej(long long n) const {
        long long ret = 0;
        while (n) ret += n, n /= p;
        return ret;
    }

    combination_prime_pow(int p_, int q_) : p(p_), q(q_), m(1), ppow{1} {
        for (int t = 0; t < q; ++t) m *= p, ppow.push_back(m);
        fac.assign(m, 1);
        invfac.assign(m, 1);
        for (int i = 1; i < m; ++i) fac[i] = (long long)fac[i - 1] * (i % p ? i : 1) % m;
        invfac[m - 1] = fac[m - 1]; // Same as Wilson's theorem
        assert(1LL * fac.back() * invfac.back() % m == 1);
        for (int i = m - 1; i; --i) invfac[i - 1] = (long long)invfac[i] * (i % p ? i : 1) % m;
    }

    int nCr(long long n, long long r) const {
        if (r < 0 or n < r) return 0;
        if (p == 2 and q == 1) return !((~n) & r);
        long long k = n - r;
        long long e0 = _ej(n / p) - _ej(r / p) - _ej(k / p);
        if (e0 >= q) return 0;

        long long ret = ppow[e0];
        if (q == 1) {
            while (n) {
                ret = __int128(ret) * fac[n % p] * invfac[r % p] * invfac[k % p] % p;
                n /= p, r /= p, k /= p;
            }
            return (int)ret;
        } else {
            if ((p > 2 or q < 3) and (_ej(n / m) - _ej(r / m) - _ej(k / m)) & 1) ret = m - ret;
            while (n) {
                ret = __int128(ret) * fac[n % m] * invfac[r % m] * invfac[k % m] % m;
                n /= p, r /= p, k /= p;
            }
            return (int)ret;
        }
    }
};

// nCr mod m
// Complexity: O(m) space worst (construction), O(polylog(n)) (per query)
// Input: pairs of (prime, degree), such as vector<pair<int, int>> and map<int, int>
// https://judge.yosupo.jp/problem/binomial_coefficient
struct combination {
    std::vector<combination_prime_pow> cpps;
    std::vector<int> ms;

    template <class Map> combination(const Map &p2deg) {
        for (auto f : p2deg) {
            cpps.push_back(combination_prime_pow(f.first, f.second));
            ms.push_back(cpps.back().m);
        }
    }

    int operator()(long long n, long long r) const {
        if (r < 0 or n < r) return 0;
        std::vector<int> rs;
        for (const auto &cpp : cpps) rs.push_back(cpp.nCr(n, r));
        return crt(rs, ms).first;
    }
};
