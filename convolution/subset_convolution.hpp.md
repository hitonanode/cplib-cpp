---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: convolution/test/subset_convolution.test.cpp
    title: convolution/test/subset_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"convolution/subset_convolution.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// CUT begin\n// Subset sum (fast zeta transform)\n// Complexity:\
    \ O(N 2^N) for array of size 2^N\ntemplate <typename T> void subset_sum(std::vector<T>\
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
    \    return ret;\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Subset\
    \ sum (fast zeta transform)\n// Complexity: O(N 2^N) for array of size 2^N\ntemplate\
    \ <typename T> void subset_sum(std::vector<T> &f) {\n    const int sz = f.size(),\
    \ n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz) == 1);\n    for (int\
    \ d = 0; d < n; d++) {\n        for (int S = 0; S < 1 << n; S++)\n           \
    \ if (S & (1 << d)) f[S] += f[S ^ (1 << d)];\n    }\n}\n// Inverse of subset sum\
    \ (fast moebius transform)\n// Complexity: O(N 2^N) for array of size 2^N\ntemplate\
    \ <typename T> void subset_sum_inv(std::vector<T> &g) {\n    const int sz = g.size(),\
    \ n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz) == 1);\n    for (int\
    \ d = 0; d < n; d++) {\n        for (int S = 0; S < 1 << n; S++)\n           \
    \ if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];\n    }\n}\n\n// Superset sum / its\
    \ inverse (fast zeta/moebius transform)\n// Complexity: O(N 2^N) for array of\
    \ size 2^N\ntemplate <typename T> void superset_sum(std::vector<T> &f) {\n   \
    \ const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
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
    \    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/subset_convolution.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:06:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - convolution/test/subset_convolution.test.cpp
documentation_of: convolution/subset_convolution.hpp
layout: document
redirect_from:
- /library/convolution/subset_convolution.hpp
- /library/convolution/subset_convolution.hpp.html
title: convolution/subset_convolution.hpp
---
