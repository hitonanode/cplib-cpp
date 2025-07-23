---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/monge_shortest_path.yuki705.test.cpp
    title: other_algorithms/test/monge_shortest_path.yuki705.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.hatenablog.com/entry/2022/01/13/001217
    - https://noshi91.hatenablog.com/entry/2023/02/18/005856
  bundledCode: "#line 2 \"other_algorithms/monge_shortest_path.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// Shortest path of Monge-weighted graph\n// Variant of LARSCH\
    \ Algorithm: https://noshi91.hatenablog.com/entry/2023/02/18/005856\n// Complexity:\
    \ O(n log n)\n//\n// Given a directed graph with n vertices and weighted edges\n\
    // (w(i, j) = cost_callback(i, j) (i < j)),\n// this class calculates the shortest\
    \ path from vertex 0 to all other vertices.\ntemplate <class Cost> struct monge_shortest_path\
    \ {\n    std::vector<Cost> dist; // dist[i] = shortest distance from 0 to i\n\
    \    std::vector<int> amin;  // amin[i] = previous vertex of i in the shortest\
    \ path\n\n    template <class F> void _check(int i, int k, F cost_callback) {\n\
    \        if (i <= k) return;\n        if (Cost c = dist[k] + cost_callback(k,\
    \ i); c < dist[i]) dist[i] = c, amin[i] = k;\n    }\n\n    template <class F>\
    \ void _rec_solve(int l, int r, F cost_callback) {\n        if (r - l == 1) return;\n\
    \n        const int m = (l + r) / 2;\n        for (int k = amin[l]; k <= amin[r];\
    \ ++k) _check(m, k, cost_callback);\n\n        _rec_solve(l, m, cost_callback);\n\
    \        for (int k = l + 1; k <= m; ++k) _check(r, k, cost_callback);\n     \
    \   _rec_solve(m, r, cost_callback);\n    }\n\n    template <class F> Cost solve(int\
    \ n, F cost_callback) {\n        assert(n > 0);\n        dist.resize(n);\n   \
    \     amin.assign(n, 0);\n\n        dist[0] = Cost();\n        for (int i = 1;\
    \ i < n; ++i) dist[i] = cost_callback(0, i);\n\n        _rec_solve(0, n - 1, cost_callback);\n\
    \n        return dist.back();\n    }\n\n    template <class F> int num_edges()\
    \ const {\n        int ret = 0;\n        for (int c = (int)amin.size() - 1; c\
    \ >= 0; c = amin[c]) ++ret;\n        return ret;\n    }\n};\n\n// Find shortest\
    \ path length from 0 to n - 1 with k edges, min_edges <= k <= max_edges\n// https://noshi91.hatenablog.com/entry/2022/01/13/001217\n\
    template <class Cost, class F>\nCost monge_shortest_path_with_specified_edges(int\
    \ n, int min_edges, int max_edges,\n                                         \
    \     Cost max_abs_cost, F cost_callback) {\n\n    assert(1 <= n);\n    assert(0\
    \ <= min_edges);\n    assert(min_edges <= max_edges);\n    assert(max_edges <=\
    \ n - 1);\n\n    monge_shortest_path<Cost> msp;\n\n    auto eval = [&](Cost p)\
    \ -> Cost {\n        msp.solve(n, [&](int i, int j) { return cost_callback(i,\
    \ j) - p; });\n        return -msp.dist.back() - p * (p < 0 ? max_edges : min_edges);\n\
    \    };\n\n    Cost lo = -max_abs_cost * 3, hi = max_abs_cost * 3;\n\n    while\
    \ (lo + 1 < hi) {\n        Cost p = (lo + hi) / 2, f = eval(p), df = eval(p +\
    \ 1) - f;\n        if (df == Cost()) {\n            return -f;\n        } else\
    \ {\n            (df < Cost() ? lo : hi) = p;\n        }\n    }\n\n    Cost flo\
    \ = eval(lo), fhi = eval(hi);\n\n    return flo < fhi ? -flo : -fhi;\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Shortest path of\
    \ Monge-weighted graph\n// Variant of LARSCH Algorithm: https://noshi91.hatenablog.com/entry/2023/02/18/005856\n\
    // Complexity: O(n log n)\n//\n// Given a directed graph with n vertices and weighted\
    \ edges\n// (w(i, j) = cost_callback(i, j) (i < j)),\n// this class calculates\
    \ the shortest path from vertex 0 to all other vertices.\ntemplate <class Cost>\
    \ struct monge_shortest_path {\n    std::vector<Cost> dist; // dist[i] = shortest\
    \ distance from 0 to i\n    std::vector<int> amin;  // amin[i] = previous vertex\
    \ of i in the shortest path\n\n    template <class F> void _check(int i, int k,\
    \ F cost_callback) {\n        if (i <= k) return;\n        if (Cost c = dist[k]\
    \ + cost_callback(k, i); c < dist[i]) dist[i] = c, amin[i] = k;\n    }\n\n   \
    \ template <class F> void _rec_solve(int l, int r, F cost_callback) {\n      \
    \  if (r - l == 1) return;\n\n        const int m = (l + r) / 2;\n        for\
    \ (int k = amin[l]; k <= amin[r]; ++k) _check(m, k, cost_callback);\n\n      \
    \  _rec_solve(l, m, cost_callback);\n        for (int k = l + 1; k <= m; ++k)\
    \ _check(r, k, cost_callback);\n        _rec_solve(m, r, cost_callback);\n   \
    \ }\n\n    template <class F> Cost solve(int n, F cost_callback) {\n        assert(n\
    \ > 0);\n        dist.resize(n);\n        amin.assign(n, 0);\n\n        dist[0]\
    \ = Cost();\n        for (int i = 1; i < n; ++i) dist[i] = cost_callback(0, i);\n\
    \n        _rec_solve(0, n - 1, cost_callback);\n\n        return dist.back();\n\
    \    }\n\n    template <class F> int num_edges() const {\n        int ret = 0;\n\
    \        for (int c = (int)amin.size() - 1; c >= 0; c = amin[c]) ++ret;\n    \
    \    return ret;\n    }\n};\n\n// Find shortest path length from 0 to n - 1 with\
    \ k edges, min_edges <= k <= max_edges\n// https://noshi91.hatenablog.com/entry/2022/01/13/001217\n\
    template <class Cost, class F>\nCost monge_shortest_path_with_specified_edges(int\
    \ n, int min_edges, int max_edges,\n                                         \
    \     Cost max_abs_cost, F cost_callback) {\n\n    assert(1 <= n);\n    assert(0\
    \ <= min_edges);\n    assert(min_edges <= max_edges);\n    assert(max_edges <=\
    \ n - 1);\n\n    monge_shortest_path<Cost> msp;\n\n    auto eval = [&](Cost p)\
    \ -> Cost {\n        msp.solve(n, [&](int i, int j) { return cost_callback(i,\
    \ j) - p; });\n        return -msp.dist.back() - p * (p < 0 ? max_edges : min_edges);\n\
    \    };\n\n    Cost lo = -max_abs_cost * 3, hi = max_abs_cost * 3;\n\n    while\
    \ (lo + 1 < hi) {\n        Cost p = (lo + hi) / 2, f = eval(p), df = eval(p +\
    \ 1) - f;\n        if (df == Cost()) {\n            return -f;\n        } else\
    \ {\n            (df < Cost() ? lo : hi) = p;\n        }\n    }\n\n    Cost flo\
    \ = eval(lo), fhi = eval(hi);\n\n    return flo < fhi ? -flo : -fhi;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/monge_shortest_path.hpp
  requiredBy: []
  timestamp: '2024-10-06 15:03:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/monge_shortest_path.yuki705.test.cpp
documentation_of: other_algorithms/monge_shortest_path.hpp
layout: document
title: Shortest path of DAG with Monge weights
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
