---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/hadamard.hpp
    title: convolution/hadamard.hpp
  - icon: ':question:'
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
    \n#include <iostream>\n#include <set>\n#include <vector>\n\n// CUT begin\ntemplate\
    \ <int mod> struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n\
    #else\n#define MDCONST\n#endif\n    using lint = long long;\n    MDCONST static\
    \ int get_mod() { return mod; }\n    static int get_primitive_root() {\n     \
    \   static int primitive_root = 0;\n        if (!primitive_root) {\n         \
    \   primitive_root = [&]() {\n                std::set<int> fac;\n           \
    \     int v = mod - 1;\n                for (lint i = 2; i * i <= v; i++)\n  \
    \                  while (v % i == 0) fac.insert(i), v /= i;\n               \
    \ if (v > 1) fac.insert(v);\n                for (int g = 1; g < mod; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((mod - 1) / i) == 1) {\n          \
    \                  ok = false;\n                            break;\n         \
    \               }\n                    if (ok) return g;\n                }\n\
    \                return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n    MDCONST ModInt &_setval(lint\
    \ v) { return val = (v >= mod ? v - mod : v), *this; }\n    MDCONST ModInt(lint\
    \ v) { _setval(v % mod + mod); }\n    MDCONST explicit operator bool() const {\
    \ return val != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val + x.val); }\n    MDCONST ModInt operator-(const ModInt\
    \ &x) const { return ModInt()._setval((lint)val - x.val + mod); }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ * x.val % mod); }\n    MDCONST ModInt operator/(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.inv() % mod); }\n    MDCONST ModInt operator-()\
    \ const { return ModInt()._setval(mod - val); }\n    MDCONST ModInt &operator+=(const\
    \ ModInt &x) { return *this = *this + x; }\n    MDCONST ModInt &operator-=(const\
    \ ModInt &x) { return *this = *this - x; }\n    MDCONST ModInt &operator*=(const\
    \ ModInt &x) { return *this = *this * x; }\n    MDCONST ModInt &operator/=(const\
    \ ModInt &x) { return *this = *this / x; }\n    friend MDCONST ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }\n    friend\
    \ MDCONST ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod - x.val + mod); }\n    friend MDCONST ModInt operator*(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod * x.val % mod); }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.inv() % mod); }\n    MDCONST bool operator==(const ModInt &x) const { return\
    \ val == x.val; }\n    MDCONST bool operator!=(const ModInt &x) const { return\
    \ val != x.val; }\n    MDCONST bool operator<(const ModInt &x) const { return\
    \ val < x.val; } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) { return os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n      \
    \  lint ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1)\
    \ ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod, n /= 2;\n       \
    \ }\n        return ans;\n    }\n\n    static std::vector<long long> facs, invs;\n\
    \    MDCONST static void _precalculation(int N) {\n        int l0 = facs.size();\n\
    \        if (N <= l0) return;\n        facs.resize(N), invs.resize(N);\n     \
    \   for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i % mod;\n        long\
    \ long facinv = ModInt(facs.back()).pow(mod - 2).val;\n        for (int i = N\
    \ - 1; i >= l0; i--) {\n            invs[i] = facinv * facs[i - 1] % mod;\n  \
    \          facinv = facinv * i % mod;\n        }\n    }\n    MDCONST lint inv()\
    \ const {\n        if (this->val < std::min(mod >> 1, 1 << 21)) {\n          \
    \  while (this->val >= int(facs.size())) _precalculation(facs.size() * 2);\n \
    \           return invs[this->val];\n        } else {\n            return this->pow(mod\
    \ - 2).val;\n        }\n    }\n    MDCONST ModInt fac() const {\n        while\
    \ (this->val >= int(facs.size())) _precalculation(facs.size() * 2);\n        return\
    \ facs[this->val];\n    }\n\n    MDCONST ModInt doublefac() const {\n        lint\
    \ k = (this->val + 1) / 2;\n        return (this->val & 1) ? ModInt(k * 2).fac()\
    \ / (ModInt(2).pow(k) * ModInt(k).fac())\n                               : ModInt(k).fac()\
    \ * ModInt(2).pow(k);\n    }\n    MDCONST ModInt nCr(const ModInt &r) const {\n\
    \        return (this->val < r.val) ? 0 : this->fac() / ((*this - r).fac() * r.fac());\n\
    \    }\n\n    ModInt sqrt() const {\n        if (val == 0) return 0;\n       \
    \ if (mod == 2) return val;\n        if (pow((mod - 1) / 2) != 1) return 0;\n\
    \        ModInt b = 1;\n        while (b.pow((mod - 1) / 2) == 1) b += 1;\n  \
    \      int e = 0, m = mod - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n   \
    \     ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n\
    \        ModInt z = b.pow(m);\n        while (y != 1) {\n            int j = 0;\n\
    \            ModInt t = y;\n            while (t != 1) j++, t *= t;\n        \
    \    z = z.pow(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n   \
    \         e = j;\n        }\n        return ModInt(std::min(x.val, mod - x.val));\n\
    \    }\n};\ntemplate <int mod> std::vector<long long> ModInt<mod>::facs = {1};\n\
    template <int mod> std::vector<long long> ModInt<mod>::invs = {0};\n\n// using\
    \ mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"convolution/hadamard.hpp\"\
    \n#include <cassert>\n#line 4 \"convolution/hadamard.hpp\"\n\n// CUT begin\n//\
    \ Fast Walsh-Hadamard transform and its abstraction\n// Tutorials: <https://codeforces.com/blog/entry/71899>\n\
    //            <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>\n\
    template <typename T, typename F> void abstract_fwht(std::vector<T>& seq, F f)\
    \ {\n    const int n = seq.size();\n    assert(__builtin_popcount(n) == 1);\n\
    \    for (int w = 1; w < n; w *= 2) {\n        for (int i = 0; i < n; i += w *\
    \ 2) {\n            for (int j = 0; j < w; j++) { f(seq[i + j], seq[i + j + w]);\
    \ }\n        }\n    }\n}\n\ntemplate <typename T, typename F1, typename F2> std::vector<T>\
    \ bitwise_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv) {\n    const\
    \ int n = x.size();\n    assert(__builtin_popcount(n) == 1);\n    assert(x.size()\
    \ == y.size());\n    if (x == y) {\n        abstract_fwht(x, f), y = x;\n    }\
    \ else {\n        abstract_fwht(x, f), abstract_fwht(y, f);\n    }\n    for (size_t\
    \ i = 0; i < x.size(); i++) { x[i] *= y[i]; }\n    abstract_fwht(x, finv);\n \
    \   return x;\n}\n\n// bitwise xor convolution (FWHT-based)\n// ret[i] = \\sum_j\
    \ x[j] * y[i ^ j]\n// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()\n\
    template <typename T> std::vector<T> xorconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    auto f = [](T& lo, T& hi) {\n        T c = lo + hi;\n        hi =\
    \ lo - hi, lo = c;\n    };\n    auto finv = [](T& lo, T& hi) {\n        T c =\
    \ lo + hi;\n        hi = (lo - hi) / 2, lo = c / 2; // Reconsider HEAVY complexity\
    \ of division by 2 when T is ModInt\n    };\n    return bitwise_conv(x, y, f,\
    \ finv);\n}\n\n// bitwise AND conolution\n// ret[i] = \\sum_{(j & k) == i} x[j]\
    \ * y[k]\ntemplate <typename T> std::vector<T> andconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    return bitwise_conv(\n        x, y, [](T& lo, T& hi) { lo += hi; },\
    \ [](T& lo, T& hi) { lo -= hi; });\n}\n\n// bitwise OR convolution\n// ret[i]\
    \ = \\sum_{(j | k) == i} x[j] * y[k]\ntemplate <typename T> std::vector<T> orconv(std::vector<T>\
    \ x, std::vector<T> y) {\n    return bitwise_conv(\n        x, y, [](T& lo, T&\
    \ hi) { hi += lo; }, [](T& lo, T& hi) { hi -= lo; });\n}\n#line 5 \"convolution/test/bitwise_xor_conv.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    vector<ModInt<998244353>> A(1 << N), B(1 << N);\n\
    \    for (auto &x : A) cin >> x;\n    for (auto &x : B) cin >> x;\n\n    for (auto\
    \ x : xorconv(A, B)) cout << x << ' ';\n}\n"
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
  timestamp: '2021-03-27 19:28:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/bitwise_xor_conv.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/bitwise_xor_conv.test.cpp
- /verify/convolution/test/bitwise_xor_conv.test.cpp.html
title: convolution/test/bitwise_xor_conv.test.cpp
---
