---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table_2d.hpp
    title: 2D sparse table
  _extendedVerifiedWith:
  - icon: ':x:'
    path: sparse_table/test/sparse_table.test.cpp
    title: sparse_table/test/sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table_2d.test.cpp
    title: sparse_table/test/sparse_table_2d.test.cpp
  - icon: ':x:'
    path: sparse_table/test/sparse_table_aoj.test.cpp
    title: sparse_table/test/sparse_table_aoj.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sparse_table/sparse_table.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Static sequence sparse table\n// Complexity: O(NlogN)\
    \ for precalculation, O(1) per query\ntemplate <class S, S (*op)(S, S), S (*e)()>\
    \ struct sparse_table {\n    int N, lgN;\n    std::vector<std::vector<S>> d;\n\
    \    std::vector<int> lgx_table;\n    sparse_table() {}\n    sparse_table(const\
    \ std::vector<S> &sequence) : N(sequence.size()) {\n        lgx_table.resize(N\
    \ + 1);\n        for (int i = 2; i < N + 1; ++i) lgx_table[i] = lgx_table[i >>\
    \ 1] + 1;\n        lgN = lgx_table[N] + 1;\n        d.assign(lgN, std::vector<S>(N,\
    \ e()));\n        d[0] = sequence;\n        for (int h = 1; h < lgN; ++h) {\n\
    \            for (int i = 0; i + (1 << h) <= N; ++i) {\n                d[h][i]\
    \ = op(d[h - 1][i], d[h - 1][i + (1 << (h - 1))]);\n            }\n        }\n\
    \    }\n    S prod(int l, int r) const { // [l, r), 0-indexed\n        assert(l\
    \ >= 0 and r <= N);\n        if (l >= r) return e();\n        int h = lgx_table[r\
    \ - l];\n        return op(d[h][l], d[h][r - (1 << h)]);\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Static\
    \ sequence sparse table\n// Complexity: O(NlogN) for precalculation, O(1) per\
    \ query\ntemplate <class S, S (*op)(S, S), S (*e)()> struct sparse_table {\n \
    \   int N, lgN;\n    std::vector<std::vector<S>> d;\n    std::vector<int> lgx_table;\n\
    \    sparse_table() {}\n    sparse_table(const std::vector<S> &sequence) : N(sequence.size())\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; ++i)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     d.assign(lgN, std::vector<S>(N, e()));\n        d[0] = sequence;\n     \
    \   for (int h = 1; h < lgN; ++h) {\n            for (int i = 0; i + (1 << h)\
    \ <= N; ++i) {\n                d[h][i] = op(d[h - 1][i], d[h - 1][i + (1 << (h\
    \ - 1))]);\n            }\n        }\n    }\n    S prod(int l, int r) const {\
    \ // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n        if (l >= r)\
    \ return e();\n        int h = lgx_table[r - l];\n        return op(d[h][l], d[h][r\
    \ - (1 << h)]);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/sparse_table.hpp
  requiredBy:
  - sparse_table/sparse_table_2d.hpp
  timestamp: '2021-11-02 23:36:31+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - sparse_table/test/sparse_table_2d.test.cpp
  - sparse_table/test/sparse_table.test.cpp
  - sparse_table/test/sparse_table_aoj.test.cpp
documentation_of: sparse_table/sparse_table.hpp
layout: document
title: Sparse table
---

Sparse table の実装．[AC Library の Segtree](https://atcoder.github.io/ac-library/document_ja/segtree.html) と同様のインターフェース．前計算 $O(N \log N)$，クエリ $O(1)$．`S` の二項演算 `op` は結合法則と冪等性が成り立つ必要がある．

## 使用方法

```cpp
S op(S l, S r);                 // 半群の元同士の演算．
vector<S> A(N);                 // 列．
sparse_table<S, op> st(A);
cout << st.prod(l, r) << '\n';  // 半開区間積クエリ．
```

## 問題例

- [Library Checker: Static RMQ](https://judge.yosupo.jp/problem/staticrmq)
