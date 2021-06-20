---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/multipoint_evaluation.hpp
    title: formal_power_series/multipoint_evaluation.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/bernoulli_number.test.cpp
    title: formal_power_series/test/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/division_number.test.cpp
    title: formal_power_series/test/division_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_exp.test.cpp
    title: formal_power_series/test/fps_exp.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_exp_modintruntime.test.cpp
    title: formal_power_series/test/fps_exp_modintruntime.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_inv.test.cpp
    title: formal_power_series/test/fps_inv.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_log.test.cpp
    title: formal_power_series/test/fps_log.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_pow.test.cpp
    title: formal_power_series/test/fps_pow.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_pow_another.test.cpp
    title: formal_power_series/test/fps_pow_another.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_sqrt.test.cpp
    title: formal_power_series/test/fps_sqrt.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/fps_sqrt_modintruntime.test.cpp
    title: formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/multipoint_evaluation.test.cpp
    title: formal_power_series/test/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/poly_taylor_shift.test.cpp
    title: formal_power_series/test/poly_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/polynomial_interpolation.test.cpp
    title: formal_power_series/test/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sharp_p_subset_sum.test.cpp
    title: formal_power_series/test/sharp_p_subset_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/stirling_number_of_1st.test.cpp
    title: formal_power_series/test/stirling_number_of_1st.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/stirling_number_of_2nd.test.cpp
    title: formal_power_series/test/stirling_number_of_2nd.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = md - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < md;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v - md : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + md); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % md); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % md); }\n  \
    \  MDCONST ModInt operator-() const { return ModInt()._setval(md - val); }\n \
    \   MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % md + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x)\
    \ { return ModInt()._setval(a % md - x.val + md); }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) { return ModInt()._setval(a % md * x.val\
    \ % md); }\n    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        ModInt ans =\
    \ 1, tmp = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n \
    \           tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n  \
    \  static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static void _precalculation(int\
    \ N) {\n        int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n    MDCONST lint inv() const {\n       \
    \ if (this->val < std::min(md >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val].val;\n\
    \        } else {\n            return this->pow(md - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\
    \    MDCONST ModInt facinv() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val];\n    }\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST\
    \ ModInt nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x\
    \ * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <tuple>\n\
    #line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner = false);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
    \ 469762049};\n\n// Integer FFT (Fast Fourier Transform) for ModInt class\n//\
    \ (Also known as Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n\
    // ** Input size must be 2^n **\ntemplate <typename MODINT> void ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false) {\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::mod();\n    static const MODINT root = MODINT::get_primitive_root();\n\
    \    assert(__builtin_popcount(n) == 1 and (mod - 1) % n == 0);\n\n    static\
    \ std::vector<MODINT> w{1}, iw{1};\n    for (int m = w.size(); m < n / 2; m *=\
    \ 2) {\n        MODINT dw = root.pow((mod - 1) / (4 * m)), dwinv = 1 / dw;\n \
    \       w.resize(m * 2), iw.resize(m * 2);\n        for (int i = 0; i < m; i++)\
    \ w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n    }\n\n    if (!is_inverse)\
    \ {\n        for (int m = n; m >>= 1;) {\n            for (int s = 0, k = 0; s\
    \ < n; s += 2 * m, k++) {\n                for (int i = s; i < s + m; i++) {\n\
    \                    MODINT x = a[i], y = a[i + m] * w[k];\n                 \
    \   a[i] = x + y, a[i + m] = x - y;\n                }\n            }\n      \
    \  }\n    } else {\n        for (int m = 1; m < n; m *= 2) {\n            for\
    \ (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int i = s;\
    \ i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m];\n    \
    \                a[i] = x + y, a[i + m] = (x - y) * iw[k];\n                }\n\
    \            }\n        }\n        int n_inv = MODINT(n).inv();\n        for (auto\
    \ &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD> std::vector<ModInt<MOD>> nttconv_(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n    int sz = a.size();\n\
    \    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n    std::vector<ModInt<MOD>>\
    \ ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++) ap[i] = a[i], bp[i] = b[i];\n\
    \    ntt(ap, false);\n    if (a == b)\n        bp = ap;\n    else\n        ntt(bp,\
    \ false);\n    for (int i = 0; i < sz; i++) ap[i] *= bp[i];\n    ntt(ap, true);\n\
    \    return ap;\n}\nlong long garner_ntt_(int r0, int r1, int r2, int mod) {\n\
    \    using mint2 = ModInt<nttprimes[2]>;\n    static const long long m01 = 1LL\
    \ * nttprimes[0] * nttprimes[1];\n    static const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n\
    \    static const long long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1\
    \ * (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 -\
    \ mint2(nttprimes[0]) * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0]\
    \ * v1 + m01 % mod * v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT>\
    \ nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {\n\
    \    if (a.empty() or b.empty()) return {};\n    int sz = 1, n = a.size(), m =\
    \ b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT>\
    \ ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n            for (int\
    \ j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n\
    \    }\n    int mod = MODINT::mod();\n    if (skip_garner or std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\
    \ a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n    }\n   \
    \ return a;\n}\n#line 6 \"formal_power_series/formal_power_series.hpp\"\nusing\
    \ namespace std;\n\n// CUT begin\n// Formal Power Series (\u5F62\u5F0F\u7684\u51AA\
    \u7D1A\u6570) based on ModInt<mod> / ModIntRuntime\n// Reference: https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html\n\
    template <typename T> struct FormalPowerSeries : vector<T> {\n    using vector<T>::vector;\n\
    \    using P = FormalPowerSeries;\n\n    void shrink() {\n        while (this->size()\
    \ and this->back() == T(0)) this->pop_back();\n    }\n\n    P operator+(const\
    \ P &r) const { return P(*this) += r; }\n    P operator+(const T &v) const { return\
    \ P(*this) += v; }\n    P operator-(const P &r) const { return P(*this) -= r;\
    \ }\n    P operator-(const T &v) const { return P(*this) -= v; }\n    P operator*(const\
    \ P &r) const { return P(*this) *= r; }\n    P operator*(const T &v) const { return\
    \ P(*this) *= v; }\n    P operator/(const P &r) const { return P(*this) /= r;\
    \ }\n    P operator/(const T &v) const { return P(*this) /= v; }\n    P operator%(const\
    \ P &r) const { return P(*this) %= r; }\n\n    P &operator+=(const P &r) {\n \
    \       if (r.size() > this->size()) this->resize(r.size());\n        for (int\
    \ i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];\n        shrink();\n    \
    \    return *this;\n    }\n    P &operator+=(const T &v) {\n        if (this->empty())\
    \ this->resize(1);\n        (*this)[0] += v;\n        shrink();\n        return\
    \ *this;\n    }\n    P &operator-=(const P &r) {\n        if (r.size() > this->size())\
    \ this->resize(r.size());\n        for (int i = 0; i < (int)r.size(); i++) (*this)[i]\
    \ -= r[i];\n        shrink();\n        return *this;\n    }\n    P &operator-=(const\
    \ T &v) {\n        if (this->empty()) this->resize(1);\n        (*this)[0] -=\
    \ v;\n        shrink();\n        return *this;\n    }\n    P &operator*=(const\
    \ T &v) {\n        for (auto &x : (*this)) x *= v;\n        shrink();\n      \
    \  return *this;\n    }\n    P &operator*=(const P &r) {\n        if (this->empty()\
    \ || r.empty())\n            this->clear();\n        else {\n            auto\
    \ ret = nttconv(*this, r);\n            *this = P(ret.begin(), ret.end());\n \
    \       }\n        return *this;\n    }\n    P &operator%=(const P &r) {\n   \
    \     *this -= *this / r * r;\n        shrink();\n        return *this;\n    }\n\
    \    P operator-() const {\n        P ret = *this;\n        for (auto &v : ret)\
    \ v = -v;\n        return ret;\n    }\n    P &operator/=(const T &v) {\n     \
    \   assert(v != T(0));\n        for (auto &x : (*this)) x /= v;\n        return\
    \ *this;\n    }\n    P &operator/=(const P &r) {\n        if (this->size() < r.size())\
    \ {\n            this->clear();\n            return *this;\n        }\n      \
    \  int n = (int)this->size() - r.size() + 1;\n        return *this = (reversed().pre(n)\
    \ * r.reversed().inv(n)).pre(n).reversed(n);\n    }\n    P pre(int sz) const {\n\
    \        P ret(this->begin(), this->begin() + min((int)this->size(), sz));\n \
    \       ret.shrink();\n        return ret;\n    }\n    P operator>>(int sz) const\
    \ {\n        if ((int)this->size() <= sz) return {};\n        return P(this->begin()\
    \ + sz, this->end());\n    }\n    P operator<<(int sz) const {\n        if (this->empty())\
    \ return {};\n        P ret(*this);\n        ret.insert(ret.begin(), sz, T(0));\n\
    \        return ret;\n    }\n\n    P reversed(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        P ret(*this);\n        if (deg != -1) ret.resize(deg, T(0));\n\
    \        reverse(ret.begin(), ret.end());\n        ret.shrink();\n        return\
    \ ret;\n    }\n\n    P differential() const { // formal derivative (differential)\
    \ of f.p.s.\n        const int n = (int)this->size();\n        P ret(max(0, n\
    \ - 1));\n        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);\n\
    \        return ret;\n    }\n\n    P integral() const {\n        const int n =\
    \ (int)this->size();\n        P ret(n + 1);\n        ret[0] = T(0);\n        for\
    \ (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n        return\
    \ ret;\n    }\n\n    P inv(int deg) const {\n        assert(deg >= -1);\n    \
    \    assert(this->size() and ((*this)[0]) != T(0)); // Requirement: F(0) != 0\n\
    \        const int n = this->size();\n        if (deg == -1) deg = n;\n      \
    \  P ret({T(1) / (*this)[0]});\n        for (int i = 1; i < deg; i <<= 1) { ret\
    \ = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1); }\n        ret = ret.pre(deg);\n\
    \        ret.shrink();\n        return ret;\n    }\n\n    P log(int deg = -1)\
    \ const {\n        assert(deg >= -1);\n        assert(this->size() and ((*this)[0])\
    \ == T(1)); // Requirement: F(0) = 1\n        const int n = (int)this->size();\n\
    \        if (deg == 0) return {};\n        if (deg == -1) deg = n;\n        return\
    \ (this->differential() * this->inv(deg)).pre(deg - 1).integral();\n    }\n\n\
    \    P sqrt(int deg = -1) const {\n        assert(deg >= -1);\n        const int\
    \ n = (int)this->size();\n        if (deg == -1) deg = n;\n        if (this->empty())\
    \ return {};\n        if ((*this)[0] == T(0)) {\n            for (int i = 1; i\
    \ < n; i++)\n                if ((*this)[i] != T(0)) {\n                    if\
    \ ((i & 1) or deg - i / 2 <= 0) return {};\n                    return (*this\
    \ >> i).sqrt(deg - i / 2) << (i / 2);\n                }\n            return {};\n\
    \        }\n        T sqrtf0 = (*this)[0].sqrt();\n        if (sqrtf0 == T(0))\
    \ return {};\n\n        P y = (*this) / (*this)[0], ret({T(1)});\n        T inv2\
    \ = T(1) / T(2);\n        for (int i = 1; i < deg; i <<= 1) { ret = (ret + y.pre(i\
    \ << 1) * ret.inv(i << 1)) * inv2; }\n        return ret.pre(deg) * sqrtf0;\n\
    \    }\n\n    P exp(int deg = -1) const {\n        assert(deg >= -1);\n      \
    \  assert(this->empty() or ((*this)[0]) == T(0)); // Requirement: F(0) = 0\n \
    \       const int n = (int)this->size();\n        if (deg == -1) deg = n;\n  \
    \      P ret({T(1)});\n        for (int i = 1; i < deg; i <<= 1) { ret = (ret\
    \ * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1); }\n        return ret.pre(deg);\n\
    \    }\n\n    P pow(long long k, int deg = -1) const {\n        assert(deg >=\
    \ -1);\n        const int n = (int)this->size();\n        if (deg == -1) deg =\
    \ n;\n        for (int i = 0; i < n; i++) {\n            if ((*this)[i] != T(0))\
    \ {\n                T rev = T(1) / (*this)[i];\n                P C = (*this)\
    \ * rev, D(n - i);\n                for (int j = i; j < n; j++) D[j - i] = C.coeff(j);\n\
    \                D = (D.log(deg) * T(k)).exp(deg) * (*this)[i].pow(k);\n     \
    \           if (k * (i > 0) > deg or k * i > deg) return {};\n               \
    \ P E(deg);\n                long long S = i * k;\n                for (int j\
    \ = 0; j + S < deg and j < (int)D.size(); j++) E[j + S] = D[j];\n            \
    \    E.shrink();\n                return E;\n            }\n        }\n      \
    \  return *this;\n    }\n\n    // Calculate f(X + c) from f(X), O(NlogN)\n   \
    \ P shift(T c) const {\n        const int n = (int)this->size();\n        P ret\
    \ = *this;\n        for (int i = 0; i < n; i++) { ret[i] *= T(i).fac(); }\n  \
    \      reverse(ret.begin(), ret.end());\n        P exp_cx(n, 1);\n        for\
    \ (int i = 1; i < n; i++) { exp_cx[i] = exp_cx[i - 1] * c / i; }\n        ret\
    \ = (ret * exp_cx), ret.resize(n);\n        reverse(ret.begin(), ret.end());\n\
    \        for (int i = 0; i < n; i++) { ret[i] /= T(i).fac(); }\n        return\
    \ ret;\n    }\n\n    T coeff(int i) const {\n        if ((int)this->size() <=\
    \ i or i < 0) return T(0);\n        return (*this)[i];\n    }\n\n    T eval(T\
    \ x) const {\n        T ret = 0, w = 1;\n        for (auto &v : *this) ret +=\
    \ w * v, w *= x;\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include \"convolution/ntt.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\nusing namespace std;\n\n// CUT begin\n// Formal\
    \ Power Series (\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570) based on ModInt<mod> / ModIntRuntime\n\
    // Reference: https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html\n\
    template <typename T> struct FormalPowerSeries : vector<T> {\n    using vector<T>::vector;\n\
    \    using P = FormalPowerSeries;\n\n    void shrink() {\n        while (this->size()\
    \ and this->back() == T(0)) this->pop_back();\n    }\n\n    P operator+(const\
    \ P &r) const { return P(*this) += r; }\n    P operator+(const T &v) const { return\
    \ P(*this) += v; }\n    P operator-(const P &r) const { return P(*this) -= r;\
    \ }\n    P operator-(const T &v) const { return P(*this) -= v; }\n    P operator*(const\
    \ P &r) const { return P(*this) *= r; }\n    P operator*(const T &v) const { return\
    \ P(*this) *= v; }\n    P operator/(const P &r) const { return P(*this) /= r;\
    \ }\n    P operator/(const T &v) const { return P(*this) /= v; }\n    P operator%(const\
    \ P &r) const { return P(*this) %= r; }\n\n    P &operator+=(const P &r) {\n \
    \       if (r.size() > this->size()) this->resize(r.size());\n        for (int\
    \ i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];\n        shrink();\n    \
    \    return *this;\n    }\n    P &operator+=(const T &v) {\n        if (this->empty())\
    \ this->resize(1);\n        (*this)[0] += v;\n        shrink();\n        return\
    \ *this;\n    }\n    P &operator-=(const P &r) {\n        if (r.size() > this->size())\
    \ this->resize(r.size());\n        for (int i = 0; i < (int)r.size(); i++) (*this)[i]\
    \ -= r[i];\n        shrink();\n        return *this;\n    }\n    P &operator-=(const\
    \ T &v) {\n        if (this->empty()) this->resize(1);\n        (*this)[0] -=\
    \ v;\n        shrink();\n        return *this;\n    }\n    P &operator*=(const\
    \ T &v) {\n        for (auto &x : (*this)) x *= v;\n        shrink();\n      \
    \  return *this;\n    }\n    P &operator*=(const P &r) {\n        if (this->empty()\
    \ || r.empty())\n            this->clear();\n        else {\n            auto\
    \ ret = nttconv(*this, r);\n            *this = P(ret.begin(), ret.end());\n \
    \       }\n        return *this;\n    }\n    P &operator%=(const P &r) {\n   \
    \     *this -= *this / r * r;\n        shrink();\n        return *this;\n    }\n\
    \    P operator-() const {\n        P ret = *this;\n        for (auto &v : ret)\
    \ v = -v;\n        return ret;\n    }\n    P &operator/=(const T &v) {\n     \
    \   assert(v != T(0));\n        for (auto &x : (*this)) x /= v;\n        return\
    \ *this;\n    }\n    P &operator/=(const P &r) {\n        if (this->size() < r.size())\
    \ {\n            this->clear();\n            return *this;\n        }\n      \
    \  int n = (int)this->size() - r.size() + 1;\n        return *this = (reversed().pre(n)\
    \ * r.reversed().inv(n)).pre(n).reversed(n);\n    }\n    P pre(int sz) const {\n\
    \        P ret(this->begin(), this->begin() + min((int)this->size(), sz));\n \
    \       ret.shrink();\n        return ret;\n    }\n    P operator>>(int sz) const\
    \ {\n        if ((int)this->size() <= sz) return {};\n        return P(this->begin()\
    \ + sz, this->end());\n    }\n    P operator<<(int sz) const {\n        if (this->empty())\
    \ return {};\n        P ret(*this);\n        ret.insert(ret.begin(), sz, T(0));\n\
    \        return ret;\n    }\n\n    P reversed(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        P ret(*this);\n        if (deg != -1) ret.resize(deg, T(0));\n\
    \        reverse(ret.begin(), ret.end());\n        ret.shrink();\n        return\
    \ ret;\n    }\n\n    P differential() const { // formal derivative (differential)\
    \ of f.p.s.\n        const int n = (int)this->size();\n        P ret(max(0, n\
    \ - 1));\n        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);\n\
    \        return ret;\n    }\n\n    P integral() const {\n        const int n =\
    \ (int)this->size();\n        P ret(n + 1);\n        ret[0] = T(0);\n        for\
    \ (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n        return\
    \ ret;\n    }\n\n    P inv(int deg) const {\n        assert(deg >= -1);\n    \
    \    assert(this->size() and ((*this)[0]) != T(0)); // Requirement: F(0) != 0\n\
    \        const int n = this->size();\n        if (deg == -1) deg = n;\n      \
    \  P ret({T(1) / (*this)[0]});\n        for (int i = 1; i < deg; i <<= 1) { ret\
    \ = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1); }\n        ret = ret.pre(deg);\n\
    \        ret.shrink();\n        return ret;\n    }\n\n    P log(int deg = -1)\
    \ const {\n        assert(deg >= -1);\n        assert(this->size() and ((*this)[0])\
    \ == T(1)); // Requirement: F(0) = 1\n        const int n = (int)this->size();\n\
    \        if (deg == 0) return {};\n        if (deg == -1) deg = n;\n        return\
    \ (this->differential() * this->inv(deg)).pre(deg - 1).integral();\n    }\n\n\
    \    P sqrt(int deg = -1) const {\n        assert(deg >= -1);\n        const int\
    \ n = (int)this->size();\n        if (deg == -1) deg = n;\n        if (this->empty())\
    \ return {};\n        if ((*this)[0] == T(0)) {\n            for (int i = 1; i\
    \ < n; i++)\n                if ((*this)[i] != T(0)) {\n                    if\
    \ ((i & 1) or deg - i / 2 <= 0) return {};\n                    return (*this\
    \ >> i).sqrt(deg - i / 2) << (i / 2);\n                }\n            return {};\n\
    \        }\n        T sqrtf0 = (*this)[0].sqrt();\n        if (sqrtf0 == T(0))\
    \ return {};\n\n        P y = (*this) / (*this)[0], ret({T(1)});\n        T inv2\
    \ = T(1) / T(2);\n        for (int i = 1; i < deg; i <<= 1) { ret = (ret + y.pre(i\
    \ << 1) * ret.inv(i << 1)) * inv2; }\n        return ret.pre(deg) * sqrtf0;\n\
    \    }\n\n    P exp(int deg = -1) const {\n        assert(deg >= -1);\n      \
    \  assert(this->empty() or ((*this)[0]) == T(0)); // Requirement: F(0) = 0\n \
    \       const int n = (int)this->size();\n        if (deg == -1) deg = n;\n  \
    \      P ret({T(1)});\n        for (int i = 1; i < deg; i <<= 1) { ret = (ret\
    \ * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1); }\n        return ret.pre(deg);\n\
    \    }\n\n    P pow(long long k, int deg = -1) const {\n        assert(deg >=\
    \ -1);\n        const int n = (int)this->size();\n        if (deg == -1) deg =\
    \ n;\n        for (int i = 0; i < n; i++) {\n            if ((*this)[i] != T(0))\
    \ {\n                T rev = T(1) / (*this)[i];\n                P C = (*this)\
    \ * rev, D(n - i);\n                for (int j = i; j < n; j++) D[j - i] = C.coeff(j);\n\
    \                D = (D.log(deg) * T(k)).exp(deg) * (*this)[i].pow(k);\n     \
    \           if (k * (i > 0) > deg or k * i > deg) return {};\n               \
    \ P E(deg);\n                long long S = i * k;\n                for (int j\
    \ = 0; j + S < deg and j < (int)D.size(); j++) E[j + S] = D[j];\n            \
    \    E.shrink();\n                return E;\n            }\n        }\n      \
    \  return *this;\n    }\n\n    // Calculate f(X + c) from f(X), O(NlogN)\n   \
    \ P shift(T c) const {\n        const int n = (int)this->size();\n        P ret\
    \ = *this;\n        for (int i = 0; i < n; i++) { ret[i] *= T(i).fac(); }\n  \
    \      reverse(ret.begin(), ret.end());\n        P exp_cx(n, 1);\n        for\
    \ (int i = 1; i < n; i++) { exp_cx[i] = exp_cx[i - 1] * c / i; }\n        ret\
    \ = (ret * exp_cx), ret.resize(n);\n        reverse(ret.begin(), ret.end());\n\
    \        for (int i = 0; i < n; i++) { ret[i] /= T(i).fac(); }\n        return\
    \ ret;\n    }\n\n    T coeff(int i) const {\n        if ((int)this->size() <=\
    \ i or i < 0) return T(0);\n        return (*this)[i];\n    }\n\n    T eval(T\
    \ x) const {\n        T ret = 0, w = 1;\n        for (auto &v : *this) ret +=\
    \ w * v, w *= x;\n        return ret;\n    }\n};\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  isVerificationFile: false
  path: formal_power_series/formal_power_series.hpp
  requiredBy:
  - formal_power_series/multipoint_evaluation.hpp
  timestamp: '2021-06-06 14:54:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/division_number.test.cpp
  - formal_power_series/test/multipoint_evaluation.test.cpp
  - formal_power_series/test/polynomial_interpolation.test.cpp
  - formal_power_series/test/bernoulli_number.test.cpp
  - formal_power_series/test/fps_exp_modintruntime.test.cpp
  - formal_power_series/test/fps_pow_another.test.cpp
  - formal_power_series/test/poly_taylor_shift.test.cpp
  - formal_power_series/test/fps_sqrt.test.cpp
  - formal_power_series/test/fps_log.test.cpp
  - formal_power_series/test/fps_pow.test.cpp
  - formal_power_series/test/fps_exp.test.cpp
  - formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - formal_power_series/test/stirling_number_of_1st.test.cpp
  - formal_power_series/test/stirling_number_of_2nd.test.cpp
  - formal_power_series/test/sharp_p_subset_sum.test.cpp
  - formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  - formal_power_series/test/fps_inv.test.cpp
documentation_of: formal_power_series/formal_power_series.hpp
layout: document
redirect_from:
- /library/formal_power_series/formal_power_series.hpp
- /library/formal_power_series/formal_power_series.hpp.html
title: formal_power_series/formal_power_series.hpp
---
