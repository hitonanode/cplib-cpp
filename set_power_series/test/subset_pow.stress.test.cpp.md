---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/subset_convolution.hpp
    title: "Subset convolution \uFF08\u96C6\u5408\u95A2\u6570\u306E\u5404\u7A2E\u6F14\
      \u7B97\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"set_power_series/test/subset_pow.stress.test.cpp\"\n// Stress\
    \ test by comparing subset subset_pow(f, k) & subset_conv (x k times)\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
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
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v - md : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + md); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % md); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % md); }\n  \
    \  MDCONST ModInt operator-() const { return ModInt()._setval(md - val); }\n \
    \   MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % md + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x)\
    \ { return ModInt()._setval(a % md - x.val + md); }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) { return ModInt()._setval(a % md * x.val\
    \ % md); }\n    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        ModInt ans =\
    \ 1, tmp = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n \
    \           tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n  \
    \  static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static void _precalculation(int\
    \ N) {\n        int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n    MDCONST lint inv() const {\n       \
    \ if (this->val < std::min(md >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val].val;\n\
    \        } else {\n            return this->pow(md - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\
    \    MDCONST ModInt facinv() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val];\n    }\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST\
    \ ModInt nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x\
    \ * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"random/xorshift.hpp\"\
    \n#include <cstdint>\n\n// CUT begin\nuint32_t rand_int() // XorShift random integer\
    \ generator\n{\n    static uint32_t x = 123456789, y = 362436069, z = 521288629,\
    \ w = 88675123;\n    uint32_t t = x ^ (x << 11);\n    x = y;\n    y = z;\n   \
    \ z = w;\n    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double()\
    \ { return (double)rand_int() / UINT32_MAX; }\n#line 2 \"set_power_series/subset_convolution.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#line 5 \"set_power_series/subset_convolution.hpp\"\
    \n\n// CUT begin\n// Subset sum (fast zeta transform)\n// Complexity: O(N 2^N)\
    \ for array of size 2^N\ntemplate <typename T> void subset_sum(std::vector<T>\
    \ &f) {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (S & (1 << d)) f[S] += f[S ^ (1 << d)];\n    }\n}\n\
    // Inverse of subset sum (fast moebius transform)\n// Complexity: O(N 2^N) for\
    \ array of size 2^N\ntemplate <typename T> void subset_sum_inv(std::vector<T>\
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
    \    return ret;\n}\n\n// https://hos-lyric.hatenablog.com/entry/2021/01/14/201231\n\
    template <class T, class Function> void subset_func(std::vector<T> &f, const Function\
    \ &func) {\n    const int sz = f.size(), m = __builtin_ctz(sz) + 1;\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    std::vector<std::vector<T>> ff(m, std::vector<T>(sz));\n    for\
    \ (int i = 0; i < sz; i++) ff[__builtin_popcount(i)][i] += f[i];\n    for (auto\
    \ &vec : ff) subset_sum(vec);\n\n    std::vector<T> p(m);\n    for (int i = 0;\
    \ i < sz; i++) {\n        for (int d = 0; d < m; d++) p[d] = ff[d][i];\n     \
    \   func(p);\n        for (int d = 0; d < m; d++) ff[d][i] = p[d];\n    }\n\n\
    \    for (auto &vec : ff) subset_sum_inv(vec);\n    for (int i = 0; i < sz; i++)\
    \ f[i] = ff[__builtin_popcount(i)][i];\n}\n\n// log(f(x)) for f(x), f(0) == 1\n\
    // Requires inv()\ntemplate <class T> void poly_log(std::vector<T> &f) {\n   \
    \ assert(f.at(0) == T(1));\n    static std::vector<T> invs{0};\n    const int\
    \ m = f.size();\n    std::vector<T> finv(m);\n    for (int d = 0; d < m; d++)\
    \ {\n        finv[d] = (d == 0);\n        if (int(invs.size()) <= d) invs.push_back(T(d).inv());\n\
    \        for (int e = 0; e < d; e++) finv[d] -= finv[e] * f[d - e];\n    }\n \
    \   std::vector<T> ret(m);\n    for (int d = 1; d < m; d++) {\n        for (int\
    \ e = 0; d + e < m; e++) ret[d + e] += f[d] * d * finv[e] * invs[d + e];\n   \
    \ }\n    f = ret;\n}\n\n// log(f(S)) for set function f(S), f(0) == 1\n// Requires\
    \ inv()\n// Complexity: O(n^2 2^n)\n// https://atcoder.jp/contests/abc213/tasks/abc213_g\n\
    template <class T> void subset_log(std::vector<T> &f) { subset_func(f, poly_log<T>);\
    \ }\n\n// exp(f(S)) for set function f(S), f(0) == 0\n// Complexity: O(n^2 2^n)\n\
    // https://codeforces.com/blog/entry/92183\ntemplate <class T> void subset_exp(std::vector<T>\
    \ &f) {\n    const int sz = f.size(), m = __builtin_ctz(sz);\n    assert(sz ==\
    \ 1 << m);\n    assert(f.at(0) == 0);\n    std::vector<T> ret{T(1)};\n    ret.reserve(sz);\n\
    \    for (int d = 0; d < m; d++) {\n        auto c = subset_convolution({f.begin()\
    \ + (1 << d), f.begin() + (1 << (d + 1))}, ret);\n        ret.insert(ret.end(),\
    \ c.begin(), c.end());\n    }\n    f = ret;\n}\n\n// sqrt(f(x)), f(x) == 1\n//\
    \ Requires inv of 2\n// Compelxity: O(n^2)\ntemplate <class T> void poly_sqrt(std::vector<T>\
    \ &f) {\n    assert(f.at(0) == T(1));\n    const int m = f.size();\n    static\
    \ const auto inv2 = T(2).inv();\n    for (int d = 1; d < m; d++) {\n        if\
    \ (~(d & 1)) f[d] -= f[d / 2] * f[d / 2];\n        f[d] *= inv2;\n        for\
    \ (int e = 1; e < d - e; e++) f[d] -= f[e] * f[d - e];\n    }\n}\n\n// sqrt(f(S))\
    \ for set function f(S), f(0) == 1\n// Requires inv()\n// https://atcoder.jp/contests/xmascon20/tasks/xmascon20_h\n\
    template <class T> void subset_sqrt(std::vector<T> &f) { subset_func(f, poly_sqrt<T>);\
    \ }\n\n// exp(f(S)) for set function f(S), f(0) == 0\ntemplate <class T> void\
    \ poly_exp(std::vector<T> &P) {\n    const int m = P.size();\n    assert(m and\
    \ P[0] == 0);\n    std::vector<T> Q(m), logQ(m), Qinv(m);\n    Q[0] = Qinv[0]\
    \ = T(1);\n    static std::vector<T> invs{0};\n\n    auto set_invlog = [&](int\
    \ d) {\n        Qinv[d] = 0;\n        for (int e = 0; e < d; e++) Qinv[d] -= Qinv[e]\
    \ * Q[d - e];\n        while (d >= int(invs.size())) {\n            int sz = invs.size();\n\
    \            invs.push_back(T(sz).inv());\n        }\n        logQ[d] = 0;\n \
    \       for (int e = 1; e <= d; e++) logQ[d] += Q[e] * e * Qinv[d - e];\n    \
    \    logQ[d] *= invs[d];\n    };\n    for (int d = 1; d < m; d++) {\n        Q[d]\
    \ += P[d] - logQ[d];\n        set_invlog(d);\n        assert(logQ[d] == P[d]);\n\
    \        if (d + 1 < m) set_invlog(d + 1);\n    }\n    P = Q;\n}\n\n// f(S)^k\
    \ for set function f(S)\n// Requires inv()\ntemplate <class T> void subset_pow(std::vector<T>\
    \ &f, long long k) {\n    auto poly_pow = [&](std::vector<T> &f) {\n        const\
    \ int m = f.size();\n        if (k == 0) f[0] = 1, std::fill(f.begin() + 1, f.end(),\
    \ T(0));\n        if (k <= 1) return;\n        int nzero = 0;\n        while (nzero\
    \ < int(f.size()) and f[nzero] == T(0)) nzero++;\n        int rem = std::max<long\
    \ long>((long long)f.size() - nzero * k, 0LL);\n        if (rem == 0) {\n    \
    \        std::fill(f.begin(), f.end(), 0);\n            return;\n        }\n \
    \       f.erase(f.begin(), f.begin() + nzero);\n        f.resize(rem);\n     \
    \   const T f0 = f.at(0), f0inv = f0.inv(), f0pow = f0.pow(k);\n        for (auto\
    \ &x : f) x *= f0inv;\n        poly_log(f);\n        for (auto &x : f) x *= k;\n\
    \        poly_exp(f);\n        for (auto &x : f) x *= f0pow;\n        f.resize(rem,\
    \ 0);\n        f.insert(f.begin(), m - int(f.size()), T(0));\n    };\n    subset_func(f,\
    \ poly_pow);\n}\n#line 9 \"set_power_series/test/subset_pow.stress.test.cpp\"\n\
    using namespace std;\n\nvoid test_polylog_polyexp() {\n    using mint = ModInt<11>;\n\
    \    for (int len = 1; len < 10; len++) {\n        for (int t = 0; t < 100000;\
    \ t++) {\n            vector<mint> f(len, 1);\n            for (int i = 1; i <\
    \ len; i++) f[i] = rand_int() % mint::mod();\n            auto g = f;\n      \
    \      poly_log(g);\n            poly_exp(g);\n            assert(f == g);\n \
    \       }\n    }\n}\n\nvoid test_subset_pow() {\n    using mint = ModInt<7>;\n\
    \    for (int lglen = 0; lglen < 5; lglen++) {\n        const int len = 1 << lglen;\n\
    \        for (int t = 0; t < 100000; t++) {\n            int k = rand_int() %\
    \ 10;\n            vector<mint> f(len);\n            for (auto &x : f) x = rand_int()\
    \ % mint::mod();\n            auto gpow = f;\n            subset_pow(gpow, k);\n\
    \            vector<mint> gconv(len);\n            gconv[0] = 1;\n           \
    \ for (int j = 0; j < k; j++) gconv = subset_convolution(gconv, f);\n        \
    \    assert(gpow == gconv);\n        }\n    }\n}\n\nint main() {\n    test_polylog_polyexp();\n\
    \    test_subset_pow();\n    cout << \"Hello World\\n\";\n}\n"
  code: "// Stress test by comparing subset subset_pow(f, k) & subset_conv (x k times)\n\
    #define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../../modint.hpp\"\n#include \"../../random/xorshift.hpp\"\
    \n#include \"../subset_convolution.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\nusing namespace std;\n\nvoid test_polylog_polyexp() {\n   \
    \ using mint = ModInt<11>;\n    for (int len = 1; len < 10; len++) {\n       \
    \ for (int t = 0; t < 100000; t++) {\n            vector<mint> f(len, 1);\n  \
    \          for (int i = 1; i < len; i++) f[i] = rand_int() % mint::mod();\n  \
    \          auto g = f;\n            poly_log(g);\n            poly_exp(g);\n \
    \           assert(f == g);\n        }\n    }\n}\n\nvoid test_subset_pow() {\n\
    \    using mint = ModInt<7>;\n    for (int lglen = 0; lglen < 5; lglen++) {\n\
    \        const int len = 1 << lglen;\n        for (int t = 0; t < 100000; t++)\
    \ {\n            int k = rand_int() % 10;\n            vector<mint> f(len);\n\
    \            for (auto &x : f) x = rand_int() % mint::mod();\n            auto\
    \ gpow = f;\n            subset_pow(gpow, k);\n            vector<mint> gconv(len);\n\
    \            gconv[0] = 1;\n            for (int j = 0; j < k; j++) gconv = subset_convolution(gconv,\
    \ f);\n            assert(gpow == gconv);\n        }\n    }\n}\n\nint main() {\n\
    \    test_polylog_polyexp();\n    test_subset_pow();\n    cout << \"Hello World\\\
    n\";\n}\n"
  dependsOn:
  - modint.hpp
  - random/xorshift.hpp
  - set_power_series/subset_convolution.hpp
  isVerificationFile: true
  path: set_power_series/test/subset_pow.stress.test.cpp
  requiredBy: []
  timestamp: '2021-08-09 14:30:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: set_power_series/test/subset_pow.stress.test.cpp
layout: document
redirect_from:
- /verify/set_power_series/test/subset_pow.stress.test.cpp
- /verify/set_power_series/test/subset_pow.stress.test.cpp.html
title: set_power_series/test/subset_pow.stress.test.cpp
---
