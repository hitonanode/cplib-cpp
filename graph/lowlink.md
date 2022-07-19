---
title: Lowlink （無向グラフの DFS tree, lowlink, 橋・二重辺連結成分・関節点・二重頂点連結成分）
documentation_of: ./lowlink.hpp
---

$N$ 頂点 $M$ 辺の無向グラフの DFS tree, lowlink を構築し，この情報をもとに橋・二重辺連結成分・関節点・二重頂点連結成分の情報を構築する．時間計算量 $O(N + M)$．

- 橋：その辺 $e$ を消すとグラフの $e$ を含む連結成分が非連結になるような辺．
- 二重辺連結成分：任意の一辺を削除しても互いに連結であるような部分グラフ（極大頂点集合）．グラフから全ての橋を削除したものをイメージするとよい．一般にグラフの二重辺連結成分分解において，橋となる辺はどの二重辺連結成分にも属さないが，全ての頂点はちょうど一つの二重辺連結成分に属するので，本ライブラリでは各頂点に二重辺連結成分のラベルを付与することで分解を行う．
- 関節点：その頂点 $v$ を消すとグラフの $v$ に関する連結成分が非連結になるような頂点．
- 二重頂点連結成分（二重連結成分）：任意の一頂点（とそこから生える辺）を削除しても連結であるような連結部分グラフ．一般にグラフの二重頂点連結成分分解において，ある頂点が複数の二重頂点連結成分に属することがある．一方全ての辺はちょうど一つの二重頂点連結成分に属するので，本ライブラリでは各辺に二重頂点連結成分のラベルを付与することで分解を行う（`biconnected_components_by_edges()`）．また，頂点の重複を許容して各成分に所属する頂点集合を出力するメソッドも用意した（`biconnected_components_by_vertices()`）．これは孤立点を含めて列挙を行いたい場合に有用である．

## 使用方法

```cpp
lowlink graph(V);
while (E--) {
    int s, t;
    cin >> s >> t;
    graph.add_edge(s, t);
}
vector<vector<int>> vgrpups = graph.two_edge_connected_components();
vector<vector<int>> egrpups = graph.biconnected_components_by_edges();
```

## 問題例

- [Library Checker: Biconnected Components](https://judge.yosupo.jp/problem/biconnected_components)
- [Library Checker: Two-Edge-Connected Components](https://judge.yosupo.jp/problem/two_edge_connected_components)
