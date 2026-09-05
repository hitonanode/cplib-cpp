---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: graph/test/strongly_connected_components_bitset.test.cpp
    title: graph/test/strongly_connected_components_bitset.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://codeforces.com/contest/1268/submission/68125495>
  bundledCode: "#line 2 \"graph/strongly_connected_components_bitset.hpp\"\n#include\
    \ <bitset>\n#include <iostream>\n#include <vector>\n\n// CUT begin\n// Directed\
    \ graph library to find strongly connected components \uFF08\u5F37\u9023\u7D50\
    \u6210\u5206\u5206\u89E3\uFF09\n// 0-indexed directed graph\n// - using std::bitset\n\
    // - Fast for dense graphs\n// Complexity: O(V^2/64)\n// Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>\n\
    template <int VMAX> struct DirectedGraphSCC64 {\n    static int find_first(const\
    \ std::bitset<VMAX> &bits) {\n#ifdef __GLIBCXX__\n        return bits._Find_first();\n\
    #else\n        for (int i = 0; i < VMAX; i++)\n            if (bits[i]) return\
    \ i;\n        return VMAX;\n#endif\n    }\n    int V;\n    const std::vector<std::bitset<VMAX>>\
    \ &e, &einv;\n    std::vector<int> vs, cmp;\n    std::bitset<VMAX> unvisited;\n\
    \    int scc_num;\n    std::vector<int> _st;\n\n    void _dfs(int head) {\n  \
    \      _st = {head};\n        unvisited.reset(head);\n        while (!_st.empty())\
    \ {\n            int now = _st.back();\n            unvisited.reset(now);\n  \
    \          int nxt = find_first(unvisited & e[now]);\n            if (nxt < V)\
    \ {\n                unvisited.reset(nxt);\n                _st.push_back(nxt);\n\
    \            } else {\n                _st.pop_back();\n                vs.push_back(now);\n\
    \            }\n        }\n    }\n\n    void _rdfs(int head, int k) {\n      \
    \  _st = {head};\n        unvisited.reset(head);\n        while (!_st.empty())\
    \ {\n            int now = _st.back();\n            _st.pop_back();\n        \
    \    cmp[now] = k;\n            while (true) {\n                int nxt = find_first(unvisited\
    \ & einv[now]);\n                if (nxt >= V) break;\n                _st.push_back(nxt);\n\
    \                unvisited.reset(nxt);\n            }\n        }\n    }\n\n  \
    \  // Detect strongly connected components and return # of them.\n    // Also,\
    \ assign each vertex `v` the scc id `cmp[v]` (0-indexed)\n    DirectedGraphSCC64(const\
    \ std::vector<std::bitset<VMAX>> &edge,\n                       const std::vector<std::bitset<VMAX>>\
    \ &edge_inv)\n        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()),\
    \ scc_num(0) {\n        unvisited.set();\n        for (int i = 0; i < V; i++)\n\
    \            if (unvisited[i]) _dfs(i);\n        unvisited.set();\n        for\
    \ (int i = (int)vs.size() - 1; i >= 0; i--)\n            if (unvisited[vs[i]])\
    \ { _rdfs(vs[i], scc_num++); }\n    }\n};\n"
  code: "#pragma once\n#include <bitset>\n#include <iostream>\n#include <vector>\n\
    \n// CUT begin\n// Directed graph library to find strongly connected components\
    \ \uFF08\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\uFF09\n// 0-indexed directed\
    \ graph\n// - using std::bitset\n// - Fast for dense graphs\n// Complexity: O(V^2/64)\n\
    // Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>\n\
    template <int VMAX> struct DirectedGraphSCC64 {\n    static int find_first(const\
    \ std::bitset<VMAX> &bits) {\n#ifdef __GLIBCXX__\n        return bits._Find_first();\n\
    #else\n        for (int i = 0; i < VMAX; i++)\n            if (bits[i]) return\
    \ i;\n        return VMAX;\n#endif\n    }\n    int V;\n    const std::vector<std::bitset<VMAX>>\
    \ &e, &einv;\n    std::vector<int> vs, cmp;\n    std::bitset<VMAX> unvisited;\n\
    \    int scc_num;\n    std::vector<int> _st;\n\n    void _dfs(int head) {\n  \
    \      _st = {head};\n        unvisited.reset(head);\n        while (!_st.empty())\
    \ {\n            int now = _st.back();\n            unvisited.reset(now);\n  \
    \          int nxt = find_first(unvisited & e[now]);\n            if (nxt < V)\
    \ {\n                unvisited.reset(nxt);\n                _st.push_back(nxt);\n\
    \            } else {\n                _st.pop_back();\n                vs.push_back(now);\n\
    \            }\n        }\n    }\n\n    void _rdfs(int head, int k) {\n      \
    \  _st = {head};\n        unvisited.reset(head);\n        while (!_st.empty())\
    \ {\n            int now = _st.back();\n            _st.pop_back();\n        \
    \    cmp[now] = k;\n            while (true) {\n                int nxt = find_first(unvisited\
    \ & einv[now]);\n                if (nxt >= V) break;\n                _st.push_back(nxt);\n\
    \                unvisited.reset(nxt);\n            }\n        }\n    }\n\n  \
    \  // Detect strongly connected components and return # of them.\n    // Also,\
    \ assign each vertex `v` the scc id `cmp[v]` (0-indexed)\n    DirectedGraphSCC64(const\
    \ std::vector<std::bitset<VMAX>> &edge,\n                       const std::vector<std::bitset<VMAX>>\
    \ &edge_inv)\n        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()),\
    \ scc_num(0) {\n        unvisited.set();\n        for (int i = 0; i < V; i++)\n\
    \            if (unvisited[i]) _dfs(i);\n        unvisited.set();\n        for\
    \ (int i = (int)vs.size() - 1; i >= 0; i--)\n            if (unvisited[vs[i]])\
    \ { _rdfs(vs[i], scc_num++); }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/strongly_connected_components_bitset.hpp
  requiredBy: []
  timestamp: '2026-09-05 15:19:09+09:00'
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
