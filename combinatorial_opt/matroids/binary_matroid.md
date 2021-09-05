---
title: Binary matroid （二値マトロイド）
documentation_of: ./binary_matroid.hpp
---

$\mathbb{F}_2$ 上の $N$ 行 $M$ 列の行列 $A$ によって定義されるマトロイド．集合 $I \subset 2^M$ は，$A$ のうち $I$ に含まれる番号の列のみを抜き出した部分行列が列フルランクのとき，およびその時に限り独立集合である．

## 使用例

```cpp
bitset<5> v0, v1, v2, v3;
v0.set(0);
v1.set(1), v1.set(2);
v2.set(0), v2.set(1), v2.set(2);
v3.set(0), v3.set(2);
vector<bitset<5>> mat{v0, v1, v2, v3};
BinaryMatroid<5> M(mat);

vector<bool> I{0, 1, 1, 0};
M.set(I);
assert((M.circuit(0) == vector<int>{0, 1, 2}));
```
