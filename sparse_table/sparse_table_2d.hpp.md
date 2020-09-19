---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table.hpp
    title: sparse_table/sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table_2d.test.cpp
    title: sparse_table/test/sparse_table_2d.test.cpp
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
    \ - l];\n        return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n\
    #line 5 \"sparse_table/sparse_table_2d.hpp\"\n\n// CUT begin\n// Static matrix\
    \ sparse table\n// Complexity; O(HWlogHlogW) for precalculation, O(1) per query\n\
    template<typename T, typename F>\nstruct SparseTable2D {\n    int H, lgH, W;\n\
    \    T defaultT;\n    F func;\n    std::vector<std::vector<SparseTable<T, F>>>\
    \ data;\n    std::vector<int> lgx_table;\n    SparseTable2D(F func) : func(func)\
    \ {}\n    SparseTable2D(const std::vector<std::vector<T>> &matrix, T defaultT,\
    \ F func) : defaultT(defaultT), func(func) {\n        H = matrix.size(), W = (matrix.size()\
    \ ? matrix[0].size() : 0);\n        lgx_table.resize(H + 1);\n        for (int\
    \ i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgH =\
    \ lgx_table[H] + 1;\n        data.resize(lgH);\n        for (auto v : matrix)\
    \ data[0].emplace_back(SparseTable<T, F>(v, defaultT, func));\n        for (int\
    \ d = 1; d < lgH; d++) {\n            for (int i = 0; i + (1 << d) <= H; i++)\
    \ {\n                std::vector<T> v(W);\n                for (int j = 0; j <\
    \ W; j++) v[j] = func(data[d - 1][i].data[0][j], data[d - 1][i + (1 << (d - 1))].data[0][j]);\n\
    \                data[d].emplace_back(SparseTable<T, F>(v, defaultT, func));\n\
    \            }\n        }\n    }\n    T get(int xl, int xr, int yl, int yr) {\n\
    \        assert(xl >= 0 and xr <= H and yl >= 0 and yr <= W);\n        if (xl\
    \ >= xr) return defaultT;\n        int d = lgx_table[xr - xl];\n        return\
    \ func(data[d][xl].get(yl, yr), data[d][xr - (1 << d)].get(yl, yr));\n    }\n\
    };\n"
  code: "#pragma once\n#include \"sparse_table/sparse_table.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// CUT begin\n// Static matrix sparse table\n// Complexity;\
    \ O(HWlogHlogW) for precalculation, O(1) per query\ntemplate<typename T, typename\
    \ F>\nstruct SparseTable2D {\n    int H, lgH, W;\n    T defaultT;\n    F func;\n\
    \    std::vector<std::vector<SparseTable<T, F>>> data;\n    std::vector<int> lgx_table;\n\
    \    SparseTable2D(F func) : func(func) {}\n    SparseTable2D(const std::vector<std::vector<T>>\
    \ &matrix, T defaultT, F func) : defaultT(defaultT), func(func) {\n        H =\
    \ matrix.size(), W = (matrix.size() ? matrix[0].size() : 0);\n        lgx_table.resize(H\
    \ + 1);\n        for (int i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >>\
    \ 1] + 1;\n        lgH = lgx_table[H] + 1;\n        data.resize(lgH);\n      \
    \  for (auto v : matrix) data[0].emplace_back(SparseTable<T, F>(v, defaultT, func));\n\
    \        for (int d = 1; d < lgH; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= H; i++) {\n                std::vector<T> v(W);\n                for (int\
    \ j = 0; j < W; j++) v[j] = func(data[d - 1][i].data[0][j], data[d - 1][i + (1\
    \ << (d - 1))].data[0][j]);\n                data[d].emplace_back(SparseTable<T,\
    \ F>(v, defaultT, func));\n            }\n        }\n    }\n    T get(int xl,\
    \ int xr, int yl, int yr) {\n        assert(xl >= 0 and xr <= H and yl >= 0 and\
    \ yr <= W);\n        if (xl >= xr) return defaultT;\n        int d = lgx_table[xr\
    \ - xl];\n        return func(data[d][xl].get(yl, yr), data[d][xr - (1 << d)].get(yl,\
    \ yr));\n    }\n};\n"
  dependsOn:
  - sparse_table/sparse_table.hpp
  isVerificationFile: false
  path: sparse_table/sparse_table_2d.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - sparse_table/test/sparse_table_2d.test.cpp
documentation_of: sparse_table/sparse_table_2d.hpp
layout: document
redirect_from:
- /library/sparse_table/sparse_table_2d.hpp
- /library/sparse_table/sparse_table_2d.hpp.html
title: sparse_table/sparse_table_2d.hpp
---
