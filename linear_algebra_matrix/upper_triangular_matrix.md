---
title: Upper triangular matrix （定数次元上三角行列）
documentation_of: ./upper_triangular_matrix.hpp
---

一定次元の上三角行列を表す構造体の実装．現時点では、特に $3 \times 3$ 上三角行列

$\displaystyle
\begin{pmatrix}
a_{00} & a_{01} & a_{02} \\
0      & a_{11} & a_{12} \\
0      & 0      & a_{22}
\end{pmatrix}
$

が実装されている．乗算（行列積），単項マイナス，加算，大小比較が定義されている．乗算の実装を毎回手で行わなくて済み，また一般次元の行列を使いまわすより高速に動作する．

## 使用方法

```cpp
using mint = atcoder::modint998244353;

UpperTriangular3d<mint> A{
    .a00 = 1,
    .a01 = 2,
    .a02 = 3,
    .a11 = 4,
    .a12 = 5,
    .a22 = 6,
};

UpperTriangular3d<mint> B{
    .a00 = 7,
    .a01 = 8,
    .a02 = 9,
    .a11 = 10,
    .a12 = 11,
    .a22 = 12,
};

auto C = A * B;
auto D = A + B;
auto E = -A;
```

## 問題例

- [No.3530 「」 - yukicoder](https://yukicoder.me/problems/no/3530)
