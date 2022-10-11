---
title: UnionFind with Undo operation, monoid weights （Undo 可能・重み和取得可能 UnionFind）
documentation_of: ./undo_monoid_unionfind.hpp
---

Undo 操作が可能な UnionFind．もともと同じ連結成分に属する元同士の `unite()` も操作一回に数える．

また，各要素に重みを与え，連結成分の重み総和取得も可能．`undo_dsu<class S>` として与えるクラス `S` は以下のように `operator+=` が定義されている必要がある：

```cpp
struct S {
    S &operator+=(const S &x);
};

undo_dsu<S> dsu;
```

経路圧縮を行わないため，`find()` の計算量はクエリあたり $O(n \log n)$ となる．

## 使用方法

```cpp
vector<int> a{2, 3, 4, 5};
undo_dsu<int> uf(a);

uf.unite(0, 2);
uf.undo();
uf.unite(0, 1);
uf.count(0);
uf.sum(0);
uf.reset();
```
