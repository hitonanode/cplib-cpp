---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/pow_of_sparse_fps.hpp
    title: "Power of sparse formal power series \uFF08\u975E\u96F6\u306A\u9805\u304C\
      \u758E\u306A\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570\u306E\u7D2F\u4E57\uFF09"
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
    PROBLEM: https://yukicoder.me/problems/no/1939
    links:
    - https://yukicoder.me/problems/no/1939
  bundledCode: "#line 1 \"formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1939\"\n#line 2 \"formal_power_series/pow_of_sparse_fps.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// Calculate f(x)^k up to x^N\n// Requirement: k > 0\n//\
    \ Complexity: O(NM) (M : num. of nonzero coefficients of f(x))\ntemplate <class\
    \ T> std::vector<T> pow_of_sparse_fps(const std::vector<T> &f, int N, long long\
    \ k) {\n    assert(k > 0);\n    std::vector<std::pair<int, T>> nonzero_terms;\n\
    \    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <= N and f[d0] == T())\
    \ ++d0;\n    if (d0 == int(f.size()) or d0 > N) return std::vector<T>(N + 1);\n\
    \n    if (d0 and N / d0 < k) return std::vector<T>(N + 1);\n\n    for (int d =\
    \ d0; d < std::min<int>(N + 1, f.size()); ++d) {\n        if (f[d] != T()) nonzero_terms.emplace_back(d\
    \ - d0, f[d]);\n    }\n\n    int Ncalc = N - d0 * k;\n\n    std::vector<T> ret(Ncalc\
    \ + 1);\n    ret[0] = f[d0].pow(k);\n    for (int d = 0; d + 1 < int(ret.size());\
    \ ++d) {\n        // Compare [x^d](k f'g - fg')\n        T tmp = T();\n      \
    \  int i, j;\n        T fi;\n        for (auto i_fi : nonzero_terms) {\n     \
    \       std::tie(i, fi) = i_fi;\n            if (!i) continue;\n            j\
    \ = d - i;\n            if (0 <= j) tmp -= fi * ret[j + 1] * (j + 1);\n      \
    \      j = d - (i - 1);\n            if (0 <= j) tmp += fi * i * ret[j] * T(k);\n\
    \        }\n        ret[d + 1] = tmp / (f[d0] * (d + 1));\n    }\n\n    ret.resize(N\
    \ + 1, T());\n    std::rotate(ret.begin(), ret.end() - d0 * k, ret.end());\n \
    \   return ret;\n}\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n\
    #line 5 \"modint.hpp\"\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >=\
    \ 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
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
    \ val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint\
    \ v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint\
    \ v) { _setval(v % md + md); }\n    MDCONST explicit operator bool() const { return\
    \ val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const {\n      \
    \  return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST ModInt operator-(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ - x.val_ + md);\n\
    \    }\n    MDCONST ModInt operator*(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ * x.inv().val()\
    \ % md);\n    }\n    MDCONST ModInt operator-() const { return ModInt()._setval(md\
    \ - val_); }\n    MDCONST ModInt &operator+=(const ModInt &x) { return *this =\
    \ *this + x; }\n    MDCONST ModInt &operator-=(const ModInt &x) { return *this\
    \ = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt &x) { return *this\
    \ = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt &x) { return *this\
    \ = *this / x; }\n    friend MDCONST ModInt operator+(lint a, const ModInt &x)\
    \ {\n        return ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST\
    \ ModInt operator-(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md - x.val_ + md);\n    }\n    friend MDCONST ModInt operator*(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.val_ % md);\n    }\n\
    \    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
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
    \            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n      \
    \      while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \            return invs[this->val_];\n        } else {\n            return this->pow(md\
    \ - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n        while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n        return facs[this->val_];\n\
    \    }\n    MDCONST ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    MDCONST ModInt doublefac() const {\n        lint k = (this->val_ + 1)\
    \ / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val_\
    \ < r.val_) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n  \
    \  MDCONST ModInt nPr(const ModInt &r) const {\n        return (this->val_ < r.val_)\
    \ ? 0 : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const\
    \ {\n        if (val_ == 0) return 0;\n        if (md == 2) return val_;\n   \
    \     if (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while\
    \ (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n       \
    \ while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while\
    \ (y != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 6 \"formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp\"\nusing\
    \ namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M;\n    cin >> N >> M;\n    vector<mint>\
    \ f(N + 1);\n    f[0] = 1;\n    while (M--) {\n        int l;\n        cin >>\
    \ l;\n        f[l] += 1;\n    }\n    cout << pow_of_sparse_fps(f, N, N + 1)[N]\
    \ / (N + 1) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1939\"\n#include \"../pow_of_sparse_fps.hpp\"\
    \n#include \"../../modint.hpp\"\n#include <iostream>\n#include <vector>\nusing\
    \ namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M;\n    cin >> N >> M;\n    vector<mint>\
    \ f(N + 1);\n    f[0] = 1;\n    while (M--) {\n        int l;\n        cin >>\
    \ l;\n        f[l] += 1;\n    }\n    cout << pow_of_sparse_fps(f, N, N + 1)[N]\
    \ / (N + 1) << '\\n';\n}\n"
  dependsOn:
  - formal_power_series/pow_of_sparse_fps.hpp
  - modint.hpp
  isVerificationFile: true
  path: formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
  requiredBy: []
  timestamp: '2022-07-12 00:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
- /verify/formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp.html
title: formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
---
