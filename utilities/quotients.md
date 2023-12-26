---
title: Quotients of integer （商列挙）
documentation_of: ./quotients.hpp
---

正の整数 $n$ に対して $\lfloor n / k \rfloor$ （ $k$ は整数）の形で表される整数を昇順に列挙する．計算量は $O(\sqrt{n})$.

## 使用方法

```cpp
long long n = 10;
vector<long long> v = get_quotients(n);  // 1, 2, 3, 5, 10
```

## 問題例

- [Library Checker: Enumerate Quotients](https://judge.yosupo.jp/problem/enumerate_quotients)
