---
title: Multivariate linear convolution （多変数線形畳み込み）
documentation_of: ./multivar_ntt.hpp
---

## 解いてくれる問題

[Library Checker: Multivariate Convolution](https://judge.yosupo.jp/problem/multivariate_convolution)

$\displaystyle
f(x_1, x_2, \dots, x_K), \ g(x_1, x_2, \dots, x_K)
$

に対して，

$\displaystyle
f \cdot g \bmod (x_1^{N_1} x_2^{N_2} \dots x_K^{N_K})
$

を計算（線形畳み込み，「はみ出し」分は無視）．

## アルゴリズム（要点）

[参考](https://rushcheyo.blog.uoj.ac/blog/6547)

- subset convolution と同様のアイデアを適用する．
- subset convolution は `popcount` に着目して要素ごとの格納する位置を決めたが，代わりに上のリンクにある $\chi$ 関数を使って決めてあげると万事うまくいく．
