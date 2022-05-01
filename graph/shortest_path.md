---
title: Shortest Path （単一始点最短路）
documentation_of: ./shortest_path.hpp
---

単一始点最短路問題を解く．`solve(int s)` 関数を用いると以下の要領でアルゴリズムが自動的に選択される．

- 負の重みの辺が存在するならば，Bellman-Ford 法で解く．$O(VE)$
- 全ての辺重みが非負で，非零の辺重みの値が高々一通りならば， 0-1 BFS で解く．$O(V + E)$
- それ以外の場合，Dijkstra 法で解く．$O(V^2 + E)$ または $O(E \log E)$

また，SPFA （$O(VE)$），全点対最短路アルゴリズム（Floyd-Warshall 法，$O(E + V^3)$），DAG用ソルバー（$O(V + E)$）も実装されている．`retrieve_path(int t)` で最短路の復元が，また `dump_graphviz(string filename)` で `.DOT` 形式のグラフ出力が可能．

## 使用方法

```cpp
constexpr long long INF = 1LL << 60;
shortest_path<long long, INF> graph(N);
while (M--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.add_edge(a, b, c);
}

graph.solve(s, t);
cout << graph.dist[t] << '\n';

```

## 問題例

- [Library Checker - Shortest Path](https://judge.yosupo.jp/problem/shortest_path)
- [No.1660 Matrix Exponentiation - yukicoder](https://yukicoder.me/problems/no/1660) DAG の場合．
