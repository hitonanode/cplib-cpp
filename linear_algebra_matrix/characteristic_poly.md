---
title: Characteristic polynomial （行列の特性多項式）
documentation_of: ./characteristic_poly.hpp
---

Upper Hessenberg な体上の $n$ 次正方行列 $M$ の特性多項式 $p_M(x) = \det (xI - M)$ を $O(n^3)$ で求める決定的アルゴリズム．

## やっていること

入力として与えられた (upper) Hessenberg な正方行列 $M$ に対して $M$ の首座小行列の特性多項式を再帰的に求めていく（La Budde's method, [1]）．

## References

- [1] R. Rehman, I. C. Ipsen, "La Budde's Method for Computing Characteristic Polynomials," 2011.
