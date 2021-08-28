---
title: Maxflow (push-relabel, Goldberg & Tarjan) （Push-relabel による最大流）
documentation_of: ./maxflow_pushrelabel.hpp
---

Push-relabel による最大流．Highest-label rule に従うことで時間計算量は $O(n^2 \sqrt{m})$．更にいくつかのヒューリスティックを入れることで定数倍が改善される．Dinic 法の計算量が $O(n^2 m)$ であるのに対し最悪計算量はオーダーレベルで改善されているが，特殊なグラフで Dinic の計算量が更に改善される点などの事情があるため，常にこちらを使用すればよいという訳でもない．

## 使用方法

- `mf_pushrelabel<CapType, int GlobalRelabelFreq, bool UseGapRelabeling> graph(int N)` : $N$ 頂点のグラフを作成する．辺容量は整数型 `CapType`．`GlobalRelabelFreq` の値 $k$ が正の場合，グラフの辺の本数を $m$ として $km$ 回の反復毎に global relabelling heuristics を行う．また，`UseGapRelabeling` が真の場合，gap relabeling heuristics を行う．いずれかの heuristics を有効化し，かつ `flow()` の引数で `retrieve = false` を選択した場合，アルゴリズムの停止時点で変数（プリフロー）がフロー条件を必ずしも満たさないことに注意．その他インターフェースは AC Library と同様．
- `graph.add_edge(int u, int v, CapType cap)` 辺を張る．
- `CapType ret = graph.flow(s, t, flow_limit, retrieve)` 最大流を求める．

```cpp
mf_pushrelabel<int, 1 << 29, 10, true> graph(N);
while (E--) {
    int u, v, c;
    cin >> u >> v >> c;
    graph.add_edge(u, v, c);
}
int f = graph.flow(s, t);
```

## 問題例

- [No.957 植林 - yukicoder](https://yukicoder.me/problems/no/957)
- [AtCoder Library Practice Contest D - Maxflow](https://atcoder.jp/contests/practice2/tasks/practice2_d)
- [CPSCO2019 Session2 F - Treasure Collector](https://atcoder.jp/contests/cpsco2019-s2/tasks/cpsco2019_s2_f)

## リンク

- [1] A. V. Goldberg and R. E. Tarjan, "A new approach to the maximum-flow problem,"
  Journal of the ACM, 35(4), 921-940, 1988.
- [2] B. V. Cherkassky and A. V. Goldberg, "On implementing the push-relabel method for the maximum flow problem,"
  Algorithmica, 19(4), 390-410, 1997.
- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/)
- [ORIE 6330: Network Flows](https://people.orie.cornell.edu/dpw/orie6330/)
- [TL Issue in the #659 (Div. 1) Problem F - Codeforces](https://codeforces.com/blog/entry/80627) 時間制限が厳しい最大流の問題．
- [or-tools/max_flow.h at stable · google/or-tools](https://github.com/google/or-tools/blob/stable/ortools/graph/max_flow.h) highest-label を高速に管理するデータ構造の実装が参考になる．
