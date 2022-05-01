---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
    #define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long\
    \ long;\n    MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
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
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    MDCONST\
    \ ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint v) { return val_ = (v\
    \ >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md +\
    \ md); }\n    MDCONST explicit operator bool() const { return val_ != 0; }\n \
    \   MDCONST ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    MDCONST ModInt operator-(const ModInt &x) const {\n \
    \       return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    MDCONST ModInt operator-() const { return ModInt()._setval(md - val_); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST ModInt operator-(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md - x.val_ + md);\n\
    \    }\n    friend MDCONST ModInt operator*(lint a, const ModInt &x) {\n     \
    \   return ModInt()._setval(a % md * x.val_ % md);\n    }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const ModInt\
    \ &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const ModInt\
    \ &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const ModInt\
    \ &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
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
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <tuple>\n\
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
    \ b, false);\n}\n#line 4 \"convolution/convolutive_translation_2d.hpp\"\n#include\
    \ <utility>\n#line 6 \"convolution/convolutive_translation_2d.hpp\"\n\n// Two\
    \ dimensional fast DP using FFT.\n// Complexity: O(HW log (HW)) for each step.\n\
    // Verification: TCO 2020 Round 3A 1000 ZombieRPGDice\n// Verification: TCO 2020\
    \ Round 3B 500 ShortBugPaths\ntemplate <typename MODINT>\nstd::vector<std::vector<MODINT>>\n\
    convolutive_translation_2d(const std::vector<std::vector<MODINT>> &initial_dist,\
    \ // size: H * W\n                           const std::vector<std::pair<std::pair<int,\
    \ int>, MODINT>>\n                               &trans_coeffs, // [((dx, dy),\
    \ coefficient), ...]\n                           int nb_step = 1) {\n    int H\
    \ = initial_dist.size(), W = initial_dist[0].size();\n    int xlo = 0, xhi = 0,\
    \ ylo = 0, yhi = 0;\n\n    std::vector<std::pair<std::pair<int, int>, MODINT>>\
    \ t2c_1d;\n    for (auto p : trans_coeffs)\n        if (p.second != 0) {\n   \
    \         if (p.first.first <= -H or p.first.first >= H) continue;\n         \
    \   if (p.first.second <= -W or p.first.second >= W) continue;\n            xlo\
    \ = std::max(xlo, -p.first.first), xhi = std::max(xhi, p.first.first);\n     \
    \       ylo = std::max(ylo, -p.first.second), yhi = std::max(yhi, p.first.second);\n\
    \            t2c_1d.emplace_back(p);\n        }\n    const int WW = W + ylo +\
    \ yhi;\n    std::vector<MODINT> dp((H - 1) * WW + W);\n    for (int i = 0; i <\
    \ H; i++) {\n        std::copy(initial_dist[i].begin(), initial_dist[i].end(),\
    \ dp.begin() + i * WW);\n    }\n\n    int tlo = 0, thi = 0;\n    for (auto p :\
    \ t2c_1d) {\n        int t = p.first.first * WW + p.first.second;\n        tlo\
    \ = std::max(tlo, -t), thi = std::max(thi, t);\n    }\n\n    std::vector<MODINT>\
    \ trans1d(tlo + thi + 1);\n    for (auto p : t2c_1d) { trans1d[tlo + p.first.first\
    \ * WW + p.first.second] += p.second; }\n    for (int t = 0; t < nb_step; t++)\
    \ {\n        auto dp_nxt = nttconv(dp, trans1d);\n        for (int i = 0; i <\
    \ H; i++) {\n            std::copy(dp_nxt.begin() + i * WW + tlo, dp_nxt.begin()\
    \ + i * WW + W + tlo,\n                      dp.begin() + i * WW);\n        }\n\
    \    }\n    std::vector<std::vector<MODINT>> ret(H);\n    for (int i = 0; i <\
    \ H; i++) {\n        ret[i].insert(ret[i].end(), dp.begin() + i * WW, dp.begin()\
    \ + i * WW + W);\n    }\n    return ret;\n}\n"
  code: "#pragma once\n#include \"convolution/ntt.hpp\"\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\n// Two dimensional fast DP using FFT.\n// Complexity:\
    \ O(HW log (HW)) for each step.\n// Verification: TCO 2020 Round 3A 1000 ZombieRPGDice\n\
    // Verification: TCO 2020 Round 3B 500 ShortBugPaths\ntemplate <typename MODINT>\n\
    std::vector<std::vector<MODINT>>\nconvolutive_translation_2d(const std::vector<std::vector<MODINT>>\
    \ &initial_dist, // size: H * W\n                           const std::vector<std::pair<std::pair<int,\
    \ int>, MODINT>>\n                               &trans_coeffs, // [((dx, dy),\
    \ coefficient), ...]\n                           int nb_step = 1) {\n    int H\
    \ = initial_dist.size(), W = initial_dist[0].size();\n    int xlo = 0, xhi = 0,\
    \ ylo = 0, yhi = 0;\n\n    std::vector<std::pair<std::pair<int, int>, MODINT>>\
    \ t2c_1d;\n    for (auto p : trans_coeffs)\n        if (p.second != 0) {\n   \
    \         if (p.first.first <= -H or p.first.first >= H) continue;\n         \
    \   if (p.first.second <= -W or p.first.second >= W) continue;\n            xlo\
    \ = std::max(xlo, -p.first.first), xhi = std::max(xhi, p.first.first);\n     \
    \       ylo = std::max(ylo, -p.first.second), yhi = std::max(yhi, p.first.second);\n\
    \            t2c_1d.emplace_back(p);\n        }\n    const int WW = W + ylo +\
    \ yhi;\n    std::vector<MODINT> dp((H - 1) * WW + W);\n    for (int i = 0; i <\
    \ H; i++) {\n        std::copy(initial_dist[i].begin(), initial_dist[i].end(),\
    \ dp.begin() + i * WW);\n    }\n\n    int tlo = 0, thi = 0;\n    for (auto p :\
    \ t2c_1d) {\n        int t = p.first.first * WW + p.first.second;\n        tlo\
    \ = std::max(tlo, -t), thi = std::max(thi, t);\n    }\n\n    std::vector<MODINT>\
    \ trans1d(tlo + thi + 1);\n    for (auto p : t2c_1d) { trans1d[tlo + p.first.first\
    \ * WW + p.first.second] += p.second; }\n    for (int t = 0; t < nb_step; t++)\
    \ {\n        auto dp_nxt = nttconv(dp, trans1d);\n        for (int i = 0; i <\
    \ H; i++) {\n            std::copy(dp_nxt.begin() + i * WW + tlo, dp_nxt.begin()\
    \ + i * WW + W + tlo,\n                      dp.begin() + i * WW);\n        }\n\
    \    }\n    std::vector<std::vector<MODINT>> ret(H);\n    for (int i = 0; i <\
    \ H; i++) {\n        ret[i].insert(ret[i].end(), dp.begin() + i * WW, dp.begin()\
    \ + i * WW + W);\n    }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/convolutive_translation_2d.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convolution/convolutive_translation_2d.hpp
layout: document
redirect_from:
- /library/convolution/convolutive_translation_2d.hpp
- /library/convolution/convolutive_translation_2d.hpp.html
title: convolution/convolutive_translation_2d.hpp
---
