---
title: Sum of $k$-th powers of first $n$ positive integers （自然数の $k$ 乗和）
documentation_of: ./kth_power_sum.hpp
---

「 $1$ 以上 $n$ 以下の自然数の $k$ 乗の総和」を Faulhaber の公式を用いて計算する．

内部で Bernoulli 数の先頭 $k + 1$ 項を計算する必要がある．このコードでは `prefix_sum()` メンバ関数が呼ばれた時点で動的に不足している部分を計算し， $\Theta(k^2)$ で動く．より高速にする必要があれば，母関数 $x / (\exp(x) - 1) + x$ （第 1 項の定義に $+1/2$ を採用している点に注意）の冪級数展開を FFT 等で計算してメンバ変数 `bernoulli` に事前に設定しておけばよい．

## 使用方法

```cpp
using mint = ModInt<998244353>;
kth_power_sum<mint> kp;

int k = 1;
long long n = 10;

auto sum = kp.prefix_sum(k, n);  // 1^k + ... + n^k

assert(sum == mint(55));
```

## 問題例

- [No.665 Bernoulli Bernoulli - yukicoder](https://yukicoder.me/problems/no/665)
- [Educational Codeforces Round 7 F. The Sum of the k-th Powers - Codeforces](https://codeforces.com/contest/622/problem/F)
