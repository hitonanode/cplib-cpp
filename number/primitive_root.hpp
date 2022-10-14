#pragma once
#include "bare_mod_algebra.hpp"
#include "factorize.hpp"

// Find smallest primitive root for given prime P （最小の原始根探索）
// Complexity: maybe O(sqrt(p))
// Algorithm: http://kirika-comp.hatenablog.com/entry/2018/03/12/210446
// Verified: https://yukicoder.me/submissions/405938 https://judge.yosupo.jp/problem/primitive_root
// Sample:
//  - 998244353 ( = (119 << 23) + 1 ) -> 3
//  - 163577857 ( = (39 << 22) + 1 ) -> 23
//  - 2 -> 1
//  - 1 -> -1
long long find_smallest_primitive_root(long long p) {
    std::vector<long long> fac;
    for (long long q : FactorizeLonglong(p - 1)) {
        if (fac.empty() or fac.back() != q) fac.push_back(q);
    }

    for (long long g = 1; g < p; g++) {
        if (pow_mod<long long, __int128>(g, p - 1, p) != 1) return -1;
        bool ok = true;
        for (auto pp : fac) {
            if (pow_mod<long long, __int128>(g, (p - 1) / pp, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return -1;
}
