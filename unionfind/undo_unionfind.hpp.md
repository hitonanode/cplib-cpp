---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"unionfind/undo_unionfind.hpp\"\n#include <numeric>\n#include\
    \ <stack>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// UnionFind,\
    \ able to rewind to the previous state by undo()\n// Written for Educational Codeforces\
    \ 62 F, although not verified yet.\nstruct UndoUnionFind {\n    using pint = std::pair<int,\
    \ int>;\n    std::vector<int> par, cou;\n    std::stack<std::pair<int, pint>>\
    \ history;\n    UndoUnionFind(int N) : par(N), cou(N, 1) { std::iota(par.begin(),\
    \ par.end(), 0); }\n    int find(int x) const { return (par[x] == x) ? x : find(par[x]);\
    \ }\n    bool unite(int x, int y) {\n        x = find(x), y = find(y);\n     \
    \   if (cou[x] < cou[y]) std::swap(x, y);\n        history.emplace(y, pint(par[y],\
    \ cou[x]));\n        return x != y ? par[y] = x, cou[x] += cou[y], true : false;\n\
    \    }\n    void undo() {\n        cou[par[history.top().first]] = history.top().second.second;\n\
    \        par[history.top().first] = history.top().second.first;\n        history.pop();\n\
    \    }\n    void reset() {\n        while (!history.empty()) undo();\n    }\n\
    \    int count(int x) const { return cou[find(x)]; }\n    bool same(int x, int\
    \ y) const { return find(x) == find(y); }\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <stack>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// UnionFind, able to rewind to the previous\
    \ state by undo()\n// Written for Educational Codeforces 62 F, although not verified\
    \ yet.\nstruct UndoUnionFind {\n    using pint = std::pair<int, int>;\n    std::vector<int>\
    \ par, cou;\n    std::stack<std::pair<int, pint>> history;\n    UndoUnionFind(int\
    \ N) : par(N), cou(N, 1) { std::iota(par.begin(), par.end(), 0); }\n    int find(int\
    \ x) const { return (par[x] == x) ? x : find(par[x]); }\n    bool unite(int x,\
    \ int y) {\n        x = find(x), y = find(y);\n        if (cou[x] < cou[y]) std::swap(x,\
    \ y);\n        history.emplace(y, pint(par[y], cou[x]));\n        return x !=\
    \ y ? par[y] = x, cou[x] += cou[y], true : false;\n    }\n    void undo() {\n\
    \        cou[par[history.top().first]] = history.top().second.second;\n      \
    \  par[history.top().first] = history.top().second.first;\n        history.pop();\n\
    \    }\n    void reset() {\n        while (!history.empty()) undo();\n    }\n\
    \    int count(int x) const { return cou[find(x)]; }\n    bool same(int x, int\
    \ y) const { return find(x) == find(y); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/undo_unionfind.hpp
  requiredBy: []
  timestamp: '2021-07-31 00:27:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: unionfind/undo_unionfind.hpp
layout: document
title: "UnionFind with Undo operation \uFF08Undo \u53EF\u80FD UnionFind\uFF09"
---

Undo 操作が可能な UnionFind．もともと同じ連結成分に属する元同士の `unite()` も操作一回に数える．

## 使用方法

```cpp
UndoUnionFind uf(N);
uf.unite(a, b);
uf.undo();
uf.unite(c, d);
uf.count(0);
uf.same(e, f);
uf.reset();
```

## 問題例

- [Educational Codeforces Round 62 F. Extending Set of Points](https://codeforces.com/contest/1140/problem/F)
- [Harbour.Space Scholarship Contest 2021-2022 G. Common Divisor Graph](https://codeforces.com/contest/1553/problem/G)
