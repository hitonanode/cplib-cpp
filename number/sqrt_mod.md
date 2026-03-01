---
title: Square root modulo prime （平方剰余）
documentation_of: ./sqrt_mod.hpp
---

素数 $p$ と整数 $a$ に対して，$x^2 \equiv a \pmod{p}$ を満たす $x$ を求める．解が存在しない場合は $-1$ を返す．Tonelli-Shanks algorithm に基づく．

## 使用方法

```cpp
int a, p;
int x = sqrt_mod<int>(a, p);  // x^2 ≡ a (mod p), or -1

long long al, pl;
long long xl = sqrt_mod<long long>(al, pl);  // __int128 を内部で使用
```

`Int` が `int` のとき内部で `long long`，`long long` のとき `__int128` を乗算のオーバーフロー回避に使用する．

## 問題例

- [Library Checker: Sqrt Mod](https://judge.yosupo.jp/problem/sqrt_mod)

## リンク

- [Tonelli–Shanks algorithm - Wikipedia](https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm)
