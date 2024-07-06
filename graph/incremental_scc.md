---
title: Incremental SCC （強連結成分）
documentation_of: ./incremental_scc.hpp
---

$m$ 個の有向辺からなる列が与えられ，先頭の要素から順にグラフに追加していく．各有向辺について，グラフに何番目の辺まで追加したときに初めてその辺を含む閉路ができるかを $O(m \log m)$ で計算する．

この処理は以下のような用途に使える．

- UnionFind などのデータ構造を併用することで，各時点での強連結成分を管理できる．
- 各辺を含む閉路ができる時刻を重みとして最小全域木を求め，更に heavy-light decomposition やセグメント木と併用することで， 2 頂点が同一の強連結成分に初めて属する時刻をクエリ $O(n \log n)$ 等で計算できる．

## 使用方法

```cpp
vector<pair<int, int>> edges;  // 有向辺の列． edges[i] は時刻 i に追加される

auto ticks = incremental_scc(edges);

assert(ticks.size() == edges.size());
// ticks[i] = (edges[i] を含む閉路ができる時刻 (0 <= ticks[i] < m)) または m （閉路ができない場合・自己ループの場合）
```

## 問題例

- [Educational Codeforces Round 167 (Rated for Div. 2) F. Simultaneous Coloring](https://codeforces.com/contest/1989/problem/F)

## リンク

- [My own algorithm — offline incremental strongly connected components in O(m*log(m)) - Codeforces](https://codeforces.com/blog/entry/91608)
