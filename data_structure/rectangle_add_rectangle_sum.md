---
title: Static rectangle add rectangle sum （矩形一様加算・矩形総和取得）
documentation_of: ./rectangle_add_rectangle_sum.hpp
---

以下の処理を $O(n \log n)$ （$n$ は総クエリ数）で行う．

- 事前矩形加算クエリ：$x\_l \le x < x\_r, y\_l \le y < y\_r$ を満たす各格子点 $(x, y)$ に重み $v$ を加算する．
- 矩形和取得クエリ：$x\_l \le x < x\_r, y\_l \le y < y\_r$ を満たす各格子点 $(x, y)$ の重みの総和を取得する．

## 原理

単一の矩形和取得クエリ $(x\_l, x\_r, y\_l, y\_r)$ によって得られる値を $f(x\_l, x\_r, y\_l, y\_r)$ と表記すると，


$\displaystyle
    f(x\_l, x\_r, y\_l, y\_r) = f(-\infty, x\_r, -\infty, y\_r) - f(-\infty, x\_l, -\infty, y\_r) - f(-\infty, x\_r, -\infty, y\_l) + f(-\infty, x\_l, -\infty, y\_l)
$

が成立する．よって，矩形和取得クエリとして $x\_l = y\_l = -\infty$ のものにだけ対応できればよい．

同様に，$(x\_l, x\_r, y\_l, y\_r)$ 型の矩形加算クエリも，$(x\_*, \infty, y\_*, \infty)$ 型のクエリの重ね合わせとして表現できる．

$(x\_a, \infty, y\_a, \infty)$ 型の矩形加算クエリの，$(-\infty, x\_s, -\infty, y\_s)$ 型の矩形和取得クエリへの寄与を考えたい．この寄与は $x\_a < x\_s$ または $y\_a < y\_s$ を満たさない場合ゼロとなる．両方を満たす場合は重みの寄与は $(x\_s - x\_a)(y\_s - y\_a)$ 倍される．

$y$ 軸方向のデータの管理に Fenwick tree を使用して $x$ 軸方向に平面走査を行うことで，$x\_a < x\_s$ 及び $y\_a < y\_s$ の制約の考慮が可能である．各矩形加算クエリに対して Fenwick tree を更新し，矩形和取得クエリ $(x\_s, y\_s)$ に対して Fenwick tree の和を求めればよい．このとき，取得すべき重みは $x\_s, y\_s$ についてそれぞれ $1$ 次の項と $0$ 次の項に展開できるから，それぞれの項を管理する $2^2 = 4$ 本の Fenwick tree を持つことで $x\_s, y\_s$ に関する多項式の形をした重みの寄与が適切に計算できる．

## 使用方法

```cpp
RectangleAddRectangleSum<int, mint> rect_sum;

rect_sum.add_rectangle(xl, xr, yl, yr, mint(w));  // Add w to each of [xl, xr) * [yl, yr)

rect_sum.add_query(l, r, d, u); // Get sum of [l, r) * [d, u)

vector<mint> ret = rect_sum.solve();
```

## 問題例

- [Codeforces Round #789 (Div. 1) E. Tokitsukaze and Beautiful Subsegments](https://codeforces.com/contest/1677/problem/E)
