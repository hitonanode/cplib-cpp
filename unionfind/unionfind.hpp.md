---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/incremental_bridge_connectivity.hpp
    title: graph/incremental_bridge_connectivity.hpp
  - icon: ':warning:'
    path: graph/paths_of_length_two_decomposition.hpp
    title: "\u7121\u5411\u30B0\u30E9\u30D5\u306E\u9577\u3055 2 \u306E\u30D1\u30B9\u3078\
      \u306E\u5206\u89E3"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/incremental-bridge-connectivity.test.cpp
    title: graph/test/incremental-bridge-connectivity.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/manhattan_mst.test.cpp
    title: graph/test/manhattan_mst.test.cpp
  - icon: ':heavy_check_mark:'
    path: unionfind/test/unionfind.test.cpp
    title: unionfind/test/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"unionfind/unionfind.hpp\"\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// UnionFind Tree (0-indexed),\
    \ based on size of each disjoint set\nstruct UnionFind {\n    std::vector<int>\
    \ par, cou;\n    UnionFind(int N = 0) : par(N), cou(N, 1) { iota(par.begin(),\
    \ par.end(), 0); }\n    int find(int x) { return (par[x] == x) ? x : (par[x] =\
    \ find(par[x])); }\n    bool unite(int x, int y) {\n        x = find(x), y = find(y);\n\
    \        if (x == y) return false;\n        if (cou[x] < cou[y]) std::swap(x,\
    \ y);\n        par[y] = x, cou[x] += cou[y];\n        return true;\n    }\n  \
    \  int count(int x) { return cou[find(x)]; }\n    bool same(int x, int y) { return\
    \ find(x) == find(y); }\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// UnionFind Tree (0-indexed), based on size of each disjoint\
    \ set\nstruct UnionFind {\n    std::vector<int> par, cou;\n    UnionFind(int N\
    \ = 0) : par(N), cou(N, 1) { iota(par.begin(), par.end(), 0); }\n    int find(int\
    \ x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }\n    bool unite(int\
    \ x, int y) {\n        x = find(x), y = find(y);\n        if (x == y) return false;\n\
    \        if (cou[x] < cou[y]) std::swap(x, y);\n        par[y] = x, cou[x] +=\
    \ cou[y];\n        return true;\n    }\n    int count(int x) { return cou[find(x)];\
    \ }\n    bool same(int x, int y) { return find(x) == find(y); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/unionfind.hpp
  requiredBy:
  - graph/incremental_bridge_connectivity.hpp
  - graph/paths_of_length_two_decomposition.hpp
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/manhattan_mst.test.cpp
  - graph/test/incremental-bridge-connectivity.test.cpp
  - unionfind/test/unionfind.test.cpp
documentation_of: unionfind/unionfind.hpp
layout: document
redirect_from:
- /library/unionfind/unionfind.hpp
- /library/unionfind/unionfind.hpp.html
title: unionfind/unionfind.hpp
---
