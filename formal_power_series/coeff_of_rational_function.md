---
title: 線形漸化式に関する高速計算（Bostan-Mori algorithm）
documentation_of: ./coeff_of_rational_function.hpp
---

## 線形漸化式の第 $N$ 項計算

$K$ 次多項式 $P(x), Q(x)$ に対して $\displaystyle [x^N] \frac{P(x)}{Q(x)}$ を計算する（Bostan-Mori algorithm [1]）．時間計算量は $O(K \log K \log N)$．

```cpp
long long N;
vector<mint> P, Q;
mint nth_coeff = coefficient_of_rational_function(N, P, Q);
```

## 初項と漸化式から第 $N$ 項計算

$K$ 次漸化式と先頭 $K$ 項 $[a_0, a_1, \dots, a_{K-1}]$ から第 $N$ 項 $a_N$ を計算する．時間計算量は $O(K \log K \log N)$．

```cpp
vector<mint> init = {1, 9, 1, 2}, recurrence = {1, -4, -1, 0, -1};
mint x = find_kth_term(init, recurrence, 12345678910111213);
```

実装上は，$A(x) = \sum_{i=0}^{K-1} a_i x^i$ と漸化式である $Q(x)$ を線形畳み込みして（積をとって）長さ $K$ で打ち切ったものを $P(x)$ として用いることで，上の `coefficient_of_rational_function()` 関数が使用可能な形式に帰着させている．

## 文献・リンク

- [1] A. Bostan and R. Mori, “A simple and fast algorithm for computing the N-th term of a linearly recurrent sequence,” SIAM SOSA, pp.118–132, Jan. 11–12 2021.
- [線形漸化的数列のN項目の計算 - Qiita](https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a)
