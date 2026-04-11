---
title: Modular arithmetic utilities （C++ の基本型整数に対する拡張 GCD・中国剰余定理・連立線形合同式などの実装）
documentation_of: ./bare_mod_algebra.hpp
---

modint を使わない `int` などの整数型上での剰余演算ユーティリティ集．拡張ユークリッドの互除法，モジュラ逆元，中国剰余定理 (CRT)，連立線形合同式の求解などを提供する．

## 使用方法

### `extgcd(a, b, x, y)`

$ax + by = \gcd(a, b)$ を満たす整数 $x, y$ を求め，$\gcd(a, b)$ を返す．

```cpp
long long x, y;
long long g = extgcd(12LL, 8LL, x, y); // g = 4
```

### `inv_mod(a, m)`

$a$ の $m$ を法とする逆元を返す．$\gcd(a, m) = 1$ であることが必要．返り値は $[0, m)$ の範囲．

```cpp
long long inv = inv_mod(3LL, 7LL); // inv = 5 (3*5 = 15 ≡ 1 mod 7)
```

### `inv_gcd(a, b)`

$g = \gcd(a, b)$ および $xa \equiv g \pmod{b}$，$0 \le x < b/g$ を満たす $(g, x)$ を返す．$b \ge 1$ が必要．

### `crt(r, m)`

中国剰余定理．$x \equiv r_i \pmod{m_i}$ $(i = 0, \ldots, n-1)$ を同時に満たす $x$ を求める．解が存在すれば $(x \bmod \mathrm{lcm}, \mathrm{lcm})$ を，存在しなければ $(0, 0)$ を返す．

```cpp
vector<long long> r = {2, 3}, m = {3, 5};
auto [x, lcm] = crt(r, m); // x = 8, lcm = 15
```

### `linear_congruence(A, R, M)`

連立線形合同式 $A_i x \equiv R_i \pmod{M_i}$ の解を求める．解が存在すれば $(x \bmod m, m)$ を，存在しなければ $(0, 0)$ を返す．

```cpp
vector<long long> A = {1, 1}, R = {2, 3}, M = {3, 5};
auto [x, m] = linear_congruence(A, R, M); // x ≡ 8 mod 15
```
