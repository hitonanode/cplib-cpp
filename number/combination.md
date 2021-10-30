---
title: Combination （${}_n \mathrm{C}_r \bmod{m}$，Lucas の定理の拡張）
documentation_of: ./combination.hpp
---

固定された正整数 $m = p\_1^{q\_1} \dots p\_{k}^{q\_k} ( \le 10^7)$ について，$\binom{n}{r} \bmod{m}$ の値を計算する．前計算 $O(\sum_i p\_i^{q\_i})$，クエリ $O(k \mathrm{log}(n))$．

## 原理

$m$ を素因数分解し，各素数冪 $p^q$ を法とした $\binom{n}{r}$ の値を拡張 Lucas の定理を用いて計算し，中国剰余定理を用いて解を復元する．

## 使用方法

コンストラクタには法 $m$ を素因数分解した結果の（素数，次数）の組として（例：`vector<pair<int, int>>`, `map<int, int>` ）与える．例えば $\bmod{60}$ で計算したい場合は `{2, 2}, {3, 1}, {5, 1}` を与えればよい．また，本ライブラリの `Sieve` クラスの `factorize()` が返す結果をそのまま渡してもよい：

```cpp
combination nCr(Sieve(1 << 20).factorize(mod));
cout << nCr(n, r) << '\n';
```

## 問題例

- [Library Checker: Binomial Coefficient](https://judge.yosupo.jp/problem/binomial_coefficient)

## リンク

- [2015 ICL, Finals, Div. 1　J. Ceizenpok’s formula (nCk mod m の求め方) - ferinの競プロ帳](https://ferin-tech.hatenablog.com/entry/2018/01/17/010829)
