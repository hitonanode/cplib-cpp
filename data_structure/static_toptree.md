---
title: Static top tree
documentation_of: ./static_toptree.hpp
---

いわゆる Static top tree を扱う．根付き木の部分木に関する各種演算をクエリあたり $O(n \log n)$ で行える．

## 原理

Static top tree のしくみについては [解説 - AtCoder Beginner Contest 351](https://atcoder.jp/contests/abc351/editorial/9868) 等も併せて参照されたい．

Static top tree は，根付き木をもとに平衡二分木を構築する．平衡二分木の各頂点には `PointCluster` と `PathCluster` の 2 種類のデータ構造のいずれかが載る．

例えば，入力として以下の根付き木（ $0$ が根）を与えた場合に構築される static top tree を下に示す．ここで入力の木の辺のうち二重線は heavy-light decomposition (HLD) の heavy edge, 破線は light edge を示す．

![入力](https://gist.githubusercontent.com/hitonanode/330e4c27e0fb231f82cafaba541bbe19/raw/d9ce4a3b4fdda25e8cb9380c65ead5475cce18e6/static-top-tree-example-input-graph.svg)

![出力](https://gist.githubusercontent.com/hitonanode/330e4c27e0fb231f82cafaba541bbe19/raw/d9ce4a3b4fdda25e8cb9380c65ead5475cce18e6/static-top-tree-example-output-graph.svg)

出力の辺のうち実線は PathCluster, 破線は PointCluster が親頂点に伝播されることをそれぞれ意味する．

図から分かるように，HLD の heavy path は PathCluster として管理され， compress 処理によってマージされる．また， light edge で親と繋がる子頂点たちは PointCluster として管理され， rake 処理によってマージされる．これらの処理を問題に応じてうまく考案・実装してやる必要がある．

## 使用方法

まず，以下のように `Point` クラス・ `Path` クラスと `vertex()` / `compress()` / `rake()` / `add_edge()` / `add_vertex()` メソッドを持つクラスを定義する（ `static` はなくても可）．

```cpp
struct tree_dp {
    // Point Cluster
    struct Point {};

    // Path Cluster
    struct Path {};

    Path vertex(int i);

    static Path compress(const Path &parent, const Path &child);

    static Point rake(const Point &l, const Point &r);

    static Point add_edge(const Path &d);

    Path add_vertex(const Point &d, int i);
};
```

その後，以下の手順で構築・利用する．

```cpp
// 前準備
vector<vector<int>> to;  // 隣接リスト
int root = 0;

// 構築
const static_toptree_structure stts(to, root);
tree_dp dp;
static_toptree tree(stts, dp);

// 利用
tree.set(u); // 頂点 u に更新があった場合に呼ぶ

auto p = tree.all_prod();  // 根に関して値取得
```

## 問題例

- [AtCoder Beginner Contest 351 G - Hash on Tree](https://atcoder.jp/contests/abc351/tasks/abc351_g)
- [Library Checker: Point Set Tree Path Composite Sum (Fixed Root)](https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root)
