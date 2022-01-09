---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/factorial_power.hpp
    title: "factorial power \uFF08\u968E\u4E57\u51AA\u306B\u95A2\u3059\u308B\u6F14\
      \u7B97\uFF09"
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
    links:
    - https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial
  bundledCode: "#line 1 \"formal_power_series/test/shift_of_sampling_points.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial\"\
    \n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
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
    \    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n    MDCONST ModInt &_setval(lint\
    \ v) { return val = (v >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint\
    \ v) { _setval(v % md + md); }\n    MDCONST explicit operator bool() const { return\
    \ val != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const {\n       \
    \ return ModInt()._setval((lint)val - x.val + md);\n    }\n    MDCONST ModInt\
    \ operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ * x.val % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val * x.inv() % md);\n    }\n    MDCONST\
    \ ModInt operator-() const { return ModInt()._setval(md - val); }\n    MDCONST\
    \ ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n    MDCONST\
    \ ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n    MDCONST\
    \ ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n    MDCONST\
    \ ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend\
    \ MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md + x.val);\n    }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md - x.val + md);\n    }\n    friend\
    \ MDCONST ModInt operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.val % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.inv() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val == x.val; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val != x.val; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val < x.val;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST lint inv() const {\n        if (this->val < std::min(md >>\
    \ 1, 1 << 21)) {\n            while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val].val;\n        } else {\n         \
    \   return this->pow(md - 2).val;\n        }\n    }\n    MDCONST ModInt fac()\
    \ const {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[this->val];\n    }\n    MDCONST ModInt facinv() const\
    \ {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facinvs[this->val];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val + 1) / 2;\n        return (this->val &\
    \ 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n          \
    \                     : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val\
    \ == 0) return 0;\n        if (md == 2) return val;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
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
    \            }\n        }\n        int n_inv = MODINT(n).inv();\n        for (auto\
    \ &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n    static\
    \ const long long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1 *\
    \ (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0])\
    \ * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod *\
    \ v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner) {\n    if (a.empty() or b.empty())\
    \ return {};\n    int sz = 1, n = a.size(), m = b.size();\n    while (sz < n +\
    \ m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT> ret(n + m - 1);\n\
    \        for (int i = 0; i < n; i++) {\n            for (int j = 0; j < m; j++)\
    \ ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n    }\n    int mod\
    \ = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 5 \"formal_power_series/factorial_power.hpp\"\n\n// CUT\
    \ begin\n// Convert factorial power -> sampling\n// [y[0], y[1], ..., y[N - 1]]\
    \ -> \\sum_i a_i x^\\underline{i}\n// Complexity: O(N log N)\ntemplate <class\
    \ T> std::vector<T> factorial_to_ys(const std::vector<T> &as) {\n    const int\
    \ N = as.size();\n    std::vector<T> exp(N, 1);\n    for (int i = 1; i < N; i++)\
    \ exp[i] = T(i).facinv();\n    auto ys = nttconv(as, exp);\n    ys.resize(N);\n\
    \    for (int i = 0; i < N; i++) ys[i] *= T(i).fac();\n    return ys;\n}\n\n//\
    \ Convert sampling -> factorial power\n// [y[0], y[1], ..., y[N - 1]] -> \\sum_i\
    \ a_i x^\\underline{i}\n// Complexity: O(N log N)\ntemplate <class T> std::vector<T>\
    \ ys_to_factorial(std::vector<T> ys) {\n    const int N = ys.size();\n    for\
    \ (int i = 1; i < N; i++) ys[i] *= T(i).facinv();\n    std::vector<T> expinv(N,\
    \ 1);\n    for (int i = 1; i < N; i++) expinv[i] = T(i).facinv() * (i % 2 ? -1\
    \ : 1);\n    auto as = nttconv(ys, expinv);\n    as.resize(N);\n    return as;\n\
    }\n\n// Compute factorial power series of f(x + shift) from that of f(x)\n// Complexity:\
    \ O(N log N)\ntemplate <class T> std::vector<T> shift_of_factorial(const std::vector<T>\
    \ &as, T shift) {\n    const int N = as.size();\n    std::vector<T> b(N, 1), c(N,\
    \ 1);\n    for (int i = 1; i < N; i++) b[i] = b[i - 1] * (shift - i + 1) * T(i).inv();\n\
    \    for (int i = 0; i < N; i++) c[i] = as[i] * T(i).fac();\n    std::reverse(c.begin(),\
    \ c.end());\n    auto ret = nttconv(b, c);\n    ret.resize(N);\n    std::reverse(ret.begin(),\
    \ ret.end());\n    for (int i = 0; i < N; i++) ret[i] *= T(i).facinv();\n    return\
    \ ret;\n}\n\n// Compute y[c], ..., y[c + width - 1] from y[0], ..., y[N - 1] where\
    \ y = f(x) is poly of up to\n// (N - 1)-th degree Complexity: O(N log N)\ntemplate\
    \ <class T>\nstd::vector<T> shift_of_sampling_points(const std::vector<T> ys,\
    \ T c, int width) {\n    auto as = ys_to_factorial(ys);\n    as = shift_of_factorial(as,\
    \ c);\n    as.resize(width);\n    auto ret = factorial_to_ys(as);\n    return\
    \ ret;\n}\n#line 5 \"formal_power_series/test/shift_of_sampling_points.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    using mint = ModInt<998244353>;\n    int N, M, c;\n    cin >> N >> M >> c;\n\
    \    std::vector<mint> f(N);\n    for (auto &x : f) cin >> x;\n    auto ret =\
    \ shift_of_sampling_points<mint>(f, c, M);\n    for (auto x : ret) cout << x <<\
    \ ' ';\n    cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial\"\
    \n#include \"../../modint.hpp\"\n#include \"../factorial_power.hpp\"\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    using mint = ModInt<998244353>;\n    int N, M, c;\n    cin >> N >> M >> c;\n\
    \    std::vector<mint> f(N);\n    for (auto &x : f) cin >> x;\n    auto ret =\
    \ shift_of_sampling_points<mint>(f, c, M);\n    for (auto x : ret) cout << x <<\
    \ ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - modint.hpp
  - formal_power_series/factorial_power.hpp
  - convolution/ntt.hpp
  isVerificationFile: true
  path: formal_power_series/test/shift_of_sampling_points.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/shift_of_sampling_points.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/shift_of_sampling_points.test.cpp
- /verify/formal_power_series/test/shift_of_sampling_points.test.cpp.html
title: formal_power_series/test/shift_of_sampling_points.test.cpp
---
