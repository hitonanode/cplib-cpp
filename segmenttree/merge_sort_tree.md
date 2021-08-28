---
title: Merge sort tree （静的な列の部分列に含まれる閾値以下の要素数クエリ）
documentation_of: ./merge_sort_tree.hpp
---

静的な列 $[A_0, \dots, A_{N - 1}]$ について，以下のクエリを処理：


- `int cntLess(int l, int r, T query)` : $[l, r)$ に含まれる `query` 未満の要素数を計算．
- `int cntLesseq(int l, int r, T query)` : $[l, r)$ に含まれる `query` 以下の要素数を計算．
- `int cntMore(int l, int r, T query)` : $[l, r)$ に含まれる `query` より大きい要素数を計算．
- `int cntMoreeq(int l, int r, T query)` : $[l, r)$ に含まれる `query` 以上の要素数を計算．

計算量は構築 $O(N \log N)$，クエリ $O(N (\log N)^2)$，空間 $O(N \log N)$．

## Example

```cpp
vector<long long> ys;
merge_sort_tree<long long> tree(ys);
int ret = tree.cntLess(l, r, ylim) << '\n';
```

## 問題例

- [Educational Codeforces Round 80 (Rated for Div. 2) E. Messenger Simulator](https://codeforces.com/contest/1288/problem/E)
- [Japanese Alumni Group Summer Camp 2018 Day 3 Prefix Suffix Search](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907)
