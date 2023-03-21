---
title: Semi-relaxed multiplication / semi-relaxed convolution （片方先読み可能な場合のオンライン畳み込み）
documentation_of: ./semirelaxed_multiplication.hpp
---

## 解いてくれる問題

FFT 可能な数列 $a = (a\_0, a\_1, \ldots, a\_{n - 1})$ と $f = (f\_0, f\_1, \ldots, f\_{m - 1})$ を畳み込む． $a$ は全て既知であることを要請． $f$ の第 $i$ 項までを求めた時点で $g = a * f$ の第 $i$ 項までが取得可能．計算量は $O((n + m) (\log \min(n, m))^2)$．

## 文献・リンク集

- [オンライン畳み込み - Qiita](https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c)
