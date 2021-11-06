---
title: Binary indexed tree / Fenwick tree （BIT・フェニック木）
documentation_of: ./binary_indexed_tree.hpp
---

BIT の実装．テンプレート引数として渡すクラス $S$ は加算について結合法則を満たし，また逆元が取れる必要がある．

- `BIT<S> bit(n)` : コンストラクタ．長さ $n$ の数列 $A$ を $A\_0 = \dots = A\_{n - 1} = S()$ で初期化．計算量は $O(n)$．
- `sum(l, r)` : $A\_l + \dots + A\_{r - 1}$ を計算．計算量は $O(\log n)$．
- `sum(k)` : `sum(0, k)` と同じ．計算量は $O(\log n)$．
- `add(x, v)`: $A\_x$ に $v$ を加算．計算量は $O(\log n)$．

## Example

```cpp
BIT<int> bit(N);
bit.add(2, 5);

bit.sum(1, 6);
```

## 問題例

- [AOJ DSL_2_B: Range Sum Query (RSQ)](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B)
