---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/hafnian.hpp
    title: "Hafnian \uFF08\u884C\u5217\u306E\u30CF\u30D5\u30CB\u30A2\u30F3\uFF0C\u7121\
      \u5411\u30B0\u30E9\u30D5\u306E\u5B8C\u5168\u30DE\u30C3\u30C1\u30F3\u30B0\u306E\
      \u6570\u3048\u4E0A\u3052\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/hafnian.test.cpp
    title: linear_algebra_matrix/test/hafnian.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_conv.test.cpp
    title: set_power_series/test/subset_conv.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_exp.stress.test.cpp
    title: set_power_series/test/subset_exp.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_log.test.cpp
    title: set_power_series/test/subset_log.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_pow.stress.test.cpp
    title: set_power_series/test/subset_pow.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/test/subset_pow.yuki1594.test.cpp
    title: set_power_series/test/subset_pow.yuki1594.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc213/tasks/abc213_g
    - https://atcoder.jp/contests/xmascon20/tasks/xmascon20_h
    - https://codeforces.com/blog/entry/92183
    - https://hos-lyric.hatenablog.com/entry/2021/01/14/201231
  bundledCode: "#line 2 \"set_power_series/subset_convolution.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Subset sum (fast zeta\
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
    }\n\ntemplate <typename T> std::vector<std::vector<T>> build_zeta_(int D, const\
    \ std::vector<T> &f) {\n    int n = f.size();\n    std::vector<std::vector<T>>\
    \ ret(D, std::vector<T>(n));\n    for (int i = 0; i < n; i++) ret[__builtin_popcount(i)][i]\
    \ += f[i];\n    for (auto &vec : ret) subset_sum(vec);\n    return ret;\n}\n\n\
    template <typename T>\nstd::vector<T> get_moebius_of_prod_(const std::vector<std::vector<T>>\
    \ &mat1,\n                                    const std::vector<std::vector<T>>\
    \ &mat2) {\n    int D = mat1.size(), n = mat1[0].size();\n    std::vector<std::vector<int>>\
    \ pc2i(D);\n    for (int i = 0; i < n; i++) pc2i[__builtin_popcount(i)].push_back(i);\n\
    \    std::vector<T> tmp, ret(mat1[0].size());\n    for (int d = 0; d < D; d++)\
    \ {\n        tmp.assign(mat1[d].size(), 0);\n        for (int e = 0; e <= d; e++)\
    \ {\n            for (int i = 0; i < int(tmp.size()); i++) tmp[i] += mat1[e][i]\
    \ * mat2[d - e][i];\n        }\n        subset_sum_inv(tmp);\n        for (auto\
    \ i : pc2i[d]) ret[i] = tmp[i];\n    }\n    return ret;\n};\n\n// Subset convolution\n\
    // h[S] = \\sum_T f[T] * g[S - T]\n// Complexity: O(N^2 2^N) for arrays of size\
    \ 2^N\ntemplate <typename T> std::vector<T> subset_convolution(std::vector<T>\
    \ f, std::vector<T> g) {\n    const int sz = f.size(), m = __builtin_ctz(sz) +\
    \ 1;\n    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());\n    auto\
    \ ff = build_zeta_(m, f), fg = build_zeta_(m, g);\n    return get_moebius_of_prod_(ff,\
    \ fg);\n}\n\n// https://hos-lyric.hatenablog.com/entry/2021/01/14/201231\ntemplate\
    \ <class T, class Function> void subset_func(std::vector<T> &f, const Function\
    \ &func) {\n    const int sz = f.size(), m = __builtin_ctz(sz) + 1;\n    assert(__builtin_popcount(sz)\
    \ == 1);\n\n    auto ff = build_zeta_(m, f);\n\n    std::vector<T> p(m);\n   \
    \ for (int i = 0; i < sz; i++) {\n        for (int d = 0; d < m; d++) p[d] = ff[d][i];\n\
    \        func(p);\n        for (int d = 0; d < m; d++) ff[d][i] = p[d];\n    }\n\
    \n    for (auto &vec : ff) subset_sum_inv(vec);\n    for (int i = 0; i < sz; i++)\
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
    \ poly_pow);\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n// CUT begin\n// Subset sum (fast zeta transform)\n// Complexity: O(N 2^N) for\
    \ array of size 2^N\ntemplate <typename T> void subset_sum(std::vector<T> &f)\
    \ {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
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
    }\n\ntemplate <typename T> std::vector<std::vector<T>> build_zeta_(int D, const\
    \ std::vector<T> &f) {\n    int n = f.size();\n    std::vector<std::vector<T>>\
    \ ret(D, std::vector<T>(n));\n    for (int i = 0; i < n; i++) ret[__builtin_popcount(i)][i]\
    \ += f[i];\n    for (auto &vec : ret) subset_sum(vec);\n    return ret;\n}\n\n\
    template <typename T>\nstd::vector<T> get_moebius_of_prod_(const std::vector<std::vector<T>>\
    \ &mat1,\n                                    const std::vector<std::vector<T>>\
    \ &mat2) {\n    int D = mat1.size(), n = mat1[0].size();\n    std::vector<std::vector<int>>\
    \ pc2i(D);\n    for (int i = 0; i < n; i++) pc2i[__builtin_popcount(i)].push_back(i);\n\
    \    std::vector<T> tmp, ret(mat1[0].size());\n    for (int d = 0; d < D; d++)\
    \ {\n        tmp.assign(mat1[d].size(), 0);\n        for (int e = 0; e <= d; e++)\
    \ {\n            for (int i = 0; i < int(tmp.size()); i++) tmp[i] += mat1[e][i]\
    \ * mat2[d - e][i];\n        }\n        subset_sum_inv(tmp);\n        for (auto\
    \ i : pc2i[d]) ret[i] = tmp[i];\n    }\n    return ret;\n};\n\n// Subset convolution\n\
    // h[S] = \\sum_T f[T] * g[S - T]\n// Complexity: O(N^2 2^N) for arrays of size\
    \ 2^N\ntemplate <typename T> std::vector<T> subset_convolution(std::vector<T>\
    \ f, std::vector<T> g) {\n    const int sz = f.size(), m = __builtin_ctz(sz) +\
    \ 1;\n    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());\n    auto\
    \ ff = build_zeta_(m, f), fg = build_zeta_(m, g);\n    return get_moebius_of_prod_(ff,\
    \ fg);\n}\n\n// https://hos-lyric.hatenablog.com/entry/2021/01/14/201231\ntemplate\
    \ <class T, class Function> void subset_func(std::vector<T> &f, const Function\
    \ &func) {\n    const int sz = f.size(), m = __builtin_ctz(sz) + 1;\n    assert(__builtin_popcount(sz)\
    \ == 1);\n\n    auto ff = build_zeta_(m, f);\n\n    std::vector<T> p(m);\n   \
    \ for (int i = 0; i < sz; i++) {\n        for (int d = 0; d < m; d++) p[d] = ff[d][i];\n\
    \        func(p);\n        for (int d = 0; d < m; d++) ff[d][i] = p[d];\n    }\n\
    \n    for (auto &vec : ff) subset_sum_inv(vec);\n    for (int i = 0; i < sz; i++)\
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
    \ poly_pow);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: set_power_series/subset_convolution.hpp
  requiredBy:
  - linear_algebra_matrix/hafnian.hpp
  timestamp: '2021-10-16 14:40:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - set_power_series/test/subset_log.test.cpp
  - set_power_series/test/subset_pow.stress.test.cpp
  - set_power_series/test/subset_exp.stress.test.cpp
  - set_power_series/test/subset_conv.test.cpp
  - set_power_series/test/subset_pow.yuki1594.test.cpp
  - linear_algebra_matrix/test/hafnian.test.cpp
documentation_of: set_power_series/subset_convolution.hpp
layout: document
title: "Subset convolution \uFF08\u96C6\u5408\u95A2\u6570\u306E\u5404\u7A2E\u6F14\u7B97\
  \uFF09"
---

集合関数 $f(S)$ に関する各種演算．

## 使用方法

```cpp
vector<mint> f(1 << n), g(1 << n);
subset_sum(f);                      // T ⊂ S なる T に関する和．O(n 2^n)
subset_sum_inv(f);                  // subset_sum() の逆関数．O(n 2^n)
superset_sum(f);                    // T ⊃ S なる T に関する和．O(n 2^n)
superset_sum_inv(f);                // superset_sum() の逆関数．O(n 2^n)
auto h = subset_convolution(f, g);  // T ∪ U = S なる T, U に関する積の和．O(n^2 2^n)
subset_log(f);                      // f(φ) == 1 なる f について，log(f(S))．O(n^2 2^n)
subset_exp(f);                      // f(φ) == 0 なる f について，exp(f(S))．O(n^2 2^n)
subset_sqrt(f);                     // f(φ) == 1 なる f について，sqrt(f(S))．O(n^2 2^n)
subset_pow(f, k);                      // f(S)^k (O(n^2 2^n))
```

## 問題例

- [Subset Convolution - Library Checker](https://judge.yosupo.jp/problem/subset_convolution) `subset_convolution()`
- [F - Lights Out on Connected Graph](https://atcoder.jp/contests/arc105/tasks/arc105_f) 連結二部グラフの数え上げ．`subset_log()`
- [G - Connectivity 2](https://atcoder.jp/contests/abc213/tasks/abc213_g) 連結グラフの数え上げ．`subset_log()`
- [H - Hierarchical Phylogeny](https://atcoder.jp/contests/xmascon20/tasks/xmascon20_h) `subset_sqrt()`
- [No.1594 Three Classes - yukicoder](https://yukicoder.me/problems/no/1594) `subset_pow()`

## リンク

- [Xmas Contest 2020 H: Hierarchical Phylogeny 解説 - hos.lyric's blog](https://hos-lyric.hatenablog.com/entry/2021/01/14/201231) $\sqrt{f(S)}$ の計算アルゴリズムとその一般化．
- [Optimal Algorithm on Polynomial Composite Set Power Series - Codeforces](https://codeforces.com/blog/entry/92183) $\exp (f(S))$ の計算アルゴリズム（逆元不要）と一般の関数への拡張．
