#pragma once
#include "../convolution/ntt.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Calculate f^{-1}(x) mod x^l: Inverse of polynomial mod x^l in $O(N \log N)$ complexity.
// return: vector of length l
// Requirement:
// - NTT-friendliness for faster implementation.
// - f[0] has its inverse. Otherwise, return empty vector `{}`.
// Reference: http://people.csail.mit.edu/madhu/ST12/scribe/lect06.pdf
template <typename ModInt> std::vector<ModInt> inv_of_poly_mod_monomial(const std::vector<ModInt> &f, int l) {
    assert(l >= 0);
    if (f.empty()) return {};
    if (l == 0) return {};
    const ModInt ret0 = f[0].inv();
    if (ret0 * f[0] != ModInt(1)) return {};
    std::vector<ModInt> ret{ret0};
    unsigned sz = 1;
    while (ret.size() < l) {
        std::vector<ModInt> h0(sz * 2), h1(sz * 2), a(sz * 2);
        std::copy(ret.begin(), ret.end(), a.begin());
        std::copy(f.begin(), f.begin() + std::min<unsigned>(sz, f.size()), h0.begin());
        if (f.size() >= sz) {
            std::copy(f.begin() + sz, f.begin() + std::min<unsigned>(sz * 2, f.size()), h1.begin());
        }
        ntt(a, false);
        ntt(h0, false);
        ntt(h1, false);
        for (unsigned i = 0; i < sz * 2; i++) h0[i] *= a[i];
        for (unsigned i = 0; i < sz * 2; i++) h1[i] *= a[i];
        ntt(h0, true);
        ntt(h1, true);
        for (unsigned i = 0; i < sz; i++) h1[i] += h0[i + sz];
        std::fill(h1.begin() + sz, h1.end(), 0);
        ntt(h1, false);
        for (unsigned i = 0; i < sz * 2; i++) h1[i] *= a[i];
        ntt(h1, true);
        ret.resize(std::min<unsigned>(sz * 2, l));
        for (unsigned i = sz; i < ret.size(); i++) ret[i] = -h1[i - sz];
        sz *= 2;
    }
    assert(ret.size() == l);
    return ret;
}

// Solve f(x) = g(x) * q(x) + r(x), deg(r) < deg(g) for given f(x) and g(x)
// return: (q(x), r(x))
// requirement: f, g: nonzero, f.back() != 0, g.back() != 0
template <typename ModInt>
std::pair<std::vector<ModInt>, std::vector<ModInt>> polynomial_division(const std::vector<ModInt> &f, const std::vector<ModInt> &g) {
    assert(f.size() and f.back() != 0);
    assert(g.size() and g.back() != 0);
    if (f.size() < g.size()) { return {{}, f}; }
    const int l = f.size() - g.size();
    std::vector<ModInt> revf(l), revg(l);
    for (int i = 0; i < l; i++) revf[i] = f[f.size() - 1 - i];
    for (int i = 0; i < std::min<int>(l, g.size()); i++) revg[i] = g[g.size() - 1 - i];
    auto revginv = inv_of_poly_mod_monomial(revg, l);
    auto q = nttconv(revginv, revf);
    q.resize(l + 1);
    std::reverse(q.begin(), q.end());
    int d = int(g.size()) - 1;
    q[0] = f[d];
    for (int e = std::max(0, d - int(q.size()) + 1); e < d; e++) q[0] -= g[e] * q[d - e];
    q[0] /= g.back();
    auto gq = nttconv(g, q);
    std::vector<ModInt> r(g.size() - 1);
    for (unsigned i = 0; i < r.size(); i++) r[i] = f[i] - gq[i];
    while (r.size() and r.back() == 0) r.pop_back();
    return {q, r};
}
