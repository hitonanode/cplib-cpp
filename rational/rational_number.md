---
title: Rational number （有理数）
documentation_of: ./rational_number.hpp
---

分子と分母の値をそれぞれ整数型で持つ有理数の実装．

## 使用方法

```cpp
Rational<__int128, true> r1;  // true: 約分する
Rational<__int128, false> r2;  // false: 約分しない，CHT など四則演算を繰り返さない場合はこちらが高速でよい
```

## 問題例

- [Yandex Cup 2022 Algorithm Final E. Stepwise subsequence](https://contest.yandex.com/contest/42710/problems/K/) : 有理数で CHT する．
