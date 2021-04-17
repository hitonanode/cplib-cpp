---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/incremental_bridge_connectivity.hpp
    title: graph/incremental_bridge_connectivity.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/incremental-bridge-connectivity.test.cpp
    title: graph/test/incremental-bridge-connectivity.test.cpp
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
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - unionfind/test/unionfind.test.cpp
  - graph/test/incremental-bridge-connectivity.test.cpp
documentation_of: unionfind/unionfind.hpp
layout: document
redirect_from:
- /library/unionfind/unionfind.hpp
- /library/unionfind/unionfind.hpp.html
title: unionfind/unionfind.hpp
---
