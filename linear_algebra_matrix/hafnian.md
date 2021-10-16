---
title: Hafnian （行列のハフニアン，無向グラフの完全マッチングの数え上げ）
documentation_of: ./hafnian.hpp
---

全ての対角成分がゼロの $N \times N$ 対称行列 $\mathbf{M}$ のハフニアン（完全マッチングの個数）を $O(N^2 2^N)$ で求める．

## 問題例

- [Library Checker: Hafnian of Matrix](https://judge.yosupo.jp/problem/hafnian_of_matrix) $N \le 38$, $\bmod 998244353$ で 2.5 秒程度．

## References

- [1] A. Björklund, "Counting Perfect Matchings as Fast as Ryser,
  Proc. of 23rd ACM-SIAM symposium on Discrete Algorithms, pp.914–921, 2012.

