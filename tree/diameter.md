---
title: Tree diameter （木の直径）
documentation_of: ./diameter.hpp
---

木の直径を計算．

## 使用方法

```cpp
TreeDiameter<long long> tree(N);
for (auto [s, t, w] : edges) tree.add_edge(s, t, w);

// 頂点 r を含む部分木に関して，直径 D とこれをなす頂点列 vs （の一つ）を計算
auto [D, vs] = tree.get_diameter_edges(r);
```

## 問題例

- [Library Checker: Tree Diameter](https://judge.yosupo.jp/problem/tree_diameter)
