---
title: Maxflow (push-relabel, Goldberg & Tarjan) （Push-relabel による最大流）
documentation_of: ./maxflow_pushrelabel.hpp
---

Push-relabel による最大流．時間計算量は $O(n^2 \sqrt{m})$．更にいくつかのヒューリスティックを入れることで定数倍が改善される．Dinic 法の計算量が $O(n^2 m)$ であるのに対し最悪計算量はオーダーレベルで改善されているが，特殊なグラフで Dinic の計算量が更に改善される点などの事情があるため，常にこちらを使用すればよいという訳でもない．

## 使用方法

```cpp
mf_pushrelabel<int> graph(N);
while (E--) {
    int u, v, c;
    cin >> u >> v >> c;
    graph.add_edge(u, v, c);
}
int f = graph.flow(s, t);
```

## リンク

- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/), [ORIE 6330: Network Flows](https://people.orie.cornell.edu/dpw/orie6330/)
- [TL Issue in the #659 (Div. 1) Problem F - Codeforces](https://codeforces.com/blog/entry/80627)