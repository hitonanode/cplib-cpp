---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/pow_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/pow_of_formal_power_series
  bundledCode: "#line 1 \"formal_power_series/test/fps_pow.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/pow_of_formal_power_series\"\n#line 2 \"modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \ntemplate <int md> struct ModInt {\n    using lint = long long;\n    constexpr\
    \ static int mod() { return md; }\n    static int get_primitive_root() {\n   \
    \     static int primitive_root = 0;\n        if (!primitive_root) {\n       \
    \     primitive_root = [&]() {\n                std::set<int> fac;\n         \
    \       int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n \
    \                   while (v % i == 0) fac.insert(i), v /= i;\n              \
    \  if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    constexpr\
    \ ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint v) { return val_ =\
    \ (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint v) { _setval(v %\
    \ md + md); }\n    constexpr explicit operator bool() const { return val_ != 0;\
    \ }\n    constexpr ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    constexpr ModInt operator-(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    constexpr ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    constexpr ModInt operator-() const { return ModInt()._setval(md - val_);\
    \ }\n    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this\
    \ + x; }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint a,\
    \ const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
    \ a, const ModInt &x) { return ModInt(a) / x; }\n    constexpr bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    constexpr bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    constexpr bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    constexpr\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n\n    constexpr ModInt pow(lint n) const {\n\
    \        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n\
    \ & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static constexpr int cache_limit = std::min(md, 1 << 21);\n\
    \    static std::vector<ModInt> facs, facinvs, invs;\n\n    constexpr static void\
    \ _precalculation(int N) {\n        const int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr\
    \ ModInt inv() const {\n        if (this->val_ < cache_limit) {\n            if\
    \ (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n            while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val_];\n\
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n \
    \   constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val_];\n    }\n\
    \    constexpr ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    constexpr ModInt doublefac() const {\n        lint k = (this->val_ +\
    \ 1) / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr ModInt nCr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv() *\
    \ ModInt(r).facinv();\n    }\n\n    constexpr ModInt nPr(int r) const {\n    \
    \    if (r < 0 or this->val_ < r) return ModInt(0);\n        return this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    static ModInt binom(int n, int r) {\n\
    \        static long long bruteforce_times = 0;\n\n        if (r < 0 or n < r)\
    \ return ModInt(0);\n        if (n <= bruteforce_times or n < (int)facs.size())\
    \ return ModInt(n).nCr(r);\n\n        r = std::min(r, n - r);\n\n        ModInt\
    \ ret = ModInt(r).facinv();\n        for (int i = 0; i < r; ++i) ret *= n - i;\n\
    \        bruteforce_times += r;\n\n        return ret;\n    }\n\n    // Multinomial\
    \ coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n    // Complexity:\
    \ O(sum(ks))\n    template <class Vec> static ModInt multinomial(const Vec &ks)\
    \ {\n        ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n\
    \            assert(k >= 0);\n            ret *= ModInt(k).facinv(), sum += k;\n\
    \        }\n        return ret * ModInt(sum).fac();\n    }\n\n    // Catalan number,\
    \ C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4\
    \ = 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt(n * 2).fac() * ModInt(n + 1).facinv() * ModInt(n).facinv();\n    }\n\n\
    \    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
    \ 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n        ModInt\
    \ b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0,\
    \ m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j\
    \ - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val_, md - x.val_));\n    }\n};\ntemplate <int\
    \ md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\ntemplate <int md> std::vector<ModInt<md>>\
    \ ModInt<md>::facinvs = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::invs\
    \ = {0};\n\nusing ModInt998244353 = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n\
    // using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\n\n#include\
    \ <algorithm>\n#include <array>\n#line 7 \"convolution/ntt.hpp\"\n#include <tuple>\n\
    #line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
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
    \            }\n        }\n        int n_inv = MODINT(n).inv().val();\n      \
    \  for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
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
    \ i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];\n        return *this;\n\
    \    }\n    P &operator+=(const T &v) {\n        if (this->empty()) this->resize(1);\n\
    \        (*this)[0] += v;\n        return *this;\n    }\n    P &operator-=(const\
    \ P &r) {\n        if (r.size() > this->size()) this->resize(r.size());\n    \
    \    for (int i = 0; i < (int)r.size(); i++) (*this)[i] -= r[i];\n        return\
    \ *this;\n    }\n    P &operator-=(const T &v) {\n        if (this->empty()) this->resize(1);\n\
    \        (*this)[0] -= v;\n        return *this;\n    }\n    P &operator*=(const\
    \ T &v) {\n        for (auto &x : (*this)) x *= v;\n        return *this;\n  \
    \  }\n    P &operator*=(const P &r) {\n        if (this->empty() || r.empty())\n\
    \            this->clear();\n        else {\n            auto ret = nttconv(*this,\
    \ r);\n            *this = P(ret.begin(), ret.end());\n        }\n        return\
    \ *this;\n    }\n    P &operator%=(const P &r) {\n        *this -= *this / r *\
    \ r;\n        return *this;\n    }\n    P operator-() const {\n        P ret =\
    \ *this;\n        for (auto &v : ret) v = -v;\n        return ret;\n    }\n  \
    \  P &operator/=(const T &v) {\n        assert(v != T(0));\n        for (auto\
    \ &x : (*this)) x /= v;\n        return *this;\n    }\n    P &operator/=(const\
    \ P &r) {\n        if (this->size() < r.size()) {\n            this->clear();\n\
    \            return *this;\n        }\n        int n = (int)this->size() - r.size()\
    \ + 1;\n        return *this = (reversed().pre(n) * r.reversed().inv(n)).pre(n).reversed(n);\n\
    \    }\n    P pre(int sz) const {\n        P ret(this->begin(), this->begin()\
    \ + std::min((int)this->size(), sz));\n        return ret;\n    }\n    P operator>>(int\
    \ sz) const {\n        if ((int)this->size() <= sz) return {};\n        return\
    \ P(this->begin() + sz, this->end());\n    }\n    P operator<<(int sz) const {\n\
    \        if (this->empty()) return {};\n        P ret(*this);\n        ret.insert(ret.begin(),\
    \ sz, T(0));\n        return ret;\n    }\n\n    P reversed(int sz = -1) const\
    \ {\n        assert(sz >= -1);\n        P ret(*this);\n        if (sz != -1) ret.resize(sz,\
    \ T());\n        std::reverse(ret.begin(), ret.end());\n        return ret;\n\
    \    }\n\n    P differential() const { // formal derivative (differential) of\
    \ f.p.s.\n        const int n = (int)this->size();\n        P ret(std::max(0,\
    \ n - 1));\n        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);\n\
    \        return ret;\n    }\n\n    P integral() const {\n        const int n =\
    \ (int)this->size();\n        P ret(n + 1);\n        ret[0] = T(0);\n        for\
    \ (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n        return\
    \ ret;\n    }\n\n    /**\n     * @brief f(x)g(x) = 1 (mod x^deg)\n     *\n   \
    \  * @param deg\n     * @return P ret.size() == deg\n     */\n    P inv(int deg)\
    \ const {\n        assert(deg >= -1);\n        if (deg == 0) return {};\n\n  \
    \      assert(this->size() and this->at(0) != T()); // Requirement: F(0) != 0\n\
    \        const int n = this->size();\n        if (deg == -1) deg = n;\n\n    \
    \    P ret({T(1) / this->at(0)});\n        for (int i = 1; i < deg; i <<= 1) {\n\
    \            auto h = (pre(i << 1) * ret).pre(i << 1) >> i;\n            auto\
    \ tmp = (-h * ret).pre(i);\n            ret.insert(ret.end(), tmp.cbegin(), tmp.cend());\n\
    \            ret.resize(i << 1);\n        }\n        return ret.pre(deg);\n  \
    \  }\n\n    P log(int len = -1) const {\n        assert(len >= -1);\n        if\
    \ (len == 0) return {};\n\n        assert(this->size() and ((*this)[0]) == T(1));\
    \ // Requirement: F(0) = 1\n\n        const int n = (int)this->size();\n     \
    \   if (len == 0) return {};\n        if (len == -1) len = n;\n        return\
    \ (this->differential() * this->inv(len)).pre(len - 1).integral();\n    }\n\n\
    \    P sqrt(int deg = -1) const {\n        assert(deg >= -1);\n        const int\
    \ n = (int)this->size();\n        if (deg == -1) deg = n;\n        if (this->empty())\
    \ return {};\n        if ((*this)[0] == T(0)) {\n            for (int i = 1; i\
    \ < n; i++)\n                if ((*this)[i] != T(0)) {\n                    if\
    \ ((i & 1) or deg - i / 2 <= 0) return {};\n                    return (*this\
    \ >> i).sqrt(deg - i / 2) << (i / 2);\n                }\n            return {};\n\
    \        }\n        T sqrtf0 = (*this)[0].sqrt();\n        if (sqrtf0 == T(0))\
    \ return {};\n\n        P y = (*this) / (*this)[0], ret({T(1)});\n        T inv2\
    \ = T(1) / T(2);\n        for (int i = 1; i < deg; i <<= 1) ret = (ret + y.pre(i\
    \ << 1) * ret.inv(i << 1)) * inv2;\n        return ret.pre(deg) * sqrtf0;\n  \
    \  }\n\n    P exp(int deg = -1) const {\n        assert(deg >= -1);\n        assert(this->empty()\
    \ or ((*this)[0]) == T(0)); // Requirement: F(0) = 0\n        const int n = (int)this->size();\n\
    \        if (deg == -1) deg = n;\n        P ret({T(1)});\n        for (int i =\
    \ 1; i < deg; i <<= 1) {\n            ret = (ret * (pre(i << 1) + T(1) - ret.log(i\
    \ << 1))).pre(i << 1);\n        }\n        return ret.pre(deg);\n    }\n\n   \
    \ P pow(long long k, int deg = -1) const {\n        assert(deg >= -1);\n     \
    \   const int n = (int)this->size();\n        if (deg == -1) deg = n;\n\n    \
    \    if (k == 0) {\n            P ret(deg);\n            if (deg >= 1) ret[0]\
    \ = T(1);\n            ret.shrink();\n            return ret;\n        }\n\n \
    \       for (int i = 0; i < n; i++) {\n            if ((*this)[i] != T(0)) {\n\
    \                T rev = T(1) / (*this)[i];\n                P C = (*this) * rev,\
    \ D(n - i);\n                for (int j = i; j < n; j++) D[j - i] = C.coeff(j);\n\
    \                D = (D.log(deg) * T(k)).exp(deg) * (*this)[i].pow(k);\n     \
    \           if (__int128(k) * i > deg) return {};\n                P E(deg);\n\
    \                long long S = i * k;\n                for (int j = 0; j + S <\
    \ deg and j < (int)D.size(); j++) E[j + S] = D[j];\n                E.shrink();\n\
    \                return E;\n            }\n        }\n        return *this;\n\
    \    }\n\n    // Calculate f(X + c) from f(X), O(NlogN)\n    P shift(T c) const\
    \ {\n        const int n = (int)this->size();\n        P ret = *this;\n      \
    \  for (int i = 0; i < n; i++) ret[i] *= T(i).fac();\n        std::reverse(ret.begin(),\
    \ ret.end());\n        P exp_cx(n, 1);\n        for (int i = 1; i < n; i++) exp_cx[i]\
    \ = exp_cx[i - 1] * c * T(i).inv();\n        ret = ret * exp_cx;\n        ret.resize(n);\n\
    \        std::reverse(ret.begin(), ret.end());\n        for (int i = 0; i < n;\
    \ i++) ret[i] *= T(i).facinv();\n        return ret;\n    }\n\n    T coeff(int\
    \ i) const {\n        if ((int)this->size() <= i or i < 0) return T(0);\n    \
    \    return (*this)[i];\n    }\n\n    T eval(T x) const {\n        T ret = 0,\
    \ w = 1;\n        for (auto &v : *this) ret += w * v, w *= x;\n        return\
    \ ret;\n    }\n};\n#line 5 \"formal_power_series/test/fps_pow.test.cpp\"\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    long long M;\n    cin >> N >> M;\n    FormalPowerSeries<ModInt<998244353>>\
    \ A(N);\n    for (auto &a : A) cin >> a;\n    auto ret = A.pow(M, N);\n    for\
    \ (int i = 0; i < N; i++) cout << ret.coeff(i) << ' ';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/pow_of_formal_power_series\"\
    \n#include \"formal_power_series/formal_power_series.hpp\"\n#include \"modint.hpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N;\n    long long M;\n    cin >> N >>\
    \ M;\n    FormalPowerSeries<ModInt<998244353>> A(N);\n    for (auto &a : A) cin\
    \ >> a;\n    auto ret = A.pow(M, N);\n    for (int i = 0; i < N; i++) cout <<\
    \ ret.coeff(i) << ' ';\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: formal_power_series/test/fps_pow.test.cpp
  requiredBy: []
  timestamp: '2023-08-22 20:41:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/fps_pow.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/fps_pow.test.cpp
- /verify/formal_power_series/test/fps_pow.test.cpp.html
title: formal_power_series/test/fps_pow.test.cpp
---
