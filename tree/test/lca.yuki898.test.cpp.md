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
    PROBLEM: https://yukicoder.me/problems/no/898
    links:
    - https://yukicoder.me/problems/no/898
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
    \        _doubling_precalc();\n    }\n\n    int kth_parent(int x, int k) {\n \
    \       if (depth[x] < k) return INVALID;\n        for (int d = 0; d < lgV; d++)\
    \ {\n            if (x == INVALID) return INVALID;\n            if (k & (1 <<\
    \ d)) x = doubling[d][x];\n        }\n        return x;\n    }\n\n    int lowest_common_ancestor(int\
    \ u, int v) {\n        if (depth[u] > depth[v]) std::swap(u, v);\n\n        v\
    \ = kth_parent(v, depth[v] - depth[u]);\n        if (u == v) return u;\n     \
    \   for (int d = lgV - 1; d >= 0; d--) {\n            if (doubling[d][u] != doubling[d][v])\
    \ u = doubling[d][u], v = doubling[d][v];\n        }\n        return par[u];\n\
    \    }\n\n    T path_length(int u, int v) {\n        // Not distance, but the\
    \ sum of weights\n        int r = lowest_common_ancestor(u, v);\n        return\
    \ (acc_weight[u] - acc_weight[r]) + (acc_weight[v] - acc_weight[r]);\n    }\n\
    };\n#line 2 \"tree/test/lca.yuki898.test.cpp\"\n#include <iostream>\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/898\"\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N;\n    cin\
    \ >> N;\n    UndirectedWeightedTree<long long> g(N);\n    for (int i = 1; i <=\
    \ N - 1; i++) {\n        int u, v, w;\n        cin >> u >> v >> w;\n        g.add_edge(u,\
    \ v, w);\n    }\n    g.fix_root(0);\n\n    int Q;\n    cin >> Q;\n\n    while\
    \ (Q--) {\n        int x, y, z;\n        cin >> x >> y >> z;\n        int xy =\
    \ g.lowest_common_ancestor(x, y);\n        int xyz = g.lowest_common_ancestor(xy,\
    \ z);\n        if (xy != xyz) {\n            cout << g.path_length(xy, z) + g.path_length(x,\
    \ y) << '\\n';\n        } else {\n            int v = g.lowest_common_ancestor(x,\
    \ z) + g.lowest_common_ancestor(y, z) - xy;\n            cout << g.path_length(x,\
    \ y) + g.path_length(z, v) << '\\n';\n        }\n    }\n}\n"
  code: "#include \"../lowest_common_ancestor.hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/898\"\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N;\n\
    \    cin >> N;\n    UndirectedWeightedTree<long long> g(N);\n    for (int i =\
    \ 1; i <= N - 1; i++) {\n        int u, v, w;\n        cin >> u >> v >> w;\n \
    \       g.add_edge(u, v, w);\n    }\n    g.fix_root(0);\n\n    int Q;\n    cin\
    \ >> Q;\n\n    while (Q--) {\n        int x, y, z;\n        cin >> x >> y >> z;\n\
    \        int xy = g.lowest_common_ancestor(x, y);\n        int xyz = g.lowest_common_ancestor(xy,\
    \ z);\n        if (xy != xyz) {\n            cout << g.path_length(xy, z) + g.path_length(x,\
    \ y) << '\\n';\n        } else {\n            int v = g.lowest_common_ancestor(x,\
    \ z) + g.lowest_common_ancestor(y, z) - xy;\n            cout << g.path_length(x,\
    \ y) + g.path_length(z, v) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - tree/lowest_common_ancestor.hpp
  isVerificationFile: true
  path: tree/test/lca.yuki898.test.cpp
  requiredBy: []
  timestamp: '2021-07-30 23:28:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/lca.yuki898.test.cpp
layout: document
redirect_from:
- /verify/tree/test/lca.yuki898.test.cpp
- /verify/tree/test/lca.yuki898.test.cpp.html
title: tree/test/lca.yuki898.test.cpp
---
