---
title: Sparse formal power series （疎な形式的冪級数の演算）
documentation_of: ./sparse_fps.hpp
---

疎な形式的冪級数 $f(x)$ に対して，$x^N$ までの累乗・逆元・対数・指数関数・平方根を計算する．$f(x)$ の非零項数を $K$ として，いずれも $O(NK)$ で動作する．

## 使用方法

名前空間 `sparse_fps` に以下の関数が定義されている．テンプレート引数 `Vec` は `std::vector<T>` を継承した型で，`T` は体の元として `+`, `-`, `*`, `/`, `pow`, `inv` 等をサポートする必要がある（典型的には ModInt）．

### `sparse_fps::pow`

```cpp
Vec sparse_fps::pow(const Vec &f, int max_deg, long long k);
```

$f(x)^k \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$k \ge 0$．

### `sparse_fps::inv`

```cpp
Vec sparse_fps::inv(const Vec &f, int max_deg);
```

$1 / f(x) \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$f_0 \neq 0$ が必要．

### `sparse_fps::log`

```cpp
Vec sparse_fps::log(const Vec &f, int max_deg);
```

$\log f(x) \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$f_0 \neq 0$ が必要．

### `sparse_fps::exp`

```cpp
Vec sparse_fps::exp(const Vec &f, int max_deg);
```

$\exp f(x) \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．$f_0 = 0$ が必要．

### `sparse_fps::sqrt`

```cpp
std::optional<Vec> sparse_fps::sqrt(const Vec &f, int max_deg);
```

$\sqrt{f(x)} \bmod x^{\mathrm{max\\_deg}+1}$ を計算する．最小次数の非零項 $f_{d_0}$ について $d_0$ が偶数かつ $f_{d_0}$ が平方根を持つ必要がある．解が存在しない場合は `std::nullopt` を返す．

## 問題例

- [Pow of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse)
- [No.1939 Numbered Colorful Balls - yukicoder](https://yukicoder.me/problems/no/1939)
- [Codeforces Round 1058 (Div. 1) E. Super-Short-Polynomial-San](https://codeforces.com/contest/2159/problem/E)
- [Inv of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse)
- [Log of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse)
- [Exp of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse)
- [Sqrt of Formal Power Series (Sparse) - Library Checker](https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse)

## リンク

- [A problem collection of ODE and differential technique - Codeforces](https://codeforces.com/blog/entry/76447)
- [library-checker-problems #767 (comment)](https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020)
