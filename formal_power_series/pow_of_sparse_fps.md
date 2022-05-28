---
title: Power of sparse formal power series （非零な項が疎な形式的冪級数の累乗）
documentation_of: ./pow_of_sparse_fps.hpp
---

形式的冪級数 $f(x)$ について，$(f(x))^k$ の $x^N$ までの項を $O(NM)$ で計算する．ここで $M$ は $f(x)$ の $N$ 次以下で非零な項の個数．

## ナイーブな説明

$\displaystyle
g(x) = f(x)^k
$

について，両辺 $\log$ をとってから微分することで

$\displaystyle
\frac{g'(x)}{g(x)} = k \frac{f'(x)}{f(x)}
$

を得る．これより

$\displaystyle
f(x) g'(x) = k f'(x) g(x)
$

が成立する．両辺の各項の次数を低い順から順に合わせていけばよい．

## 使用方法

```cpp
vector<mint> f;  // mint は除算が可能でなければならない
long long k;

// f(x)^k を x^N の係数まで計算
vector<mint> g = pow_of_sparse_fps(f, N, k)  // g.size() == N + 1
```

## 問題例

- [No.1939 Numbered Colorful Balls - yukicoder](https://yukicoder.me/problems/no/1939)

## リンク
- [A problem collection of ODE and differential technique - Codeforces](https://codeforces.com/blog/entry/76447)
