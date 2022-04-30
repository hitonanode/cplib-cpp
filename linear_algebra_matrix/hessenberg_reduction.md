---
title: Hessenberg reduction of matrix
documentation_of: ./hessenberg_reduction.hpp
---

体上の $n$ 次正方行列の Upper Hessenberg reduction を $O(n^3)$ で行う．

## やっていること

(Upper) Hessenberg reduction とは，行列に相似変換を施すことでその対角成分より2つ以上左下側の成分を全てゼロにするというもので，このような変換は特に Householder 変換の組合せによって可能である．相似変換で特性多項式は不変なため，本ライブラリでは特性多項式の導出などに応用されている．
