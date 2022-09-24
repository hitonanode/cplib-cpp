---
title: Lowest common ancestor of tree based on sparse table （クエリ $O(1)$ の最小共通祖先）
documentation_of: ./lca_rmq.hpp
---

根を固定した木に対する 2 頂点の最小共通祖先，および 2 頂点間の距離の計算．前処理 $O(N \log N)$, 空間 $O(N \log N)$, クエリ $O(1)$．

## 使用方法

`add_edge(int u, int v)` を $N - 1$ 回行って木を構築した後，`build(int root)` によって根を指定する．

```cpp
TreeLCA tree(N);
for (int e = 0; e < N - 1; e++) {
    int u, v;
    cin >> u >> v;
    tree.add_edge(u, v);
}

tree.build(0);

cout << tree.lca(a, b) << '\n'; // (a, b) の最長共通祖先
cout << tree.path_length(a, b) << '\n'; // 2 頂点 a, b の距離
```

## 問題例

- [Library Checker: Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
