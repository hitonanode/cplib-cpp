---
title: Chromatic number of undirected graph （無向グラフの彩色数）
documentation_of: ./chromatic_number.hpp
---

$N$ 頂点のグラフの彩色数（隣り合う頂点を異なる色で全頂点を塗るときに要する最小の色の数）を求める確率的アルゴリズム．時間計算量 $O(N 2^N)$．

コード中の $f(S)$ は頂点集合 $S$ に関する部分グラフ上の（空集合を含む）独立集合の個数．各要素を $k$ 乗した $f^k(S)$ にメビウス変換を施したもの $h(S)$ は，「集合 $S$ を $k$ 個の独立集合で被覆する方法の総数」となるので，全頂点に関するこの個数が非零になるまで $k$ を増やしていけばよい．本コードでは $\bmod p$ で計算を行うが，初めて非零になったときの組合せの個数がたまたま $p$ の倍数になったときに動作が失敗することに注意．

## 使用方法

```cpp
vector<int> to(N);
while (M--) {
    int u, v;
    cin >> u >> v;
    to[u] |= 1 << v;
    to[v] |= 1 << u;
}
cout << ChromaticNumber<ModIntRuntime>(to) << '\n';
```

## 問題例

- [Library Checker - Chromatic Number](https://judge.yosupo.jp/problem/chromatic_number)
- [AtCoder Beginner Contest 187 F - Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)
