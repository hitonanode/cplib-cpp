---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/jump_on_tree.test.cpp
    title: tree/test/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/lca.test.cpp
    title: tree/test/lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/lca.yuki898.test.cpp
    title: tree/test/lca.yuki898.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/lowest_common_ancestor.hpp\"\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// lowest common ancestor (LCA) for undirected\
    \ weighted tree\ntemplate <typename T> struct UndirectedWeightedTree {\n    int\
    \ INVALID = -1;\n    int V, lgV;\n    int E;\n    int root;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> adj; // (nxt_vertex, edge_id)\n    // vector<pint> edge; // edges[edge_id]\
    \ = (vertex_id, vertex_id)\n    std::vector<T> weight;     // w[edge_id]\n   \
    \ std::vector<int> par;      // parent_vertex_id[vertex_id]\n    std::vector<int>\
    \ depth;    // depth_from_root[vertex_id]\n    std::vector<T> acc_weight; // w_sum_from_root[vertex_id]\n\
    \n    void _fix_root_dfs(int now, int prv, int prv_edge_id) {\n        par[now]\
    \ = prv;\n        if (prv_edge_id != INVALID) acc_weight[now] = acc_weight[prv]\
    \ + weight[prv_edge_id];\n        for (auto nxt : adj[now])\n            if (nxt.first\
    \ != prv) {\n                depth[nxt.first] = depth[now] + 1;\n            \
    \    _fix_root_dfs(nxt.first, now, nxt.second);\n            }\n    }\n\n    UndirectedWeightedTree()\
    \ = default;\n    UndirectedWeightedTree(int N) : V(N), E(0), adj(N) {\n     \
    \   lgV = 1;\n        while (1 << lgV < V) lgV++;\n    }\n\n    void add_edge(int\
    \ u, int v, T w) {\n        adj[u].emplace_back(v, E);\n        adj[v].emplace_back(u,\
    \ E);\n        // edge.emplace_back(u, v);\n        weight.emplace_back(w);\n\
    \        E++;\n    }\n\n    std::vector<std::vector<int>> doubling;\n    void\
    \ _doubling_precalc() {\n        doubling.assign(lgV, std::vector<int>(V));\n\
    \        doubling[0] = par;\n        for (int d = 0; d < lgV - 1; d++)\n     \
    \       for (int i = 0; i < V; i++) {\n                if (doubling[d][i] == INVALID)\n\
    \                    doubling[d + 1][i] = INVALID;\n                else\n   \
    \                 doubling[d + 1][i] = doubling[d][doubling[d][i]];\n        \
    \    }\n    }\n\n    void fix_root(int r) {\n        root = r;\n        par.resize(V);\n\
    \        depth.resize(V);\n        depth[r] = 0;\n        acc_weight.resize(V);\n\
    \        acc_weight[r] = 0;\n        _fix_root_dfs(root, INVALID, INVALID);\n\
    \        _doubling_precalc();\n    }\n\n    int kth_parent(int x, int k) const\
    \ {\n        if (depth[x] < k) return INVALID;\n        for (int d = 0; d < lgV;\
    \ d++) {\n            if (x == INVALID) return INVALID;\n            if (k & (1\
    \ << d)) x = doubling[d][x];\n        }\n        return x;\n    }\n\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        if (depth[u] > depth[v]) std::swap(u, v);\n\n   \
    \     v = kth_parent(v, depth[v] - depth[u]);\n        if (u == v) return u;\n\
    \        for (int d = lgV - 1; d >= 0; d--) {\n            if (doubling[d][u]\
    \ != doubling[d][v]) u = doubling[d][u], v = doubling[d][v];\n        }\n    \
    \    return par[u];\n    }\n\n    T path_length(int u, int v) const {\n      \
    \  // Not distance, but the sum of weights\n        int r = lowest_common_ancestor(u,\
    \ v);\n        return (acc_weight[u] - acc_weight[r]) + (acc_weight[v] - acc_weight[r]);\n\
    \    }\n\n    int s_to_t_by_k_steps(int s, int t, int k) const {\n        int\
    \ l = lowest_common_ancestor(s, t);\n        int dsl = depth[s] - depth[l], dtl\
    \ = depth[t] - depth[l];\n        if (k > dsl + dtl) {\n            return INVALID;\n\
    \        } else if (k < dsl) {\n            return kth_parent(s, k);\n       \
    \ } else if (k == dsl) {\n            return l;\n        } else {\n          \
    \  return kth_parent(t, dsl + dtl - k);\n        }\n    }\n};\n"
  code: "#pragma once\n#include <utility>\n#include <vector>\n\n// CUT begin\n// lowest\
    \ common ancestor (LCA) for undirected weighted tree\ntemplate <typename T> struct\
    \ UndirectedWeightedTree {\n    int INVALID = -1;\n    int V, lgV;\n    int E;\n\
    \    int root;\n    std::vector<std::vector<std::pair<int, int>>> adj; // (nxt_vertex,\
    \ edge_id)\n    // vector<pint> edge; // edges[edge_id] = (vertex_id, vertex_id)\n\
    \    std::vector<T> weight;     // w[edge_id]\n    std::vector<int> par;     \
    \ // parent_vertex_id[vertex_id]\n    std::vector<int> depth;    // depth_from_root[vertex_id]\n\
    \    std::vector<T> acc_weight; // w_sum_from_root[vertex_id]\n\n    void _fix_root_dfs(int\
    \ now, int prv, int prv_edge_id) {\n        par[now] = prv;\n        if (prv_edge_id\
    \ != INVALID) acc_weight[now] = acc_weight[prv] + weight[prv_edge_id];\n     \
    \   for (auto nxt : adj[now])\n            if (nxt.first != prv) {\n         \
    \       depth[nxt.first] = depth[now] + 1;\n                _fix_root_dfs(nxt.first,\
    \ now, nxt.second);\n            }\n    }\n\n    UndirectedWeightedTree() = default;\n\
    \    UndirectedWeightedTree(int N) : V(N), E(0), adj(N) {\n        lgV = 1;\n\
    \        while (1 << lgV < V) lgV++;\n    }\n\n    void add_edge(int u, int v,\
    \ T w) {\n        adj[u].emplace_back(v, E);\n        adj[v].emplace_back(u, E);\n\
    \        // edge.emplace_back(u, v);\n        weight.emplace_back(w);\n      \
    \  E++;\n    }\n\n    std::vector<std::vector<int>> doubling;\n    void _doubling_precalc()\
    \ {\n        doubling.assign(lgV, std::vector<int>(V));\n        doubling[0] =\
    \ par;\n        for (int d = 0; d < lgV - 1; d++)\n            for (int i = 0;\
    \ i < V; i++) {\n                if (doubling[d][i] == INVALID)\n            \
    \        doubling[d + 1][i] = INVALID;\n                else\n               \
    \     doubling[d + 1][i] = doubling[d][doubling[d][i]];\n            }\n    }\n\
    \n    void fix_root(int r) {\n        root = r;\n        par.resize(V);\n    \
    \    depth.resize(V);\n        depth[r] = 0;\n        acc_weight.resize(V);\n\
    \        acc_weight[r] = 0;\n        _fix_root_dfs(root, INVALID, INVALID);\n\
    \        _doubling_precalc();\n    }\n\n    int kth_parent(int x, int k) const\
    \ {\n        if (depth[x] < k) return INVALID;\n        for (int d = 0; d < lgV;\
    \ d++) {\n            if (x == INVALID) return INVALID;\n            if (k & (1\
    \ << d)) x = doubling[d][x];\n        }\n        return x;\n    }\n\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        if (depth[u] > depth[v]) std::swap(u, v);\n\n   \
    \     v = kth_parent(v, depth[v] - depth[u]);\n        if (u == v) return u;\n\
    \        for (int d = lgV - 1; d >= 0; d--) {\n            if (doubling[d][u]\
    \ != doubling[d][v]) u = doubling[d][u], v = doubling[d][v];\n        }\n    \
    \    return par[u];\n    }\n\n    T path_length(int u, int v) const {\n      \
    \  // Not distance, but the sum of weights\n        int r = lowest_common_ancestor(u,\
    \ v);\n        return (acc_weight[u] - acc_weight[r]) + (acc_weight[v] - acc_weight[r]);\n\
    \    }\n\n    int s_to_t_by_k_steps(int s, int t, int k) const {\n        int\
    \ l = lowest_common_ancestor(s, t);\n        int dsl = depth[s] - depth[l], dtl\
    \ = depth[t] - depth[l];\n        if (k > dsl + dtl) {\n            return INVALID;\n\
    \        } else if (k < dsl) {\n            return kth_parent(s, k);\n       \
    \ } else if (k == dsl) {\n            return l;\n        } else {\n          \
    \  return kth_parent(t, dsl + dtl - k);\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/lowest_common_ancestor.hpp
  requiredBy: []
  timestamp: '2022-07-31 01:04:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/lca.test.cpp
  - tree/test/lca.yuki898.test.cpp
  - tree/test/jump_on_tree.test.cpp
documentation_of: tree/lowest_common_ancestor.hpp
layout: document
title: "Lowest common ancestor \uFF08\u6700\u5C0F\u5171\u901A\u7956\u5148\uFF09"
---

根を固定した木に対する 2 頂点の最小共通祖先，および 2 頂点間の距離，$k$ 番目の親の計算．前処理 $O(N \log N)$, クエリ $O(\log N)$．

## 使用方法

```cpp
UndirectedWeightedTree<long long> tree(N);
for (int e = 0; e < N - 1; e++) {
    int u, v, w;
    cin >> u >> v >> w;
    tree.add_edge(u, v, w);
}

tree.fix_root(0);

cout << tree.lowest_common_ancestor(a, b) << '\n'; // (a, b) の最長共通祖先
cout << tree.kth_parent(a, k) << '\n';  // 頂点 a の k 世代親
cout << tree.path_length(a, b) << '\n'; // 2 頂点 a, b の距離
```

## 問題例

- [Library Checker: Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
- [yukicoder No.898 tri-βutree](https://yukicoder.me/problems/no/898)
