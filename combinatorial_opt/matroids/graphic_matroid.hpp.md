---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
    title: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
    title: combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
    title: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
    title: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/matroids/graphic_matroid.hpp\"\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\n// GraphicMatroid: subgraph\
    \ of undirected graphs, without loops\nclass GraphicMatroid {\n    using Vertex\
    \ = int;\n    using Element = int;\n    int M;\n    int V; // # of vertices of\
    \ graph\n    std::vector<std::vector<std::pair<Vertex, Element>>> to;\n    std::vector<std::pair<Vertex,\
    \ Vertex>> edges;\n    std::vector<Element> backtrack;\n    std::vector<Vertex>\
    \ vprev;\n    std::vector<int> depth, root;\n\npublic:\n    GraphicMatroid(int\
    \ V, const std::vector<std::pair<Vertex, Vertex>> &edges_)\n        : M(edges_.size()),\
    \ V(V), to(V), edges(edges_) {\n        for (int e = 0; e < int(edges_.size());\
    \ e++) {\n            int u = edges_[e].first, v = edges_[e].second;\n       \
    \     assert(0 <= u and u < V);\n            assert(0 <= v and v < V);\n     \
    \       if (u != v) {\n                to[u].emplace_back(v, e);\n           \
    \     to[v].emplace_back(u, e);\n            }\n        }\n    }\n    int size()\
    \ const { return M; }\n\n    std::vector<Vertex> que;\n    template <class State>\
    \ void set(State I) {\n        assert(int(I.size()) == M);\n        backtrack.assign(V,\
    \ -1);\n        vprev.assign(V, -1);\n        depth.assign(V, -1);\n        root.assign(V,\
    \ -1);\n        que.resize(V);\n        int qb = 0, qe = 0;\n        for (Vertex\
    \ i = 0; i < V; i++) {\n            if (backtrack[i] >= 0) continue;\n       \
    \     que[qb = 0] = i, qe = 1, depth[i] = 0;\n            while (qb < qe) {\n\
    \                Vertex now = que[qb++];\n                root[now] = i;\n   \
    \             for (auto nxt : to[now]) {\n                    if (depth[nxt.first]\
    \ < 0 and I[nxt.second]) {\n                        backtrack[nxt.first] = nxt.second;\n\
    \                        vprev[nxt.first] = now;\n                        depth[nxt.first]\
    \ = depth[now] + 1;\n                        que[qe++] = nxt.first;\n        \
    \            }\n                }\n            }\n        }\n    }\n\n    std::vector<Element>\
    \ circuit(const Element e) const {\n        assert(0 <= e and e < M);\n      \
    \  Vertex s = edges[e].first, t = edges[e].second;\n        if (root[s] != root[t])\
    \ return {};\n        std::vector<Element> ret{e};\n        auto step = [&](Vertex\
    \ &i) { ret.push_back(backtrack[i]), i = vprev[i]; };\n        int ddepth = depth[s]\
    \ - depth[t];\n        for (; ddepth > 0; --ddepth) step(s);\n        for (; ddepth\
    \ < 0; ++ddepth) step(t);\n        while (s != t) step(s), step(t);\n        return\
    \ ret;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// GraphicMatroid: subgraph of undirected graphs, without loops\nclass GraphicMatroid\
    \ {\n    using Vertex = int;\n    using Element = int;\n    int M;\n    int V;\
    \ // # of vertices of graph\n    std::vector<std::vector<std::pair<Vertex, Element>>>\
    \ to;\n    std::vector<std::pair<Vertex, Vertex>> edges;\n    std::vector<Element>\
    \ backtrack;\n    std::vector<Vertex> vprev;\n    std::vector<int> depth, root;\n\
    \npublic:\n    GraphicMatroid(int V, const std::vector<std::pair<Vertex, Vertex>>\
    \ &edges_)\n        : M(edges_.size()), V(V), to(V), edges(edges_) {\n       \
    \ for (int e = 0; e < int(edges_.size()); e++) {\n            int u = edges_[e].first,\
    \ v = edges_[e].second;\n            assert(0 <= u and u < V);\n            assert(0\
    \ <= v and v < V);\n            if (u != v) {\n                to[u].emplace_back(v,\
    \ e);\n                to[v].emplace_back(u, e);\n            }\n        }\n \
    \   }\n    int size() const { return M; }\n\n    std::vector<Vertex> que;\n  \
    \  template <class State> void set(State I) {\n        assert(int(I.size()) ==\
    \ M);\n        backtrack.assign(V, -1);\n        vprev.assign(V, -1);\n      \
    \  depth.assign(V, -1);\n        root.assign(V, -1);\n        que.resize(V);\n\
    \        int qb = 0, qe = 0;\n        for (Vertex i = 0; i < V; i++) {\n     \
    \       if (backtrack[i] >= 0) continue;\n            que[qb = 0] = i, qe = 1,\
    \ depth[i] = 0;\n            while (qb < qe) {\n                Vertex now = que[qb++];\n\
    \                root[now] = i;\n                for (auto nxt : to[now]) {\n\
    \                    if (depth[nxt.first] < 0 and I[nxt.second]) {\n         \
    \               backtrack[nxt.first] = nxt.second;\n                        vprev[nxt.first]\
    \ = now;\n                        depth[nxt.first] = depth[now] + 1;\n       \
    \                 que[qe++] = nxt.first;\n                    }\n            \
    \    }\n            }\n        }\n    }\n\n    std::vector<Element> circuit(const\
    \ Element e) const {\n        assert(0 <= e and e < M);\n        Vertex s = edges[e].first,\
    \ t = edges[e].second;\n        if (root[s] != root[t]) return {};\n        std::vector<Element>\
    \ ret{e};\n        auto step = [&](Vertex &i) { ret.push_back(backtrack[i]), i\
    \ = vprev[i]; };\n        int ddepth = depth[s] - depth[t];\n        for (; ddepth\
    \ > 0; --ddepth) step(s);\n        for (; ddepth < 0; ++ddepth) step(t);\n   \
    \     while (s != t) step(s), step(t);\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/graphic_matroid.hpp
  requiredBy: []
  timestamp: '2021-09-05 18:41:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
  - combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
documentation_of: combinatorial_opt/matroids/graphic_matroid.hpp
layout: document
title: "Graphic matroid \uFF08\u30B0\u30E9\u30D5\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
---

無向グラフ $(V, E)$ によって定義されるマトロイド．辺集合 $E$ の部分集合 $I$ は，無向グラフ上に $I$ に属する辺のみによる閉路が存在しないときに独立．

## 使用例

```cpp
vector<pair<int, int>> edges;
edges.emplace_back(0, 1);
edges.emplace_back(0, 2);
edges.emplace_back(1, 3);
edges.emplace_back(1, 4);
edges.emplace_back(3, 4);
edges.emplace_back(2, 4);

GraphicMatroid M(5, edges);
vector<bool> state{1, 1, 1, 1, 0, 0};
M.set(state);
vector<int> c1 = M.circuit(4); // [4, 2, 3]
vector<int> c2 = M.circuit(5); // [5, 3, 1, 0]
```
