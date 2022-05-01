---
title: Hessenberg reduction of matrix
documentation_of: ./hessenberg_reduction.hpp
---

体上の $n$ 次正方行列の Upper Hessenberg reduction を $O(n^3)$ で行う．

## やっていること

(Upper) Hessenberg reduction とは，行列に相似変換を施すことでその対角成分より2つ以上左下側の成分を全てゼロにするというもので，このような変換は特に Householder 変換の組合せによって可能である．相似変換で特性多項式は不変なため，本ライブラリでは特性多項式の導出などに応用されている．

## 使用方法

`matrix<T>` に対して upper Hessenberg reduction を行う関数は以下のように使用する．
### `T` が逆元がとれるデータ構造の場合

```cpp
matrix<T> mat(N, N);
hessenberg_reduction(mat);
```

### `T` が逆元がとれないがユークリッドの互除法が可能なデータ構造の場合（例：合成数 modint）

```cpp
matrix<T> mat(N, N);
ring_hessenberg_reduction(mat);
```

## 問題例

- [Library Checker: Determinant of Matrix (arbitrary mod)](https://judge.yosupo.jp/problem/matrix_det_arbitrary_mod): 任意 mod のケースでも特性多項式が $O(n^3)$ で計算可能である．
