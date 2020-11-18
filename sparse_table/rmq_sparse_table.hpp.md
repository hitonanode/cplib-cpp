---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table.test.cpp
    title: sparse_table/test/sparse_table.test.cpp
  - icon: ':x:'
    path: sparse_table/test/sparse_table_aoj.test.cpp
    title: sparse_table/test/sparse_table_aoj.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Range Minimum Query\
    \ for static sequence by sparse table\n// Complexity: O(NlogN) for precalculation,\
    \ O(1) per query\ntemplate <typename T> struct StaticRMQ {\n    inline T func(const\
    \ T &l, const T &r) { return std::min<T>(l, r); }\n    int N, lgN;\n    T defaultT;\n\
    \    std::vector<std::vector<T>> data;\n    std::vector<int> lgx_table;\n    StaticRMQ(const\
    \ std::vector<T> &sequence, T defaultT) : N(sequence.size()), defaultT(defaultT)\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) { data[d][i] = func(data[d - 1][i], data[d - 1][i + (1 << (d -\
    \ 1))]); }\n        }\n    }\n    T get(int l, int r) { // [l, r), 0-indexed\n\
    \        assert(l >= 0 and r <= N);\n        if (l >= r) return defaultT;\n  \
    \      int d = lgx_table[r - l];\n        return func(data[d][l], data[d][r -\
    \ (1 << d)]);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n// CUT begin\n// Range Minimum Query for static sequence by sparse table\n//\
    \ Complexity: O(NlogN) for precalculation, O(1) per query\ntemplate <typename\
    \ T> struct StaticRMQ {\n    inline T func(const T &l, const T &r) { return std::min<T>(l,\
    \ r); }\n    int N, lgN;\n    T defaultT;\n    std::vector<std::vector<T>> data;\n\
    \    std::vector<int> lgx_table;\n    StaticRMQ(const std::vector<T> &sequence,\
    \ T defaultT) : N(sequence.size()), defaultT(defaultT) {\n        lgx_table.resize(N\
    \ + 1);\n        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >>\
    \ 1] + 1;\n        lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N,\
    \ defaultT));\n        data[0] = sequence;\n        for (int d = 1; d < lgN; d++)\
    \ {\n            for (int i = 0; i + (1 << d) <= N; i++) { data[d][i] = func(data[d\
    \ - 1][i], data[d - 1][i + (1 << (d - 1))]); }\n        }\n    }\n    T get(int\
    \ l, int r) { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n     \
    \   if (l >= r) return defaultT;\n        int d = lgx_table[r - l];\n        return\
    \ func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/rmq_sparse_table.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - sparse_table/test/sparse_table_aoj.test.cpp
  - sparse_table/test/sparse_table.test.cpp
documentation_of: sparse_table/rmq_sparse_table.hpp
layout: document
redirect_from:
- /library/sparse_table/rmq_sparse_table.hpp
- /library/sparse_table/rmq_sparse_table.hpp.html
title: sparse_table/rmq_sparse_table.hpp
---
