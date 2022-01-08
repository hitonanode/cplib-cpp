---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: sparse_table/sparse_table.hpp
    title: Sparse table
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: sparse_table/test/sparse_table_2d.test.cpp
    title: sparse_table/test/sparse_table_2d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
    \ - l];\n        return op(d[h][l], d[h][r - (1 << h)]);\n    }\n};\n#line 5 \"\
    sparse_table/sparse_table_2d.hpp\"\n\n// CUT begin\n// Static matrix sparse table\n\
    // Complexity; O(HWlogHlogW) for precalculation, O(1) per query\ntemplate <class\
    \ S, S (*op)(S, S), S (*e)()> struct SparseTable2D {\n    int H, lgH, W;\n   \
    \ std::vector<std::vector<sparse_table<S, op, e>>> d;\n    std::vector<int> lgx_table;\n\
    \    SparseTable2D() {}\n    SparseTable2D(const std::vector<std::vector<S>> &matrix)\
    \ {\n        H = matrix.size(), W = (matrix.size() ? matrix[0].size() : 0);\n\
    \        lgx_table.resize(H + 1);\n        for (int i = 2; i < H + 1; i++) lgx_table[i]\
    \ = lgx_table[i >> 1] + 1;\n        lgH = lgx_table[H] + 1;\n        d.resize(lgH);\n\
    \        for (auto v : matrix) d[0].emplace_back(sparse_table<S, op, e>(v));\n\
    \        for (int h = 1; h < lgH; h++) {\n            for (int i = 0; i + (1 <<\
    \ h) <= H; ++i) {\n                std::vector<S> v(W);\n                for (int\
    \ j = 0; j < W; ++j) {\n                    v[j] = op(d[h - 1][i].d[0][j], d[h\
    \ - 1][i + (1 << (h - 1))].d[0][j]);\n                }\n                d[h].emplace_back(sparse_table<S,\
    \ op, e>(v));\n            }\n        }\n    }\n    S prod(int xl, int xr, int\
    \ yl, int yr) const {\n        assert(xl >= 0 and xr <= H and yl >= 0 and yr <=\
    \ W);\n        if (xl >= xr) return e();\n        int h = lgx_table[xr - xl];\n\
    \        return op(d[h][xl].prod(yl, yr), d[h][xr - (1 << h)].prod(yl, yr));\n\
    \    }\n};\n"
  code: "#pragma once\n#include \"sparse_table.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Static matrix sparse table\n// Complexity; O(HWlogHlogW)\
    \ for precalculation, O(1) per query\ntemplate <class S, S (*op)(S, S), S (*e)()>\
    \ struct SparseTable2D {\n    int H, lgH, W;\n    std::vector<std::vector<sparse_table<S,\
    \ op, e>>> d;\n    std::vector<int> lgx_table;\n    SparseTable2D() {}\n    SparseTable2D(const\
    \ std::vector<std::vector<S>> &matrix) {\n        H = matrix.size(), W = (matrix.size()\
    \ ? matrix[0].size() : 0);\n        lgx_table.resize(H + 1);\n        for (int\
    \ i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgH =\
    \ lgx_table[H] + 1;\n        d.resize(lgH);\n        for (auto v : matrix) d[0].emplace_back(sparse_table<S,\
    \ op, e>(v));\n        for (int h = 1; h < lgH; h++) {\n            for (int i\
    \ = 0; i + (1 << h) <= H; ++i) {\n                std::vector<S> v(W);\n     \
    \           for (int j = 0; j < W; ++j) {\n                    v[j] = op(d[h -\
    \ 1][i].d[0][j], d[h - 1][i + (1 << (h - 1))].d[0][j]);\n                }\n \
    \               d[h].emplace_back(sparse_table<S, op, e>(v));\n            }\n\
    \        }\n    }\n    S prod(int xl, int xr, int yl, int yr) const {\n      \
    \  assert(xl >= 0 and xr <= H and yl >= 0 and yr <= W);\n        if (xl >= xr)\
    \ return e();\n        int h = lgx_table[xr - xl];\n        return op(d[h][xl].prod(yl,\
    \ yr), d[h][xr - (1 << h)].prod(yl, yr));\n    }\n};\n"
  dependsOn:
  - sparse_table/sparse_table.hpp
  isVerificationFile: false
  path: sparse_table/sparse_table_2d.hpp
  requiredBy: []
  timestamp: '2021-11-02 23:36:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - sparse_table/test/sparse_table_2d.test.cpp
documentation_of: sparse_table/sparse_table_2d.hpp
layout: document
title: 2D sparse table
---

2D sparse table の実装．[AC Library の Segtree](https://atcoder.github.io/ac-library/document_ja/segtree.html) と同様のインターフェース．前計算 $O(HW \log HW)$，クエリ $O(1)$．`S` の二項演算 `op` は結合法則と冪等性が成り立つ必要がある．

## 使用方法

```cpp
S op(S l, S r);                           // 半群の元同士の演算．
vector<vector<S>> A(H, vector<S>(W));     // 行列．
SparseTable2D<S, op, e> rmq(mat);
cout << st.prod(xl, xr, yl, yr) << '\n';  // 矩形領域積クエリ．
```

## 問題例

- [AOJ 1068: School of Killifish](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068)
