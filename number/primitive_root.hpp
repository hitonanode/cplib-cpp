#pragma once
#include "bare_mod_algebra.hpp"
#include "factorize.hpp"

// Find smallest primitive root for given number n （最小の原始根探索）
// n must be 2 / 4 / p^k / 2p^k (p: odd prime, k > 0)
// (https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
//
// Complexity: maybe O(sqrt(n)), if n is
// prime Algorithm: http://kirika-comp.hatenablog.com/entry/2018/03/12/210446 Verified:
// - https://yukicoder.me/submissions/405938
// - https://judge.yosupo.jp/problem/primitive_root
// - SRM 840 Div.1 900 https://community.topcoder.com/stat?c=problem_statement&pm=17877
// Sample:
//  - 998244353 ( = (119 << 23) + 1 ) -> 3
//  - 163577857 ( = (39 << 22) + 1 ) -> 23
//  - 2 -> 1
//  - 1 -> -1
long long find_smallest_primitive_root(long long n) {
    std::vector<long long> fac;
    const long long phi = FactorizeLonglong.euler_phi(n);
    for (long long q : FactorizeLonglong(phi)) {
        if (fac.empty() or fac.back() != q) fac.push_back(q);
    }

    for (long long g = 1; g < n; g++) {
        if (std::__gcd(n, g) != 1) continue;
        if (pow_mod<long long, __int128>(g, phi, n) != 1) return -1;
        bool ok = true;
        for (auto pp : fac) {
            if (pow_mod<long long, __int128>(g, phi / pp, n) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return -1;
}
