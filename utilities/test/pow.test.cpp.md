---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/pow.hpp
    title: "Power \uFF08\u7D2F\u4E57\uFF09"
  - icon: ':heavy_check_mark:'
    path: utilities/pow_sum.hpp
    title: "power sum \uFF08\u7D2F\u4E57\u548C\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B
  bundledCode: "#line 1 \"utilities/test/pow.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B\"\
    \n#line 2 \"utilities/pow.hpp\"\n\ntemplate <typename T, typename Int> T pow(T\
    \ x, Int n) {\n    T ans = 1;\n    while (n) {\n        if (n & 1) ans *= x;\n\
    \        x *= x;\n        n >>= 1;\n    }\n    return ans;\n}\n#line 2 \"modint.hpp\"\
    \n#include <iostream>\n#include <set>\n#include <vector>\n\ntemplate <int md>\
    \ struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n\
    #define MDCONST\n#endif\n    using lint = long long;\n    MDCONST static int mod()\
    \ { return md; }\n    static int get_primitive_root() {\n        static int primitive_root\
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
    \ noexcept { return val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST\
    \ ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit operator bool()\
    \ const { return val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    MDCONST ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    MDCONST ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    MDCONST ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend MDCONST ModInt operator+(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md + x.val_);\n \
    \   }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x) {\n      \
    \  return ModInt()._setval(a % md - x.val_ + md);\n    }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a % md\
    \ * x.val_ % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md * x.inv().val() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val_ == x.val_; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val_ != x.val_; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val_ < x.val_;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST ModInt inv() const {\n        if (this->val_ < std::min(md\
    \ >> 1, 1 << 21)) {\n            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
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
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"utilities/pow_sum.hpp\"\
    \n#include <algorithm>\n#include <utility>\n\n// CUT begin\n// {x^n, x^0 + ...\
    \ + x^(n - 1)} for n >= 1\n// Verify: ABC212H\ntemplate <typename T, typename\
    \ Int> std::pair<T, T> pow_sum(T x, Int n) {\n    T sum = 1, p = x; // ans = x^0\
    \ + ... + x^(len - 1), p = x^len\n    for (int d = std::__lg(n) - 1; d >= 0; d--)\
    \ {\n        sum = sum * (p + 1);\n        p *= p;\n        if ((n >> d) & 1)\
    \ {\n            sum += p;\n            p *= x;\n        }\n    }\n    return\
    \ {p, sum};\n}\n#line 5 \"utilities/test/pow.test.cpp\"\n#include <cassert>\n\
    #line 7 \"utilities/test/pow.test.cpp\"\nusing namespace std;\n\nint main() {\n\
    \    ModInt<1000000007> M;\n    int N;\n    cin >> M >> N;\n    auto ret = pow(M,\
    \ N);\n    assert(pow_sum(M, N).first == ret);\n    assert((pow_sum(M, N).second)\
    \ * (M - 1) + 1 == ret);\n\n    cout << ret << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B\"\
    \n#include \"../pow.hpp\"\n#include \"../../modint.hpp\"\n#include \"../pow_sum.hpp\"\
    \n#include <cassert>\n#include <iostream>\nusing namespace std;\n\nint main()\
    \ {\n    ModInt<1000000007> M;\n    int N;\n    cin >> M >> N;\n    auto ret =\
    \ pow(M, N);\n    assert(pow_sum(M, N).first == ret);\n    assert((pow_sum(M,\
    \ N).second) * (M - 1) + 1 == ret);\n\n    cout << ret << '\\n';\n}\n"
  dependsOn:
  - utilities/pow.hpp
  - modint.hpp
  - utilities/pow_sum.hpp
  isVerificationFile: true
  path: utilities/test/pow.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/pow.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/pow.test.cpp
- /verify/utilities/test/pow.test.cpp.html
title: utilities/test/pow.test.cpp
---
