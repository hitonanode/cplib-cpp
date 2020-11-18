---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: graph/test/strongly_connected_components_bitset.test.cpp
    title: graph/test/strongly_connected_components_bitset.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://codeforces.com/contest/1268/submission/68125495>
  bundledCode: "#line 2 \"graph/strongly_connected_components_bitset.hpp\"\n#include\
    \ <bitset>\n#include <vector>\n\n// CUT begin\n// Directed graph library to find\
    \ strongly connected components \uFF08\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\
    \uFF09\n// 0-indexed directed graph\n// - using std::bitset\n// - Fast for dense\
    \ graphs\n// Complexity: O(V^2/64)\n// Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>\n\
    template<int VMAX>\nstruct DirectedGraphSCC64 {\n    int V;\n    const std::vector<std::bitset<VMAX>>\
    \ &e, &einv;\n    std::vector<int> vs, cmp;\n    std::bitset<VMAX> unvisited;\n\
    \    int scc_num;\n    void _dfs(int now) {\n        unvisited.reset(now);\n \
    \       while (true) {\n            int nxt = (unvisited & e[now])._Find_first();\n\
    \            if (nxt >= V) break;\n            _dfs(nxt);\n        }\n       \
    \ vs.push_back(now);\n    }\n    void _rdfs(int now, int k) {\n        unvisited.reset(now);\n\
    \        cmp[now] = k;\n        while (true) {\n            int nxt = (unvisited\
    \ & einv[now])._Find_first();\n            if (nxt >= V) break;\n            _rdfs(nxt,\
    \ k);\n        }\n    }\n    // Detect strongly connected components and return\
    \ # of them.\n    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)\n\
    \    DirectedGraphSCC64(const std::vector<std::bitset<VMAX>> &edge, const std::vector<std::bitset<VMAX>>\
    \ &edge_inv)\n        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()),\
    \ scc_num(0)\n    {\n        unvisited.set();\n        for (int i = 0; i < V;\
    \ i++) if (unvisited[i]) _dfs(i);\n        unvisited.set();\n        for (int\
    \ i = (int)vs.size() - 1; i >= 0; i--) if (unvisited[vs[i]]) {\n            _rdfs(vs[i],\
    \ scc_num++);\n        }\n    }\n};\n"
  code: "#pragma once\n#include <bitset>\n#include <vector>\n\n// CUT begin\n// Directed\
    \ graph library to find strongly connected components \uFF08\u5F37\u9023\u7D50\
    \u6210\u5206\u5206\u89E3\uFF09\n// 0-indexed directed graph\n// - using std::bitset\n\
    // - Fast for dense graphs\n// Complexity: O(V^2/64)\n// Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>\n\
    template<int VMAX>\nstruct DirectedGraphSCC64 {\n    int V;\n    const std::vector<std::bitset<VMAX>>\
    \ &e, &einv;\n    std::vector<int> vs, cmp;\n    std::bitset<VMAX> unvisited;\n\
    \    int scc_num;\n    void _dfs(int now) {\n        unvisited.reset(now);\n \
    \       while (true) {\n            int nxt = (unvisited & e[now])._Find_first();\n\
    \            if (nxt >= V) break;\n            _dfs(nxt);\n        }\n       \
    \ vs.push_back(now);\n    }\n    void _rdfs(int now, int k) {\n        unvisited.reset(now);\n\
    \        cmp[now] = k;\n        while (true) {\n            int nxt = (unvisited\
    \ & einv[now])._Find_first();\n            if (nxt >= V) break;\n            _rdfs(nxt,\
    \ k);\n        }\n    }\n    // Detect strongly connected components and return\
    \ # of them.\n    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)\n\
    \    DirectedGraphSCC64(const std::vector<std::bitset<VMAX>> &edge, const std::vector<std::bitset<VMAX>>\
    \ &edge_inv)\n        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()),\
    \ scc_num(0)\n    {\n        unvisited.set();\n        for (int i = 0; i < V;\
    \ i++) if (unvisited[i]) _dfs(i);\n        unvisited.set();\n        for (int\
    \ i = (int)vs.size() - 1; i >= 0; i--) if (unvisited[vs[i]]) {\n            _rdfs(vs[i],\
    \ scc_num++);\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/strongly_connected_components_bitset.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:40:57+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - graph/test/strongly_connected_components_bitset.test.cpp
documentation_of: graph/strongly_connected_components_bitset.hpp
layout: document
redirect_from:
- /library/graph/strongly_connected_components_bitset.hpp
- /library/graph/strongly_connected_components_bitset.hpp.html
title: graph/strongly_connected_components_bitset.hpp
---
