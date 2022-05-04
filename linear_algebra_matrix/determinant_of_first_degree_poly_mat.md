---
title: Determinant of $M_0 + M_1 x$ （各要素が高々 $1$ 次の行列の行列式）
documentation_of: ./determinant_of_first_degree_poly_mat.hpp
---

$\mathbb{F}_p$ 上の $n$ 次正方行列 $M_0, M_1$ に対して，$\det (M_0 + M_1 x)$ を $O(n^3)$ で求める決定的アルゴリズム．

## 使用方法

```cpp
vector<vector<mint>> M0, M1;
vector<mint> det = determinant_of_first_degree_poly_mat(M0, M1);
```

## 問題例

- [No.1907 DETERMINATION - yukicoder](https://yukicoder.me/problems/no/1907)

## References

- [Things I don't know - Codeforces](https://codeforces.com/blog/entry/92248?#comment-818786)
- [解説 No.1907 DETERMINATION - yukicoder](https://yukicoder.me/problems/no/1907/editorial)
