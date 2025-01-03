---
title: Euler tour （木のオイラーツアー）
documentation_of: ./euler_tour.hpp
---

木のオイラーツアーを構築．パスクエリをデータ構造に載せて高速に解く場合や， Mo's algorithm を適用する場合に有用．

## 使用方法

以下で構築できる．

```cpp
int n, root;
vector<pair<int, int>> edges;

const euler_tour et(n, edges, root);
```

木上の $u$-$v$ パスに着目したい場合，以下の処理を行うと，当該パスを構成する辺が半開区間 `[begins, ends)` に丁度奇数回登場する．

```cpp
int begins = et.begins.at(u), ends = et.begins.at(v);

for (int i = begins; i < ends; ++i) {
    // Insert or erase et.tour_child(i);
}
```

半開区間 `[begins, ends)` たちに対して Mo's algorithm などを適用することで，クエリたちが効率的に処理できることがある．

## 問題例

- [Primitive Queries \| CodeChef](https://www.codechef.com/problems/DISTNUM3)
  - 木のパス上の頂点集合に関するクエリを Mo's algorithm で解く．

## 参考文献・リンク

- [Mo's algorithm - ei1333の日記](https://ei1333.hateblo.jp/entry/2017/09/11/211011)
