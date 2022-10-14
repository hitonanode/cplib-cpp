---
title: Primitive root （原始根の発見）
documentation_of: ./primitive_root.hpp
---

与えられた素数 $P$ に対して最小の原始根を計算する．$P \le 10^{18}$ を想定．

## 最小の原始根について

本コードの
```cpp
    for (long long g = 1; g < p; g++) {
```
の部分について，`g` をインクリメンタルに調べることで最小の原始根を見つけている．$10^{16}$ 以下の範囲では， $p = 6525032504501281$ のとき最小の原始根が $417$ となってこれが最大という（参考文献 [2]）．

上記のようなケースに対して，$g$ について乱択すれば（「最小の」原始根を諦める代わりに）実用上の高速化が可能と思われる [3]．

## 問題例

- [No.931 Multiplicative Convolution - yukicoder](https://yukicoder.me/problems/no/931)

## 参考文献・リンク

- [1] [整数論テクニック集 - kirika_compのブログ](https://kirika-comp.hatenablog.com/entry/2018/03/12/210446)
- [2] [[2206.14193] Computation of the least primitive root](https://arxiv.org/abs/2206.14193)
- [3] [原始根のアルゴリズム – 37zigenのHP](https://37zigen.com/primitive-root/)
