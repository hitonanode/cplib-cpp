---
title: Relaxed multiplication / relaxed convolution （オンライン畳み込み）
documentation_of: ./relaxed_multiplication.hpp
---

## 解いてくれる問題

FFT 可能な数列 $f = (f\_0, f\_1, \ldots, f\_{n - 1})$ と $g = (g\_0, g\_1, \ldots, g\_{n - 1})$ を畳み込む． $f$ および $g$ の第 $i$ 項までを求めた時点で $h = f * g$ の第 $i$ 項までが取得可能．「オンライン FFT」とよく呼ばれるもの．計算量は $O(n (\log n)^2)$．

## 文献・リンク集

- [オンライン畳み込み - Qiita](https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c)
- [Relaxed Convolution(Online FFT)によるexp/inv/log/sqrt/pow 【備忘録】 - hotmanの備忘録とライブラリ置き場](https://hotman78.hatenablog.com/entry/2023/01/04/173507)
