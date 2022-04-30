---
title: Linear matroid parity (unweighted) （線形マトロイドパリティ）
documentation_of: ./linear_matroid_parity.hpp
---

（重みなし）線形マトロイドパリティ問題とは，$M$ 個のベクトルの組 $(\mathbf{b}_i, \mathbf{c}_i)$ $(i = 1, \dots, M)$ が与えられたとき，${1, \dots, M}$ の部分集合 $S$ であって $2 |S|$ 個のベクトル ${\\{b_i\\}}_{i \in S} + {\\{ c_i \\}}_{i \in S}$ が線形独立であるようなもののうち要素数最大のものを求める問題．

本コードは，線形マトロイドパリティ問題を $O(r^2 (r + m))$ で解く乱択アルゴリズムである．試行一回あたりの失敗確率は $O(r / p)$ （$p$ は有限体の位数）である．

## 使用方法

```cpp
vector<pair<mint, mint>> vector_pairs;

vector<bool> sol_vec = linear_matroid_parity(vector_pairs);

int answer_size = linear_matroid_parity_size(vector_pairs); // Return size only, a bit faster
```

## 問題例

- [No.1773 Love Triangle - yukicoder](https://yukicoder.me/problems/no/1773)

## 文献・リンク集

- [1] H. Y. Cheung, L. C. Lau, K. M. Leung,
      "Algebraic Algorithms for Linear Matroid Parity Problems,"
      ACM Transactions on Algorithms, 10(3), 1-26, 2014.
- [Matroid parity problem - Wikipedia](https://en.wikipedia.org/wiki/Matroid_parity_problem)
