---
title: Heavy-light decomposition （HLD, 木の重軽分解）
documentation_of: ./heavy_light_decomposition.hpp
---

木の重軽分解を行い，列に対する処理を木上のパスや部分木に含まれる全ての頂点に拡張した処理や，最小共通祖先の効率的な計算を可能にする．前処理 $O(n)$．

## 使用方法

### 前処理

```cpp
int n;  // 頂点数
vector<pair<int, int>> edges;

heavy_light_decomposition hld(n, edges);
hld.build();  // O(N)
```

### 木に対する基本的なクエリ

以下，すべてクエリ $O(\log n)$．

```cpp
cout << hld.lowest_common_ancestor(a, b) << '\n'; // (a, b) の最長共通祖先
cout << hld.kth_parent(a, k) << '\n';  // 頂点 a の k 世代親
cout << hld.distance(a, b) << '\n';  // 2 頂点 a, b の距離
cout << hld.s_to_t_by_k_steps(s, t, k) << '\n'; // 頂点 s から t 方向に k 歩動いた頂点
```

### セグメント木などを利用した木上パスクエリへの対応

```cpp
// 各頂点の情報
std::vector<S> vertices_info(n);

// HLD の分解順を考慮したセグメント木の初期化
// セグメント木上で，分解されたパス上の要素は「根方向のものから順に」連続して並ぶことに注意
atcoder::segtree<S, op, e> segtree(hld.segtree_rearrange(vertices_info));

// 頂点 from から頂点 to へのパス（両端点を含む）上の要素合成クエリ
S ret = e();
auto func = [&](int u, int v) { ret = op(ret, segtree.prod(u, v + 1)); };
hld.for_each_vertex(from, to, func);
```

## 問題例

- [Library Checker: Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
- [Library Checker: Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
- [いろはちゃんコンテスト Day2 K - 虫取り](https://atcoder.jp/contests/iroha2019-day2/tasks/iroha2019_day2_k)
  - 部分木クエリとパスクエリの両方が使われる．

## 参考文献・リンク

- [Easiest HLD with subtree queries - Codeforces](https://codeforces.com/blog/entry/53170)
