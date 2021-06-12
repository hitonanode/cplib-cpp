---
title: Cyclotomic polynomials （円分多項式）
documentation_of: ./cyclotomic_polynomials.hpp
---

## できること

円分多項式（[Wikipedia (en)](https://en.wikipedia.org/wiki/Cyclotomic_polynomial)）の係数を愚直に計算

## Definition

$\displaystyle
\Phi_n (x) := \prod_{1 \leq k \leq n, gcd(k, n) = 1} \left( x - e^{2 \mathrm{i} \pi k / n} \right)
$

## 使用例

``` cpp
vector<vector<int>> Phi = cyclotomic_polynomials(120); // Phi[i][j] = [x^j]Phi_i(x) for i <= 120
```

- Complexity: $O(n^2)$
- All coefficients are known to be "small" integers.

## 等式

- $\prod_{d \mid n} \Phi_d (x) = x^n - 1$
- $\Phi_n (x) = \prod_{d \mid n} \left(x^{n / d} - 1 \right) ^ {\mu(d)}$
- $\Phi_p (x) = 1 + x + \ldots + x^{p - 1} \ (p : \text{prime})$

## 応用

- 環 $R$ 上で長さ $n$ の離散フーリエ変換をしたいが $1$ の原始 $n$ 乗根がとれないとき，$R[x] / \Phi_n(x)$ 上で考えると $x$ が所望の原始 $n$ 乗根となる．高次元の円状畳み込みなどで有用．
  - [問題例](https://codeforces.com/contest/1103/problem/E)

## 問題例

- SRM 776 Div.1 Hard
