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
  bundledCode: "#line 2 \"combinatorial_opt/matroids/graph_matroid.hpp\"\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\n// GraphMatroid: subgraph\
    \ of undirected graphs, without loops\nclass GraphMatroid {\n    using Vertex\
    \ = int;\n    using Element = int;\n    int M;\n    int V; // # of vertices of\
    \ graph\n    std::vector<std::vector<std::pair<Vertex, Element>>> to;\n    std::vector<std::pair<Vertex,\
    \ Vertex>> edges;\n    std::vector<Element> backtrack;\n    std::vector<Vertex>\
    \ vprev;\n    std::vector<int> depth, root;\n\npublic:\n    GraphMatroid(int V,\
    \ std::vector<std::pair<Vertex, Vertex>> edges_)\n        : M(edges_.size()),\
    \ V(V), to(V), edges(edges_) {\n        for (int e = 0; e < int(edges_.size());\
    \ e++) {\n            assert(edges_[e].first < V and edges_[e].second < V);\n\
    \            to[edges_[e].first].emplace_back(edges_[e].second, e);\n        \
    \    to[edges_[e].second].emplace_back(edges_[e].first, e);\n        }\n    }\n\
    \    int size() const { return M; }\n\n    template <class State> void set(State\
    \ I) {\n        assert(int(I.size()) == M);\n        backtrack.assign(V, -1);\n\
    \        vprev.resize(V);\n        depth.assign(V, -1);\n        root.resize(V);\n\
    \        static std::vector<Vertex> que(V);\n        int qb, qe;\n        for\
    \ (Vertex i = 0; i < V; i++) {\n            if (backtrack[i] >= 0) continue;\n\
    \            que[qb = 0] = i, qe = 1, depth[i] = 0;\n            while (qb < qe)\
    \ {\n                Vertex now = que[qb++];\n                root[now] = i;\n\
    \                for (auto nxt : to[now]) {\n                    if (depth[nxt.first]\
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
    \n// GraphMatroid: subgraph of undirected graphs, without loops\nclass GraphMatroid\
    \ {\n    using Vertex = int;\n    using Element = int;\n    int M;\n    int V;\
    \ // # of vertices of graph\n    std::vector<std::vector<std::pair<Vertex, Element>>>\
    \ to;\n    std::vector<std::pair<Vertex, Vertex>> edges;\n    std::vector<Element>\
    \ backtrack;\n    std::vector<Vertex> vprev;\n    std::vector<int> depth, root;\n\
    \npublic:\n    GraphMatroid(int V, std::vector<std::pair<Vertex, Vertex>> edges_)\n\
    \        : M(edges_.size()), V(V), to(V), edges(edges_) {\n        for (int e\
    \ = 0; e < int(edges_.size()); e++) {\n            assert(edges_[e].first < V\
    \ and edges_[e].second < V);\n            to[edges_[e].first].emplace_back(edges_[e].second,\
    \ e);\n            to[edges_[e].second].emplace_back(edges_[e].first, e);\n  \
    \      }\n    }\n    int size() const { return M; }\n\n    template <class State>\
    \ void set(State I) {\n        assert(int(I.size()) == M);\n        backtrack.assign(V,\
    \ -1);\n        vprev.resize(V);\n        depth.assign(V, -1);\n        root.resize(V);\n\
    \        static std::vector<Vertex> que(V);\n        int qb, qe;\n        for\
    \ (Vertex i = 0; i < V; i++) {\n            if (backtrack[i] >= 0) continue;\n\
    \            que[qb = 0] = i, qe = 1, depth[i] = 0;\n            while (qb < qe)\
    \ {\n                Vertex now = que[qb++];\n                root[now] = i;\n\
    \                for (auto nxt : to[now]) {\n                    if (depth[nxt.first]\
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
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/graph_matroid.hpp
  requiredBy: []
  timestamp: '2021-09-01 23:53:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/graph_matroid.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/matroids/graph_matroid.hpp
- /library/combinatorial_opt/matroids/graph_matroid.hpp.html
title: combinatorial_opt/matroids/graph_matroid.hpp
---
