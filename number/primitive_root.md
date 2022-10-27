---
title: Primitive root modulo $n$ （原始根の発見）
documentation_of: ./primitive_root.hpp
---

与えられた整数 $n$ に対して，乗法群 $\mathbb{Z}^{\times}\_{n}$ に原始根が存在する場合に最小の原始根を計算する．$n \le 10^{18}$ を想定．

## 乗法群の原始根とは

$\mod n$ 上の整数のうち，乗法の逆元が存在するもののみをとって作る群を乗法群 $\mathbb{Z}^{\times}\_{n}$ と呼ぶ．

乗法群 $\mathbb{Z}^{\times}\_{n}$ の元 $r$ について，$r^0, r^1, r^2, \dots$ の集合が $\mathbb{Z}^{\times}\_{n}$ と（集合として）一致するとき，$r$ を乗法群の原始根と呼ぶ．

$\mathbb{Z}^\times\_{n}$ に原始根が存在するような $n$ は限られている．具体的には，$n = 2, 4, p^k, 2p^k$ のみである（$p$ は奇素数，$k$ は正の整数）．

## 最小の原始根について

本コードの
```cpp
    for (long long g = 1; g < n; g++) {
```
の部分について，`g` をインクリメンタルに調べることで最小の原始根を見つけている．$n$ が素数でかつ $10^{16}$ 以下の範囲では， $n = 6525032504501281$ のとき最小の原始根が $417$ となってこれが最大という（参考文献 [2]）．

上記のようなケースに対して，$g$ について乱択すれば（「最小の」原始根を諦める代わりに）実用上の高速化が可能と思われる [3]．

## 問題例

- [No.931 Multiplicative Convolution - yukicoder](https://yukicoder.me/problems/no/931)

## 参考文献・リンク

- [1] [整数論テクニック集 - kirika_compのブログ](https://kirika-comp.hatenablog.com/entry/2018/03/12/210446)
- [2] [[2206.14193] Computation of the least primitive root](https://arxiv.org/abs/2206.14193)
- [3] [原始根のアルゴリズム – 37zigenのHP](https://37zigen.com/primitive-root/)
- [4] [Primitive root modulo n - Wikipedia](https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
