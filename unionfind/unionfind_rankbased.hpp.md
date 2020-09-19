---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: unionfind/test/unionfind_plain.test.cpp
    title: unionfind/test/unionfind_plain.test.cpp
  - icon: ':heavy_check_mark:'
    path: unionfind/test/unionfind_rankbased.test.cpp
    title: unionfind/test/unionfind_rankbased.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"unionfind/unionfind_rankbased.hpp\"\n#include <numeric>\n\
    #include <vector>\n\n// CUT begin\n// UnionFind Tree (0-indexed)\nstruct RankBasedUnionFind\n\
    {\n    std::vector<int> par, rank;\n    RankBasedUnionFind(int N = 0): par(N),\
    \ rank(N) {\n        iota(par.begin(), par.end(), 0);\n    }\n    int find(int\
    \ x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }\n    bool unite(int\
    \ x, int y) {\n        x = find(x), y = find(y);\n        if (x == y) return false;\n\
    \        if (rank[x] < rank[y]) par[x] = y;\n        else par[y] = x;\n      \
    \  if (rank[x] == rank[y]) rank[x]++;\n        return true;\n    }\n    bool same(int\
    \ x, int y) { return find(x) == find(y); }\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <vector>\n\n// CUT begin\n// UnionFind\
    \ Tree (0-indexed)\nstruct RankBasedUnionFind\n{\n    std::vector<int> par, rank;\n\
    \    RankBasedUnionFind(int N = 0): par(N), rank(N) {\n        iota(par.begin(),\
    \ par.end(), 0);\n    }\n    int find(int x) { return (par[x] == x) ? x : (par[x]\
    \ = find(par[x])); }\n    bool unite(int x, int y) {\n        x = find(x), y =\
    \ find(y);\n        if (x == y) return false;\n        if (rank[x] < rank[y])\
    \ par[x] = y;\n        else par[y] = x;\n        if (rank[x] == rank[y]) rank[x]++;\n\
    \        return true;\n    }\n    bool same(int x, int y) { return find(x) ==\
    \ find(y); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/unionfind_rankbased.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - unionfind/test/unionfind_plain.test.cpp
  - unionfind/test/unionfind_rankbased.test.cpp
documentation_of: unionfind/unionfind_rankbased.hpp
layout: document
redirect_from:
- /library/unionfind/unionfind_rankbased.hpp
- /library/unionfind/unionfind_rankbased.hpp.html
title: unionfind/unionfind_rankbased.hpp
---
