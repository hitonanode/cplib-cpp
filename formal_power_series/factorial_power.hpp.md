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
    path: formal_power_series/test/factorial_power.stirling_number_of_2nd.test.cpp
    title: formal_power_series/test/factorial_power.stirling_number_of_2nd.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/shift_of_sampling_points.test.cpp
    title: formal_power_series/test/shift_of_sampling_points.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <set>\n#include <vector>\n\ntemplate <int md> struct ModInt {\n    static_assert(md\
    \ > 1);\n    using lint = long long;\n    constexpr static int mod() { return\
    \ md; }\n    static int get_primitive_root() {\n        static int primitive_root\
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
    \ noexcept { return val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr\
    \ ModInt &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n \
    \   constexpr ModInt(lint v) { _setval(v % md + md); }\n    constexpr explicit\
    \ operator bool() const { return val_ != 0; }\n    constexpr ModInt operator+(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ + x.val_);\n\
    \    }\n    constexpr ModInt operator-(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n\
    \    }\n    constexpr ModInt operator/(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n    constexpr ModInt\
    \ operator-() const { return ModInt()._setval(md - val_); }\n    constexpr ModInt\
    \ &operator+=(const ModInt &x) { return *this = *this + x; }\n    constexpr ModInt\
    \ &operator-=(const ModInt &x) { return *this = *this - x; }\n    constexpr ModInt\
    \ &operator*=(const ModInt &x) { return *this = *this * x; }\n    constexpr ModInt\
    \ &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend constexpr\
    \ ModInt operator+(lint a, const ModInt &x) { return ModInt(a) + x; }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt(a) - x;\
    \ }\n    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt(a)\
    \ * x; }\n    friend constexpr ModInt operator/(lint a, const ModInt &x) { return\
    \ ModInt(a) / x; }\n    constexpr bool operator==(const ModInt &x) const { return\
    \ val_ == x.val_; }\n    constexpr bool operator!=(const ModInt &x) const { return\
    \ val_ != x.val_; }\n    constexpr bool operator<(const ModInt &x) const {\n \
    \       return val_ < x.val_;\n    } // To use std::map<ModInt, T>\n    friend\
    \ std::istream &operator>>(std::istream &is, ModInt &x) {\n        lint t;\n \
    \       return is >> t, x = ModInt(t), is;\n    }\n    constexpr friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) {\n        return os << x.val_;\n\
    \    }\n\n    constexpr ModInt pow(lint n) const {\n        ModInt ans = 1, tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    static\
    \ constexpr int cache_limit = std::min(md, 1 << 21);\n    static std::vector<ModInt>\
    \ facs, facinvs, invs;\n\n    constexpr static void _precalculation(int N) {\n\
    \        const int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr ModInt inv() const {\n \
    \       if (this->val_ < cache_limit) {\n            if (facs.empty()) facs =\
    \ {1}, facinvs = {1}, invs = {0};\n            while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n            return invs[this->val_];\n  \
    \      } else {\n            return this->pow(md - 2);\n        }\n    }\n\n \
    \   constexpr static ModInt fac(int n) {\n        assert(n >= 0);\n        if\
    \ (n >= md) return ModInt(0);\n        while (n >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[n];\n    }\n\n    constexpr static ModInt facinv(int\
    \ n) {\n        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n    \
    \    while (n >= int(facs.size())) _precalculation(facs.size() * 2);\n       \
    \ return facinvs[n];\n    }\n\n    constexpr static ModInt doublefac(int n) {\n\
    \        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n        long\
    \ long k = (n + 1) / 2;\n        return (n & 1) ? ModInt::fac(k * 2) / (ModInt(2).pow(k)\
    \ * ModInt::fac(k))\n                       : ModInt::fac(k) * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr static ModInt nCr(int n, int r) {\n        assert(n >=\
    \ 0);\n        if (r < 0 or n < r) return ModInt(0);\n        return ModInt::fac(n)\
    \ * ModInt::facinv(r) * ModInt::facinv(n - r);\n    }\n\n    constexpr static\
    \ ModInt nPr(int n, int r) {\n        assert(n >= 0);\n        if (r < 0 or n\
    \ < r) return ModInt(0);\n        return ModInt::fac(n) * ModInt::facinv(n - r);\n\
    \    }\n\n    static ModInt binom(long long n, long long r) {\n        static\
    \ long long bruteforce_times = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n\
    \        if (n <= bruteforce_times or n < (int)facs.size()) return ModInt::nCr(n,\
    \ r);\n\n        r = std::min(r, n - r);\n        assert((int)r == r);\n\n   \
    \     ModInt ret = ModInt::facinv(r);\n        for (int i = 0; i < r; ++i) ret\
    \ *= n - i;\n        bruteforce_times += r;\n\n        return ret;\n    }\n\n\
    \    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n\
    \    // Complexity: O(sum(ks))\n    // Verify: https://yukicoder.me/problems/no/3178\n\
    \    template <class Vec> static ModInt multinomial(const Vec &ks) {\n       \
    \ ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n         \
    \   assert(k >= 0);\n            ret *= ModInt::facinv(k), sum += k;\n       \
    \ }\n        return ret * ModInt::fac(sum);\n    }\n    template <class... Args>\
    \ static ModInt multinomial(Args... args) {\n        int sum = (0 + ... + args);\n\
    \        ModInt result = (1 * ... * ModInt::facinv(args));\n        return ModInt::fac(sum)\
    \ * result;\n    }\n\n    // Catalan number, C_n = binom(2n, n) / (n + 1) = #\
    \ of Dyck words of length 2n\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4 =\
    \ 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);\n    }\n\n \
    \   ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
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
    \ b, false);\n}\n#line 5 \"formal_power_series/factorial_power.hpp\"\n\n// Convert\
    \ factorial power -> sampling\n// [y[0], y[1], ..., y[N - 1]] -> \\sum_i a_i x^\\\
    underline{i}\n// Complexity: O(N log N)\ntemplate <class T> std::vector<T> factorial_to_ys(const\
    \ std::vector<T> &as) {\n    const int N = as.size();\n    std::vector<T> exp(N,\
    \ 1);\n    for (int i = 1; i < N; i++) exp[i] = T::facinv(i);\n    auto ys = nttconv(as,\
    \ exp);\n    ys.resize(N);\n    for (int i = 0; i < N; i++) ys[i] *= T::fac(i);\n\
    \    return ys;\n}\n\n// Convert sampling -> factorial power\n// [y[0], y[1],\
    \ ..., y[N - 1]] -> \\sum_i a_i x^\\underline{i}\n// Complexity: O(N log N)\n\
    template <class T> std::vector<T> ys_to_factorial(std::vector<T> ys) {\n    const\
    \ int N = ys.size();\n    for (int i = 1; i < N; i++) ys[i] *= T::facinv(i);\n\
    \    std::vector<T> expinv(N, 1);\n    for (int i = 1; i < N; i++) expinv[i] =\
    \ T::facinv(i) * (i % 2 ? -1 : 1);\n    auto as = nttconv(ys, expinv);\n    as.resize(N);\n\
    \    return as;\n}\n\n// Compute factorial power series of f(x + shift) from that\
    \ of f(x)\n// Complexity: O(N log N)\ntemplate <class T> std::vector<T> shift_of_factorial(const\
    \ std::vector<T> &as, T shift) {\n    const int N = as.size();\n    std::vector<T>\
    \ b(N, 1), c(N, 1);\n    for (int i = 1; i < N; i++) b[i] = b[i - 1] * (shift\
    \ - i + 1) * T(i).inv();\n    for (int i = 0; i < N; i++) c[i] = as[i] * T::fac(i);\n\
    \    std::reverse(c.begin(), c.end());\n    auto ret = nttconv(b, c);\n    ret.resize(N);\n\
    \    std::reverse(ret.begin(), ret.end());\n    for (int i = 0; i < N; i++) ret[i]\
    \ *= T::facinv(i);\n    return ret;\n}\n\n// Compute y[c], ..., y[c + width -\
    \ 1] from y[0], ..., y[N - 1] where y = f(x) is poly of up to\n// (N - 1)-th degree\
    \ Complexity: O(N log N)\ntemplate <class T>\nstd::vector<T> shift_of_sampling_points(const\
    \ std::vector<T> ys, T c, int width) {\n    auto as = ys_to_factorial(ys);\n \
    \   as = shift_of_factorial(as, c);\n    as.resize(width);\n    auto ret = factorial_to_ys(as);\n\
    \    return ret;\n}\n"
  code: "#pragma once\n#include \"../convolution/ntt.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// Convert factorial power -> sampling\n// [y[0], y[1], ...,\
    \ y[N - 1]] -> \\sum_i a_i x^\\underline{i}\n// Complexity: O(N log N)\ntemplate\
    \ <class T> std::vector<T> factorial_to_ys(const std::vector<T> &as) {\n    const\
    \ int N = as.size();\n    std::vector<T> exp(N, 1);\n    for (int i = 1; i < N;\
    \ i++) exp[i] = T::facinv(i);\n    auto ys = nttconv(as, exp);\n    ys.resize(N);\n\
    \    for (int i = 0; i < N; i++) ys[i] *= T::fac(i);\n    return ys;\n}\n\n//\
    \ Convert sampling -> factorial power\n// [y[0], y[1], ..., y[N - 1]] -> \\sum_i\
    \ a_i x^\\underline{i}\n// Complexity: O(N log N)\ntemplate <class T> std::vector<T>\
    \ ys_to_factorial(std::vector<T> ys) {\n    const int N = ys.size();\n    for\
    \ (int i = 1; i < N; i++) ys[i] *= T::facinv(i);\n    std::vector<T> expinv(N,\
    \ 1);\n    for (int i = 1; i < N; i++) expinv[i] = T::facinv(i) * (i % 2 ? -1\
    \ : 1);\n    auto as = nttconv(ys, expinv);\n    as.resize(N);\n    return as;\n\
    }\n\n// Compute factorial power series of f(x + shift) from that of f(x)\n// Complexity:\
    \ O(N log N)\ntemplate <class T> std::vector<T> shift_of_factorial(const std::vector<T>\
    \ &as, T shift) {\n    const int N = as.size();\n    std::vector<T> b(N, 1), c(N,\
    \ 1);\n    for (int i = 1; i < N; i++) b[i] = b[i - 1] * (shift - i + 1) * T(i).inv();\n\
    \    for (int i = 0; i < N; i++) c[i] = as[i] * T::fac(i);\n    std::reverse(c.begin(),\
    \ c.end());\n    auto ret = nttconv(b, c);\n    ret.resize(N);\n    std::reverse(ret.begin(),\
    \ ret.end());\n    for (int i = 0; i < N; i++) ret[i] *= T::facinv(i);\n    return\
    \ ret;\n}\n\n// Compute y[c], ..., y[c + width - 1] from y[0], ..., y[N - 1] where\
    \ y = f(x) is poly of up to\n// (N - 1)-th degree Complexity: O(N log N)\ntemplate\
    \ <class T>\nstd::vector<T> shift_of_sampling_points(const std::vector<T> ys,\
    \ T c, int width) {\n    auto as = ys_to_factorial(ys);\n    as = shift_of_factorial(as,\
    \ c);\n    as.resize(width);\n    auto ret = factorial_to_ys(as);\n    return\
    \ ret;\n}\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  isVerificationFile: false
  path: formal_power_series/factorial_power.hpp
  requiredBy: []
  timestamp: '2025-09-11 21:33:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/shift_of_sampling_points.test.cpp
  - formal_power_series/test/factorial_power.stirling_number_of_2nd.test.cpp
documentation_of: formal_power_series/factorial_power.hpp
layout: document
title: "factorial power \uFF08\u968E\u4E57\u51AA\u306B\u95A2\u3059\u308B\u6F14\u7B97\
  \uFF09"
---

下降階乗冪（下降冪） $x^{\underline{i}} = x \cdot (x - 1) \cdots (x - (i - 1))$ を用いた多項式 $f(x)$ の展開係数

$\displaystyle
f(x) = \sum_{i=0}^{N-1} a_i x^{\underline{i}}
$

に関する各種演算．

## 階乗冪・サンプリング値の変換

高々 $(N - 1)$ 次の多項式 $f(x)$ について，値の列 $[f(0), \dots, f(N - 1)]$ と下降冪による展開係数 $[a_i]_{i=0, \dots, N - 1}$ は $O(N \log N)$ で相互に変換可能．関数 `ys_to_factorial(vector<T> ys)` によって前者から後者の， `factorial_to_ys(vector<T> as)` によって後者から前者の変換がそれぞれ可能．

### アルゴリズムの概要

下降冪の定義より，

$\displaystyle
\frac{f(i)}{i!} = \sum_{j=0}^i \frac{a_j}{(i - j)!}
$

が成立．これより，$A(x) = \sum_i a_i x^i$ とおくと，

$\displaystyle
[[x^i]] (\exp(x) \cdot A(x)) = \frac{f(i)}{i!}
$

となり，これは畳み込みの形．

## 下降冪係数表現された多項式のシフト

多項式 $f(x)$ の下降冪表現 $[a_i]_{i = 0, \dots, N - 1}$ から $f(x + c)$ の下降冪表現は $O(N \log N)$ で計算可能．関数 `shift_of_factorial(vector<T> as, T shift)` が実装されている．

### アルゴリズムの概要

下降冪に関して（二項定理のような）等式

$\displaystyle
(a + b)^{\underline{n}} = \sum_{k=0}^n \binom{n}{k} a^{\underline{k}} b^{\underline{n - k}}
$

が成立することを用いると，シフトされた多項式 $f(x + c)$ は $f(x)$ の展開係数を用いて

$\displaystyle
f(x + c) = \sum_{i=0}^{N - 1} a_i (x + c)^{\underline{i}}
= \sum_{i = 0}^{N - 1} \sum_{j = 0}^{i} a_i \frac{i!}{j! (i - j)!} c^{\underline{j}} x^{\underline{i - j}}
$

と書けて，この等式の各次の係数は数列 $[a_{N - 1} (N - 1)!, \dots a_i i!, \dots, a_0]$ と $[c^{\underline{0}} / 0!, \dots, c^{\underline{i}} / i!, \dots, c^{\underline{N - 1}} / (N - 1)!]$ を畳み込むことで計算可能．

## 多項式関数の値の区間外挿

以上のアルゴリズムを組み合わせることで，高々 $(N - 1)$ 次の多項式関数 $f(x)$ について $f(0), \dots, f(N - 1)$ が既知のとき，$f(c), \dots, f(c + M - 1)$ の値の一括計算が $O((N + M)\log (N + M))$ で可能．関数 `shift_of_sampling_points(vector<T> ys, T c, int M)` が実装されている．


## 使用方法

```cpp
vector<mint> as{2, 3, 5}; // f(x) = 2 + 3x + 5x(x - 1) = 5x^2 - 2x + 2
auto ys = factorial_to_ys(as); // [2,5,18,] : f(0), f(1), f(2)
assert(ys_to_factorial(ys) == as);

auto shifted_as = shift_of_factorial<mint>(as, 10);  // f(x) => f(x + 10)

auto shifted_ys = shift_of_sampling_points<mint>(ys, 10000, 50); // f(10000), ..., f(10049) を計算
```

### 応用例：第二種スターリング数の計算

第二種スターリング数 $S(n, k)$ は

$\displaystyle
x^n = \sum_{k=0}^n S(n, k) x^{\underline{k}}
$

と定義される．固定した $n$ に対する $S(n, 0), \dots, S(n, n)$ の値は
```cpp
auto ys = Sieve(N).enumerate_kth_pows<mint>(N, N);
const auto stirling_number_of_2nd = ys_to_factorial(ys);
```
によって $O(n \log n)$ で計算できる．


## リンク

- [階乗冪 - Wikipedia](https://ja.wikipedia.org/wiki/%E9%9A%8E%E4%B9%97%E5%86%AA)
- [[問題案] Shift of Sampling Points · Issue #680 · yosupo06/library-checker-problems](https://github.com/yosupo06/library-checker-problems/issues/680)
- [Library Checker: Stirling Number of the Second Kind](https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind)
