#pragma once
#include <atcoder/modint>
#include <cassert>
#include <iostream>
#include <vector>

// Utility functions for atcoder::static_modint<md>
template <int md> std::istream &operator>>(std::istream &is, atcoder::static_modint<md> &x) {
    long long t;
    return is >> t, x = t, is;
}
template <int md> std::ostream &operator<<(std::ostream &os, const atcoder::static_modint<md> &x) {
    return os << x.val();
}
// atcoder::static_modint<P>, P: prime number
template <typename modint> struct acl_fac {
    std::vector<modint> facs, facinvs;
    acl_fac(int N) {
        assert(-1 <= N and N < modint::mod());
        facs.resize(N + 1, 1);
        for (int i = 1; i <= N; i++) facs[i] = facs[i - 1] * i;
        facinvs.assign(N + 1, facs.back().inv());
        for (int i = N; i > 0; i--) facinvs[i - 1] = facinvs[i] * i;
    }
    modint ncr(int n, int r) const {
        if (n < 0 or r < 0 or n < r) return 0;
        return facs[n] * facinvs[r] * facinvs[n - r];
    }
    modint operator[](int i) const { return facs[i]; }
    modint finv(int i) const { return facinvs[i]; }
};
// acl_fac<mint> fac(1000000);
