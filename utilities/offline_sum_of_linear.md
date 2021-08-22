---
title: Offline sum of linear segments （区間一次関数加算クエリの累積和を用いたオフライン処理）
documentation_of: ./offline_sum_of_linear.hpp
---

全ての項の値がゼロで初期化された数列 $[A_0, \dots, A_{N -1}]$ に対して以下のクエリを処理．

- $l \le i < r$ を満たす各 $i$ について $A_i$ に $f_0 + (i - l) \cdot df$ を加算．時間計算量 $O(1)$．
- $[A_0, \dots, A_{N - 1}]$ の値を陽に計算・取得．$O(N)$．

## 使用方法

```cpp
offline_sum_of_linear<long long> f(N);
f.add_linear(l, r, f0, df);

long long vi = f[i]; // 特定の項の取得
vector<long long> values = f.vals(); // [f[0], ..., f[N - 1]] の一括取得
```

## 問題例

- [AtCoder Regular Contest 125 E - Snack](https://atcoder.jp/contests/arc125/tasks/arc125_e)
- [AtCoder Grand Contest 052 E - 3 Letters](https://atcoder.jp/contests/agc052/tasks/agc052_e)
