---
title: 線形漸化式の発見・第 $N$ 項推定
documentation_of: ./linear_recurrence.hpp
---

線形漸化式

## 漸化式（最小多項式）の推定

Berlekamp-Massey algorithm を用いて，最初の数項から漸化式を推定する．時間計算量は入力数列長 $L$ に対して $O(L^2)$．

```cpp
vector<mint> a = {1, 1, 2, 3, 5, 8, 11};
auto [d, Crev] = find_linear_recurrence(a);  // (2, [1, -1, -1])
```

推測して得られた $C^\mathrm{rev}$ は，

$\displaystyle
    \sum_{j=0}^d C^\mathrm{rev}_{i - j} a_{j} = 0
$

が成立．

## $K$ 次線形漸化式に従う数列の第 $N$ 項の，先頭 $K$ 項の寄与への分解

時間計算量は現在の実装だと $O(K^2 \log N)$ （正しくアルゴリズムを設計すれば $O(K \log K \log N)$）．

```cpp
long long n = 12345678910111213LL;
vector<mint> b = monomial_mod_polynomial(n, Crev);
```

母関数の言葉で述べると，単項式 $x^n$ を $K$ 次多項式 $C^\mathrm{rev} (x)$ で割った剰余を求めている．先頭 $K$ 項を $[a_0, \dots, a_{K-1}]$ とすると，第$N$ 項の値は $\displaystyle \sum_{i=0}^{K-1} a_i b_i$ で与えられる．

## 線形漸化式に従う数列の先頭の $L$ 項からの，第 $N$ 項の値の推定

上記を一括で行う．時間計算量は入力数列長 $L$ に対して $O(L^2 \log N)$．

```cpp
mint kth_term = guess_kth_term(vector<mint>{1, 1, 2, 3, 5, 8}, 12345678910111213);
```
