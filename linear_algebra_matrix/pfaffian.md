---
title: Pfaffian of skew-symmetric matrix （歪対称行列のパフィアン）
documentation_of: ./pfaffian.hpp
---

`T` を加減乗除が可能な型（体）として， `std::vector<std::vector<T>>` の形で与えられる $n \times n$ 歪対称正方行列の Pfaffian を $O(n^3)$ で計算する．

## 使用方法

```cpp
int N;
using mint = atcoder::modint998244353;
vector A(N, vector<mint>(N));

const mint res = Pfaffian(A);
```

## 問題例

- [Library Checker: Pfaffian of Matrix](https://judge.yosupo.jp/problem/pfaffian_of_matrix)

## 参考文献・リンク

- [Submission #278787](https://judge.yosupo.jp/submission/278787)
  - Nachia さんの実装．歪対称性を保ったまま
