---
title: Mo's algorithm （区間クエリに関する平方分割テクニック）
documentation_of: ./mos_algorithm.hpp
---

## 使用方法

```cpp
vector<Result> ret(Q); // 答えを格納する領域
MosAlgorithm mo;
for (int q = 0; q < Q; q++) {
    mo.add_range(L[q], R[q]);
}
auto add = [&](int i) -> void { /* 区間を延ばして i 番目の要素を追加したときの処理 */ };
auto remove = [&](int i) -> void { /* 区間を縮めて i 番目の要素を削除したときの処理 */ };
auto solve = [&](int q) -> void { ret[q] = f(q); /* q 個目のクエリを解く処理 */ };

mo.run(add, remove, solve);

for (auto x : ret) cout << x << '\n';
```

## 最適なバケット幅設定

列の長さを $N$, クエリを $Q$ 個とする．バケット幅を $W$ とするとバケット個数は $B = N / W$ 程度．

このとき，Add/Remove 演算は $BN + QW = \frac{N^2}{W} + QW$ 回程度生じる．これを最小にするのは $W = N / \sqrt{Q}$ と設定したときで，全体計算量は $O(N \sqrt{Q} \cdot C_\mathrm{Add/Erase} + Q \cdot C_\mathrm{query})$ となる．

## 問題例

- [Codeforces Round #221 (Div. 1) D. Tree and Queries](https://codeforces.com/contest/375/submission/114665433)
  - 部分木クエリにも使用可能．

## Links

- [Codeforces blog のコメント](https://codeforces.com/blog/entry/20032?#comment-248430) : "Mo's algorithm" の起源に関する議論．
