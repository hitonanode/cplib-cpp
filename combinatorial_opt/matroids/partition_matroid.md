---
title: Partition matroid （分割マトロイド）
documentation_of: ./partition_matroid.hpp
---

$e = 0, \dots, M - 1$ からなる $M$ 要素の集合 $E$ の分割 $E$ = $E_1 \cup \dots \cup E_K \, (E_i \cap E_j = \varnothing (i \neq j))$と，分割された各部分集合に対する上限要素数 $R_k \ge 0 \, (k = 0, \dots, K - 1)$ によって定められるマトロイド：

$\displaystyle
\mathcal{I} = \{ I \subset E \mid |I \cup E_k| \le R_k \, (k = 0, \dots, K - 1) \}.
$

## 使用例

```cpp
vector<vector<int>> grp; // 登場しない要素があってもよい（それらは制約なしとして扱われる）
grp.push_back({0, 2, 5});
grp.push_back({1, 3});
vector<int> lim{2, 1};
PartitionMatroid M(6, grp, lim);

assert(M.size() == 6);
vector<bool> I(6);
I[0] = I[1] = I[2] = 1;
M.set(I);
assert((M.circuit(5) == vector<int>{0, 2, 5}));
```
