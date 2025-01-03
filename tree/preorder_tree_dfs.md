---
title: Preorder tree DFS （木の行きがけ順 DFS）
documentation_of: ./preorder_tree_dfs.hpp
---

与えられた木に対して，行きがけ順に頂点を列挙した列を構築する．部分木を構成する頂点は連続して現れるので，部分木の頂点クエリ等に有用．

## 使用方法

```cpp
int N;
vector<vector<int>> to(N);
int root;

preorder_tree_dfs tour(to, root);

// 頂点 v の部分木を構成する頂点は半開区間 [tour.subtree_begin[v], tour.subtree_end[v]) に現れる
```

## 問題例

- [Library Checker: Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
