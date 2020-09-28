---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"unionfind/undo_unionfind.hpp\"\n#include <stack>\n#include\
    \ <vector>\n#include <numeric>\n#include <utility>\n\n// CUT begin\n// UnionFind,\
    \ able to rewind to the previous state by undo()\n// Written for Educational Codeforces\
    \ 62 F, although not verified yet.\nstruct UndoSizeAwareUnionFind\n{\n    using\
    \ pint = std::pair<int, int>;\n    std::vector<int> par, cou;\n    std::stack<std::pair<int,\
    \ pint>> history;\n    UndoSizeAwareUnionFind(int N) : par(N), cou(N, 1) {\n \
    \       std::iota(par.begin(), par.end(), 0);\n    }\n    int find(int x) { return\
    \ (par[x] == x) ? x :find(par[x]); }\n    void unite(int x, int y) {\n       \
    \ x = find(x), y = find(y);\n        if (cou[x] < cou[y]) std::swap(x, y);\n \
    \       history.emplace(y, pint(par[y], cou[x]));\n        if (x != y) par[y]\
    \ = x, cou[x] += cou[y];\n    }\n    void undo() {\n        cou[par[history.top().first]]\
    \ = history.top().second.second;\n        par[history.top().first] = history.top().second.first;\n\
    \        history.pop();\n    }\n    void reset() {\n        while (!history.empty())\
    \ undo();\n    }\n    int count(int x) { return cou[find(x)]; }\n    bool same(int\
    \ x, int y) { return find(x) == find(y); }\n};\n"
  code: "#pragma once \n#include <stack>\n#include <vector>\n#include <numeric>\n\
    #include <utility>\n\n// CUT begin\n// UnionFind, able to rewind to the previous\
    \ state by undo()\n// Written for Educational Codeforces 62 F, although not verified\
    \ yet.\nstruct UndoSizeAwareUnionFind\n{\n    using pint = std::pair<int, int>;\n\
    \    std::vector<int> par, cou;\n    std::stack<std::pair<int, pint>> history;\n\
    \    UndoSizeAwareUnionFind(int N) : par(N), cou(N, 1) {\n        std::iota(par.begin(),\
    \ par.end(), 0);\n    }\n    int find(int x) { return (par[x] == x) ? x :find(par[x]);\
    \ }\n    void unite(int x, int y) {\n        x = find(x), y = find(y);\n     \
    \   if (cou[x] < cou[y]) std::swap(x, y);\n        history.emplace(y, pint(par[y],\
    \ cou[x]));\n        if (x != y) par[y] = x, cou[x] += cou[y];\n    }\n    void\
    \ undo() {\n        cou[par[history.top().first]] = history.top().second.second;\n\
    \        par[history.top().first] = history.top().second.first;\n        history.pop();\n\
    \    }\n    void reset() {\n        while (!history.empty()) undo();\n    }\n\
    \    int count(int x) { return cou[find(x)]; }\n    bool same(int x, int y) {\
    \ return find(x) == find(y); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/undo_unionfind.hpp
  requiredBy: []
  timestamp: '2020-04-05 20:29:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: unionfind/undo_unionfind.hpp
layout: document
redirect_from:
- /library/unionfind/undo_unionfind.hpp
- /library/unionfind/undo_unionfind.hpp.html
title: unionfind/undo_unionfind.hpp
---
