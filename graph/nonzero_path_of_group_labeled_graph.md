---
title: Shortest Non-zero Path in Group-Labeled Graphs （無向グラフの群ラベル制約付き最短路）
documentation_of: ./nonzero_path_of_group_labeled_graph.md
---

各辺 $e$ に群ラベル $g_e$ が付いた無向グラフについて，単一始点 $s$ から各頂点 $v$ への（同一頂点を複数回通らない）パス $(e_1, \dots, e_K)$ であって $g_{e_1} \cdot g_{e_2} \cdot \dots \cdot g_{e_K} \neq 1$ を満たすようなもののうち最短のものの長さを計算する．

## 使用方法

```cpp
struct G { // 群の構造体
    unsigned g;
    G(unsigned x = 0) : g(x) {} // G() が定義されている必要がある
    G operator-() const noexcept { return *this; } //  -g が必要
    G operator+(const G &r) const noexcept { return G(g ^ r.g); } // g_1 + g_2 が必要
    bool operator==(const G &x) const noexcept { return g == x.g; } // g_1 = g_2 が必要
};

ShortestNonzeroPath<long long, 1LL << 60, G> graph(N);
int a, b;
long long len;
G g;
graph.add_bi_edge(a, b, len, g); // a -> b の長さ len, 群ラベル g の辺を追加（b -> a に通ると -g）
graph.solve(s);
long long ret = graph.dist[t];
```

## リンク

- [1] Y. Iwata and Y. Yamaguchi, "Finding a Shortest Non-zero Path in Group-Labeled Graphs", https://arxiv.org/abs/1906.04062.
- [No.1602 With Animals into Institute 2 - yukicoder](https://yukicoder.me/problems/no/1602)
- [群ラベル制約付き最短路問題](https://ygussany.hatenablog.com/entry/2019/12/04/000000)
