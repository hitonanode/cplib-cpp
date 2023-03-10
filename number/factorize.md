---
title: Integer factorization （素因数分解）
documentation_of: ./factorize.hpp
---

$10^{18}$ 以下の正の整数を素因数分解する．

## 使用方法

### 素数判定

```cpp
long long a;
bool ret = is_prime(a);
```

### 素因数分解

```cpp
long long a;
vector<long long> ret = FactorizeLonglong(a);  // returns sorted primes
```

## 問題例

- [Library Checker: Factorize](https://judge.yosupo.jp/problem/factorize)
