---
title: Frequency table of tree distance
documentation_of: ./frequency_table_of_tree_distance.hpp
---

各頂点 $i$ が畳み込み可能な可換環上の重み $w_i$ を持つような木について，

$\displaystyle
A[k] = \sum_{i < j: d(i, j) = k} w_i w_j
$

の値を $k = 0, \dots, N - 1$ について計算．木の重心分解を用いる．

## 使用方法

```cpp
vector<vector<int>> to(n);
vector<mint> weight(n);
vector<mint> ret1 = frequency_table_of_tree_distance(to).solve<mint, nttconv<mint>>(weight);
vector<long long> ret2 = frequency_table_of_tree_distance(to).solve<long long, fftconv>(std::vector<long long>(N, 1));
```

## 問題例

- [Library Checker: Frequency Table of Tree Distance](https://judge.yosupo.jp/problem/frequency_table_of_tree_distance)
