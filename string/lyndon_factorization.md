---
title: Lyndon factorization （Lyndon 分解）
documentation_of: ./lyndon_factorization.hpp
---

文字列・数列などの比較可能なものの列に対して Lyndon 分解を行う．

## Lyndon 文字列

- $S$ が Lyndon 文字列であるとは，$S$ の（非空な）接尾辞の中で $S$ 自身が辞書順最小であること

## Lyndon 分解

- （定義）Lyndon 分解とは，文字列 $S$ の分割 $S = w_1 w_2 \dots w_M$ で，各 $w_i$ は Lyndon 文字列で，しかも $w_i$ たちが辞書順非増加であるもの．
- （一意性）Lyndon 分解は一意．
- （構成）$w_1$ は，$S$ の接頭辞で Lyndon であるような最長のもの．
