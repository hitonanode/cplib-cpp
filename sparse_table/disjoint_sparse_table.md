---
title: Disjoint sparse table
documentation_of: ./disjoint_sparse_table.hpp
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
