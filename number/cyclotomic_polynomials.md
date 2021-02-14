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

## 問題例

- SRM 776 Div.1 Hard
