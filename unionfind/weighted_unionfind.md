---
title: Weighted UnionFind （重み付き UnionFind）
documentation_of: ./weighted_unionfind.hpp
---

2個の要素間の重みづけが可能な UnionFind．

## 使用方法

- ポテンシャルが（ふつうの）整数の場合．
```cpp
WeightedUnionFind<int> uf(N);
uf.unite(s, t, diff);  // f[t] = f[s] + diff を要請．これまでの要請と矛盾すれば false を返す．

auto x = uf.diff(s, t);  // f[t] - f[s] （として考えられる値の一つ）を出力．
```

- ポテンシャルが $\mathbb{F}_2$ 上のベクトルの場合．
```cpp
WeightedUnionFind<F2vec<unsigned>> uf(N);
```

## 問題例

- [No.1420 国勢調査 (Easy) - yukicoder](https://yukicoder.me/problems/no/1420) $\mathbb{F}_2$ 上のベクトル．