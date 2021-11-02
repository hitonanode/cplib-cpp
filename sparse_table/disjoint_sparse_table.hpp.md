---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: sparse_table/disjoint_sparse_table_2d.hpp
    title: sparse_table/disjoint_sparse_table_2d.hpp
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
    - https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404
    - https://drken1215.hatenablog.com/entry/2018/09/08/162600
  bundledCode: "#line 2 \"sparse_table/disjoint_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Disjoint sparse table\n\
    // https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404\n// https://drken1215.hatenablog.com/entry/2018/09/08/162600\n\
    // Complexity: O(NlogN) for precalculation, O(1) per query\n// - get(l, r): return\
    \ op(x_l, ..., x_{r - 1})\ntemplate <class S, S (*op)(S, S)> struct disj_sparse_table\
    \ {\n    int N, sz;\n    std::vector<std::vector<S>> d;\n    static int _msb(int\
    \ x) noexcept { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }\n    disj_sparse_table()\
    \ = default;\n    disj_sparse_table(const std::vector<S> &seq) : N(seq.size())\
    \ {\n        sz = 1 << (_msb(N - 1) + 1);\n        d.assign(_msb(sz) + 1, std::vector<S>(sz));\n\
    \        std::copy(seq.begin(), seq.end(), d[0].begin());\n\n        for (int\
    \ h = 1, half = 2; half < N; ++h, half <<= 1) {\n            for (int i = half;\
    \ i < sz; i += half * 2) {\n                d[h][i - 1] = d[0][i - 1];\n     \
    \           for (int j = i - 2; j >= i - half; --j) d[h][j] = op(d[0][j], d[h][j\
    \ + 1]);\n                d[h][i] = d[0][i];\n                for (int j = i +\
    \ 1; j < i + half; ++j) d[h][j] = op(d[h][j - 1], d[0][j]);\n            }\n \
    \       }\n    }\n    // [l, r), 0-indexed\n    S prod(int l, int r) const {\n\
    \        assert(l >= 0 and r <= N and l < r);\n        if (l + 1 == r) return\
    \ d[0][l];\n        int h = _msb(l ^ (r - 1));\n        return op(d[h][l], d[h][r\
    \ - 1]);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n// CUT begin\n// Disjoint sparse table\n// https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404\n\
    // https://drken1215.hatenablog.com/entry/2018/09/08/162600\n// Complexity: O(NlogN)\
    \ for precalculation, O(1) per query\n// - get(l, r): return op(x_l, ..., x_{r\
    \ - 1})\ntemplate <class S, S (*op)(S, S)> struct disj_sparse_table {\n    int\
    \ N, sz;\n    std::vector<std::vector<S>> d;\n    static int _msb(int x) noexcept\
    \ { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }\n    disj_sparse_table() =\
    \ default;\n    disj_sparse_table(const std::vector<S> &seq) : N(seq.size()) {\n\
    \        sz = 1 << (_msb(N - 1) + 1);\n        d.assign(_msb(sz) + 1, std::vector<S>(sz));\n\
    \        std::copy(seq.begin(), seq.end(), d[0].begin());\n\n        for (int\
    \ h = 1, half = 2; half < N; ++h, half <<= 1) {\n            for (int i = half;\
    \ i < sz; i += half * 2) {\n                d[h][i - 1] = d[0][i - 1];\n     \
    \           for (int j = i - 2; j >= i - half; --j) d[h][j] = op(d[0][j], d[h][j\
    \ + 1]);\n                d[h][i] = d[0][i];\n                for (int j = i +\
    \ 1; j < i + half; ++j) d[h][j] = op(d[h][j - 1], d[0][j]);\n            }\n \
    \       }\n    }\n    // [l, r), 0-indexed\n    S prod(int l, int r) const {\n\
    \        assert(l >= 0 and r <= N and l < r);\n        if (l + 1 == r) return\
    \ d[0][l];\n        int h = _msb(l ^ (r - 1));\n        return op(d[h][l], d[h][r\
    \ - 1]);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: sparse_table/disjoint_sparse_table.hpp
  requiredBy:
  - sparse_table/disjoint_sparse_table_2d.hpp
  timestamp: '2021-11-02 23:36:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - sparse_table/test/disjoint_sparse_table_rmq.test.cpp
  - sparse_table/test/disjoint_sparse_table_rsq.test.cpp
documentation_of: sparse_table/disjoint_sparse_table.hpp
layout: document
title: Disjoint sparse table
---

Disjoint sparse table の実装．[AC Library の Segtree](https://atcoder.github.io/ac-library/document_ja/segtree.html) と同様のインターフェース．前計算 $O(N \log N)$，クエリ $O(1)$．Sparse table と異なり，`S` の二項演算 `op` は結合法則が成り立てばよい．

## 使用方法

```cpp
S op(S l, S r);                 // 半群の元同士の演算．結合法則が成り立てばよい．
vector<S> A(N);                 // 列．
disj_sparse_table<S, op> st(A);
cout << st.prod(l, r) << '\n';  // 半開区間積クエリ．
```

## 問題例

- [Library Checker: Static RMQ](https://judge.yosupo.jp/problem/staticrmq)
