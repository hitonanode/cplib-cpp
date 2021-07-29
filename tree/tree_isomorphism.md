---
title: Tree isomrphism （木の同型判定）
documentation_of: ./tree_isomorphism.hpp
---

根付き木のハッシュをとる．

## 使用方法

```cpp
tree_isomorphism<mint> tree(N);
for (auto [u, v] : edges) tree.add_edge(u, v);
tree.build_hash(0, 15319159, 181263479);
auto h = tree.hash[r]; // r を根にとったときのハッシュ値
```

## 問題例

- [AtCoder 第二回全国統一プログラミング王決定戦本戦 D - 木、](https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_d)
- [AOJ 1613: Deciphering Characters](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613)
