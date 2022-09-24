---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/rmq_sparse_table.hpp
    title: sparse_table/rmq_sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/lca_rmq.test.cpp
    title: tree/test/lca_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Range Minimum Query\
    \ for static sequence by sparse table\n// Complexity: $O(N \\log N)$ for precalculation,\
    \ $O(1)$ per query\ntemplate <typename T> struct StaticRMQ {\n    inline T func(const\
    \ T &l, const T &r) const noexcept { return std::min<T>(l, r); }\n    int N, lgN;\n\
    \    T defaultT;\n    std::vector<std::vector<T>> data;\n    std::vector<int>\
    \ lgx_table;\n    StaticRMQ() = default;\n    StaticRMQ(const std::vector<T> &sequence,\
    \ T defaultT)\n        : N(sequence.size()), defaultT(defaultT) {\n        lgx_table.resize(N\
    \ + 1);\n        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >>\
    \ 1] + 1;\n        lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N,\
    \ defaultT));\n        data[0] = sequence;\n        for (int d = 1; d < lgN; d++)\
    \ {\n            for (int i = 0; i + (1 << d) <= N; i++) {\n                data[d][i]\
    \ = func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);\n            }\n  \
    \      }\n    }\n    T get(int l, int r) const { // [l, r), 0-indexed\n      \
    \  assert(l >= 0 and r <= N);\n        if (l >= r) return defaultT;\n        int\
    \ d = lgx_table[r - l];\n        return func(data[d][l], data[d][r - (1 << d)]);\n\
    \    }\n};\n#line 5 \"tree/lca_rmq.hpp\"\n#include <utility>\n#line 7 \"tree/lca_rmq.hpp\"\
    \n\nstruct TreeLCA {\n    const int N;\n    std::vector<std::vector<int>> to;\n\
    \    int root;\n    TreeLCA(int V = 0) : N(V), to(V), root(-1) {}\n\n    void\
    \ add_edge(int u, int v) {\n        assert(0 <= u and u < N);\n        assert(0\
    \ <= v and v < N);\n        assert(u != v);\n        to[u].push_back(v);\n   \
    \     to[v].push_back(u);\n    }\n\n    using P = std::pair<int, int>;\n    std::vector<int>\
    \ subtree_begin;\n    std::vector<P> vis_order;\n    std::vector<int> depth;\n\
    \    void _build_dfs(int now, int prv, int dnow) {\n        subtree_begin[now]\
    \ = vis_order.size();\n        vis_order.emplace_back(dnow, now);\n        depth[now]\
    \ = dnow;\n        for (auto &&nxt : to[now]) {\n            if (nxt != prv) {\n\
    \                _build_dfs(nxt, now, dnow + 1);\n                vis_order.emplace_back(dnow,\
    \ now);\n            }\n        }\n    }\n\n    StaticRMQ<P> rmq;\n    void build(int\
    \ root_) {\n        assert(root_ >= 0 and root_ < N);\n        if (root == root_)\
    \ return;\n        root = root_;\n        subtree_begin.assign(N, 0);\n      \
    \  vis_order.clear();\n        vis_order.reserve(N * 2);\n        depth.assign(N,\
    \ 0);\n        _build_dfs(root, -1, 0);\n        rmq = {vis_order, P{N, -1}};\n\
    \    }\n\n    bool built() const noexcept { return root >= 0; }\n\n    int lca(int\
    \ u, int v) const {\n        assert(0 <= u and u < N);\n        assert(0 <= v\
    \ and v < N);\n        assert(built());\n\n        int a = subtree_begin[u], b\
    \ = subtree_begin[v];\n        if (a > b) std::swap(a, b);\n        return rmq.get(a,\
    \ b + 1).second;\n    };\n\n    int path_length(int u, int v) const { return depth[u]\
    \ + depth[v] - depth[lca(u, v)] * 2; }\n};\n"
  code: "#pragma once\n#include \"../sparse_table/rmq_sparse_table.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\nstruct\
    \ TreeLCA {\n    const int N;\n    std::vector<std::vector<int>> to;\n    int\
    \ root;\n    TreeLCA(int V = 0) : N(V), to(V), root(-1) {}\n\n    void add_edge(int\
    \ u, int v) {\n        assert(0 <= u and u < N);\n        assert(0 <= v and v\
    \ < N);\n        assert(u != v);\n        to[u].push_back(v);\n        to[v].push_back(u);\n\
    \    }\n\n    using P = std::pair<int, int>;\n    std::vector<int> subtree_begin;\n\
    \    std::vector<P> vis_order;\n    std::vector<int> depth;\n    void _build_dfs(int\
    \ now, int prv, int dnow) {\n        subtree_begin[now] = vis_order.size();\n\
    \        vis_order.emplace_back(dnow, now);\n        depth[now] = dnow;\n    \
    \    for (auto &&nxt : to[now]) {\n            if (nxt != prv) {\n           \
    \     _build_dfs(nxt, now, dnow + 1);\n                vis_order.emplace_back(dnow,\
    \ now);\n            }\n        }\n    }\n\n    StaticRMQ<P> rmq;\n    void build(int\
    \ root_) {\n        assert(root_ >= 0 and root_ < N);\n        if (root == root_)\
    \ return;\n        root = root_;\n        subtree_begin.assign(N, 0);\n      \
    \  vis_order.clear();\n        vis_order.reserve(N * 2);\n        depth.assign(N,\
    \ 0);\n        _build_dfs(root, -1, 0);\n        rmq = {vis_order, P{N, -1}};\n\
    \    }\n\n    bool built() const noexcept { return root >= 0; }\n\n    int lca(int\
    \ u, int v) const {\n        assert(0 <= u and u < N);\n        assert(0 <= v\
    \ and v < N);\n        assert(built());\n\n        int a = subtree_begin[u], b\
    \ = subtree_begin[v];\n        if (a > b) std::swap(a, b);\n        return rmq.get(a,\
    \ b + 1).second;\n    };\n\n    int path_length(int u, int v) const { return depth[u]\
    \ + depth[v] - depth[lca(u, v)] * 2; }\n};\n"
  dependsOn:
  - sparse_table/rmq_sparse_table.hpp
  isVerificationFile: false
  path: tree/lca_rmq.hpp
  requiredBy: []
  timestamp: '2022-09-24 13:25:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/lca_rmq.test.cpp
documentation_of: tree/lca_rmq.hpp
layout: document
title: "Lowest common ancestor of tree based on sparse table \uFF08\u30AF\u30A8\u30EA\
  \ $O(1)$ \u306E\u6700\u5C0F\u5171\u901A\u7956\u5148\uFF09"
---

根を固定した木に対する 2 頂点の最小共通祖先，および 2 頂点間の距離の計算．前処理 $O(N \log N)$, 空間 $O(N \log N)$, クエリ $O(1)$．

## 使用方法

`add_edge(int u, int v)` を $N - 1$ 回行って木を構築した後，`build(int root)` によって根を指定する．

```cpp
TreeLCA tree(N);
for (int e = 0; e < N - 1; e++) {
    int u, v;
    cin >> u >> v;
    tree.add_edge(u, v);
}

tree.build(0);

cout << tree.lca(a, b) << '\n'; // (a, b) の最長共通祖先
cout << tree.path_length(a, b) << '\n'; // 2 頂点 a, b の距離
```

## 問題例

- [Library Checker: Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
