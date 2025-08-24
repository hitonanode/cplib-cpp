---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/kth_power_sum.hpp
    title: "Sum of $k$-th powers of first $n$ positive integers \uFF08\u81EA\u7136\
      \u6570\u306E $k$ \u4E57\u548C\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/665
    links:
    - https://yukicoder.me/problems/no/665
  bundledCode: "#line 1 \"utilities/test/kth_power_sum.yuki665.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/665\"\n#line 2 \"utilities/kth_power_sum.hpp\"\
    \n#include <vector>\n\n// Computes the sum of the k-th powers\n// Complexity:\n\
    // - O(k) per query,\n// - O(k^2) precomputation (can be reduced to O(k log k)\
    \ with FFT)\ntemplate <class MODINT> struct kth_power_sum {\n\n    // generating\
    \ function:  x / (e^x - 1) + x\n    // NOTE: use B(1) = 1/2 definition\n    std::vector<MODINT>\
    \ bernoulli;\n\n    kth_power_sum() = default;\n\n    void expand() {\n      \
    \  if (bernoulli.empty()) {\n            bernoulli = {1};\n        } else {\n\
    \            const int k = bernoulli.size();\n            MODINT x(0);\n     \
    \       for (int i = 0; i < k; ++i) { x = -x + bernoulli[i] * MODINT::binom(k\
    \ + 1, i); }\n            bernoulli.push_back(x / (k + 1));\n        }\n    }\n\
    \n    // Calculate 1^k + 2^k + ... + n^k\n    // Based on Faulhaber's formula:\n\
    \    // S_k(n) = 1 / (k + 1) * sum_{j=0}^{k} B_j * C(k + 1, j) * n^(k + 1 - j)\n\
    \n    template <class T> MODINT prefix_sum(int k, const T &n) {\n        while\
    \ ((int)bernoulli.size() <= k) expand();\n\n        MODINT ret(0), np(1);\n  \
    \      for (int j = k; j >= 0; --j) {\n            np *= n;\n            ret +=\
    \ MODINT::binom(k + 1, j) * bernoulli[j] * np;\n        }\n        return ret\
    \ / (k + 1);\n    }\n};\n#line 2 \"modint.hpp\"\n#include <cassert>\n#include\
    \ <iostream>\n#include <set>\n#line 6 \"modint.hpp\"\n\ntemplate <int md> struct\
    \ ModInt {\n    using lint = long long;\n    constexpr static int mod() { return\
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
    \      } else {\n            return this->pow(md - 2);\n        }\n    }\n   \
    \ constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val_];\n    }\n\
    \    constexpr ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    constexpr ModInt doublefac() const {\n        lint k = (this->val_ +\
    \ 1) / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr ModInt nCr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv() *\
    \ ModInt(r).facinv();\n    }\n\n    constexpr ModInt nPr(int r) const {\n    \
    \    if (r < 0 or this->val_ < r) return ModInt(0);\n        return this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    static ModInt binom(int n, int r) {\n\
    \        static long long bruteforce_times = 0;\n\n        if (r < 0 or n < r)\
    \ return ModInt(0);\n        if (n <= bruteforce_times or n < (int)facs.size())\
    \ return ModInt(n).nCr(r);\n\n        r = std::min(r, n - r);\n\n        ModInt\
    \ ret = ModInt(r).facinv();\n        for (int i = 0; i < r; ++i) ret *= n - i;\n\
    \        bruteforce_times += r;\n\n        return ret;\n    }\n\n    // Multinomial\
    \ coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n    // Complexity:\
    \ O(sum(ks))\n    template <class Vec> static ModInt multinomial(const Vec &ks)\
    \ {\n        ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n\
    \            assert(k >= 0);\n            ret *= ModInt(k).facinv(), sum += k;\n\
    \        }\n        return ret * ModInt(sum).fac();\n    }\n\n    // Catalan number,\
    \ C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4\
    \ = 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt(n * 2).fac() * ModInt(n + 1).facinv() * ModInt(n).facinv();\n    }\n\n\
    \    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
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
    // using mint = ModInt<1000000007>;\n#line 5 \"utilities/test/kth_power_sum.yuki665.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    long long n;\n    int k;\n    cin\
    \ >> n >> k;\n\n    kth_power_sum<ModInt<1000000007>> kps;\n\n    cout << kps.prefix_sum(k,\
    \ n) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/665\"\n#include \"../kth_power_sum.hpp\"\
    \n#include \"../../modint.hpp\"\n#include <iostream>\nusing namespace std;\n\n\
    int main() {\n    long long n;\n    int k;\n    cin >> n >> k;\n\n    kth_power_sum<ModInt<1000000007>>\
    \ kps;\n\n    cout << kps.prefix_sum(k, n) << '\\n';\n}\n"
  dependsOn:
  - utilities/kth_power_sum.hpp
  - modint.hpp
  isVerificationFile: true
  path: utilities/test/kth_power_sum.yuki665.test.cpp
  requiredBy: []
  timestamp: '2024-12-02 06:13:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/kth_power_sum.yuki665.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/kth_power_sum.yuki665.test.cpp
- /verify/utilities/test/kth_power_sum.yuki665.test.cpp.html
title: utilities/test/kth_power_sum.yuki665.test.cpp
---
