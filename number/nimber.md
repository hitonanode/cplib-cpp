---
title: Nimber, Nim product （ニム数，$\mathbb{F}\_{2^{64}}$）
documentation_of: ./nimber.hpp
---

Nimber の実装．Nimber は非負整数として表されるが，特殊な和 $\oplus$ （実は bitwise xor 演算）と積 $\otimes$ が定義され，特に以下の性質を満たす：

- 交換・結合法則を満たす．
  - 特に，$2^{2^n}$ 未満のニム数全体はあるガロア体と同型．
- 種数 2．すなわち $x \oplus x = 0$ が常に成立．
- $x \otimes 2^{2^n} = x 2^{2^n} \, (x < 2^{2^n})$
- $2^{2^n} \otimes 2^{2^n} = (3/2) 2^{2^n}$

## Nim product の計算

本コードは，適切な前計算のもと 64 bit nimber 同士の乗算を効率的に行う．

本コードはまず以下の値を前計算する．

- $a \otimes b \, (0 \le a, b < 2^8)$
- $2^{8i} \otimes 2^{8j} \otimes k \, (0 \le i, j < 8, 0 \le k < 2^8)$

一般の $\mathbb{F}\_{2^{64}}$ 上の元 $x$, $y$ の積は，

$\displaystyle
x \otimes y = \left(\bigoplus\_{i=0}^7 2^{8i} \otimes x\_i \right) \otimes \left(\bigoplus\_{j=0}^7 2^{8j} \otimes y\_j \right)$

と 8 bit 毎に分解してこれを展開し，

$\displaystyle
\bigoplus\_{i, j} 2^{8i} \otimes 2^{8j} \otimes (x\_i \otimes y\_j)$

と整理することで，前計算の結果を用いて計算できる．

## 問題例

- [Library Checker: Nim Product](https://judge.yosupo.jp/problem/nim_product_64)

## 参考文献・リンク

- [Nimber - Wikipedia](https://en.wikipedia.org/wiki/Nimber)
- [Nim product - kyopro_friends’ diary](https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850)
