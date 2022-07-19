---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/formal_power_series.hpp
    title: formal_power_series/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/pow_of_sparse_fps.hpp
    title: "Power of sparse formal power series \uFF08\u975E\u96F6\u306A\u9805\u304C\
      \u758E\u306A\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570\u306E\u7D2F\u4E57\uFF09"
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"formal_power_series/test/pow_of_sparse_fps.stress.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"formal_power_series/pow_of_sparse_fps.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // Calculate f(x)^k up to x^N\n// Requirement: k > 0\n// Complexity: O(NM) (M\
    \ : num. of nonzero coefficients of f(x))\ntemplate <class T> std::vector<T> pow_of_sparse_fps(const\
    \ std::vector<T> &f, int N, long long k) {\n    assert(k > 0);\n    std::vector<std::pair<int,\
    \ T>> nonzero_terms;\n    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <=\
    \ N and f[d0] == T()) ++d0;\n    if (d0 == int(f.size()) or d0 > N) return std::vector<T>(N\
    \ + 1);\n\n    if (d0 and N / d0 < k) return std::vector<T>(N + 1);\n\n    for\
    \ (int d = d0; d < std::min<int>(N + 1, f.size()); ++d) {\n        if (f[d] !=\
    \ T()) nonzero_terms.emplace_back(d - d0, f[d]);\n    }\n\n    int Ncalc = N -\
    \ d0 * k;\n\n    std::vector<T> ret(Ncalc + 1);\n    ret[0] = f[d0].pow(k);\n\
    \    for (int d = 0; d + 1 < int(ret.size()); ++d) {\n        // Compare [x^d](k\
    \ f'g - fg')\n        T tmp = T();\n        int i, j;\n        T fi;\n       \
    \ for (auto i_fi : nonzero_terms) {\n            std::tie(i, fi) = i_fi;\n   \
    \         if (!i) continue;\n            j = d - i;\n            if (0 <= j) tmp\
    \ -= fi * ret[j + 1] * (j + 1);\n            j = d - (i - 1);\n            if\
    \ (0 <= j) tmp += fi * i * ret[j] * T(k);\n        }\n        ret[d + 1] = tmp\
    \ / (f[d0] * (d + 1));\n    }\n\n    ret.resize(N + 1, T());\n    std::rotate(ret.begin(),\
    \ ret.end() - d0 * k, ret.end());\n    return ret;\n}\n#line 2 \"modint.hpp\"\n\
    #include <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\n\ntemplate <int md>\
    \ struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n\
    #define MDCONST\n#endif\n    using lint = long long;\n    MDCONST static int mod()\
    \ { return md; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModInt(g).pow((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val_;\n    int val() const\
    \ noexcept { return val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST\
    \ ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit operator bool()\
    \ const { return val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    MDCONST ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    MDCONST ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    MDCONST ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend MDCONST ModInt operator+(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md + x.val_);\n \
    \   }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x) {\n      \
    \  return ModInt()._setval(a % md - x.val_ + md);\n    }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a % md\
    \ * x.val_ % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md * x.inv().val() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val_ == x.val_; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val_ != x.val_; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val_ < x.val_;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST ModInt inv() const {\n        if (this->val_ < std::min(md\
    \ >> 1, 1 << 21)) {\n            if (facs.empty()) facs = {1}, facinvs = {1},\
    \ invs = {0};\n            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val_];\n        } else {\n            return\
    \ this->pow(md - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n   \
    \     while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \        return facs[this->val_];\n    }\n    MDCONST ModInt facinv() const {\n\
    \        while (this->val_ >= int(facs.size())) _precalculation(facs.size() *\
    \ 2);\n        return facinvs[this->val_];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val_ + 1) / 2;\n        return (this->val_\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n        \
    \                        : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val_ < r.val_) ?\
    \ 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val_ < r.val_) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val_\
    \ == 0) return 0;\n        if (md == 2) return val_;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 2 \"random/xorshift.hpp\"\n#include <cstdint>\n\n// CUT begin\nuint32_t\
    \ rand_int() // XorShift random integer generator\n{\n    static uint32_t x =\
    \ 123456789, y = 362436069, z = 521288629, w = 88675123;\n    uint32_t t = x ^\
    \ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    return w = (w ^ (w >> 19))\
    \ ^ (t ^ (t >> 8));\n}\ndouble rand_double() { return (double)rand_int() / UINT32_MAX;\
    \ }\n#line 3 \"convolution/ntt.hpp\"\n\n#line 5 \"convolution/ntt.hpp\"\n#include\
    \ <array>\n#line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution\
    \ for arbitrary mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime\
    \ class.\n// We skip Garner's algorithm if `skip_garner` is true or mod is in\
    \ `nttprimes`.\n// input: a (size: n), b (size: m)\n// return: vector (size: n\
    \ + m - 1)\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner);\n\nconstexpr int nttprimes[3] =\
    \ {998244353, 167772161, 469762049};\n\n// Integer FFT (Fast Fourier Transform)\
    \ for ModInt class\n// (Also known as Number Theoretic Transform, NTT)\n// is_inverse:\
    \ inverse transform\n// ** Input size must be 2^n **\ntemplate <typename MODINT>\
    \ void ntt(std::vector<MODINT> &a, bool is_inverse = false) {\n    int n = a.size();\n\
    \    if (n == 1) return;\n    static const int mod = MODINT::mod();\n    static\
    \ const MODINT root = MODINT::get_primitive_root();\n    assert(__builtin_popcount(n)\
    \ == 1 and (mod - 1) % n == 0);\n\n    static std::vector<MODINT> w{1}, iw{1};\n\
    \    for (int m = w.size(); m < n / 2; m *= 2) {\n        MODINT dw = root.pow((mod\
    \ - 1) / (4 * m)), dwinv = 1 / dw;\n        w.resize(m * 2), iw.resize(m * 2);\n\
    \        for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] *\
    \ dwinv;\n    }\n\n    if (!is_inverse) {\n        for (int m = n; m >>= 1;) {\n\
    \            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n              \
    \  for (int i = s; i < s + m; i++) {\n                    MODINT x = a[i], y =\
    \ a[i + m] * w[k];\n                    a[i] = x + y, a[i + m] = x - y;\n    \
    \            }\n            }\n        }\n    } else {\n        for (int m = 1;\
    \ m < n; m *= 2) {\n            for (int s = 0, k = 0; s < n; s += 2 * m, k++)\
    \ {\n                for (int i = s; i < s + m; i++) {\n                    MODINT\
    \ x = a[i], y = a[i + m];\n                    a[i] = x + y, a[i + m] = (x - y)\
    \ * iw[k];\n                }\n            }\n        }\n        int n_inv = MODINT(n).inv().val();\n\
    \        for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv().val();\n\
    \    static const long long m01_inv_m2 = mint2(m01).inv().val();\n\n    int v1\
    \ = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2)\
    \ - r0 - mint2(nttprimes[0]) * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0]\
    \ * v1 + m01 % mod * v2.val()) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT>\
    \ nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {\n\
    \    if (a.empty() or b.empty()) return {};\n    int sz = 1, n = a.size(), m =\
    \ b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT>\
    \ ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n            for (int\
    \ j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n\
    \    }\n    int mod = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val();\n        for (int i = 0; i < m;\
    \ i++) bi[i] = b[i].val();\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n\
    \        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val(), ntt1[i].val(), ntt2[i].val(), mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 6 \"formal_power_series/formal_power_series.hpp\"\n\n//\
    \ Formal Power Series (\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570) based on ModInt<mod>\
    \ / ModIntRuntime\n// Reference: https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html\n\
    template <typename T> struct FormalPowerSeries : std::vector<T> {\n    using std::vector<T>::vector;\n\
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
    \        P ret(this->begin(), this->begin() + std::min((int)this->size(), sz));\n\
    \        ret.shrink();\n        return ret;\n    }\n    P operator>>(int sz) const\
    \ {\n        if ((int)this->size() <= sz) return {};\n        return P(this->begin()\
    \ + sz, this->end());\n    }\n    P operator<<(int sz) const {\n        if (this->empty())\
    \ return {};\n        P ret(*this);\n        ret.insert(ret.begin(), sz, T(0));\n\
    \        return ret;\n    }\n\n    P reversed(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        P ret(*this);\n        if (deg != -1) ret.resize(deg, T(0));\n\
    \        reverse(ret.begin(), ret.end());\n        ret.shrink();\n        return\
    \ ret;\n    }\n\n    P differential() const { // formal derivative (differential)\
    \ of f.p.s.\n        const int n = (int)this->size();\n        P ret(std::max(0,\
    \ n - 1));\n        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);\n\
    \        return ret;\n    }\n\n    P integral() const {\n        const int n =\
    \ (int)this->size();\n        P ret(n + 1);\n        ret[0] = T(0);\n        for\
    \ (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n        return\
    \ ret;\n    }\n\n    P inv(int deg) const {\n        assert(deg >= -1);\n    \
    \    assert(this->size() and ((*this)[0]) != T(0)); // Requirement: F(0) != 0\n\
    \        const int n = this->size();\n        if (deg == -1) deg = n;\n      \
    \  P ret({T(1) / (*this)[0]});\n        for (int i = 1; i < deg; i <<= 1) {\n\
    \            ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);\n      \
    \  }\n        ret = ret.pre(deg);\n        ret.shrink();\n        return ret;\n\
    \    }\n\n    P log(int deg = -1) const {\n        assert(deg >= -1);\n      \
    \  assert(this->size() and ((*this)[0]) == T(1)); // Requirement: F(0) = 1\n \
    \       const int n = (int)this->size();\n        if (deg == 0) return {};\n \
    \       if (deg == -1) deg = n;\n        return (this->differential() * this->inv(deg)).pre(deg\
    \ - 1).integral();\n    }\n\n    P sqrt(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        const int n = (int)this->size();\n        if (deg == -1) deg\
    \ = n;\n        if (this->empty()) return {};\n        if ((*this)[0] == T(0))\
    \ {\n            for (int i = 1; i < n; i++)\n                if ((*this)[i] !=\
    \ T(0)) {\n                    if ((i & 1) or deg - i / 2 <= 0) return {};\n \
    \                   return (*this >> i).sqrt(deg - i / 2) << (i / 2);\n      \
    \          }\n            return {};\n        }\n        T sqrtf0 = (*this)[0].sqrt();\n\
    \        if (sqrtf0 == T(0)) return {};\n\n        P y = (*this) / (*this)[0],\
    \ ret({T(1)});\n        T inv2 = T(1) / T(2);\n        for (int i = 1; i < deg;\
    \ i <<= 1) ret = (ret + y.pre(i << 1) * ret.inv(i << 1)) * inv2;\n        return\
    \ ret.pre(deg) * sqrtf0;\n    }\n\n    P exp(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        assert(this->empty() or ((*this)[0]) == T(0)); // Requirement:\
    \ F(0) = 0\n        const int n = (int)this->size();\n        if (deg == -1) deg\
    \ = n;\n        P ret({T(1)});\n        for (int i = 1; i < deg; i <<= 1) {\n\
    \            ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);\n\
    \        }\n        return ret.pre(deg);\n    }\n\n    P pow(long long k, int\
    \ deg = -1) const {\n        assert(deg >= -1);\n        const int n = (int)this->size();\n\
    \        if (deg == -1) deg = n;\n\n        if (k == 0) {\n            P ret(deg);\n\
    \            if (deg >= 1) ret[0] = T(1);\n            ret.shrink();\n       \
    \     return ret;\n        }\n\n        for (int i = 0; i < n; i++) {\n      \
    \      if ((*this)[i] != T(0)) {\n                T rev = T(1) / (*this)[i];\n\
    \                P C = (*this) * rev, D(n - i);\n                for (int j =\
    \ i; j < n; j++) D[j - i] = C.coeff(j);\n                D = (D.log(deg) * T(k)).exp(deg)\
    \ * (*this)[i].pow(k);\n                if (__int128(k) * i > deg) return {};\n\
    \                P E(deg);\n                long long S = i * k;\n           \
    \     for (int j = 0; j + S < deg and j < (int)D.size(); j++) E[j + S] = D[j];\n\
    \                E.shrink();\n                return E;\n            }\n     \
    \   }\n        return *this;\n    }\n\n    // Calculate f(X + c) from f(X), O(NlogN)\n\
    \    P shift(T c) const {\n        const int n = (int)this->size();\n        P\
    \ ret = *this;\n        for (int i = 0; i < n; i++) ret[i] *= T(i).fac();\n  \
    \      std::reverse(ret.begin(), ret.end());\n        P exp_cx(n, 1);\n      \
    \  for (int i = 1; i < n; i++) exp_cx[i] = exp_cx[i - 1] * c / i;\n        ret\
    \ = (ret * exp_cx), ret.resize(n);\n        std::reverse(ret.begin(), ret.end());\n\
    \        for (int i = 0; i < n; i++) ret[i] /= T(i).fac();\n        return ret;\n\
    \    }\n\n    T coeff(int i) const {\n        if ((int)this->size() <= i or i\
    \ < 0) return T(0);\n        return (*this)[i];\n    }\n\n    T eval(T x) const\
    \ {\n        T ret = 0, w = 1;\n        for (auto &v : *this) ret += w * v, w\
    \ *= x;\n        return ret;\n    }\n};\n#line 9 \"formal_power_series/test/pow_of_sparse_fps.stress.test.cpp\"\
    \nusing namespace std;\n\nusing mint = ModInt<998244353>;\nusing fps = FormalPowerSeries<mint>;\n\
    \nint main() {\n    for (int nin = 1; nin <= 6; ++nin) {\n        for (int d0\
    \ = 0; d0 <= nin; ++d0) {\n            for (int degout = 0; degout <= 12; ++degout)\
    \ {\n                for (int k = 1; k <= 8; ++k) {\n                    for (int\
    \ iter = 0; iter < 5; ++iter) {\n                        vector<mint> f(nin);\n\
    \                        for (int i = d0; i < nin; ++i) f[i] = rand_int();\n\n\
    \                        auto ret = pow_of_sparse_fps(f, degout, k);\n       \
    \                 auto ret_fps = fps(f.begin(), f.end()).pow(k, degout + 1);\n\
    \                        for (int i = 0; i <= degout; ++i) {\n               \
    \             if (ret[i] != ret_fps.coeff(i)) {\n                            \
    \    cerr << nin << ' ' << d0 << ' ' << degout << ' ' << k << ' '\n          \
    \                           << iter << ' ' << i << ' ' << ret[i] << ' '\n    \
    \                                 << ret_fps.coeff(i) << endl;\n             \
    \                   exit(1);\n                            }\n                \
    \        }\n                    }\n                }\n            }\n        }\n\
    \    }\n    puts(\"Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../pow_of_sparse_fps.hpp\"\n#include \"../../modint.hpp\"\
    \n#include \"../../random/xorshift.hpp\"\n#include \"../formal_power_series.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\n\nusing mint = ModInt<998244353>;\nusing fps = FormalPowerSeries<mint>;\n\
    \nint main() {\n    for (int nin = 1; nin <= 6; ++nin) {\n        for (int d0\
    \ = 0; d0 <= nin; ++d0) {\n            for (int degout = 0; degout <= 12; ++degout)\
    \ {\n                for (int k = 1; k <= 8; ++k) {\n                    for (int\
    \ iter = 0; iter < 5; ++iter) {\n                        vector<mint> f(nin);\n\
    \                        for (int i = d0; i < nin; ++i) f[i] = rand_int();\n\n\
    \                        auto ret = pow_of_sparse_fps(f, degout, k);\n       \
    \                 auto ret_fps = fps(f.begin(), f.end()).pow(k, degout + 1);\n\
    \                        for (int i = 0; i <= degout; ++i) {\n               \
    \             if (ret[i] != ret_fps.coeff(i)) {\n                            \
    \    cerr << nin << ' ' << d0 << ' ' << degout << ' ' << k << ' '\n          \
    \                           << iter << ' ' << i << ' ' << ret[i] << ' '\n    \
    \                                 << ret_fps.coeff(i) << endl;\n             \
    \                   exit(1);\n                            }\n                \
    \        }\n                    }\n                }\n            }\n        }\n\
    \    }\n    puts(\"Hello World\");\n}\n"
  dependsOn:
  - formal_power_series/pow_of_sparse_fps.hpp
  - modint.hpp
  - random/xorshift.hpp
  - formal_power_series/formal_power_series.hpp
  isVerificationFile: true
  path: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
  requiredBy: []
  timestamp: '2022-07-12 00:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
- /verify/formal_power_series/test/pow_of_sparse_fps.stress.test.cpp.html
title: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
---