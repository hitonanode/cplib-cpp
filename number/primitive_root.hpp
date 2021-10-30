#pragma once
#include "bare_mod_algebra.hpp"

// Find smallest primitive root for given prime P （最小の原始根探索）
// Complexity: maybe O(sqrt(p))
// Algorithm: http://kirika-comp.hatenablog.com/entry/2018/03/12/210446
// Verified: https://yukicoder.me/submissions/405938
// Sample:
//  - 998244353 ( = (119 << 23) + 1 ) -> 3
//  - 163577857 ( = (39 << 22) + 1 ) -> 23
//  - 2 -> 1
//  - 1 -> -1
template <class Int = long long> Int find_smallest_primitive_root(Int p) {
    std::vector<Int> fac;
    Int v = p - 1;
    for (Int pp = 2; pp * pp <= v; pp++) { // prime factorization of (p - 1)
        int e = 0;
        while (v % pp == 0) e++, v /= pp;
        if (e) fac.push_back(pp);
    }
    if (v > 1) fac.push_back(v);

    for (Int g = 1; g < p; g++) {
        if (pow_mod(g, p - 1, p) != 1) return -1;
        bool ok = true;
        for (auto pp : fac) {
            if (pow_mod(g, (p - 1) / pp, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return -1;
}
