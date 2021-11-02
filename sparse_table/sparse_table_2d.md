---
title: 2D sparse table
documentation_of: ./sparse_table_2d.hpp
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
