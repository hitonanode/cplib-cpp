---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/subset_convolution.hpp
    title: convolution/subset_convolution.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
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
    \ T> void subset_sum(std::vector<T> &f) {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n\
    \    assert(__builtin_popcount(sz) == 1);\n    for (int d = 0; d < n; d++) {\n\
    \        for (int S = 0; S < 1 << n; S++)\n            if (S & (1 << d)) f[S]\
    \ += f[S ^ (1 << d)];\n    }\n}\n// Inverse of subset sum (fast moebius transform)\n\
    // Complexity: O(N 2^N) for array of size 2^N\ntemplate <typename T> void subset_sum_inv(std::vector<T>\
    \ &g) {\n    const int sz = g.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];\n    }\n}\n\n\
    // Superset sum / its inverse (fast zeta/moebius transform)\n// Complexity: O(N\
    \ 2^N) for array of size 2^N\ntemplate <typename T> void superset_sum(std::vector<T>\
    \ &f) {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (!(S & (1 << d))) f[S] += f[S | (1 << d)];\n    }\n\
    }\ntemplate <typename T> void superset_sum_inv(std::vector<T> &g) {\n    const\
    \ int sz = g.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (!(S & (1 << d))) g[S] -= g[S | (1 << d)];\n    }\n\
    }\n\n// Subset convolution\n// h[S] = \\sum_T f[T] * g[S - T]\n// Complexity:\
    \ O(N^2 2^N) for arrays of size 2^N\ntemplate <typename T> std::vector<T> subset_convolution(std::vector<T>\
    \ f, std::vector<T> g) {\n    const int sz = f.size(), m = __builtin_ctz(sz) +\
    \ 1;\n    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());\n\n  \
    \  std::vector<std::vector<T>> ff(m, std::vector<T>(sz)), fg(m, std::vector<T>(sz));\n\
    \    for (int i = 0; i < sz; i++) {\n        int pc = __builtin_popcount(i);\n\
    \        ff[pc][i] += f[i], fg[pc][i] += g[i];\n    }\n    for (auto &vec : ff)\
    \ subset_sum(vec);\n    for (auto &vec : fg) subset_sum(vec);\n\n    std::vector<std::vector<T>>\
    \ fh(m, std::vector<T>(sz));\n    for (int d = 0; d < m; d++) {\n        for (int\
    \ e = 0; d + e < m; e++) {\n            for (int i = 0; i < sz; i++) fh[d + e][i]\
    \ += ff[d][i] * fg[e][i];\n        }\n    }\n    for (auto &vec : fh) subset_sum_inv(vec);\n\
    \    std::vector<T> ret(sz);\n    for (int i = 0; i < sz; i++) ret[i] = fh[__builtin_popcount(i)][i];\n\
    \    return ret;\n}\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n\
    #line 5 \"modint.hpp\"\n\n// CUT begin\ntemplate <int mod> struct ModInt {\n#if\
    \ __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n\
    #endif\n    using lint = long long;\n    MDCONST static int get_mod() { return\
    \ mod; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&]() {\n\
    \                std::set<int> fac;\n                int v = mod - 1;\n      \
    \          for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < mod; g++) {\n                    bool ok =\
    \ true;\n                    for (auto i : fac)\n                        if (ModInt(g).pow((mod\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val;\n    MDCONST ModInt()\
    \ : val(0) {}\n    MDCONST ModInt &_setval(lint v) { return val = (v >= mod ?\
    \ v - mod : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % mod + mod);\
    \ }\n    MDCONST explicit operator bool() const { return val != 0; }\n    MDCONST\
    \ ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + mod); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % mod); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }\n \
    \   MDCONST ModInt operator-() const { return ModInt()._setval(mod - val); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod - x.val + mod); }\n    friend MDCONST\
    \ ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.val % mod); }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod * x.inv() % mod); }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        lint ans = 1,\
    \ tmp = this->val;\n        while (n) {\n            if (n & 1) ans = ans * tmp\
    \ % mod;\n            tmp = tmp * tmp % mod, n /= 2;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<long long> facs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ <= l0) return;\n        facs.resize(N), invs.resize(N);\n        for (int i\
    \ = l0; i < N; i++) facs[i] = facs[i - 1] * i % mod;\n        long long facinv\
    \ = ModInt(facs.back()).pow(mod - 2).val;\n        for (int i = N - 1; i >= l0;\
    \ i--) {\n            invs[i] = facinv * facs[i - 1] % mod;\n            facinv\
    \ = facinv * i % mod;\n        }\n    }\n    MDCONST lint inv() const {\n    \
    \    if (this->val < 1 << 20) {\n            while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n            return invs[this->val];\n   \
    \     } else {\n            return this->pow(mod - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\
    \ : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST ModInt nCr(const ModInt\
    \ &r) const { return (this->val < r.val) ? 0 : this->fac() / ((*this - r).fac()\
    \ * r.fac()); }\n\n    ModInt sqrt() const {\n        if (val == 0) return 0;\n\
    \        if (mod == 2) return val;\n        if (pow((mod - 1) / 2) != 1) return\
    \ 0;\n        ModInt b = 1;\n        while (b.pow((mod - 1) / 2) == 1) b += 1;\n\
    \        int e = 0, m = mod - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n \
    \       ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n\
    \        ModInt z = b.pow(m);\n        while (y != 1) {\n            int j = 0;\n\
    \            ModInt t = y;\n            while (t != 1) j++, t *= t;\n        \
    \    z = z.pow(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n   \
    \         e = j;\n        }\n        return ModInt(std::min(x.val, mod - x.val));\n\
    \    }\n};\ntemplate <int mod> std::vector<long long> ModInt<mod>::facs = {1};\n\
    template <int mod> std::vector<long long> ModInt<mod>::invs = {0};\n\n// using\
    \ mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 5 \"convolution/test/subset_convolution.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    vector<ModInt<998244353>> A(1 << N), B(1 << N);\n\
    \    for (auto &x : A) cin >> x;\n    for (auto &x : B) cin >> x;\n\n    for (auto\
    \ x : subset_convolution(A, B)) cout << x << ' ';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\
    #include \"convolution/subset_convolution.hpp\"\n#include \"modint.hpp\"\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    vector<ModInt<998244353>> A(1 << N), B(1 << N);\n\
    \    for (auto &x : A) cin >> x;\n    for (auto &x : B) cin >> x;\n\n    for (auto\
    \ x : subset_convolution(A, B)) cout << x << ' ';\n}\n"
  dependsOn:
  - convolution/subset_convolution.hpp
  - modint.hpp
  isVerificationFile: true
  path: convolution/test/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2020-12-02 23:44:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/subset_convolution.test.cpp
- /verify/convolution/test/subset_convolution.test.cpp.html
title: convolution/test/subset_convolution.test.cpp
---
