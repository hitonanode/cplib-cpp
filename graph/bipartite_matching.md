---
title: Bipartite matching (Hopcroft–Karp)
documentation_of: ./bipartite_matching.hpp
---

与えられた二部グラフの最大マッチングを構築する．計算量は $O((N + M)\sqrt{N})$．

## 使用方法

入力の際，

`solve()` 関数は与えられたグラフが二部グラフの場合は最大マッチングのサイズを，二部グラフではない場合は `-1` を返す．

```cpp
BipartiteMatching bm(N);
bm.add_edge(u, v);

int n_pair = bm.solve();

// match[i] = (頂点 i とペアになる頂点) 
//            or -1 （マッチングに使用されない場合）
int j = bm.match[i];
```

## 問題例

- [Library Checker: Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching)
