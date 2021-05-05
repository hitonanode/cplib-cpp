---
title: Euler's totient function（オイラーのトーシェント関数）
documentation_of: ./euler_totient_phi.hpp
---

Euler's totient function $\varphi(n)$ は正の整数 $n$ に対して $n$ と互いに素な $n$ 以下の正の整数の個数．

## 使用例

``` cpp
std::vector<int> phi_table = euler_phi_table(N);  // N 以下の正の整数に対するテーブル作成 O(N log N)

auto phi = euler_phi<long long>(12345678910LL);  // 特定の整数に対する計算 O(sqrt N)
```

## 性質

- （オイラーの定理）$a$ と $n$ が互いに素なとき，$\displaystyle a^{\varphi(n)} \equiv 1 \pmod{n}$

## 問題例

- [CS Academy FIICode 2021 Round #2 - Clown Fiesta](https://csacademy.com/contest/fii-code-2021-round-2/task/clown-fiesta/)

## リンク

- [Euler's totient function - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_totient_function)
