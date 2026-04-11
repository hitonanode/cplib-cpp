---
title: Modular exponentiation （べき乗 mod）
documentation_of: ./pow_mod.hpp
---

整数 $x$, 非負整数 $n$, 正整数 $m$ に対し，$x^n \bmod m$ を $O(\log n)$ で計算する．繰り返し二乗法による実装．`Int` が `int` のとき内部で `long long`，`long long` のとき `__int128` を用いてオーバーフローを回避する．

## 使用方法

```cpp
int a = pow_mod(3, 100, 1000000007);       // Int = int
long long b = pow_mod(3LL, 100LL, (long long)1e18 + 9); // Int = long long
```

- `x`: 底．
- `n`: 指数（$n \ge 0$）．
- `md`: 法（$m \ge 1$）．$m = 1$ のとき常に $0$ を返す．
