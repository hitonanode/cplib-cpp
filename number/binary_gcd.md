---
title: Binary GCD
documentation_of: ./binary_gcd.hpp
---

二つの整数の最大公約数を求める高速なアルゴリズムとして知られる Binary GCD の実装．Euclid の互除法によるアルゴリズムと異なり，2 以外の除算が登場しない．

## 使用例

``` cpp
long long a, b;
long long g = binary_gcd(a, b);
```

## リンク

- [Binary GCD algorithm - Wikipedia](https://en.wikipedia.org/wiki/Binary_GCD_algorithm)
