---
title: Lowest common ancestor （最小共通祖先）
documentation_of: ./lowest_common_ancestor.hpp
---

根を固定した木に対する 2 頂点の最小共通祖先，および 2 頂点間の距離，$k$ 番目の親の計算．前処理 $O(N \log N)$, クエリ $O(\log N)$．

## 使用方法

```cpp
UndirectedWeightedTree<long long> tree(N);
for (int e = 0; e < N - 1; e++) {
    int u, v, w;
    cin >> u >> v >> w;
    tree.add_edge(u, v, w);
}

tree.fix_root(0);

cout << tree.lowest_common_ancestor(a, b) << '\n'; // (a, b) の最長共通祖先
cout << tree.kth_parent(a, k) << '\n';  // 頂点 a の k 世代親
cout << tree.path_length(a, b) << '\n'; // 2 頂点 a, b の距離
```

## 問題例

- [Library Checker: Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
- [yukicoder No.898 tri-βutree](https://yukicoder.me/problems/no/898)
