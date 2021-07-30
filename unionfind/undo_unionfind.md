---
title: UnionFind with Undo operation （Undo 可能 UnionFind）
documentation_of: ./undo_unionfind.hpp
---

Undo 操作が可能な UnionFind．もともと同じ連結成分に属する元同士の `unite()` も操作一回に数える．

## 使用方法

```cpp
UndoUnionFind uf(N);
uf.unite(a, b);
uf.undo();
uf.unite(c, d);
uf.count(0);
uf.same(e, f);
uf.reset();
```

## 問題例

- [Educational Codeforces Round 62 F. Extending Set of Points](https://codeforces.com/contest/1140/problem/F)
- [Harbour.Space Scholarship Contest 2021-2022 G. Common Divisor Graph](https://codeforces.com/contest/1553/problem/G)
