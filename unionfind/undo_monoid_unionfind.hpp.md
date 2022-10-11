---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
    title: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"unionfind/undo_monoid_unionfind.hpp\"\n#include <numeric>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\n// UnionFind, able\
    \ to rewind to the previous state by undo()\ntemplate <class S> struct undo_dsu\
    \ {\n    std::vector<int> par, cou;\n    std::vector<S> weights;\n    std::vector<std::tuple<int,\
    \ int, S>> history;\n\n    explicit undo_dsu(const std::vector<S> &init)\n   \
    \     : par(init.size()), cou(init.size(), 1), weights(init) {\n        std::iota(par.begin(),\
    \ par.end(), 0);\n    }\n    explicit undo_dsu(int N) : undo_dsu(std::vector<S>(N,\
    \ S())) {}\n    undo_dsu() : undo_dsu(0) {}\n\n    int find(int x) const { return\
    \ (par[x] == x) ? x : find(par[x]); }\n    bool unite(int x, int y) {\n      \
    \  x = find(x), y = find(y);\n        if (cou[x] < cou[y]) std::swap(x, y);\n\
    \        history.emplace_back(y, cou[x], weights[x]);\n        return x != y ?\
    \ par[y] = x, cou[x] += cou[y], weights[x] += weights[y], true : false;\n    }\n\
    \n    void set_weight(int x, S w) {\n        x = find(x);\n        history.emplace_back(x,\
    \ cou[x], weights[x]);\n        weights[x] = w;\n    }\n\n    void undo() {\n\
    \        weights[par[std::get<0>(history.back())]] = std::get<2>(history.back());\n\
    \        cou[par[std::get<0>(history.back())]] = std::get<1>(history.back());\n\
    \        par[std::get<0>(history.back())] = std::get<0>(history.back());\n   \
    \     history.pop_back();\n    }\n\n    void reset() {\n        while (!history.empty())\
    \ undo();\n    }\n\n    int count(int x) const { return cou[find(x)]; }\n\n  \
    \  const S &sum(int x) const { return weights[find(x)]; }\n\n    bool same(int\
    \ x, int y) const { return find(x) == find(y); }\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// UnionFind, able to rewind to the previous state by undo()\n\
    template <class S> struct undo_dsu {\n    std::vector<int> par, cou;\n    std::vector<S>\
    \ weights;\n    std::vector<std::tuple<int, int, S>> history;\n\n    explicit\
    \ undo_dsu(const std::vector<S> &init)\n        : par(init.size()), cou(init.size(),\
    \ 1), weights(init) {\n        std::iota(par.begin(), par.end(), 0);\n    }\n\
    \    explicit undo_dsu(int N) : undo_dsu(std::vector<S>(N, S())) {}\n    undo_dsu()\
    \ : undo_dsu(0) {}\n\n    int find(int x) const { return (par[x] == x) ? x : find(par[x]);\
    \ }\n    bool unite(int x, int y) {\n        x = find(x), y = find(y);\n     \
    \   if (cou[x] < cou[y]) std::swap(x, y);\n        history.emplace_back(y, cou[x],\
    \ weights[x]);\n        return x != y ? par[y] = x, cou[x] += cou[y], weights[x]\
    \ += weights[y], true : false;\n    }\n\n    void set_weight(int x, S w) {\n \
    \       x = find(x);\n        history.emplace_back(x, cou[x], weights[x]);\n \
    \       weights[x] = w;\n    }\n\n    void undo() {\n        weights[par[std::get<0>(history.back())]]\
    \ = std::get<2>(history.back());\n        cou[par[std::get<0>(history.back())]]\
    \ = std::get<1>(history.back());\n        par[std::get<0>(history.back())] = std::get<0>(history.back());\n\
    \        history.pop_back();\n    }\n\n    void reset() {\n        while (!history.empty())\
    \ undo();\n    }\n\n    int count(int x) const { return cou[find(x)]; }\n\n  \
    \  const S &sum(int x) const { return weights[find(x)]; }\n\n    bool same(int\
    \ x, int y) const { return find(x) == find(y); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/undo_monoid_unionfind.hpp
  requiredBy: []
  timestamp: '2022-10-11 22:40:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
documentation_of: unionfind/undo_monoid_unionfind.hpp
layout: document
title: "UnionFind with Undo operation, monoid weights \uFF08Undo \u53EF\u80FD\u30FB\
  \u91CD\u307F\u548C\u53D6\u5F97\u53EF\u80FD UnionFind\uFF09"
---

Undo 操作が可能な UnionFind．もともと同じ連結成分に属する元同士の `unite()` も操作一回に数える．

また，各要素に重みを与え，連結成分の重み総和取得も可能．`undo_dsu<class S>` として与えるクラス `S` は以下のように `operator+=` が定義されている必要がある：

```cpp
struct S {
    S &operator+=(const S &x);
};

undo_dsu<S> dsu;
```

経路圧縮を行わないため，`find()` の計算量はクエリあたり $O(n \log n)$ となる．

## 使用方法

```cpp
vector<int> a{2, 3, 4, 5};
undo_dsu<int> uf(a);

uf.unite(0, 2);
uf.undo();
uf.unite(0, 1);
uf.count(0);
uf.sum(0);
uf.reset();
```
