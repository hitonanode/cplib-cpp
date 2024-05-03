---
title: $\mathbb{F}_{2}$ linear space ($\mathbb{F}_{2}$ 線形空間)
documentation_of: ./f2_linear_space.hpp
---

$\mathbb{F}_{2}$ 線形空間に関する各種演算．

## 使用方法

`A` の元で張られる線形空間と `B` の元で張られる線形空間の共通部分の基底を一つ求める関数方法．

```cpp
int n, m;
vector<int> A(n), B(m);

vector<int> C = f2_intersection(A, B);
```

## 問題例

- [Library Checker: Intersection of F_2 vector spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces)
