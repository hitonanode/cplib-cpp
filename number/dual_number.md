---
title: Dual number （二重数）
documentation_of: ./dual_number.hpp
---

二重数 `DualNumber<T>` の実装．直感的には $x$ の一次の係数まで常に保持する形式的冪級数と等価．

総和を DP で求めさせる問題で頻出する
```cpp
vector<T> dp0, dp1, dpnxt0, dpnxt1;
dpnxt1[inxt] += dp1[i] * a;
dpnxt1[inxt] += dp0[i] * b;
dpnxt0[inxt] += dp0[i] * a;
```
のような遷移について，`T` 上の二重数を導入すると
```cpp
using TT = DualNumber<T>;
vector<TT> dp, dpnxt;
dpnxt[inxt] += dp[i] * TT(a, b);
```
のように書けて楽．


## 問題例

- [AtCoder Beginner Contest 235 F - Variety of Digits](https://atcoder.jp/contests/abc235/tasks/abc235_f)
- [No.1303 Inconvenient Kingdom - yukicoder](https://yukicoder.me/problems/no/1303)
