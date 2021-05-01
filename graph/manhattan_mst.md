---
title: Manhattan MST （二次元平面上の頂点たちのマンハッタン距離による最小全域木構成）
documentation_of: ./manhattan_mst.hpp
---

$N$ 個の頂点の $x$, $y$ 座標を与えると，候補となる $O(N)$ 本の辺を（重み，端点 1，端点 2）の形式で列挙する．時間計算量 $O(N \log N)$．

## 使用方法

```cpp
vector<int> xs(N), ys(N);
for (int i = 0; i < N; i++) cin >> xs[i] >> ys[i];

UnionFind uf(N);
long long mst_weight = 0;
vector<pair<int, int>> mst_edges;
for (auto [w, i, j] : manhattan_mst(xs, ys)) {
    if (uf.unite(i, j)) {
        mst_weight += w;
        mst_edges.emplace_back(i, j);
    }
}
```

## 問題例

- [Library Checker - Manhattan MST](https://judge.yosupo.jp/problem/manhattanmst)
- [CodeChef - Hackerman](https://www.codechef.com/problems/HKRMAN)
