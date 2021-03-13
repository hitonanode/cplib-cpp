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

## 実装されている関数

### lyndon_factorization

```cpp
vector<pair<int, int>> ret = lyndon_factorization(s);
```

- 文字列など比較可能な要素の列 `s` を Lyndon 分解した際の，（先頭位置，長さ）の組の列を出力
- 計算量 $O(N)$

### longest_lyndon_prefixes

``` cpp
vector<int> ret = longest_lyndon_prefixes(s, rolling_hash_of_s);
```

- 各 suffix `s[i:N)` に関する最長な Lyndon prefix `s[i:i+len(i))` の長さ `len(i)` を格納した配列を出力
- 計算量 $O(N \log N)$
