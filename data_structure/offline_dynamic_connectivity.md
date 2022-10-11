---
title: Offline dynamic connectivity
documentation_of: ./offline_dynamic_connectivity.hpp
---

オフライン版の dynamic connectivity （の抽象化実装）．

以下の性質を満たす何らかのオブジェクト $x$ と，$x$ に対するさまざまな作用たち $f\_i$ を考えたい：

- 作用たちは可換．すなわち任意の作用 $f, g$ について $f \circ g = g \circ f$ が常に成立．
- 作用を及ぼした後の $x$ の計算と，直近に及ぼした作用の undo 操作が（十分高速に）可能．

このとき、本コードは以下のオフラインクエリ群の高速処理をサポートする．

- $l \leq t < r$ を満たす時刻 $t$ においてのみ $x$ に対して作用 $f$ を及ぼす．
- ある時刻 $t$ における $x$ の何らかの特徴量を取得する．

汎用化のため具体的なオブジェクト $x$ や作用 $f$ たちの管理は本コードでは行っておらず，実装者が UnionFind などを別途用意する必要がある．

## 原理

入力に登場する時刻 $t$ を列挙し二分木を構築する．作用クエリをセグメント木の要領で頂点に効率的に配置し，二分木を DFS しながら作用の演算・undo 操作・特徴量取得を行えばよい．

## 使用方法

```cpp
offline_dynamic_connectivity<int> dc;

dc.apply_time_range(0, 100, 1);  // 時刻 [0, 100) の範囲で辺番号 1 を追加
dc.add_observation(50, 2);  // 時刻 50 に取得クエリ 2 を追加

for (auto p : dc.generate()) {
    if (p.op == DyConOperation::Begins) {
        int edge_id = p.id_;
        // 辺番号 edge_id を張る
    } else if (p.op == DyConOperation::Ends) {
        // undo 操作を一回行う
    } else if (p.op == DyConOperation::Event) {
        int query_id = p.id_;
        // 取得クエリ query_id を行う
    }
}
```

### 具体例：無向グラフの連結成分に関する情報取得

オブジェクト $x$ を $n$ 頂点の無向グラフとして，作用として

- 2 頂点間の辺追加操作
- ある頂点の重み更新

の 2 つ，特徴量として「連結成分の頂点重み和」を考えると，これは undo 可能 UnionFind で効率的に処理できる．よって本ライブラリを利用することで高速に解ける（「問題例」の "Dynamic Graph Vertex Add Component Sum" が該当）．

## 問題例

- [Library Checker: Dynamic Graph Vertex Add Component Sum](https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum)
- [Educational Codeforces Round 38 (Rated for Div. 2) G. Shortest Path Queries](https://codeforces.com/contest/938/problem/G)
