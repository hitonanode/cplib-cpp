#pragma once
#include "modulus/modint_fixed.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>
using namespace std;

// Integer convolution for arbitrary mod
// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.
// We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.
// input: a (size: n), b (size: m)
// return: vector (size: n + m - 1)
template <typename MODINT>
vector<MODINT> nttconv(vector<MODINT> a, vector<MODINT> b, bool skip_garner = false);

constexpr int nttprimes[3] = {998244353, 167772161, 469762049};

// Integer FFT (Fast Fourier Transform) for ModInt class
// (Also known as Number Theoretic Transform, NTT)
// is_inverse: inverse transform
// ** Input size must be 2^n **
template <typename MODINT>
void ntt(vector<MODINT> &a, bool is_inverse = false)
{
    int n = a.size();
    assert(__builtin_popcount(n) == 1);
    MODINT h = MODINT(MODINT::get_primitive_root()).power((MODINT::get_mod() - 1) / n);
    if (is_inverse) h = 1 / h;

    int i = 0;
    for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }

    for (int m = 1; m < n; m *= 2) {
        int m2 = 2 * m;
        long long int base = h.power(n / m2);
        MODINT w(1);
        for(int x = 0; x < m; x++) {
            for (int s = x; s < n; s += m2) {
                MODINT u = a[s], d = a[s + m] * w;
                a[s] = u + d, a[s + m] = u - d;
            }
            w *= base;
        }
    }
    if (is_inverse) {
        long long int n_inv = MODINT(n).inv();
        for (auto &v : a) v *= n_inv;
    }
}
template<int MOD>
vector<ModInt<MOD>> nttconv_(const vector<int> &a, const vector<int> &b) {
    int sz = a.size();
    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);
    vector<ModInt<MOD>> ap(sz), bp(sz);
    for (int i = 0; i < sz; i++) ap[i] = a[i], bp[i] = b[i];
    if (a == b) {
        ntt(ap, false);
        bp = ap;
    }
    else {
        ntt(ap, false);
        ntt(bp, false);
    }
    for (int i = 0; i < sz; i++) ap[i] *= bp[i];
    ntt(ap, true);
    return ap;
}
long long int extgcd_ntt_(long long int a, long long int b, long long int &x, long long int &y)
{
    long long int d = a;
    if (b != 0) d = extgcd_ntt_(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}
long long int modinv_ntt_(long long int a, long long int m)
{
    long long int x, y;
    extgcd_ntt_(a, m, x, y);
    return (m + x % m) % m;
}
long long int garner_ntt_(int r0, int r1, int r2, int mod)
{
    array<long long int, 4> rs = {r0, r1, r2, 0};
    vector<long long int> coffs(4, 1), constants(4, 0);
    for (int i = 0; i < 3; i++) {
        long long int v = (rs[i] - constants[i]) * modinv_ntt_(coffs[i], nttprimes[i]) % nttprimes[i];
        if (v < 0) v += nttprimes[i];
        for (int j = i + 1; j < 4; j++) {
            (constants[j] += coffs[j] * v) %= (j < 3 ? nttprimes[j] : mod);
            (coffs[j] *= nttprimes[i]) %= (j < 3 ? nttprimes[j] : mod);
        }
    }
    return constants.back();
}
template <typename MODINT>
vector<MODINT> nttconv(vector<MODINT> a, vector<MODINT> b, bool skip_garner)
{
    int sz = 1, n = a.size(), m = b.size();
    while (sz < n + m) sz <<= 1;
    int mod = MODINT::get_mod();
    if (skip_garner or find(begin(nttprimes), end(nttprimes), mod) != end(nttprimes)) {
        a.resize(sz), b.resize(sz);
        if (a == b) { ntt(a, false); b = a; }
        else ntt(a, false), ntt(b, false);
        for (int i = 0; i < sz; i++) a[i] *= b[i];
        ntt(a, true);
        a.resize(n + m - 1);
    }
    else {
        vector<int> ai(sz), bi(sz);
        for (int i = 0; i < n; i++) ai[i] = a[i].val;
        for (int i = 0; i < m; i++) bi[i] = b[i].val;
        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);
        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);
        auto ntt2 = nttconv_<nttprimes[2]>(ai, bi);
        a.resize(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);
        }
    }
    return a;
}
