---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/incremental_bridge_connectivity.hpp
    title: graph/incremental_bridge_connectivity.hpp
  - icon: ':heavy_check_mark:'
    path: unionfind/unionfind.hpp
    title: unionfind/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_edge_connected_components
    links:
    - https://judge.yosupo.jp/problem/two_edge_connected_components
  bundledCode: "#line 2 \"unionfind/unionfind.hpp\"\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// UnionFind Tree (0-indexed),\
    \ based on size of each disjoint set\nstruct UnionFind {\n    std::vector<int>\
    \ par, cou;\n    UnionFind(int N = 0) : par(N), cou(N, 1) { iota(par.begin(),\
    \ par.end(), 0); }\n    int find(int x) { return (par[x] == x) ? x : (par[x] =\
    \ find(par[x])); }\n    bool unite(int x, int y) {\n        x = find(x), y = find(y);\n\
    \        if (x == y) return false;\n        if (cou[x] < cou[y]) std::swap(x,\
    \ y);\n        par[y] = x, cou[x] += cou[y];\n        return true;\n    }\n  \
    \  int count(int x) { return cou[find(x)]; }\n    bool same(int x, int y) { return\
    \ find(x) == find(y); }\n};\n#line 3 \"graph/incremental_bridge_connectivity.hpp\"\
    \n#include <cassert>\n#line 5 \"graph/incremental_bridge_connectivity.hpp\"\n\
    #include <unordered_set>\n#line 7 \"graph/incremental_bridge_connectivity.hpp\"\
    \n\n// CUT begin\n// Incremental Bridge-Connectivity\n// two-edge-connected components\n\
    // Reference: <https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity>\n\
    //            <https://ei1333.github.io/library/graph/connected-components/incremental-bridge-connectivity.cpp>\n\
    struct IncrementalBridgeConnectivity {\n    int V;\n    int nb_bridge;\n    UnionFind\
    \ con, bicon;\n    std::vector<int> bbf;\n\n    int _bicon_par(int x) {\n    \
    \    return bbf[x] == -1 ? -1 : bicon.find(bbf[x]);\n    }\n    int _lca(int x,\
    \ int y) {\n        std::unordered_set<int> us;\n        while (true) {\n    \
    \        if (x != -1) {\n                if (!us.insert(x).second) {\n       \
    \             return x;\n                }\n                x = _bicon_par(x);\n\
    \            }\n            std::swap(x, y);\n        }\n    }\n    void _compress(int\
    \ now, int lca) {\n        while (bicon.find(now) != bicon.find(lca)) {\n    \
    \        int nxt = _bicon_par(now);\n            bbf[now] = bbf[lca], bicon.unite(now,\
    \ lca), now = nxt, nb_bridge--;\n        }\n    }\n\n    IncrementalBridgeConnectivity(int\
    \ v = 0) : V(v), nb_bridge(0), con(v), bicon(v), bbf(v, -1) {}\n\n    void add_edge(int\
    \ u, int v) {\n        assert(u >= 0 and u < V);\n        assert(v >= 0 and v\
    \ < V);\n        u = bicon.find(u), v = bicon.find(v);\n        if (con.find(u)\
    \ == con.find(v)) {\n            int lca = _lca(u, v);\n            _compress(u,\
    \ lca), _compress(v, lca);\n        } else {\n            if (con.count(u) > con.count(v))\
    \ std::swap(u, v);\n            for (int now = u, pre = v; now != -1;) {\n   \
    \             int nxt = _bicon_par(now);\n                bbf[now] = pre, pre\
    \ = now, now = nxt;\n            }\n            con.unite(u, v), nb_bridge++;\n\
    \        }\n    }\n    int count_bridge() const {\n        return nb_bridge;\n\
    \    }\n    bool two_edge_connected(int x, int y) {\n        return bicon.same(x,\
    \ y);\n    }\n    int find(int x) {\n        return bicon.find(x);\n    }\n};\n\
    #line 2 \"graph/test/incremental-bridge-connectivity.test.cpp\"\n#include <algorithm>\n\
    #include <iostream>\n#line 5 \"graph/test/incremental-bridge-connectivity.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int V, E;\n    cin >> V >> E;\n    IncrementalBridgeConnectivity graph(V);\n\
    \    while (E--) {\n        int s, t;\n        cin >> s >> t;\n        graph.add_edge(s,\
    \ t);\n    }\n\n    vector<vector<int>> ret(V);\n    for (int i = 0; i < V; i++)\
    \ { ret[graph.find(i)].emplace_back(i); }\n    int K = count_if(ret.begin(), ret.end(),\
    \ [](const vector<int>& v) { return v.size() > 0; });\n    cout << K << '\\n';\n\
    \    for (const auto& vec : ret) {\n        if (vec.size()) {\n            cout\
    \ << vec.size();\n            for (auto x : vec) { cout << ' ' << x; }\n     \
    \       cout << '\\n';\n        }\n    }\n}\n"
  code: "#include \"graph/incremental_bridge_connectivity.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int V, E;\n    cin >> V >> E;\n    IncrementalBridgeConnectivity graph(V);\n\
    \    while (E--) {\n        int s, t;\n        cin >> s >> t;\n        graph.add_edge(s,\
    \ t);\n    }\n\n    vector<vector<int>> ret(V);\n    for (int i = 0; i < V; i++)\
    \ { ret[graph.find(i)].emplace_back(i); }\n    int K = count_if(ret.begin(), ret.end(),\
    \ [](const vector<int>& v) { return v.size() > 0; });\n    cout << K << '\\n';\n\
    \    for (const auto& vec : ret) {\n        if (vec.size()) {\n            cout\
    \ << vec.size();\n            for (auto x : vec) { cout << ' ' << x; }\n     \
    \       cout << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - graph/incremental_bridge_connectivity.hpp
  - unionfind/unionfind.hpp
  isVerificationFile: true
  path: graph/test/incremental-bridge-connectivity.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/incremental-bridge-connectivity.test.cpp
layout: document
redirect_from:
- /verify/graph/test/incremental-bridge-connectivity.test.cpp
- /verify/graph/test/incremental-bridge-connectivity.test.cpp.html
title: graph/test/incremental-bridge-connectivity.test.cpp
---
