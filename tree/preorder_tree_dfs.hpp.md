---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/preorder_tree_dfs.test.cpp
    title: tree/test/preorder_tree_dfs.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"tree/preorder_tree_dfs.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// Preorder tree DFS\n// \u6728\u3092 DFS \u3057\u3066\u884C\u304D\
    \u304C\u3051\u9806\u306B\u9802\u70B9\u3092\u4FDD\u6301\u3059\u308B\uFF0E\n// \u6728\
    \u3092\u533A\u9593\u306B\u5909\u63DB\u3059\u308B\uFF0E\u90E8\u5206\u6728\u3092\
    \u69CB\u6210\u3059\u308B\u9802\u70B9\u306F\u9023\u7D9A\u3057\u3066\u73FE\u308C\
    \u308B\u306E\u3067\uFF0C\u90E8\u5206\u6728\u306E\u9802\u70B9\u30AF\u30A8\u30EA\
    \u7B49\u306B\u6709\u7528\uFF0E\n// heavy_light_decomposition \u304C\u4E0A\u4F4D\
    \u4E92\u63DB\nstruct preorder_tree_dfs {\n    int n; // # of vertices of tree\n\
    \    int root;\n    std::vector<int> subtree_begin, subtree_end;\n    std::vector<int>\
    \ vis_order;\n\n    void _build_dfs(int now, const std::vector<std::vector<int>>\
    \ &to) {\n        subtree_begin[now] = vis_order.size();\n        vis_order.push_back(now);\n\
    \        for (auto nxt : to[now]) {\n            if (subtree_begin[nxt] == -1)\
    \ _build_dfs(nxt, to);\n        }\n        subtree_end[now] = vis_order.size();\n\
    \    }\n\n    preorder_tree_dfs() = default;\n\n    preorder_tree_dfs(const std::vector<std::vector<int>>\
    \ &to, int root)\n        : n(to.size()), root(root), subtree_begin(n, -1), subtree_end(n,\
    \ -1) {\n        _build_dfs(root, to);\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Preorder tree DFS\n\
    // \u6728\u3092 DFS \u3057\u3066\u884C\u304D\u304C\u3051\u9806\u306B\u9802\u70B9\
    \u3092\u4FDD\u6301\u3059\u308B\uFF0E\n// \u6728\u3092\u533A\u9593\u306B\u5909\u63DB\
    \u3059\u308B\uFF0E\u90E8\u5206\u6728\u3092\u69CB\u6210\u3059\u308B\u9802\u70B9\
    \u306F\u9023\u7D9A\u3057\u3066\u73FE\u308C\u308B\u306E\u3067\uFF0C\u90E8\u5206\
    \u6728\u306E\u9802\u70B9\u30AF\u30A8\u30EA\u7B49\u306B\u6709\u7528\uFF0E\n// heavy_light_decomposition\
    \ \u304C\u4E0A\u4F4D\u4E92\u63DB\nstruct preorder_tree_dfs {\n    int n; // #\
    \ of vertices of tree\n    int root;\n    std::vector<int> subtree_begin, subtree_end;\n\
    \    std::vector<int> vis_order;\n\n    void _build_dfs(int now, const std::vector<std::vector<int>>\
    \ &to) {\n        subtree_begin[now] = vis_order.size();\n        vis_order.push_back(now);\n\
    \        for (auto nxt : to[now]) {\n            if (subtree_begin[nxt] == -1)\
    \ _build_dfs(nxt, to);\n        }\n        subtree_end[now] = vis_order.size();\n\
    \    }\n\n    preorder_tree_dfs() = default;\n\n    preorder_tree_dfs(const std::vector<std::vector<int>>\
    \ &to, int root)\n        : n(to.size()), root(root), subtree_begin(n, -1), subtree_end(n,\
    \ -1) {\n        _build_dfs(root, to);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/preorder_tree_dfs.hpp
  requiredBy: []
  timestamp: '2025-01-03 09:34:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/preorder_tree_dfs.test.cpp
documentation_of: tree/preorder_tree_dfs.hpp
layout: document
title: "Preorder tree DFS \uFF08\u6728\u306E\u884C\u304D\u304C\u3051\u9806 DFS\uFF09"
---

与えられた木に対して，行きがけ順に頂点を列挙した列を構築する．部分木を構成する頂点は連続して現れるので，部分木の頂点クエリ等に有用．

## 使用方法

```cpp
int N;
vector<vector<int>> to(N);
int root;

preorder_tree_dfs tour(to, root);

// 頂点 v の部分木を構成する頂点は半開区間 [tour.subtree_begin[v], tour.subtree_end[v]) に現れる
```

## 問題例

- [Library Checker: Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
