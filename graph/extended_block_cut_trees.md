---
title: Extended block cut tree （Block cut tree の亜種）
documentation_of: ./extended_block_cut_trees.hpp
---

与えられた $n$ 頂点 $m$ 辺の無向グラフに対する block cut tree （のようなもの）を構築する．計算量は $O(n + m)$．

詳細な仕様は以下の通り．

- 入力グラフの二重連結成分数を $k$ とすると，頂点数 $n + k$ のグラフ（特に，森）を構築する．
  - **通常の block cut tree との相違点として，関節点ではない頂点も構築されたグラフに含まれる．**
- 頂点番号 $0, \ldots, n - 1$ が入力グラフの各頂点， $n, \ldots, n + k - 1$ が入力グラフの各二重連結成分に対応する．
- 頂点 $v$ が二重連結成分 $i$ に含まれるとき，頂点 $v$ と $n + i$ の間に辺が張られる．
- このコードにおいて，次数 0 の頂点（孤立点）はそれ単独で二重連結成分と見なされる．
  - したがって，入力グラフの全ての頂点が一つ以上の二重連結成分に属することになる．

なお，出力されるグラフは以下の性質を満たす．

- 一般に出力されるグラフは森．特に入力グラフが連結ならば出力されるグラフも連結（木）．
- 入力グラフの頂点 $v$ が関節点であることは，出力されるグラフの頂点 $v$ の次数が $2$ 以上であることと同値．

## 使用方法

```cpp
int n;  // Num. of vertices
vector<pair<int, int>> edges;

const extended_block_cut_trees bct(n, edges);

int b = bct.B;  // Num. of blocks
vector<vector<int>> bct_to = bct.to;
assert(n + b == (int)bct_to.size());

// 得られた block cut tree を heavy-light decomposition などに使う場合
heavy_light_decomposition hld(bct.size(), bct.get_edges());
hld.build();
```

## 問題例

- [Library Checker: Biconnected Components](https://judge.yosupo.jp/problem/biconnected_components)
- [No.1326 ふたりのDominator - yukicoder](https://yukicoder.me/problems/no/1326)
  - 無向グラフにおいて指定された 2 頂点間の任意のパスが含む頂点の集合は， block cut tree でその 2 頂点間のパス上に存在する頂点の集合と一致する．
- [AtCoder Beginner Contest 318 G - Typical Path Problem](https://atcoder.jp/contests/abc318/tasks/abc318_g)
- [AtCoder Beginner Contest 334 G - Christmas Color Grid 2](https://atcoder.jp/contests/abc334/tasks/abc334_g)
- [灘校文化祭コンテスト 2022 Day2 H - Tourist on Graph](https://atcoder.jp/contests/nadafes2022_day2/tasks/nadafes2022_day2_h)
- [Codeforces Round 606 (Div. 1, based on Technocup 2020 Elimination Round 4) B. Two Fairs - Codeforces](https://codeforces.com/contest/1276/problem/B)
- [2022-2023 Winter Petrozavodsk Camp, Day 2: GP of ainta I. Visiting Friend - Codeforces](https://codeforces.com/gym/104427/problem/I)

## 参考文献・リンク

- [Block-cut tree - ei1333の日記](https://ei1333.hateblo.jp/entry/2020/03/25/010057)
- [My Algorithm : kopricky アルゴリズムライブラリ](https://kopricky.github.io/code/GraphDecomposition/articulation.html)
- [拡張 Block Cut Tree | cp_library](https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html)
- [Xユーザーの熨斗袋さん: 「G = (V, E) に対する Block Cut Tree、G の2-点連結成分全体を C として...](https://x.com/noshi91/status/1529858538650374144)
