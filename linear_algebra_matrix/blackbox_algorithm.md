---
title: Black box linear algebra を利用した各種高速計算
documentation_of: ./blackbox_algorithm.hpp
---

## 行列式の高速計算

$n \times n$ 行列の行列式を $O(n T(n) + n^2)$ で計算する（$T(n)$ は行列ベクトル積の計算量）．

### 使用方法

```cpp
sparse_matrix<mint> mat(n, n);

mint det = blackbox_determinant<sparse_matrix<mint>, mint>(mat);
```

## 行列累乗 DP の高速計算

$n \times n$ 行列 $A$ と $n$ 次元ベクトル $b$ について，$A^k b$ を $O(n^2 \log k + n T(n))$ で計算する（$T(n)$ は行列ベクトル積の計算量）．

### 使用方法

```cpp
int N;

sparse_matrix<mint> mat(D, D);
vector<mint> dp(D);

dp = blackbox_matrix_pow_vec(mat, N, dp);
```

## 問題例

- [Count Sequences \| CodeChef](https://www.codechef.com/submit/COUNTSEQ2?tab=statement) 行列累乗 DP の高速計算．TL には間に合わない．最小多項式を各 $M$ について前計算して埋め込むと間に合う．
