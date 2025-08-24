---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/hadamard.hpp
    title: convolution/hadamard.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_xor_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_xor_convolution
  bundledCode: "#line 1 \"convolution/test/bitwise_xor_conv.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\n#line 2 \"modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \ntemplate <int md> struct ModInt {\n    static_assert(md > 1);\n    using lint\
    \ = long long;\n    constexpr static int mod() { return md; }\n    static int\
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
    \ primitive_root;\n    }\n    int val_;\n    int val() const noexcept { return\
    \ val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint\
    \ v) { return val_ = (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint\
    \ v) { _setval(v % md + md); }\n    constexpr explicit operator bool() const {\
    \ return val_ != 0; }\n    constexpr ModInt operator+(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    constexpr ModInt\
    \ operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    constexpr\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    constexpr ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    constexpr ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint\
    \ a, const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
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
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n\n\
    \    constexpr static ModInt fac(int n) {\n        assert(n >= 0);\n        if\
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
    \    }\n\n    static ModInt binom(int n, int r) {\n        static long long bruteforce_times\
    \ = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n        if (n <= bruteforce_times\
    \ or n < (int)facs.size()) return ModInt::nCr(n, r);\n\n        r = std::min(r,\
    \ n - r);\n\n        ModInt ret = ModInt::facinv(r);\n        for (int i = 0;\
    \ i < r; ++i) ret *= n - i;\n        bruteforce_times += r;\n\n        return\
    \ ret;\n    }\n\n    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1!\
    \ k_2! ... k_m!)\n    // Complexity: O(sum(ks))\n    template <class Vec> static\
    \ ModInt multinomial(const Vec &ks) {\n        ModInt ret{1};\n        int sum\
    \ = 0;\n        for (int k : ks) {\n            assert(k >= 0);\n            ret\
    \ *= ModInt::facinv(k), sum += k;\n        }\n        return ret * ModInt::fac(sum);\n\
    \    }\n    template <class... Args> static ModInt multinomial(Args... args) {\n\
    \        int sum = (0 + ... + args);\n        ModInt result = (1 * ... * ModInt::facinv(args));\n\
    \        return ModInt::fac(sum) * result;\n    }\n\n    // Catalan number, C_n\
    \ = binom(2n, n) / (n + 1) = # of Dyck words of length 2n\n    // C_0 = 1, C_1\
    \ = 1, C_2 = 2, C_3 = 5, C_4 = 14, ...\n    // https://oeis.org/A000108\n    //\
    \ Complexity: O(n)\n    static ModInt catalan(int n) {\n        if (n < 0) return\
    \ ModInt(0);\n        return ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);\n\
    \    }\n\n    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n      \
    \  if (md == 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n\
    \        ModInt b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n   \
    \     int e = 0, m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n     \
    \   ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n\
    \        ModInt z = b.pow(m);\n        while (y != 1) {\n            int j = 0;\n\
    \            ModInt t = y;\n            while (t != 1) j++, t *= t;\n        \
    \    z = z.pow(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n   \
    \         e = j;\n        }\n        return ModInt(std::min(x.val_, md - x.val_));\n\
    \    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\ntemplate\
    \ <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 4 \"convolution/hadamard.hpp\"\n\n// Fast Walsh-Hadamard transform and its\
    \ abstraction\n// Tutorials: <https://codeforces.com/blog/entry/71899>\n//   \
    \         <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>\n\
    template <typename T, typename F> void abstract_fwht(std::vector<T> &seq, F f)\
    \ {\n    const int n = seq.size();\n    assert(__builtin_popcount(n) == 1);\n\
    \    for (int w = 1; w < n; w *= 2) {\n        for (int i = 0; i < n; i += w *\
    \ 2) {\n            for (int j = 0; j < w; j++) f(seq.at(i + j), seq.at(i + j\
    \ + w));\n        }\n    }\n}\n\ntemplate <typename T, typename F1, typename F2>\n\
    std::vector<T> bitwise_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv)\
    \ {\n    const int n = x.size();\n    assert(__builtin_popcount(n) == 1);\n  \
    \  assert(x.size() == y.size());\n    if (x == y) {\n        abstract_fwht(x,\
    \ f), y = x;\n    } else {\n        abstract_fwht(x, f), abstract_fwht(y, f);\n\
    \    }\n    for (int i = 0; i < (int)x.size(); i++) x.at(i) *= y.at(i);\n    abstract_fwht(x,\
    \ finv);\n    return x;\n}\n\n// bitwise xor convolution (FWHT-based)\n// ret[i]\
    \ = \\sum_j x[j] * y[i ^ j]\n// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()\n\
    template <typename T> std::vector<T> xorconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    auto f = [](T &lo, T &hi) {\n        T c = lo + hi;\n        hi =\
    \ lo - hi, lo = c;\n    };\n    auto finv = [](T &lo, T &hi) {\n        T c =\
    \ lo + hi;\n        hi = (lo - hi) / 2,\n        lo = c / 2; // Reconsider HEAVY\
    \ complexity of division by 2 when T is ModInt\n    };\n    return bitwise_conv(x,\
    \ y, f, finv);\n}\n\n// bitwise AND conolution\n// ret[i] = \\sum_{(j & k) ==\
    \ i} x[j] * y[k]\ntemplate <typename T> std::vector<T> andconv(std::vector<T>\
    \ x, std::vector<T> y) {\n    return bitwise_conv(x, y, [](T &lo, T &hi) { lo\
    \ += hi; }, [](T &lo, T &hi) { lo -= hi; });\n}\n\n// bitwise OR convolution\n\
    // ret[i] = \\sum_{(j | k) == i} x[j] * y[k]\ntemplate <typename T> std::vector<T>\
    \ orconv(std::vector<T> x, std::vector<T> y) {\n    return bitwise_conv(x, y,\
    \ [](T &lo, T &hi) { hi += lo; }, [](T &lo, T &hi) { hi -= lo; });\n}\n#line 5\
    \ \"convolution/test/bitwise_xor_conv.test.cpp\"\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N;\n \
    \   cin >> N;\n    vector<ModInt<998244353>> A(1 << N), B(1 << N);\n    for (auto\
    \ &x : A) cin >> x;\n    for (auto &x : B) cin >> x;\n\n    for (auto x : xorconv(A,\
    \ B)) cout << x << ' ';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_xor_convolution\"\
    \n#include \"../../modint.hpp\"\n#include \"../hadamard.hpp\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    vector<ModInt<998244353>> A(1 << N), B(1 << N);\n\
    \    for (auto &x : A) cin >> x;\n    for (auto &x : B) cin >> x;\n\n    for (auto\
    \ x : xorconv(A, B)) cout << x << ' ';\n}\n"
  dependsOn:
  - modint.hpp
  - convolution/hadamard.hpp
  isVerificationFile: true
  path: convolution/test/bitwise_xor_conv.test.cpp
  requiredBy: []
  timestamp: '2025-08-25 00:44:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/bitwise_xor_conv.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/bitwise_xor_conv.test.cpp
- /verify/convolution/test/bitwise_xor_conv.test.cpp.html
title: convolution/test/bitwise_xor_conv.test.cpp
---
