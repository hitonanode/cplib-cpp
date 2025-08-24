---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: set_power_series/subset_convolution.hpp
    title: "Subset convolution \uFF08\u96C6\u5408\u95A2\u6570\u306E\u5404\u7A2E\u6F14\
      \u7B97\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/hafnian.test.cpp
    title: linear_algebra_matrix/test/hafnian.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
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
    \ poly_pow);\n}\n#line 4 \"linear_algebra_matrix/hafnian.hpp\"\n\n// Count perfect\
    \ matchings of undirected graph (Hafnian of the matrix)\n// Assumption: mat[i][j]\
    \ == mat[j][i], mat[i][i] == 0\n// Complexity: O(n^2 2^n)\n// [1] A. Bj\xF6rklund,\
    \ \"Counting Perfect Matchings as Fast as Ryser,\n//     Proc. of 23rd ACM-SIAM\
    \ symposium on Discrete Algorithms, pp.914-921, 2012.\ntemplate <class T> T hafnian(const\
    \ std::vector<std::vector<T>> &mat) {\n    const int N = mat.size();\n    if (N\
    \ % 2) return 0;\n    std::vector<std::vector<std::vector<T>>> B(N, std::vector<std::vector<T>>(N));\n\
    \    for (int i = 0; i < N; i++) {\n        for (int j = 0; j < N; j++) B[i][j]\
    \ = std::vector<T>{mat[i][j]};\n    }\n\n    std::vector<int> pc(1 << (N / 2));\n\
    \    std::vector<std::vector<int>> pc2i(N / 2 + 1);\n    for (int i = 0; i < int(pc.size());\
    \ i++) {\n        pc[i] = __builtin_popcount(i);\n        pc2i[pc[i]].push_back(i);\n\
    \    }\n\n    std::vector<T> h{1};\n    for (int i = 1; i < N / 2; i++) {\n  \
    \      int r1 = N - i * 2, r2 = r1 + 1;\n        auto h_add = subset_convolution(h,\
    \ B[r2][r1]);\n        h.insert(h.end(), h_add.begin(), h_add.end());\n\n    \
    \    std::vector<std::vector<std::vector<T>>> B1(r1), B2(r1);\n        for (int\
    \ j = 0; j < r1; j++) {\n            B1[j] = build_zeta_(i, B[r1][j]);\n     \
    \       B2[j] = build_zeta_(i, B[r2][j]);\n        }\n\n        for (int j = 0;\
    \ j < r1; j++) {\n            for (int k = 0; k < j; k++) {\n                auto\
    \ Sijk1 = get_moebius_of_prod_(B1[j], B2[k]);\n                auto Sijk2 = get_moebius_of_prod_(B1[k],\
    \ B2[j]);\n                for (int s = 0; s < int(Sijk2.size()); s++) Sijk1[s]\
    \ += Sijk2[s];\n                B[j][k].insert(B[j][k].end(), Sijk1.begin(), Sijk1.end());\n\
    \            }\n        }\n    }\n    T ret = 0;\n    for (int i = 0; i < int(h.size());\
    \ i++) ret += h[i] * B[1][0][h.size() - 1 - i];\n    return ret;\n}\n"
  code: "#pragma once\n#include \"../set_power_series/subset_convolution.hpp\"\n#include\
    \ <vector>\n\n// Count perfect matchings of undirected graph (Hafnian of the matrix)\n\
    // Assumption: mat[i][j] == mat[j][i], mat[i][i] == 0\n// Complexity: O(n^2 2^n)\n\
    // [1] A. Bj\xF6rklund, \"Counting Perfect Matchings as Fast as Ryser,\n//   \
    \  Proc. of 23rd ACM-SIAM symposium on Discrete Algorithms, pp.914-921, 2012.\n\
    template <class T> T hafnian(const std::vector<std::vector<T>> &mat) {\n    const\
    \ int N = mat.size();\n    if (N % 2) return 0;\n    std::vector<std::vector<std::vector<T>>>\
    \ B(N, std::vector<std::vector<T>>(N));\n    for (int i = 0; i < N; i++) {\n \
    \       for (int j = 0; j < N; j++) B[i][j] = std::vector<T>{mat[i][j]};\n   \
    \ }\n\n    std::vector<int> pc(1 << (N / 2));\n    std::vector<std::vector<int>>\
    \ pc2i(N / 2 + 1);\n    for (int i = 0; i < int(pc.size()); i++) {\n        pc[i]\
    \ = __builtin_popcount(i);\n        pc2i[pc[i]].push_back(i);\n    }\n\n    std::vector<T>\
    \ h{1};\n    for (int i = 1; i < N / 2; i++) {\n        int r1 = N - i * 2, r2\
    \ = r1 + 1;\n        auto h_add = subset_convolution(h, B[r2][r1]);\n        h.insert(h.end(),\
    \ h_add.begin(), h_add.end());\n\n        std::vector<std::vector<std::vector<T>>>\
    \ B1(r1), B2(r1);\n        for (int j = 0; j < r1; j++) {\n            B1[j] =\
    \ build_zeta_(i, B[r1][j]);\n            B2[j] = build_zeta_(i, B[r2][j]);\n \
    \       }\n\n        for (int j = 0; j < r1; j++) {\n            for (int k =\
    \ 0; k < j; k++) {\n                auto Sijk1 = get_moebius_of_prod_(B1[j], B2[k]);\n\
    \                auto Sijk2 = get_moebius_of_prod_(B1[k], B2[j]);\n          \
    \      for (int s = 0; s < int(Sijk2.size()); s++) Sijk1[s] += Sijk2[s];\n   \
    \             B[j][k].insert(B[j][k].end(), Sijk1.begin(), Sijk1.end());\n   \
    \         }\n        }\n    }\n    T ret = 0;\n    for (int i = 0; i < int(h.size());\
    \ i++) ret += h[i] * B[1][0][h.size() - 1 - i];\n    return ret;\n}\n"
  dependsOn:
  - set_power_series/subset_convolution.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/hafnian.hpp
  requiredBy: []
  timestamp: '2021-10-16 14:40:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/hafnian.test.cpp
documentation_of: linear_algebra_matrix/hafnian.hpp
layout: document
title: "Hafnian \uFF08\u884C\u5217\u306E\u30CF\u30D5\u30CB\u30A2\u30F3\uFF0C\u7121\
  \u5411\u30B0\u30E9\u30D5\u306E\u5B8C\u5168\u30DE\u30C3\u30C1\u30F3\u30B0\u306E\u6570\
  \u3048\u4E0A\u3052\uFF09"
---

全ての対角成分がゼロの $N \times N$ 対称行列 $\mathbf{M}$ のハフニアン（完全マッチングの個数）を $O(N^2 2^N)$ で求める．

## 問題例

- [Library Checker: Hafnian of Matrix](https://judge.yosupo.jp/problem/hafnian_of_matrix) $N \le 38$, $\bmod 998244353$ で 2.5 秒程度．

## References

- [1] A. Björklund, "Counting Perfect Matchings as Fast as Ryser,
  Proc. of 23rd ACM-SIAM symposium on Discrete Algorithms, pp.914–921, 2012.
