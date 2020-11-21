---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph-tree/lowest_common_ancestor.hpp
    title: graph-tree/lowest_common_ancestor.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 2 \"graph-tree/lowest_common_ancestor.hpp\"\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// lowest common ancestor (LCA) class for undirected\
    \ weighted tree\n// \u7121\u5411\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5\u306E\
    \u6700\u5C0F\u5171\u901A\u7956\u5148\n// <https://yukicoder.me/submissions/392383>\n\
    struct UndirectedWeightedTree {\n    using T = long long; // Arbitrary data structure\
    \ (operator+, operator- must be defined)\n    int INVALID = -1;\n    int V, lgV;\n\
    \    int E;\n    int root;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ adj; // (nxt_vertex, edge_id)\n    // vector<pint> edge; // edges[edge_id] =\
    \ (vertex_id, vertex_id)\n    std::vector<T> weight;     // w[edge_id]\n    std::vector<int>\
    \ par;      // parent_vertex_id[vertex_id]\n    std::vector<int> depth;    //\
    \ depth_from_root[vertex_id]\n    std::vector<T> acc_weight; // w_sum_from_root[vertex_id]\n\
    \n    void _fix_root_dfs(int now, int prv, int prv_edge_id) {\n        par[now]\
    \ = prv;\n        if (prv_edge_id != INVALID) acc_weight[now] = acc_weight[prv]\
    \ + weight[prv_edge_id];\n        for (auto nxt : adj[now])\n            if (nxt.first\
    \ != prv) {\n                depth[nxt.first] = depth[now] + 1;\n            \
    \    _fix_root_dfs(nxt.first, now, nxt.second);\n            }\n    }\n\n    UndirectedWeightedTree()\
    \ = default;\n    UndirectedWeightedTree(int N) : V(N), E(0), adj(N) {\n     \
    \   lgV = 1;\n        while (1 << lgV < V) lgV++;\n    }\n\n    void add_edge(int\
    \ u, int v, T w) {\n        adj[u].emplace_back(v, E);\n        adj[v].emplace_back(u,\
    \ E);\n        // edge.emplace_back(u, v);\n        weight.emplace_back(w);\n\
    \        E++;\n    }\n\n    void fix_root(int r) {\n        root = r;\n      \
    \  par.resize(V);\n        depth.resize(V);\n        depth[r] = 0;\n        acc_weight.resize(V);\n\
    \        acc_weight[r] = 0;\n        _fix_root_dfs(root, INVALID, INVALID);\n\
    \    }\n\n    std::vector<std::vector<int>> doubling;\n    void doubling_precalc()\
    \ {\n        doubling.assign(lgV, std::vector<int>(V));\n        doubling[0] =\
    \ par;\n        for (int d = 0; d < lgV - 1; d++)\n            for (int i = 0;\
    \ i < V; i++) {\n                if (doubling[d][i] == INVALID)\n            \
    \        doubling[d + 1][i] = INVALID;\n                else\n               \
    \     doubling[d + 1][i] = doubling[d][doubling[d][i]];\n            }\n    }\n\
    \n    int kth_parent(int x, int k) {\n        if (depth[x] < k) return INVALID;\n\
    \        for (int d = 0; d < lgV; d++) {\n            if (x == INVALID) return\
    \ INVALID;\n            if (k & (1 << d)) x = doubling[d][x];\n        }\n   \
    \     return x;\n    }\n\n    int lowest_common_ancestor(int u, int v) {\n   \
    \     if (depth[u] > depth[v]) std::swap(u, v);\n\n        v = kth_parent(v, depth[v]\
    \ - depth[u]);\n        if (u == v) return u;\n        for (int d = lgV - 1; d\
    \ >= 0; d--) {\n            if (doubling[d][u] != doubling[d][v]) u = doubling[d][u],\
    \ v = doubling[d][v];\n        }\n        return par[u];\n    }\n\n    T path_length(int\
    \ u, int v) {\n        // Not distance, but the sum of weights\n        int r\
    \ = lowest_common_ancestor(u, v);\n        return (acc_weight[u] - acc_weight[r])\
    \ + (acc_weight[v] - acc_weight[r]);\n    }\n};\n#line 2 \"graph-tree/test/lca.test.cpp\"\
    \n#include <iostream>\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \nusing namespace std;\n\nint main() {\n    int N, Q, p, u, v;\n    cin >> N >>\
    \ Q;\n    UndirectedWeightedTree graph(N);\n    for (int i = 1; i <= N - 1; i++)\
    \ {\n        cin >> p;\n        graph.add_edge(i, p, 1);\n    }\n    graph.fix_root(0);\n\
    \    graph.doubling_precalc();\n\n    for (int i = 0; i < Q; i++) {\n        cin\
    \ >> u >> v;\n        cout << graph.lowest_common_ancestor(u, v) << endl;\n  \
    \  }\n}\n"
  code: "#include \"../lowest_common_ancestor.hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/lca\"\nusing namespace std;\n\nint\
    \ main() {\n    int N, Q, p, u, v;\n    cin >> N >> Q;\n    UndirectedWeightedTree\
    \ graph(N);\n    for (int i = 1; i <= N - 1; i++) {\n        cin >> p;\n     \
    \   graph.add_edge(i, p, 1);\n    }\n    graph.fix_root(0);\n    graph.doubling_precalc();\n\
    \n    for (int i = 0; i < Q; i++) {\n        cin >> u >> v;\n        cout << graph.lowest_common_ancestor(u,\
    \ v) << endl;\n    }\n}\n"
  dependsOn:
  - graph-tree/lowest_common_ancestor.hpp
  isVerificationFile: true
  path: graph-tree/test/lca.test.cpp
  requiredBy: []
  timestamp: '2020-11-21 18:37:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph-tree/test/lca.test.cpp
layout: document
redirect_from:
- /verify/graph-tree/test/lca.test.cpp
- /verify/graph-tree/test/lca.test.cpp.html
title: graph-tree/test/lca.test.cpp
---
