---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7
  bundledCode: "#line 2 \"tree/euler_tour.hpp\"\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// Euler tour\n// https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7\n\
    struct euler_tour {\n    int n;\n    int root;\n\n    std::vector<std::pair<int,\
    \ int>> edges; // (parent, child)\n\n    // - \u9802\u70B9 v \u306B\u95A2\u3059\
    \u308B\u90E8\u5206\u6728\u306B\u542B\u307E\u308C\u308B\u8FBA\u306F\uFF0C [begins[v],\
    \ ends[v]) \u306B 2 \u56DE\u305A\u3064\u767B\u5834\n    // - [begins[u], begins[v])\
    \ (begins[u] <= begins[v]) \u306E\u534A\u958B\u533A\u9593\u306B u-v \u30D1\u30B9\
    \u3092\u69CB\u6210\u3059\u308B\u8FBA\u304C\u5947\u6570\u56DE\u767B\u5834\n   \
    \ std::vector<int> begins;\n    std::vector<int> ends;\n\n    std::vector<int>\
    \ par_eid;\n    std::vector<std::pair<int, bool>> tour; // (edge_id, flg) flg=true:\
    \ down, false: up\n\n    void _build_dfs(int now, int prv_eid, const std::vector<std::vector<std::pair<int,\
    \ int>>> &to) {\n        tour.emplace_back(prv_eid, true);\n        begins[now]\
    \ = tour.size();\n\n        for (auto [nxt, eid] : to[now]) {\n            if\
    \ (eid == prv_eid) continue;\n            par_eid[nxt] = eid;\n            if\
    \ (edges[eid].first == nxt) std::swap(edges[eid].first, edges[eid].second);\n\
    \            _build_dfs(nxt, eid, to);\n        }\n\n        ends[now] = tour.size();\n\
    \        tour.emplace_back(prv_eid, false);\n    }\n\n    euler_tour() = default;\n\
    \n    euler_tour(int n, const std::vector<std::pair<int, int>> &edges_, int root)\n\
    \        : n(n), root(root), edges(edges_), begins(n, -1), ends(n, -1), par_eid(n,\
    \ -1) {\n        std::vector<std::vector<std::pair<int, int>>> to(n);\n      \
    \  for (int eid = 0; eid < (int)edges.size(); ++eid) {\n            auto [u, v]\
    \ = edges[eid];\n            assert(u != v);\n            to.at(u).emplace_back(v,\
    \ eid);\n            to.at(v).emplace_back(u, eid);\n        }\n\n        _build_dfs(root,\
    \ -1, to);\n    }\n\n    // \u9802\u70B9 v \u306E\u90E8\u5206\u6728\u306E\u9802\
    \u70B9\u6570\n    int subtree_size(int v) const { return (ends.at(v) - begins.at(v))\
    \ / 2 + 1; }\n\n    int par(int v) const {\n        int eid = par_eid.at(v);\n\
    \        return eid == -1 ? -1 : edges[eid].first;\n    }\n\n    int tour_child(int\
    \ idx) const {\n        int eid = tour.at(idx).first;\n        return eid < 0\
    \ ? root : edges[eid].second;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// Euler tour\n// https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7\n\
    struct euler_tour {\n    int n;\n    int root;\n\n    std::vector<std::pair<int,\
    \ int>> edges; // (parent, child)\n\n    // - \u9802\u70B9 v \u306B\u95A2\u3059\
    \u308B\u90E8\u5206\u6728\u306B\u542B\u307E\u308C\u308B\u8FBA\u306F\uFF0C [begins[v],\
    \ ends[v]) \u306B 2 \u56DE\u305A\u3064\u767B\u5834\n    // - [begins[u], begins[v])\
    \ (begins[u] <= begins[v]) \u306E\u534A\u958B\u533A\u9593\u306B u-v \u30D1\u30B9\
    \u3092\u69CB\u6210\u3059\u308B\u8FBA\u304C\u5947\u6570\u56DE\u767B\u5834\n   \
    \ std::vector<int> begins;\n    std::vector<int> ends;\n\n    std::vector<int>\
    \ par_eid;\n    std::vector<std::pair<int, bool>> tour; // (edge_id, flg) flg=true:\
    \ down, false: up\n\n    void _build_dfs(int now, int prv_eid, const std::vector<std::vector<std::pair<int,\
    \ int>>> &to) {\n        tour.emplace_back(prv_eid, true);\n        begins[now]\
    \ = tour.size();\n\n        for (auto [nxt, eid] : to[now]) {\n            if\
    \ (eid == prv_eid) continue;\n            par_eid[nxt] = eid;\n            if\
    \ (edges[eid].first == nxt) std::swap(edges[eid].first, edges[eid].second);\n\
    \            _build_dfs(nxt, eid, to);\n        }\n\n        ends[now] = tour.size();\n\
    \        tour.emplace_back(prv_eid, false);\n    }\n\n    euler_tour() = default;\n\
    \n    euler_tour(int n, const std::vector<std::pair<int, int>> &edges_, int root)\n\
    \        : n(n), root(root), edges(edges_), begins(n, -1), ends(n, -1), par_eid(n,\
    \ -1) {\n        std::vector<std::vector<std::pair<int, int>>> to(n);\n      \
    \  for (int eid = 0; eid < (int)edges.size(); ++eid) {\n            auto [u, v]\
    \ = edges[eid];\n            assert(u != v);\n            to.at(u).emplace_back(v,\
    \ eid);\n            to.at(v).emplace_back(u, eid);\n        }\n\n        _build_dfs(root,\
    \ -1, to);\n    }\n\n    // \u9802\u70B9 v \u306E\u90E8\u5206\u6728\u306E\u9802\
    \u70B9\u6570\n    int subtree_size(int v) const { return (ends.at(v) - begins.at(v))\
    \ / 2 + 1; }\n\n    int par(int v) const {\n        int eid = par_eid.at(v);\n\
    \        return eid == -1 ? -1 : edges[eid].first;\n    }\n\n    int tour_child(int\
    \ idx) const {\n        int eid = tour.at(idx).first;\n        return eid < 0\
    \ ? root : edges[eid].second;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/euler_tour.hpp
  requiredBy: []
  timestamp: '2025-01-03 09:47:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tree/euler_tour.hpp
layout: document
title: "Euler tour \uFF08\u6728\u306E\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC\uFF09"
---

木のオイラーツアーを構築．パスクエリをデータ構造に載せて高速に解く場合や， Mo's algorithm を適用する場合に有用．

## 使用方法

以下で構築できる．

```cpp
int n, root;
vector<pair<int, int>> edges;

const euler_tour et(n, edges, root);
```

木上の $u$-$v$ パスに着目したい場合，以下の処理を行うと，当該パスを構成する辺が半開区間 `[begins, ends)` に丁度奇数回登場する．

```cpp
int begins = et.begins.at(u), ends = et.begins.at(v);

for (int i = begins; i < ends; ++i) {
    // Insert or erase et.tour_child(i);
}
```

半開区間 `[begins, ends)` たちに対して Mo's algorithm などを適用することで，クエリたちが効率的に処理できることがある．

## 問題例

- [Primitive Queries \| CodeChef](https://www.codechef.com/problems/DISTNUM3)
  - 木のパス上の頂点集合に関するクエリを Mo's algorithm で解く．

## 参考文献・リンク

- [Mo's algorithm - ei1333の日記](https://ei1333.hateblo.jp/entry/2017/09/11/211011)
