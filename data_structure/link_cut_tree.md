---
title: Link-Cut tree
documentation_of: ./link_cut_tree.hpp
---

パス上の頂点更新・パス上の頂点積取得が可能な Link-Cut tree．インターフェースを `atcoder::lazy_segtree` に寄せている．

## 使用方法

内部で `evert()` を使用する関数は根を変更してしまうので注意．

```cpp
using S = unsigned long long;
using F = tuple<>;

F id() noexcept { return {}; } // 恒等作用素
S op(S l, S r) noexcept { return l + r; } // （非可換）半群 S に入る演算
S mapping(F f, S x) noexcept { return x; } // 半群 S への F の作用
S reversal(S x) noexcept { return x; } // S の列 [x_1, ..., x_N] の積から反転させた列の積を求める
F composition(F f, F g) noexcept { return {}; } // 作用の合成
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

LCT tree;
vector<LCT::Node *> vs;
vs.push_back(tree.make_node(a)); // 頂点作成
tree.link(vs[u], vs[v]); // 存在していない辺 uv を新たに張る
tree.cut(vs[u], vs[v]); // 既存の辺 uv を消す
tree.set(vs[p], a); // 頂点 p に乗る半群の元を a にする
tree.apply(vs[u], vs[v], f) // u から v までの最短パス上の各元に f を作用させる
S ret = tree.prod(vs[u], vs[v]) // u から v までの最短パス上の半群の元の積を得る
tree.evert(vs[p]); // 頂点 p を含む部分木の根を p に取る（なお上記の操作は根を勝手に変える）．
auto l = tree.lca(vs[u], vs[v]); // u, v の LCA を求める．
```

## 問題例

- [AOJ 2450: Do use segment tree](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450)
  - 
- [13539번: 트리와 쿼리 11](https://www.acmicpc.net/problem/13539) - `lca()`
- [16912번: 트리와 쿼리 12](https://www.acmicpc.net/problem/16912) - `is_connected()`
- [3 - 宇宙船 (Spaceships)](https://atcoder.jp/contests/joisc2013-day4/tasks/joisc2013_spaceships) `is_connected()`, `lca()`
  - [提出 #24456559 - 2013年 日本情報オリンピック春合宿 4日目](https://atcoder.jp/contests/joisc2013-day4/submissions/24456559)
- [A - かえってきたどうぶつたち と しんりんのさいせい (Return of Animals and Regeneration of Forests)](https://atcoder.jp/contests/ijpc2012-3/tasks/ijpc_animals2) `is_connected()`
  - [提出 #24457489 - IOIer Japan Programming Contest #3](https://atcoder.jp/contests/ijpc2012-3/submissions/24457489)
  - 辺に情報を持たせる代わりに，2 頂点間を内分する補助頂点を導入した．

## 参考文献・リンク・参考にした実装

- [1] D. D. Slator and R. E. Tarjan, "A data structure for dynamic trees,"
  Journal of computer and system sciences, 26(3), 362-391, 1983.
- [プログラミングコンテストでのデータ構造 2　～動的木編～](https://www.slideshare.net/iwiwi/2-12188845)
- [Link-Cut-Tree-Lazy-Path \| Luzhiled’s Library](https://ei1333.github.io/library/structure/lct/link-cut-tree-lazy-path.cpp)
