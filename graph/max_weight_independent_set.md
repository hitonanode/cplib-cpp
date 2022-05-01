---
title: Max weight independent set （重み最大独立集合）
documentation_of: ./max_weight_independent_set.hpp
---

$N$ 頂点の単純無向グラフの重み最大独立集合の一つを求める指数時間アルゴリズム．時間計算量 $O(1.381^n n)$．頂点重みの和が最大なので，サイズ最大とは限らない．

## 使用方法

```cpp
vector<long long> weight(N);

max_weight_independent_set<long long> graph(weight);
// max_weight_independent_set<long long> graph(N); // と宣言すると重み 1 （= 重みなし）のケースを解く
while (M--) {
    int u, v;
    cin >> u >> v;
    solver.add_edge(u, v);
}
long long max_weight = solver.solve();
long long mask = solver.solution_set;
```

## 問題例

- [AOJ 3519: Breakup](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519)
