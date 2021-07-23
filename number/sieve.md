---
title: Linear sieve （線形篩）
documentation_of: ./sieve.hpp
---

線形篩．構築 $O(N)$．自然数 $K \leq N$ の素因数分解は $O(\log K)$．

## 使用例

```cpp
Sieve sieve(1 << 20); // 2^20 以下の全素数や，各整数の最小素因数を計算．

// 素数判定
bool is_prime = (sieve.min_factor[x] == x);

// 素因数分解
map<lint, int> mp = sieve.factorize(x);

// 約数列挙（昇順とは限らない）
vector<lint> divs = sieve.divisors(x);

// i = 0, 1, ..., n について i^k を格納した配列を生成． O(n)
vector vs = enumerate_kth_pows<ModInt<998244353>>(3, 10); // v = [0,1,8,27,64,125,216,343,512,729,1000,]
```

## 文献・リンク

- [1] D. Gries, J. Misra, "A Linear Sieve Algorithm for Finding Prime Numbers," Communications of the ACM, 21(12), 999-1003, 1978.
- [Sieve of Eratosthenes With Linear Time Complexity - Competitive Programming Algorithms](https://cp-algorithms.com/algebra/prime-sieve-linear.html)
- [線形篩 – 37zigenのHP](https://37zigen.com/linear-sieve/)
