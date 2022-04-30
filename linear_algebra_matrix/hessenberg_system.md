---
title: Hessenberg linear system
documentation_of: ./hessenberg_system.hpp
---

体上の $n \times n$ 正則 Hessenberg 行列 $\mathbf{A}$ と $n$ 次元ベクトル $b$ に対して，線形方程式系 $\mathbf{A} \mathbf{x} = \mathbf{b}$ を解く．計算量は $O(n^2)$．

## 使用方法

```cpp
vector<vector<mint>> A(N, vector<mint>(N));
vector<mint> b(N);

// A: lower Hessenberg, regular
vector<mint> x = solve_lower_hessenberg(A, b);

// A: upper Hessenberg, regular
vector<mint> x = solve_upper_hessenberg(A, b);
```

## 問題例

- [AtCoder Beginner Contest 249 Ex - Dye Color](https://atcoder.jp/contests/abc249/tasks/abc249_h)
