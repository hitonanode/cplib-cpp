---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/subset_convolution.hpp
    title: convolution/subset_convolution.hpp
  - icon: ':question:'
    path: modulus/modint_fixed.hpp
    title: modulus/modint_fixed.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "#line 1 \"convolution/test/subset_convolution.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n#line 2 \"convolution/subset_convolution.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Subset sum (fast zeta\
    \ transform)\n// Complexity: O(N 2^N) for array of size 2^N\ntemplate <typename\
    \ T>\nvoid subset_sum(std::vector<T> &f)\n{\n    const int sz = f.size(), n =\
    \ __builtin_ctz(sz);\n    assert(__builtin_popcount(sz) == 1);\n    for (int d\
    \ = 0; d < n; d++) {\n        for (int S = 0; S < 1 << n; S++) if (S & (1 << d))\
    \ f[S] += f[S ^ (1 << d)];\n    }\n}\n// Inverse of subset sum (fast moebius transform)\n\
    // Complexity: O(N 2^N) for array of size 2^N\ntemplate <typename T>\nvoid subset_sum_inv(std::vector<T>\
    \ &g)\n{\n    const int sz = g.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++) if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];\n    }\n}\n\n// Superset\
    \ sum / its inverse (fast zeta/moebius transform)\n// Complexity: O(N 2^N) for\
    \ array of size 2^N\ntemplate <typename T>\nvoid superset_sum(std::vector<T> &f)\n\
    {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++) if (!(S & (1 << d))) f[S] += f[S | (1 << d)];\n    }\n}\ntemplate <typename\
    \ T>\nvoid superset_sum_inv(std::vector<T> &g)\n{\n    const int sz = g.size(),\
    \ n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz) == 1);\n    for (int\
    \ d = 0; d < n; d++) {\n        for (int S = 0; S < 1 << n; S++) if (!(S & (1\
    \ << d))) g[S] -= g[S | (1 << d)];\n    }\n}\n\n\n// Subset convolution\n// h[S]\
    \ = \\sum_T f[T] * g[S - T]\n// Complexity: O(N^2 2^N) for arrays of size 2^N\n\
    template <typename T>\nstd::vector<T> subset_convolution(std::vector<T> f, std::vector<T>\
    \ g)\n{\n    const int sz = f.size(), m = __builtin_ctz(sz) + 1;\n    assert(__builtin_popcount(sz)\
    \ == 1 and f.size() == g.size());\n\n    std::vector<std::vector<T>> ff(m, std::vector<T>(sz)),\
    \ fg(m, std::vector<T>(sz));\n    for (int i = 0; i < sz; i++) {\n        int\
    \ pc = __builtin_popcount(i);\n        ff[pc][i] += f[i], fg[pc][i] += g[i];\n\
    \    }\n    for (auto &vec : ff) subset_sum(vec);\n    for (auto &vec : fg) subset_sum(vec);\n\
    \n    std::vector<std::vector<T>> fh(m, std::vector<T>(sz));\n    for (int d =\
    \ 0; d < m; d++) {\n        for (int e = 0; d + e < m; e++) {\n            for\
    \ (int i = 0; i < sz; i++) fh[d + e][i] += ff[d][i] * fg[e][i];\n        }\n \
    \   }\n    for (auto &vec : fh) subset_sum_inv(vec);\n    std::vector<T> ret(sz);\n\
    \    for (int i = 0; i < sz; i++) ret[i] = fh[__builtin_popcount(i)][i];\n   \
    \ return ret;\n}\n#line 2 \"modulus/modint_fixed.hpp\"\n#include <iostream>\n\
    #line 4 \"modulus/modint_fixed.hpp\"\n#include <set>\n\n// CUT begin\ntemplate\
    \ <int mod>\nstruct ModInt\n{\n    using lint = long long;\n    static int get_mod()\
    \ { return mod; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&](){\n\
    \                std::set<int> fac;\n                int v = mod - 1;\n      \
    \          for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < mod; g++) {\n                    bool ok = true;\n              \
    \      for (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false;\
    \ break; }\n                    if (ok) return g;\n                }\n       \
    \         return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val;\n    constexpr ModInt() : val(0) {}\n    constexpr ModInt\
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
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n#line 5 \"convolution/test/subset_convolution.test.cpp\"\
    \n\nint main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \n    int N;\n    std::cin >> N;\n    std::vector<ModInt<998244353>> A(1 << N),\
    \ B(1 << N);\n    for (auto &x : A) std::cin >> x;\n    for (auto &x : B) std::cin\
    \ >> x;\n\n    for (auto x : subset_convolution(A, B)) std::cout << x << ' ';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\
    #include \"convolution/subset_convolution.hpp\"\n#include \"modulus/modint_fixed.hpp\"\
    \n#include <iostream>\n\nint main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \n    int N;\n    std::cin >> N;\n    std::vector<ModInt<998244353>> A(1 << N),\
    \ B(1 << N);\n    for (auto &x : A) std::cin >> x;\n    for (auto &x : B) std::cin\
    \ >> x;\n\n    for (auto x : subset_convolution(A, B)) std::cout << x << ' ';\n\
    }\n"
  dependsOn:
  - convolution/subset_convolution.hpp
  - modulus/modint_fixed.hpp
  isVerificationFile: true
  path: convolution/test/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2020-04-18 21:06:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/subset_convolution.test.cpp
- /verify/convolution/test/subset_convolution.test.cpp.html
title: convolution/test/subset_convolution.test.cpp
---
