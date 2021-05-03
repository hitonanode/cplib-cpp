---
title: Sum of exponential times polynomial ($\sum_{i=0}^{N - 1} r^i f(i)$)
documentation_of: ./sum_of_exponential_times_polynomial_limit.hpp
---

一般に $f(x)$ を高々 $d$ 次の多項式として，$\displaystyle \sum_{i=0}^{N - 1} r^i f(i)$ を求める．先頭 $d + 1$ 項の値が既知であれば計算量は $O(d)$．関数は分かるが具体的な値が未知の場合は $O\left(d \left(\log d\right)^2\right)$ で先頭 $d + 1$ 項の値の multipoint evaluation を行う必要があると思われる．

## 導出の説明

[min\_25 さん](https://min-25.hatenablog.com/entry/2015/04/24/031413) によると，求めたい値は $C + g(x) r^x$, $g(x)$ はなんらかの多項式，という形になる．したがって，$r = 1$ の場合はそのまま Lagrange 補間を行えばよく，$r \neq 1$ の場合は $C$ や $r^x$ の分を打ち消した $g(x)$ に対して Lagrange 補間を行えばよい．$C$ の値は `sum_of_sum_of_exponential_times_polynomial_limit()` 関数によって $O(d)$ で求められる．

## 使用方法

先頭の $d + 1$ 項を計算して `sum_of_exponential_times_polynomial()` 関数に与える．
```cpp
using mint = ModInt<998244353>;
vector<mint> xs(d + 1);
for (int i = 0; i <= d; i++) xs[i] = i;
vector<mint> f = some_function();
vector<mint> initial_terms = MultipointEvaluation<mint>(xs).evaluate_polynomial(f);

mint sum = sum_of_exponential_times_polynomial<mint>(r, initial_terms, 12345678910111213LL);
```

単項式の場合，先頭 $d + 1$ 項の列挙が線形篩により $O(d)$ で可能である．使用方法は以下の通り．

```cpp
mint r;
int d;
vector<mint> initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);
cout << sum_of_exponential_times_polynomial<mint>(r, initial_terms, 12345678910111213LL) << '\n';
```

## リンク

- https://min-25.hatenablog.com/entry/2015/04/24/031413
- https://github.com/yosupo06/library-checker-problems/issues/98
