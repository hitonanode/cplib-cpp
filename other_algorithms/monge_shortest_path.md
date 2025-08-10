---
title: Shortest path of DAG with Monge weights （Monge 重みの DAG の最短路長・辺数上下限指定可能）
documentation_of: ./monge_shortest_path.hpp
---

$n$ 頂点の DAG で辺重みが Monge となるようなものに対して最短路長を高速に求める． [1] で紹介されている簡易版 LARSCH Algorithm が実装されていて，計算量は $O(n \log n)$ ．

また，辺数が `min_edges` 以上 `max_edges` 以下であるようなものに限った最短路長を高速に求めることも可能（計算量にさらに重み二分探索の $\log$ がつく）．

## 使用方法

### 最短路長の計算

```cpp
auto f = [&](int s, int t) -> Cost {
    //
};

monge_shortest_path<Cost> msp;
Cost ret = msp.solve(n, f);
```

### 辺の本数の下限・上限を指定した最短路長の計算

```cpp
auto f = [&](int s, int t) -> Cost {
    //
};

int n;  // 頂点数
int l, r;  // 辺の本数が [l, r] の範囲に収まる最短路を見つけたい
Cost max_weight;  // f() が返す値の絶対値の上界

Cost ret = monge_shortest_path_with_specified_edges(n, l, r, max_weight, f);
```

## 問題例

- [No.705 ゴミ拾い Hard - yukicoder](https://yukicoder.me/problems/no/705)
- [AtCoder Beginner Contest 218 H - Red and Blue Lamps](https://atcoder.jp/contests/abc218/tasks/abc218_h)
- [東京海上日動プログラミングコンテスト2024（AtCoder Beginner Contest 355） G - Baseball](https://atcoder.jp/contests/abc355/tasks/abc355_g)
- [東北大学プログラミングコンテスト 2022 K - Lebesgue Integral](https://atcoder.jp/contests/tupc2022/tasks/tupc2022_k)
- [Educational Codeforces Round 181 (Rated for Div. 2) F. Timofey and Docker](https://codeforces.com/contest/2125/problem/F)

## Links

- [1] [簡易版 LARSCH Algorithm - noshi91のメモ](https://noshi91.hatenablog.com/entry/2023/02/18/005856)
- [2] [Aliens DP における二分探索の色々 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2023/11/20/052227#fn-c9578a2a)
