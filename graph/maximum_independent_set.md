---
title: Maximum independent set （最大独立集合）
documentation_of: ./maximum_independent_set.hpp
---

$N$ 頂点の単純無向グラフの（重みなし）最大独立集合の一つを求める指数時間アルゴリズム．時間計算量 $O(1.381^n n)$．
`std::bitset` を用いて実装されている `maximum_independent_set()` 関数と， `long long` 型を使用した定数倍が若干高速な `maximum_independent_set_int_based()` 関数が用意されている．

## 問題例

- [No.382 シャイな人たち (2) - yukicoder](https://yukicoder.me/problems/no/382)
- [Library Checker - Maximum Independent Set](https://judge.yosupo.jp/problem/maximum_independent_set)
