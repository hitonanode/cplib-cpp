---
title: 非再帰セグメント木で区間に対応する頂点番号の列挙
documentation_of: ./segtree_range_covering_nodes.hpp
---

長さ $N$ の列を管理する非再帰セグメント木のよく知られた実装において，区間 $[l, r)$ をカバーする頂点番号の列を，区間が管理する要素の位置順に出力する．セグメント木上に複雑なデータ構造を載せ（例：Convex Hull Trick），区間更新や取得を行う際などに使用機会がある．

なお，長さ $N$ の列のうち $i$ 番目の**要素を含む**全ての頂点を列挙するには，
```cpp
i += N;
whlie (i) { do_something(i), i >>= 1; }
```
とすればよい．

## 使用例

```cpp
vector<ConvexHullTrick<__int128>> chts(N * 2, true); // 長さ N の列に対して，区間を管理する CHT を 2N 個生成

for (auto i : segtree_range_covering_nodes(N, l, r)) {
    chts[i].add_convex_parabola(1, x, y0);
}
```

## リンク

- [非再帰セグ木サイコー！ 一番すきなセグ木です](https://hcpc-hokudai.github.io/archive/structure_segtree_001.pdf)
  - 非再帰セグメント木の解説．
- [使用例（早稲田大学プログラミングコンテスト2019 I - Ramen）](https://atcoder.jp/contests/wupc2019/submissions/22283489)
  - セグメント木に Convex Hull Trick を載せる．
