---
title: Cartesian tree
documentation_of: ./cartesian_tree.hpp
---

比較可能な要素の列に対し，Cartesian tree を計算．各要素の親となる要素の番号を持った長さ $N$ の `std::vector<int>` を返す．$O(N)$．デフォルトでは小さい要素がより根に近くなるが，テンプレート引数に `std::greater<T>` を与えてやることで逆転可能．

## 使用方法

```cpp
std::vector<int> A(N);
for (auto &x : Ainv) x = -x;
auto ret = cartesian_tree(A);
auto ret2 = cartesian_tree<int, std::greater<int>>(Ainv);
```

## 問題例

- [Library Checker: Cartesian Tree](https://judge.yosupo.jp/problem/cartesian_tree)
- [Codeforces Round #745 (Div. 1) D. Subsequence](https://codeforces.com/contest/1580/problem/D)
