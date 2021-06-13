---
title: 無向グラフに含まれる三角形の列挙
documentation_of: ./enumerate_triangles.hpp
---

頂点数 $N$，辺数 $M$ の無向単純グラフで辺 $(s, t), (t, u), (u, s)$ が全て存在するような相異なる 3 頂点 $(s, t, u)$ の三つ組を全列挙する．時間計算量は $O(N + M \sqrt{M})$．なお完全グラフの場合に三角形は実際に $O(M \sqrt{M})$ 個できる．

## 使用方法

```cpp
EnumerateTriangles graph(N);
for (auto [u, v] : edges) graph.add_edge(u, v);
auto f = [&](int i, int j, int k) { ret += solve_problem(i, j, k); }; // 三角形の各頂点番号を引数にとる
graph.run(f);
```

## リンク

- [Library Checker: Enumerate Triangles](https://judge.yosupo.jp/problem/enumerate_triangles)
- [catupper さんの解説](https://www.slideshare.net/catupper/trianguler)
