---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modulus/modint_fixed.hpp
    title: modulus/modint_fixed.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convolution/convolutive_translation_2d.hpp
    title: convolution/convolutive_translation_2d.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/coeff_of_rational_function.hpp
    title: formal_power_series/coeff_of_rational_function.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/formal_power_series.hpp
    title: formal_power_series/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/multipoint_evaluation.hpp
    title: formal_power_series/multipoint_evaluation.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: convolution/test/ntt.test.cpp
    title: convolution/test/ntt.test.cpp
  - icon: ':heavy_check_mark:'
    path: convolution/test/ntt_arbitrary_mod.test.cpp
    title: convolution/test/ntt_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/bernoulli_number.test.cpp
    title: formal_power_series/test/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/coeff_of_rational_function.test.cpp
    title: formal_power_series/test/coeff_of_rational_function.test.cpp
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
    path: formal_power_series/test/kitamasa.test.cpp
    title: formal_power_series/test/kitamasa.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp
    title: formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/polynomial_interpolation.test.cpp
    title: formal_power_series/test/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sharp_p_subset_sum.test.cpp
    title: formal_power_series/test/sharp_p_subset_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modulus/modint_fixed.hpp\"\n#include <iostream>\n#include\
    \ <vector>\n#include <set>\n\n// CUT begin\ntemplate <int mod>\nstruct ModInt\n\
    {\n    using lint = long long;\n    static int get_mod() { return mod; }\n   \
    \ static int get_primitive_root() {\n        static int primitive_root = 0;\n\
    \        if (!primitive_root) {\n            primitive_root = [&](){\n       \
    \         std::set<int> fac;\n                int v = mod - 1;\n             \
    \   for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i), v /= i;\n\
    \                if (v > 1) fac.insert(v);\n                for (int g = 1; g\
    \ < mod; g++) {\n                    bool ok = true;\n                    for\
    \ (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false; break;\
    \ }\n                    if (ok) return g;\n                }\n              \
    \  return -1;\n            }();\n        }\n        return primitive_root;\n \
    \   }\n    int val;\n    constexpr ModInt() : val(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % mod + mod); }\n    explicit operator bool() const\
    \ { return val != 0; }\n    constexpr ModInt operator+(const ModInt &x) const\
    \ { return ModInt()._setval((lint)val + x.val); }\n    constexpr ModInt operator-(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }\n   \
    \ constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ * x.val % mod); }\n    constexpr ModInt operator/(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.inv() % mod); }\n    constexpr ModInt operator-()\
    \ const { return ModInt()._setval(mod - val); }\n    constexpr ModInt &operator+=(const\
    \ ModInt &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const\
    \ ModInt &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const\
    \ ModInt &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const\
    \ ModInt &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod - x.val + mod); }\n    friend constexpr ModInt operator*(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }\n    friend constexpr\
    \ ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.inv() % mod); }\n    constexpr bool operator==(const ModInt &x) const {\
    \ return val == x.val; }\n    constexpr bool operator!=(const ModInt &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModInt &x) const { return\
    \ val < x.val; }  // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }\n\
    \    constexpr lint power(lint n) const {\n        lint ans = 1, tmp = this->val;\n\
    \        while (n) {\n            if (n & 1) ans = ans * tmp % mod;\n        \
    \    tmp = tmp * tmp % mod;\n            n /= 2;\n        }\n        return ans;\n\
    \    }\n    constexpr lint inv() const { return this->power(mod - 2); }\n    constexpr\
    \ ModInt operator^(lint n) const { return ModInt(this->power(n)); }\n    constexpr\
    \ ModInt &operator^=(lint n) { return *this = *this ^ n; }\n\n    inline ModInt\
    \ fac() const {\n        static std::vector<ModInt> facs;\n        int l0 = facs.size();\n\
    \        if (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        if (this->val\
    \ & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();\n  \
    \      else return ModInt(k).fac() * ModInt(2).power(k);\n    }\n\n    ModInt\
    \ nCr(const ModInt &r) const {\n        if (this->val < r.val) return ModInt(0);\n\
    \        return this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n\n// constexpr\
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n#line 3 \"convolution/ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <tuple>\n\
    #line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner = false);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
    \ 469762049};\n\n// Integer FFT (Fast Fourier Transform) for ModInt class\n//\
    \ (Also known as Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n\
    // ** Input size must be 2^n **\ntemplate <typename MODINT>\nvoid ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false)\n{\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::get_mod();\n    static const MODINT root =\
    \ MODINT::get_primitive_root();\n    assert(__builtin_popcount(n) == 1 and (mod\
    \ - 1) % n == 0);\n\n    static std::vector<MODINT> w{1}, iw{1};\n    for (int\
    \ m = w.size(); m < n / 2; m *= 2) {\n        MODINT dw = root.power((mod - 1)\
    \ / (4 * m)), dwinv = 1 / dw;\n        w.resize(m * 2), iw.resize(m * 2);\n  \
    \      for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n\
    \    }\n\n    if (!is_inverse) {\n        for (int m = n; m >>= 1;) {\n      \
    \      for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int\
    \ i = s; i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m]\
    \ * w[k];\n                    a[i] = x + y, a[i + m] = x - y;\n             \
    \   }\n            }\n        }\n    }\n    else {\n        for (int m = 1; m\
    \ < n; m *= 2) {\n            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n\
    \                for (int i = s; i < s + m; i++) {\n                    MODINT\
    \ x = a[i], y = a[i + m];\n                    a[i] = x + y, a[i + m] = (x - y)\
    \ * iw[k];\n                }\n            }\n        }\n        int n_inv = MODINT(n).inv();\n\
    \        for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b) bp = ap;\n\
    \    else ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i] *= bp[i];\n\
    \    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int r0, int r1,\
    \ int r2, int mod)\n{\n    using mint2 = ModInt<nttprimes[2]>;\n    static const\
    \ long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static const long long\
    \ m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n    static const long\
    \ long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1 * (r1 + nttprimes[1]\
    \ - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0])\
    \ * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod *\
    \ v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner)\n{\n    int sz = 1, n = a.size(),\
    \ m = b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n     \
    \   std::vector<MODINT> ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n\
    \            for (int j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n\
    \        return ret;\n    }\n    int mod = MODINT::get_mod();\n    if (skip_garner\
    \ or std::find(std::begin(nttprimes), std::end(nttprimes), mod) != std::end(nttprimes))\n\
    \    {\n        a.resize(sz), b.resize(sz);\n        if (a == b) { ntt(a, false);\
    \ b = a; }\n        else ntt(a, false), ntt(b, false);\n        for (int i = 0;\
    \ i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n + m -\
    \ 1);\n    }\n    else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\
    \ {\n            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n\
    \        }\n    }\n    return a;\n}\n"
  code: "#pragma once\n#include \"modulus/modint_fixed.hpp\"\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <tuple>\n#include <vector>\n\n\
    // CUT begin\n// Integer convolution for arbitrary mod\n// with NTT (and Garner's\
    \ algorithm) for ModInt / ModIntRuntime class.\n// We skip Garner's algorithm\
    \ if `skip_garner` is true or mod is in `nttprimes`.\n// input: a (size: n), b\
    \ (size: m)\n// return: vector (size: n + m - 1)\ntemplate <typename MODINT>\n\
    std::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool\
    \ skip_garner = false);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
    \ 469762049};\n\n// Integer FFT (Fast Fourier Transform) for ModInt class\n//\
    \ (Also known as Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n\
    // ** Input size must be 2^n **\ntemplate <typename MODINT>\nvoid ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false)\n{\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::get_mod();\n    static const MODINT root =\
    \ MODINT::get_primitive_root();\n    assert(__builtin_popcount(n) == 1 and (mod\
    \ - 1) % n == 0);\n\n    static std::vector<MODINT> w{1}, iw{1};\n    for (int\
    \ m = w.size(); m < n / 2; m *= 2) {\n        MODINT dw = root.power((mod - 1)\
    \ / (4 * m)), dwinv = 1 / dw;\n        w.resize(m * 2), iw.resize(m * 2);\n  \
    \      for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n\
    \    }\n\n    if (!is_inverse) {\n        for (int m = n; m >>= 1;) {\n      \
    \      for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int\
    \ i = s; i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m]\
    \ * w[k];\n                    a[i] = x + y, a[i + m] = x - y;\n             \
    \   }\n            }\n        }\n    }\n    else {\n        for (int m = 1; m\
    \ < n; m *= 2) {\n            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n\
    \                for (int i = s; i < s + m; i++) {\n                    MODINT\
    \ x = a[i], y = a[i + m];\n                    a[i] = x + y, a[i + m] = (x - y)\
    \ * iw[k];\n                }\n            }\n        }\n        int n_inv = MODINT(n).inv();\n\
    \        for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b) bp = ap;\n\
    \    else ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i] *= bp[i];\n\
    \    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int r0, int r1,\
    \ int r2, int mod)\n{\n    using mint2 = ModInt<nttprimes[2]>;\n    static const\
    \ long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static const long long\
    \ m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n    static const long\
    \ long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1 * (r1 + nttprimes[1]\
    \ - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0])\
    \ * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod *\
    \ v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner)\n{\n    int sz = 1, n = a.size(),\
    \ m = b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n     \
    \   std::vector<MODINT> ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n\
    \            for (int j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n\
    \        return ret;\n    }\n    int mod = MODINT::get_mod();\n    if (skip_garner\
    \ or std::find(std::begin(nttprimes), std::end(nttprimes), mod) != std::end(nttprimes))\n\
    \    {\n        a.resize(sz), b.resize(sz);\n        if (a == b) { ntt(a, false);\
    \ b = a; }\n        else ntt(a, false), ntt(b, false);\n        for (int i = 0;\
    \ i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n + m -\
    \ 1);\n    }\n    else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\
    \ {\n            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n\
    \        }\n    }\n    return a;\n}\n"
  dependsOn:
  - modulus/modint_fixed.hpp
  isVerificationFile: false
  path: convolution/ntt.hpp
  requiredBy:
  - convolution/convolutive_translation_2d.hpp
  - formal_power_series/multipoint_evaluation.hpp
  - formal_power_series/coeff_of_rational_function.hpp
  - formal_power_series/formal_power_series.hpp
  timestamp: '2020-09-29 00:37:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - convolution/test/ntt_arbitrary_mod.test.cpp
  - convolution/test/ntt.test.cpp
  - formal_power_series/test/fps_pow_another.test.cpp
  - formal_power_series/test/multipoint_evaluation_arbitrary_mod.test.cpp
  - formal_power_series/test/fps_inv.test.cpp
  - formal_power_series/test/fps_exp_modintruntime.test.cpp
  - formal_power_series/test/fps_log.test.cpp
  - formal_power_series/test/sharp_p_subset_sum.test.cpp
  - formal_power_series/test/fps_sqrt_modintruntime.test.cpp
  - formal_power_series/test/fps_sqrt.test.cpp
  - formal_power_series/test/fps_exp.test.cpp
  - formal_power_series/test/division_number.test.cpp
  - formal_power_series/test/polynomial_interpolation.test.cpp
  - formal_power_series/test/fps_pow.test.cpp
  - formal_power_series/test/bernoulli_number.test.cpp
  - formal_power_series/test/coeff_of_rational_function.test.cpp
  - formal_power_series/test/kitamasa.test.cpp
documentation_of: convolution/ntt.hpp
layout: document
redirect_from:
- /library/convolution/ntt.hpp
- /library/convolution/ntt.hpp.html
title: convolution/ntt.hpp
---
