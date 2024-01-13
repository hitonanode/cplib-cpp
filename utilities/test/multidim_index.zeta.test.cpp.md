---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/multidim_index.hpp
    title: Multidimensional index
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"utilities/test/multidim_index.zeta.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n#line 2 \"modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \ntemplate <int md> struct ModInt {\n    using lint = long long;\n    constexpr\
    \ static int mod() { return md; }\n    static int get_primitive_root() {\n   \
    \     static int primitive_root = 0;\n        if (!primitive_root) {\n       \
    \     primitive_root = [&]() {\n                std::set<int> fac;\n         \
    \       int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n \
    \                   while (v % i == 0) fac.insert(i), v /= i;\n              \
    \  if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    constexpr\
    \ ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint v) { return val_ =\
    \ (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint v) { _setval(v %\
    \ md + md); }\n    constexpr explicit operator bool() const { return val_ != 0;\
    \ }\n    constexpr ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    constexpr ModInt operator-(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    constexpr ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    constexpr ModInt operator-() const { return ModInt()._setval(md - val_);\
    \ }\n    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this\
    \ + x; }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint a,\
    \ const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
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
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n \
    \   constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
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
    // using mint = ModInt<1000000007>;\n#line 3 \"utilities/multidim_index.hpp\"\n\
    \n// n-dimentional index <-> 1-dimentional index converter\n// [a_0, ..., a_{dim\
    \ - 1}] <-> a_0 + a_1 * size_0 + ... + a_{dim - 1} * (size_0 * ... * size_{dim\
    \ - 2})\ntemplate <class T = int> struct multidim_index {\n    int dim = 0;\n\
    \    T _size = 1;\n    std::vector<T> sizes;\n    std::vector<T> weights;\n\n\
    \    multidim_index() = default;\n\n    explicit multidim_index(const std::vector<T>\
    \ &sizes)\n        : dim(sizes.size()), sizes(sizes), weights(dim, T(1)) {\n \
    \       for (int d = 0; d < (int)sizes.size(); ++d) {\n            assert(sizes.at(d)\
    \ > 0);\n            _size *= sizes.at(d);\n            if (d >= 1) weights.at(d)\
    \ = weights.at(d - 1) * sizes.at(d - 1);\n        }\n    }\n\n    T size() const\
    \ { return _size; }\n\n    T flat_index(const std::vector<T> &encoded_vec) const\
    \ {\n        assert((int)encoded_vec.size() == (int)sizes.size());\n        T\
    \ ret = 0;\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n          \
    \  assert(0 <= encoded_vec.at(d) and encoded_vec.at(d) < sizes.at(d));\n     \
    \       ret += encoded_vec.at(d) * weights.at(d);\n        }\n        return ret;\n\
    \    }\n\n    std::vector<T> encode(T flat_index) const {\n        assert(0 <=\
    \ flat_index and flat_index < size());\n        std::vector<T> ret(sizes.size());\n\
    \        for (int d = (int)sizes.size() - 1; d >= 0; --d) {\n            ret.at(d)\
    \ = flat_index / weights.at(d);\n            flat_index %= weights.at(d);\n  \
    \      }\n        return ret;\n    }\n\n    template <class F> void lo_to_hi(F\
    \ f) {\n        for (int d = 0; d < (int)sizes.size(); ++d) {\n            if\
    \ (sizes.at(d) == 1) continue;\n\n            T i = 0;\n            std::vector<T>\
    \ ivec(sizes.size());\n\n            int cur = sizes.size();\n\n            while\
    \ (true) {\n                f(i, i + weights.at(d));\n                --cur;\n\
    \n                while (cur >= 0 and ivec.at(cur) + 1 == sizes.at(cur) - (cur\
    \ == d)) {\n                    i -= ivec.at(cur) * weights.at(cur);\n       \
    \             ivec.at(cur--) = 0;\n                }\n\n                if (cur\
    \ < 0) break;\n\n                ++ivec.at(cur);\n                i += weights.at(cur);\n\
    \                cur = sizes.size();\n            }\n        }\n    }\n\n    //\
    \ Subset sum (fast zeta transform)\n    template <class U> void subset_sum(std::vector<U>\
    \ &vec) {\n        assert((T)vec.size() == size());\n        lo_to_hi([&](T lo,\
    \ T hi) { vec.at(hi) += vec.at(lo); });\n    }\n\n    // Inverse of subset sum\
    \ (fast moebius transform)\n    template <class U> void subset_sum_inv(std::vector<U>\
    \ &vec) {\n        assert((T)vec.size() == size());\n        const T s = size()\
    \ - 1;\n        lo_to_hi([&](T dummylo, T dummyhi) { vec.at(s - dummylo) -= vec.at(s\
    \ - dummyhi); });\n    }\n\n    // Superset sum (fast zeta transform)\n    template\
    \ <class U> void superset_sum(std::vector<U> &vec) {\n        assert((T)vec.size()\
    \ == size());\n        const T s = size() - 1;\n        lo_to_hi([&](T dummylo,\
    \ T dummyhi) { vec.at(s - dummyhi) += vec.at(s - dummylo); });\n    }\n\n    //\
    \ Inverse of superset sum (fast moebius transform)\n    template <class U> void\
    \ superset_sum_inv(std::vector<U> &vec) {\n        assert((T)vec.size() == size());\n\
    \        lo_to_hi([&](T lo, T hi) { vec.at(lo) -= vec.at(hi); });\n    }\n};\n\
    #line 4 \"utilities/test/multidim_index.zeta.test.cpp\"\n\n#line 7 \"utilities/test/multidim_index.zeta.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n\n    multidim_index mi(std::vector<int>(N, 2));\n\
    \    vector<ModInt<998244353>> A(1 << N), B(1 << N);\n\n    for (auto &x : A)\
    \ cin >> x;\n    for (auto &x : B) cin >> x;\n    mi.superset_sum(A);\n    mi.superset_sum(B);\n\
    \    for (int i = 0; i < 1 << N; ++i) A.at(i) *= B.at(i);\n    mi.superset_sum_inv(A);\n\
    \n    for (auto x : A) cout << x << ' ';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n#include \"../../modint.hpp\"\n#include \"../multidim_index.hpp\"\n\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N;\n    cin >> N;\n\n    multidim_index\
    \ mi(std::vector<int>(N, 2));\n    vector<ModInt<998244353>> A(1 << N), B(1 <<\
    \ N);\n\n    for (auto &x : A) cin >> x;\n    for (auto &x : B) cin >> x;\n  \
    \  mi.superset_sum(A);\n    mi.superset_sum(B);\n    for (int i = 0; i < 1 <<\
    \ N; ++i) A.at(i) *= B.at(i);\n    mi.superset_sum_inv(A);\n\n    for (auto x\
    \ : A) cout << x << ' ';\n}\n"
  dependsOn:
  - modint.hpp
  - utilities/multidim_index.hpp
  isVerificationFile: true
  path: utilities/test/multidim_index.zeta.test.cpp
  requiredBy: []
  timestamp: '2024-01-13 20:41:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: utilities/test/multidim_index.zeta.test.cpp
layout: document
redirect_from:
- /verify/utilities/test/multidim_index.zeta.test.cpp
- /verify/utilities/test/multidim_index.zeta.test.cpp.html
title: utilities/test/multidim_index.zeta.test.cpp
---
