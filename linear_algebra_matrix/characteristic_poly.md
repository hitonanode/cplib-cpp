---
title: Characteristic polynomial （行列の特性多項式）
documentation_of: ./characteristic_poly.hpp
---

体上の $n$ 次正方行列 $M$ の特性多項式 $p_M(x) = \det (xI - M)$ を $O(n^3)$ で求める決定的アルゴリズム．

## やっていること

入力として与えられた正方行列 $M$ に (upper) Hessenberg reduction を施した後，これに対して $M$ の首座小行列の特性多項式を再帰的に求めていく（La Budde's method, [1]）．(Upper) Hessenberg reduction とは，行列に相似変換を施すことでその対角成分より2つ以上左下側の成分を全てゼロにするというもので，このような変換は特に Householder 変換の組合せによって可能である（もちろん相似変換で特性多項式は不変）．

## References

- [1] R. Rehman, I. C. Ipsen, "La Budde's Method for Computing Characteristic Polynomials," 2011.
