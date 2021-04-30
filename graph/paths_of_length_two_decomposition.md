---
title: 無向グラフの長さ 2 のパスへの分解
documentation_of: ./paths_of_length_two_decomposition.hpp
---

## 使用方法

```cpp
PathsOfLength2Decomposition graph(N);
for (int m = 0; m < M; m++) {
    int a, b;
    cin >> a >> b;
    graph.add_edge(a - 1, b - 1);
}
vector<pair<int, int>> pairs = graph.run();
```

## 背景

- まず全域森を構成する．
- 全域森に使用しなかった辺のみに着目し，各頂点の次数が 1 以下になるまで長さ 2 のパスを作れるだけ作る．
- 最後に，全域森を DFS し，葉の方から各頂点で辺を使い切る．
- この構成より，各連結成分について辺の本数が偶数なら全ての辺を使い切ることが可能（奇数なら DFS の根で辺が一つ余る）．

## 問題例

- [AtCoder Grand Contest 035 B - Even Degrees](https://atcoder.jp/contests/agc035/tasks/agc035_b)
  - 連結なので，辺の本数が偶数なら解ける．
- [Educational Codeforces Round 108 (Rated for Div. 2) E. Off by One](https://codeforces.com/contest/1519/problem/E)
