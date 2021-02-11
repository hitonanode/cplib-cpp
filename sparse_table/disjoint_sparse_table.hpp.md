---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/disjoint_sparse_table_rmq.test.cpp
    title: sparse_table/test/disjoint_sparse_table_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/disjoint_sparse_table_rsq.test.cpp
    title: sparse_table/test/disjoint_sparse_table_rsq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404>
    - https://drken1215.hatenablog.com/entry/2018/09/08/162600>
  bundledCode: "#line 2 \"sparse_table/disjoint_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Disjoint sparse table\n\
    // <https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404>\n// <https://drken1215.hatenablog.com/entry/2018/09/08/162600>\n\
    // Complexity: O(NlogN) for precalculation, O(1) per query\n// - get(l, r): return\
    \ op(x_l, ..., x_{r - 1})\ntemplate <typename T, typename F> struct DisjointSparseTable\
    \ {\n    int N, sz;\n    F f;\n    std::vector<std::vector<T>> data;\n    static\
    \ int _msb(int x) noexcept { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }\n\
    \    DisjointSparseTable() = default;\n    DisjointSparseTable(const std::vector<T>\
    \ &seq, F op) : N(seq.size()), f(op) {\n        sz = 1 << (_msb(N - 1) + 1);\n\
    \        data.assign(_msb(sz) + 1, std::vector<T>(sz));\n        std::copy(seq.begin(),\
    \ seq.end(), data[0].begin());\n\n        for (int h = 1, half = 2; half < N;\
    \ h++, half <<= 1) {\n            for (int i = half; i < sz; i += half * 2) {\n\
    \                data[h][i - 1] = data[0][i - 1];\n                for (int j\
    \ = i - 2; j >= i - half; j--) { data[h][j] = f(data[0][j], data[h][j + 1]); }\n\
    \                data[h][i] = data[0][i];\n                for (int j = i + 1;\
    \ j < i + half; j++) { data[h][j] = f(data[h][j - 1], data[0][j]); }\n       \
    \     }\n        }\n    }\n    // [l, r), 0-indexed\n    T get(int l, int r) {\n\
    \        assert(l >= 0 and r <= N and l < r);\n        if (l + 1 == r) return\
    \ data[0][l];\n        int h = _msb(l ^ (r - 1));\n        return f(data[h][l],\
    \ data[h][r - 1]);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n// CUT begin\n// Disjoint sparse table\n// <https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404>\n\
    // <https://drken1215.hatenablog.com/entry/2018/09/08/162600>\n// Complexity:\
    \ O(NlogN) for precalculation, O(1) per query\n// - get(l, r): return op(x_l,\
    \ ..., x_{r - 1})\ntemplate <typename T, typename F> struct DisjointSparseTable\
    \ {\n    int N, sz;\n    F f;\n    std::vector<std::vector<T>> data;\n    static\
    \ int _msb(int x) noexcept { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }\n\
    \    DisjointSparseTable() = default;\n    DisjointSparseTable(const std::vector<T>\
    \ &seq, F op) : N(seq.size()), f(op) {\n        sz = 1 << (_msb(N - 1) + 1);\n\
    \        data.assign(_msb(sz) + 1, std::vector<T>(sz));\n        std::copy(seq.begin(),\
    \ seq.end(), data[0].begin());\n\n        for (int h = 1, half = 2; half < N;\
    \ h++, half <<= 1) {\n            for (int i = half; i < sz; i += half * 2) {\n\
    \                data[h][i - 1] = data[0][i - 1];\n                for (int j\
    \ = i - 2; j >= i - half; j--) { data[h][j] = f(data[0][j], data[h][j + 1]); }\n\
    \                data[h][i] = data[0][i];\n                for (int j = i + 1;\
    \ j < i + half; j++) { data[h][j] = f(data[h][j - 1], data[0][j]); }\n       \
    \     }\n        }\n    }\n    // [l, r), 0-indexed\n    T get(int l, int r) {\n\
    \        assert(l >= 0 and r <= N and l < r);\n        if (l + 1 == r) return\
    \ data[0][l];\n        int h = _msb(l ^ (r - 1));\n        return f(data[h][l],\
    \ data[h][r - 1]);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/disjoint_sparse_table.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - sparse_table/test/disjoint_sparse_table_rmq.test.cpp
  - sparse_table/test/disjoint_sparse_table_rsq.test.cpp
documentation_of: sparse_table/disjoint_sparse_table.hpp
layout: document
redirect_from:
- /library/sparse_table/disjoint_sparse_table.hpp
- /library/sparse_table/disjoint_sparse_table.hpp.html
title: sparse_table/disjoint_sparse_table.hpp
---
