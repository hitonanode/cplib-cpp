---
title: Enumerate cliques （グラフのクリーク全列挙）
documentation_of: ./enumerate_cliques.hpp
---

与えられた $n$ 頂点 $m$ 辺の無向グラフのクリーク（完全グラフとなる部分グラフ）を全列挙する．計算量は $O(2^{\sqrt{2m}} n)$．

## 使用方法

```cpp
int n;  // Num. of vertices
enumerate_cliques ec(n);

for (auto [u, v] : edges) {
    ec.add_bi_edge(u, v);  // 0 <= u, v < n
}

vector<vector<int>> cliques;

auto op = [&](const vector<int> &clique) {
    // `clique` is NOT guaranteed to be sorted
    cliques.push_back(clique);
};

ec.run(op);  // op() runs over all cliques
```

## 問題例

- [Library Checker: Enumerate Cliques](https://judge.yosupo.jp/problem/enumerate_cliques)
- [AOJ 2306: Rabbit Party](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2306)
