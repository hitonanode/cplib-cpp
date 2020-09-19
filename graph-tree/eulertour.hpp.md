---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: graph-tree/test/vertex-add-subtree-sum.test.cpp
    title: graph-tree/test/vertex-add-subtree-sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"graph-tree/eulertour.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Preorder Euler Tour\n// \uFF08\u884C\u304D\u304C\
    \u3051\u9806\uFF0C\u90E8\u5206\u6728\u306E\u9802\u70B9\u30AF\u30A8\u30EA\u7B49\
    \u306B\u6709\u7528\uFF09\nstruct PreorderEulerTour\n{\n    int V; // # of vertices\
    \ of tree\n    int root;\n    std::vector<std::vector<int>> edges;\n    std::vector<int>\
    \ subtree_begin, subtree_end;\n    std::vector<int> vis_order;\n\n    void _build_dfs(int\
    \ now, int prv) {\n        subtree_begin[now] = vis_order.size();\n        vis_order.push_back(now);\n\
    \        for (auto nxt : edges[now]) if (nxt != prv) _build_dfs(nxt, now);\n \
    \       subtree_end[now] = vis_order.size();\n    }\n    PreorderEulerTour() =\
    \ default;\n    PreorderEulerTour(const std::vector<std::vector<int>> &to, int\
    \ root) : V(to.size()), root(root), edges(to)\n    {\n        assert(root >= 0\
    \ and root < V);\n        subtree_begin.resize(V);\n        subtree_end.resize(V);\n\
    \        _build_dfs(root, -1);\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Preorder\
    \ Euler Tour\n// \uFF08\u884C\u304D\u304C\u3051\u9806\uFF0C\u90E8\u5206\u6728\u306E\
    \u9802\u70B9\u30AF\u30A8\u30EA\u7B49\u306B\u6709\u7528\uFF09\nstruct PreorderEulerTour\n\
    {\n    int V; // # of vertices of tree\n    int root;\n    std::vector<std::vector<int>>\
    \ edges;\n    std::vector<int> subtree_begin, subtree_end;\n    std::vector<int>\
    \ vis_order;\n\n    void _build_dfs(int now, int prv) {\n        subtree_begin[now]\
    \ = vis_order.size();\n        vis_order.push_back(now);\n        for (auto nxt\
    \ : edges[now]) if (nxt != prv) _build_dfs(nxt, now);\n        subtree_end[now]\
    \ = vis_order.size();\n    }\n    PreorderEulerTour() = default;\n    PreorderEulerTour(const\
    \ std::vector<std::vector<int>> &to, int root) : V(to.size()), root(root), edges(to)\n\
    \    {\n        assert(root >= 0 and root < V);\n        subtree_begin.resize(V);\n\
    \        subtree_end.resize(V);\n        _build_dfs(root, -1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph-tree/eulertour.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - graph-tree/test/vertex-add-subtree-sum.test.cpp
documentation_of: graph-tree/eulertour.hpp
layout: document
redirect_from:
- /library/graph-tree/eulertour.hpp
- /library/graph-tree/eulertour.hpp.html
title: graph-tree/eulertour.hpp
---
