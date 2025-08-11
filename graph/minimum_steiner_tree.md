---
title: Minimum Steiner tree （最小シュタイナー木）
documentation_of: ./minimum_steiner_tree.hpp
---

各辺重みが非負の $n$ 頂点 $m$ 辺無向グラフとその $k$ 個の頂点からなるターミナル集合を入力として，最小シュタイナー木を求める．
現在は計算量 $O(3^k n + 2^k m \log m)$ の関数 `MinimumSteinerTreeDP()` と $O(m \log m + 2^{n - k} m \alpha (n))$ の関数 `MinimumSteinerTreeDense()` が実装されている．
`MinimumSteinerTree()` 関数を使うと，適切なものを選んで使ってくれる．

## 使用方法

```cpp
int N;
vector<tuple<int, int, long long>> edges;
vector<int> terminals;

const auto [total_cost, used_edge_ids] = MinimumSteinerTree(N, edges, terminals);
```

## 問題例

- [Library Checker - Minimum Steiner Tree](https://judge.yosupo.jp/problem/minimum_steiner_tree)
- [No.114 遠い未来 - yukicoder](https://yukicoder.me/problems/no/114)
