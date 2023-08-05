---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: convolution/test/semirelaxed_multiplication.test.cpp
    title: convolution/test/semirelaxed_multiplication.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c
  bundledCode: "#line 2 \"convolution/semirelaxed_multiplication.hpp\"\n\n#line 2\
    \ \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\ntemplate <int md> struct ModInt {\n    using lint = long long;\n\
    \    constexpr static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
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
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md + x.val_);\n    }\n    friend constexpr\
    \ ModInt operator-(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md - x.val_ + md);\n    }\n    friend constexpr ModInt operator*(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.val_ % md);\n    }\n\
    \    friend constexpr ModInt operator/(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md * x.inv().val() % md);\n    }\n    constexpr bool operator==(const\
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
    \ b, false);\n}\n#line 5 \"convolution/semirelaxed_multiplication.hpp\"\n\n//\
    \ Calculate g = a * f, where f is given online\n// Complexity: O(n (log n)^2)\n\
    // https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\ntemplate <class NTTModInt>\
    \ struct semirelaxed_multiplication {\n\n    int maxd = 0;\n    std::vector<NTTModInt>\
    \ a, f, g;\n    std::vector<std::vector<NTTModInt>> antt;\n\n    const std::vector<NTTModInt>\
    \ &get_antt(int d) {\n        while (int(antt.size()) <= d) {\n            const\
    \ int D = antt.size(), fftlen = 1 << (D + 1),\n                      use_len =\
    \ std::min<int>(fftlen, a.size());\n            std::vector<NTTModInt> v(a.begin(),\
    \ a.begin() + use_len);\n            v.resize(fftlen);\n            ntt(v, false);\n\
    \            antt.push_back(v);\n        }\n        return antt.at(d);\n    }\n\
    \n    semirelaxed_multiplication(const std::vector<NTTModInt> &a_) : a(a_) {\n\
    \        while (1 << maxd < int(a.size())) ++maxd;\n    }\n\n    NTTModInt add(NTTModInt\
    \ f_i) {\n        f.push_back(f_i);\n        const int n = f.size(), d = std::min(maxd,\
    \ __builtin_ctz(n));\n        if (size_t gsz = n - 1 + (1 << d); g.size() < gsz)\
    \ g.resize(gsz);\n\n        // Convolve a[0, 2 ** (d + 1)) * f[n + 1 - 2 ** d,\
    \ n + 1) -> g[n, n + 2 ** d)\n        if (d <= 4) {\n            for (int i =\
    \ n - (1 << d); i < n; ++i) {\n                for (int k = n - 1; k < n - 1 +\
    \ (1 << d) and k - i < int(a.size()); ++k) {\n                    g.at(k) += f.at(i)\
    \ * a.at(k - i);\n                }\n            }\n        } else {\n       \
    \     std::vector<NTTModInt> tmp{f.end() - (1 << d), f.end()};\n            tmp.resize(1\
    \ << (d + 1));\n            ntt(tmp, false);\n            const auto &ntta = get_antt(d);\n\
    \            for (int i = 0; i < int(tmp.size()); ++i) tmp.at(i) *= ntta.at(i);\n\
    \            ntt(tmp, true);\n\n            for (int i = 0; i < (1 << d); ++i)\
    \ g.at(n - 1 + i) += tmp.at((1 << d) - 1 + i);\n        }\n\n        return g.at(n\
    \ - 1);\n    }\n};\n"
  code: "#pragma once\n\n#include \"ntt.hpp\"\n#include <vector>\n\n// Calculate g\
    \ = a * f, where f is given online\n// Complexity: O(n (log n)^2)\n// https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c\n\
    template <class NTTModInt> struct semirelaxed_multiplication {\n\n    int maxd\
    \ = 0;\n    std::vector<NTTModInt> a, f, g;\n    std::vector<std::vector<NTTModInt>>\
    \ antt;\n\n    const std::vector<NTTModInt> &get_antt(int d) {\n        while\
    \ (int(antt.size()) <= d) {\n            const int D = antt.size(), fftlen = 1\
    \ << (D + 1),\n                      use_len = std::min<int>(fftlen, a.size());\n\
    \            std::vector<NTTModInt> v(a.begin(), a.begin() + use_len);\n     \
    \       v.resize(fftlen);\n            ntt(v, false);\n            antt.push_back(v);\n\
    \        }\n        return antt.at(d);\n    }\n\n    semirelaxed_multiplication(const\
    \ std::vector<NTTModInt> &a_) : a(a_) {\n        while (1 << maxd < int(a.size()))\
    \ ++maxd;\n    }\n\n    NTTModInt add(NTTModInt f_i) {\n        f.push_back(f_i);\n\
    \        const int n = f.size(), d = std::min(maxd, __builtin_ctz(n));\n     \
    \   if (size_t gsz = n - 1 + (1 << d); g.size() < gsz) g.resize(gsz);\n\n    \
    \    // Convolve a[0, 2 ** (d + 1)) * f[n + 1 - 2 ** d, n + 1) -> g[n, n + 2 **\
    \ d)\n        if (d <= 4) {\n            for (int i = n - (1 << d); i < n; ++i)\
    \ {\n                for (int k = n - 1; k < n - 1 + (1 << d) and k - i < int(a.size());\
    \ ++k) {\n                    g.at(k) += f.at(i) * a.at(k - i);\n            \
    \    }\n            }\n        } else {\n            std::vector<NTTModInt> tmp{f.end()\
    \ - (1 << d), f.end()};\n            tmp.resize(1 << (d + 1));\n            ntt(tmp,\
    \ false);\n            const auto &ntta = get_antt(d);\n            for (int i\
    \ = 0; i < int(tmp.size()); ++i) tmp.at(i) *= ntta.at(i);\n            ntt(tmp,\
    \ true);\n\n            for (int i = 0; i < (1 << d); ++i) g.at(n - 1 + i) +=\
    \ tmp.at((1 << d) - 1 + i);\n        }\n\n        return g.at(n - 1);\n    }\n\
    };\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  isVerificationFile: false
  path: convolution/semirelaxed_multiplication.hpp
  requiredBy: []
  timestamp: '2023-08-05 18:05:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - convolution/test/semirelaxed_multiplication.test.cpp
documentation_of: convolution/semirelaxed_multiplication.hpp
layout: document
title: "Semi-relaxed multiplication / semi-relaxed convolution \uFF08\u7247\u65B9\u5148\
  \u8AAD\u307F\u53EF\u80FD\u306A\u5834\u5408\u306E\u30AA\u30F3\u30E9\u30A4\u30F3\u7573\
  \u307F\u8FBC\u307F\uFF09"
---

## 解いてくれる問題

FFT 可能な数列 $a = (a\_0, a\_1, \ldots, a\_{n - 1})$ と $f = (f\_0, f\_1, \ldots, f\_{m - 1})$ を畳み込む． $a$ は全て既知であることを要請． $f$ の第 $i$ 項までを求めた時点で $g = a * f$ の第 $i$ 項までが取得可能．計算量は $O((n + m) (\log \min(n, m))^2)$．

## 文献・リンク集

- [オンライン畳み込み - Qiita](https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c)