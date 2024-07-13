---
title: Rational approximation （有理数近似）
documentation_of: ./rational_approximation.hpp
---

与えられた非負の有理数 `num / den` に対して，分子・分母がともに $N$ 以下の分数で両側から近似する．

## 使用方法

```cpp
int N, num, den;
const auto [l, r] = rational_approximation<int>(N, num, den);

// lnum / lden <= num / den <= rnum / rden
// max(lnum, lden, rnum, rden) <= N
const auto [lnum, lden] = l;
const auto [rnum, rden] = r;
```

## 問題例

- [Library Checker: Rational Approximation](https://judge.yosupo.jp/problem/rational_approximation)
