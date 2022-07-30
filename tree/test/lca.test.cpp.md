---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/lowest_common_ancestor.hpp
    title: "Lowest common ancestor \uFF08\u6700\u5C0F\u5171\u901A\u7956\u5148\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
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
    \  return kth_parent(t, dsl + dtl - k);\n        }\n    }\n};\n#line 2 \"tree/test/lca.test.cpp\"\
    \n#include <iostream>\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, Q, p, u, v;\n    cin >> N >> Q;\n    UndirectedWeightedTree<int> graph(N);\n\
    \    for (int i = 1; i <= N - 1; i++) {\n        cin >> p;\n        graph.add_edge(i,\
    \ p, 1);\n    }\n    graph.fix_root(0);\n\n    for (int i = 0; i < Q; i++) {\n\
    \        cin >> u >> v;\n        cout << graph.lowest_common_ancestor(u, v) <<\
    \ endl;\n    }\n}\n"
  code: "#include \"../lowest_common_ancestor.hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/lca\"\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q,\
    \ p, u, v;\n    cin >> N >> Q;\n    UndirectedWeightedTree<int> graph(N);\n  \
    \  for (int i = 1; i <= N - 1; i++) {\n        cin >> p;\n        graph.add_edge(i,\
    \ p, 1);\n    }\n    graph.fix_root(0);\n\n    for (int i = 0; i < Q; i++) {\n\
    \        cin >> u >> v;\n        cout << graph.lowest_common_ancestor(u, v) <<\
    \ endl;\n    }\n}\n"
  dependsOn:
  - tree/lowest_common_ancestor.hpp
  isVerificationFile: true
  path: tree/test/lca.test.cpp
  requiredBy: []
  timestamp: '2022-07-31 01:04:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/lca.test.cpp
layout: document
redirect_from:
- /verify/tree/test/lca.test.cpp
- /verify/tree/test/lca.test.cpp.html
title: tree/test/lca.test.cpp
---
