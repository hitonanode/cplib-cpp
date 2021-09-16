---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_prefix.hpp
    title: string/longest_common_prefix.hpp
  - icon: ':heavy_check_mark:'
    path: tree/lca_rmq.hpp
    title: "Lowest common ancestor of tree based on sparse table \uFF08\u30AF\u30A8\
      \u30EA $O(1)$ \u306E\u6700\u5C0F\u5171\u901A\u7956\u5148\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table.test.cpp
    title: sparse_table/test/sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table_aoj.test.cpp
    title: sparse_table/test/sparse_table_aoj.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_rmq.test.cpp
    title: string/test/run_enumerate_lyndon_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/lca_rmq.test.cpp
    title: tree/test/lca_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Range Minimum Query\
    \ for static sequence by sparse table\n// Complexity: $O(N \\log N)$ for precalculation,\
    \ $O(1)$ per query\ntemplate <typename T> struct StaticRMQ {\n    inline T func(const\
    \ T &l, const T &r) const noexcept { return std::min<T>(l, r); }\n    int N, lgN;\n\
    \    T defaultT;\n    std::vector<std::vector<T>> data;\n    std::vector<int>\
    \ lgx_table;\n    StaticRMQ() = default;\n    StaticRMQ(const std::vector<T> &sequence,\
    \ T defaultT) : N(sequence.size()), defaultT(defaultT) {\n        lgx_table.resize(N\
    \ + 1);\n        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >>\
    \ 1] + 1;\n        lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N,\
    \ defaultT));\n        data[0] = sequence;\n        for (int d = 1; d < lgN; d++)\
    \ {\n            for (int i = 0; i + (1 << d) <= N; i++) {\n                data[d][i]\
    \ = func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);\n            }\n  \
    \      }\n    }\n    T get(int l, int r) const { // [l, r), 0-indexed\n      \
    \  assert(l >= 0 and r <= N);\n        if (l >= r) return defaultT;\n        int\
    \ d = lgx_table[r - l];\n        return func(data[d][l], data[d][r - (1 << d)]);\n\
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n// CUT begin\n// Range Minimum Query for static sequence by sparse table\n//\
    \ Complexity: $O(N \\log N)$ for precalculation, $O(1)$ per query\ntemplate <typename\
    \ T> struct StaticRMQ {\n    inline T func(const T &l, const T &r) const noexcept\
    \ { return std::min<T>(l, r); }\n    int N, lgN;\n    T defaultT;\n    std::vector<std::vector<T>>\
    \ data;\n    std::vector<int> lgx_table;\n    StaticRMQ() = default;\n    StaticRMQ(const\
    \ std::vector<T> &sequence, T defaultT) : N(sequence.size()), defaultT(defaultT)\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) {\n                data[d][i] = func(data[d - 1][i], data[d -\
    \ 1][i + (1 << (d - 1))]);\n            }\n        }\n    }\n    T get(int l,\
    \ int r) const { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n  \
    \      if (l >= r) return defaultT;\n        int d = lgx_table[r - l];\n     \
    \   return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/rmq_sparse_table.hpp
  requiredBy:
  - tree/lca_rmq.hpp
  - string/longest_common_prefix.hpp
  timestamp: '2021-03-13 17:28:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/lca_rmq.test.cpp
  - string/test/run_enumerate_lyndon_rmq.test.cpp
  - sparse_table/test/sparse_table.test.cpp
  - sparse_table/test/sparse_table_aoj.test.cpp
documentation_of: sparse_table/rmq_sparse_table.hpp
layout: document
redirect_from:
- /library/sparse_table/rmq_sparse_table.hpp
- /library/sparse_table/rmq_sparse_table.hpp.html
title: sparse_table/rmq_sparse_table.hpp
---
