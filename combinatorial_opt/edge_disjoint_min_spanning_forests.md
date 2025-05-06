---
title: Edge disjoint minimum spanning forests （無向グラフにおける最大辺数最小重みの辺素な二つの全域森）
documentation_of: ./edge_disjoint_min_spanning_forests.hpp
---

$n$ 頂点 $m$ 辺の重み付き無向グラフを入力として，辺を共有しない二つの全域森であって辺数の和が最大となるもののうち重み最小のものを一つ構築する．
本実装の計算量は重み付きのとき $O(nm + m \log m)$，重みなしのとき $O(nm)$．

## アルゴリズムの概要

アルゴリズムの大枠は [Matroid union （マトロイドの合併） \| cplib-cpp](https://hitonanode.github.io/cplib-cpp/combinatorial_opt/matroid_union.hpp) と同様．

## 使用方法

```cpp
vector<pint> edges;
vector<int> weights;
while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.emplace_back(u, v);
    weights.push_back(w);
}
vector<bool> I1, I2;
tie(I1, I2) = edge_disjoint_min_spanning_forests(edges); // 重みなし
tie(I1, I2) = edge_disjoint_min_spanning_forests(edges, w); // 重み付き
```

返り値の `I1`, `I2` はともに長さ $m$ のベクトル．`I1[e]` の値が `true` のとき，$e$ 本目の辺が一つ目の全域森に含まれていることを示す（`I2` の解釈も同様）．

## 問題例

- [Hamel Paths \| CodeChef](https://www.codechef.com/problems/HAMEL) $n \le 64, m \le n(n - 1) / 2$, 最大 64 ケース．
- [2018 TCO Round 3A 1000 ColoringEdgesDiv1](https://archive.topcoder.com/ProblemStatement/pm/14909) $n \le 1000, m = 3n/2$
- [【UR #11】元旦老人与丛林 - 题目 - Universal Online Judge](https://uoj.ac/problem/168) $n \le 2000, m \le 4000$

## 参考文献・リンク

- [様々な全域木問題](https://www.slideshare.net/tmaehara/ss-17402143)
- [1] J. Roskind & R. E. Tarjan, 
  "A note on finding minimum-cost edge-disjoint spanning trees,"
  Mathematics of Operations Research, 10(4), 701-708, 1985.
  - 一般に $k$ 個の全域森にグラフを分割する $O(m \log m + k^2 n^2)$ のアルゴリズムが存在するらしい．
