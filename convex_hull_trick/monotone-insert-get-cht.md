---
title: Convex hull trick (monotone insert, monotone get)
documentation_of: ./monotone-insert-get_cht.hpp
---

各クエリが償却 $O(1)$．

- `insert_line(T a, T b)` 直線追加クエリ．追加される直線 $y = ax + b$ について，$a$ の値が単調非増加（最小値取得） / 単調非減少（最大値取得）．
- `get(T x)` 最小値・最大値取得クエリ．取得する $x$ 座標は単調非減少．

- `insert_convex_parabola(T c, T a, T b)` 放物線 $y = c(x - a)^2 + b$ の追加クエリ．$c$ の値は全クエリで共通でなければならない．最小値取得の場合，$ca$ の値が単調増加でなければならない．
- `parabola_get(T c, T x)` 放物線たちの最小値・最大値取得クエリ．取得する $x$ 座標は単調非減少．
- `merge(CHT cht1, CHT cht2)` 二つの CHT をマージする．計算量は $O(\mathrm{size}(\mathrm{cht1}) + \mathrm{size}(\mathrm{cht2}))$．

## 問題例

- [No.952 危険な火薬庫 - yukicoder](https://yukicoder.me/problems/no/952)
