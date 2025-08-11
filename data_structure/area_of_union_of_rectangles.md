---
title: Area of union of rectangles （2 次元平面上の長方形たちが覆う面積）
documentation_of: ./area_of_union_of_rectangles.hpp
---

与えられた 2 次元平面上の各辺が $x$ 軸や $y$ 軸に平行な $n$ 個の長方形たちに対して，これらの和集合の面積を $O(n \log n)$ で計算する．

## 使用方法

```cpp
AreaOfUnionOfRectangles<long long> aur;

long long xl, xr, yl, yr;
aur.add_rectangle(xl, xr, yl, yr);

cout << aur.solve() << '\n';
```

## 問題例

- [Library Checker: Area of Union of Rectangles](https://judge.yosupo.jp/problem/area_of_union_of_rectangles)
