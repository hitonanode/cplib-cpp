---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table_2d.hpp
    title: sparse_table/sparse_table_2d.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table_aoj.test.cpp
    title: sparse_table/test/sparse_table_aoj.test.cpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table_2d.test.cpp
    title: sparse_table/test/sparse_table_2d.test.cpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table.test.cpp
    title: sparse_table/test/sparse_table.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"sparse_table/sparse_table.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Static sequence sparse table\n// Complexity: O(NlogN)\
    \ for precalculation, O(1) per query\ntemplate<typename T, typename F>\nstruct\
    \ SparseTable {\n    int N, lgN;\n    T defaultT;\n    F func;\n    std::vector<std::vector<T>>\
    \ data;\n    std::vector<int> lgx_table;\n    SparseTable(F func) : func(func)\
    \ {}\n    SparseTable(const std::vector<T> &sequence, T defaultT, F func) : N(sequence.size()),\
    \ defaultT(defaultT), func(func)\n    {\n        lgx_table.resize(N + 1);\n  \
    \      for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n\
    \        lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N, defaultT));\n\
    \        data[0] = sequence;\n        for (int d = 1; d < lgN; d++) {\n      \
    \      for (int i = 0; i + (1 << d) <= N; i++) {\n                data[d][i] =\
    \ func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);\n            }\n    \
    \    }\n    }\n    T get(int l, int r) { // [l, r), 0-indexed\n        assert(l\
    \ >= 0 and r <= N);\n        if (l >= r) return defaultT;\n        int d = lgx_table[r\
    \ - l];\n        return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Static\
    \ sequence sparse table\n// Complexity: O(NlogN) for precalculation, O(1) per\
    \ query\ntemplate<typename T, typename F>\nstruct SparseTable {\n    int N, lgN;\n\
    \    T defaultT;\n    F func;\n    std::vector<std::vector<T>> data;\n    std::vector<int>\
    \ lgx_table;\n    SparseTable(F func) : func(func) {}\n    SparseTable(const std::vector<T>\
    \ &sequence, T defaultT, F func) : N(sequence.size()), defaultT(defaultT), func(func)\n\
    \    {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) {\n                data[d][i] = func(data[d - 1][i], data[d -\
    \ 1][i + (1 << (d - 1))]);\n            }\n        }\n    }\n    T get(int l,\
    \ int r) { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n        if\
    \ (l >= r) return defaultT;\n        int d = lgx_table[r - l];\n        return\
    \ func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/sparse_table.hpp
  requiredBy:
  - sparse_table/sparse_table_2d.hpp
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - sparse_table/test/sparse_table_aoj.test.cpp
  - sparse_table/test/sparse_table_2d.test.cpp
  - sparse_table/test/sparse_table.test.cpp
documentation_of: sparse_table/sparse_table.hpp
layout: document
redirect_from:
- /library/sparse_table/sparse_table.hpp
- /library/sparse_table/sparse_table.hpp.html
title: sparse_table/sparse_table.hpp
---
