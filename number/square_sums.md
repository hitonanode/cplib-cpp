---
title: Sum of two squares （二つの平方数の和）
documentation_of: ./square_sums.hpp
---

素数 $p$ に対して，$x^2 + y^2 = p$ を満たす非負整数の組 $(x, y)$ （$x \le y$）を求める．Fermat の二平方和定理に基づく．

$p = 2$ のとき $(1, 1)$ を，$p \equiv 1 \pmod{4}$ のとき解を返す．$p \equiv 3 \pmod{4}$ のときは解が存在せず $(-1, -1)$ を返す．

## 使用方法

```cpp
int p;  // prime
auto [x, y] = SumOfTwoSquaresPrime<int>(p);  // x <= y, x^2 + y^2 = p
```

内部で `sqrt_mod` を呼び出し，$-1$ の平方根 $r$ を求めた後，$p$ と $r$ に対するユークリッドの互除法を $r_i \le \sqrt{p}$ となるまで適用する．

## リンク

- [Fermat's theorem on sums of two squares - Wikipedia](https://en.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares)
