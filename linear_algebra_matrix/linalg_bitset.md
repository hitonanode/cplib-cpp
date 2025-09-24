---
title: Linear algebra on $\mathbb{F}_{2}$ using std::bitset (std::bitset を使用した $\mathbb{F}_{2}$ 線形代数)
documentation_of: ./linalg_bitset.hpp
---

`std::bitset<>` を使用した $\mathbb{F}_{2}$ 用線形代数演算．64 倍程度の定数倍高速化が見込まれる．

## 使用方法

### 線形方程式系

```cpp
int W;
vector<bitset<Wmax>> A;
vector<bool> b;

// Solve Ax = b (x: F_2^W)
auto [feasible, x0, freedoms] = f2_system_of_linear_equations(A, b, W);

// Calc determinant (or check whether A is regular)
int det = f2_determinant(mat);
```

## 問題例

- [AOJ 2624: Graph Automata Player](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624)
- [No.1421 国勢調査 (Hard) - yukicoder](https://yukicoder.me/problems/no/1421)
- [AtCoder Beginner Contest 276 Ex - Construct a Matrix](https://atcoder.jp/contests/abc276/tasks/abc276_h) $2000 \times 8000$ 行列の線型方程式を解く．
- [Library Checker: Determinant of Matrix (Mod 2)](https://judge.yosupo.jp/problem/matrix_det_mod_2)
