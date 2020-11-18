---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/bellman_ford.test.cpp
    title: graph/test/bellman_ford.test.cpp
  - icon: ':x:'
    path: graph/test/dijkstra.test.cpp
    title: graph/test/dijkstra.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/shortest_path.hpp\"\n#include <cassert>\n#include\
    \ <deque>\n#include <functional>\n#include <limits>\n#include <queue>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\ntemplate<typename T>\nstruct ShortestPath\n\
    {\n    int V, E;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
    \ T>>> to;\n    ShortestPath() = default;\n    ShortestPath(int V) : V(V), E(0),\
    \ to(V) {}\n    void add_edge(int s, int t, T len) {\n        assert(0 <= s and\
    \ s < V);\n        assert(0 <= t and t < V);\n        to[s].emplace_back(t, len);\n\
    \        E++;\n    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\
    \    // Dijkstra algorithm\n    // Complexity: O(E log E)\n    void Dijkstra(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, std::numeric_limits<T>::max());\n\
    \        dist[s] = 0;\n        prev.assign(V, INVALID);\n        using P = std::pair<T,\
    \ int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        pq.emplace(0, s);\n        while(!pq.empty()) {\n            T d;\n \
    \           int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
    \            if (dist[v] < d) continue;\n            for (auto nx : to[v]) {\n\
    \                T dnx = d + nx.second;\n                if (dist[nx.first] >\
    \ dnx) {\n                    dist[nx.first] = dnx, prev[nx.first] = v;\n    \
    \                pq.emplace(dnx, nx.first);\n                }\n            }\n\
    \        }\n    }\n\n    // Bellman-Ford algorithm\n    // Complexity: O(VE)\n\
    \    bool BellmanFord(int s, int nb_loop) {\n        assert(0 <= s and s < V);\n\
    \        dist.assign(V, std::numeric_limits<T>::max());\n        dist[s] = 0;\n\
    \        prev.assign(V, INVALID);\n        for (int l = 0; l < nb_loop; l++) {\n\
    \            bool upd = false;\n            for (int v = 0; v < V; v++) {\n  \
    \              if (dist[v] == std::numeric_limits<T>::max()) continue;\n     \
    \           for (auto nx : to[v]) {\n                    T dnx = dist[v] + nx.second;\n\
    \                    if (dist[nx.first] > dnx) {\n                        dist[nx.first]\
    \ = dnx, prev[nx.first] = v;\n                        upd = true;\n          \
    \          }\n                }\n            }\n            if (!upd) return true;\n\
    \        }\n        return false;\n    }\n\n    void ZeroOneBFS(int s) {\n   \
    \     assert(0 <= s and s < V);\n        dist.assign(V, std::numeric_limits<T>::max());\n\
    \        dist[s] = 0;\n        prev.assign(V, INVALID);\n        std::deque<int>\
    \ que;\n        que.push_back(s);\n        while (!que.empty()) {\n          \
    \  int v = que.front();\n            que.pop_front();\n            for (auto nx\
    \ : to[v]) {\n                T dnx = dist[v] + nx.second;\n                if\
    \ (dist[nx.first] > dnx) {\n                    dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                    if (nx.second) {\n                        que.push_back(nx.first);\n\
    \                    } else {\n                        que.push_front(nx.first);\n\
    \                    }\n                }\n            }\n        }\n    }\n\n\
    \    // Warshall-Floyd algorithm\n    // Complexity: O(E + V^3)\n    std::vector<std::vector<T>>\
    \ dist2d;\n    void WarshallFloyd() {\n        dist2d.assign(V, std::vector<T>(V,\
    \ std::numeric_limits<T>::max()));\n        for (int i = 0; i < V; i++) {\n  \
    \          dist2d[i][i] = 0;\n            for (auto p : to[i]) dist2d[i][p.first]\
    \ = min(dist2d[i][p.first], p.second);\n        }\n        for (int k = 0; k <\
    \ V; k++) {\n            for (int i = 0; i < V; i++) {\n                if (dist2d[i][k]\
    \ = std::numeric_limits<T>::max()) continue;\n                for (int j = 0;\
    \ j < V; j++) {\n                    if (dist2d[k][j] = std::numeric_limits<T>::max())\
    \ continue;\n                    dist2d[i][j] = min(dist2d[i][j], dist2d[i][k]\
    \ + dist2d[k][j]);\n                }\n            }\n        }\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <deque>\n#include <functional>\n\
    #include <limits>\n#include <queue>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\ntemplate<typename T>\nstruct ShortestPath\n{\n    int V, E;\n  \
    \  int INVALID = -1;\n    std::vector<std::vector<std::pair<int, T>>> to;\n  \
    \  ShortestPath() = default;\n    ShortestPath(int V) : V(V), E(0), to(V) {}\n\
    \    void add_edge(int s, int t, T len) {\n        assert(0 <= s and s < V);\n\
    \        assert(0 <= t and t < V);\n        to[s].emplace_back(t, len);\n    \
    \    E++;\n    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n   \
    \ // Dijkstra algorithm\n    // Complexity: O(E log E)\n    void Dijkstra(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, std::numeric_limits<T>::max());\n\
    \        dist[s] = 0;\n        prev.assign(V, INVALID);\n        using P = std::pair<T,\
    \ int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        pq.emplace(0, s);\n        while(!pq.empty()) {\n            T d;\n \
    \           int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
    \            if (dist[v] < d) continue;\n            for (auto nx : to[v]) {\n\
    \                T dnx = d + nx.second;\n                if (dist[nx.first] >\
    \ dnx) {\n                    dist[nx.first] = dnx, prev[nx.first] = v;\n    \
    \                pq.emplace(dnx, nx.first);\n                }\n            }\n\
    \        }\n    }\n\n    // Bellman-Ford algorithm\n    // Complexity: O(VE)\n\
    \    bool BellmanFord(int s, int nb_loop) {\n        assert(0 <= s and s < V);\n\
    \        dist.assign(V, std::numeric_limits<T>::max());\n        dist[s] = 0;\n\
    \        prev.assign(V, INVALID);\n        for (int l = 0; l < nb_loop; l++) {\n\
    \            bool upd = false;\n            for (int v = 0; v < V; v++) {\n  \
    \              if (dist[v] == std::numeric_limits<T>::max()) continue;\n     \
    \           for (auto nx : to[v]) {\n                    T dnx = dist[v] + nx.second;\n\
    \                    if (dist[nx.first] > dnx) {\n                        dist[nx.first]\
    \ = dnx, prev[nx.first] = v;\n                        upd = true;\n          \
    \          }\n                }\n            }\n            if (!upd) return true;\n\
    \        }\n        return false;\n    }\n\n    void ZeroOneBFS(int s) {\n   \
    \     assert(0 <= s and s < V);\n        dist.assign(V, std::numeric_limits<T>::max());\n\
    \        dist[s] = 0;\n        prev.assign(V, INVALID);\n        std::deque<int>\
    \ que;\n        que.push_back(s);\n        while (!que.empty()) {\n          \
    \  int v = que.front();\n            que.pop_front();\n            for (auto nx\
    \ : to[v]) {\n                T dnx = dist[v] + nx.second;\n                if\
    \ (dist[nx.first] > dnx) {\n                    dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                    if (nx.second) {\n                        que.push_back(nx.first);\n\
    \                    } else {\n                        que.push_front(nx.first);\n\
    \                    }\n                }\n            }\n        }\n    }\n\n\
    \    // Warshall-Floyd algorithm\n    // Complexity: O(E + V^3)\n    std::vector<std::vector<T>>\
    \ dist2d;\n    void WarshallFloyd() {\n        dist2d.assign(V, std::vector<T>(V,\
    \ std::numeric_limits<T>::max()));\n        for (int i = 0; i < V; i++) {\n  \
    \          dist2d[i][i] = 0;\n            for (auto p : to[i]) dist2d[i][p.first]\
    \ = min(dist2d[i][p.first], p.second);\n        }\n        for (int k = 0; k <\
    \ V; k++) {\n            for (int i = 0; i < V; i++) {\n                if (dist2d[i][k]\
    \ = std::numeric_limits<T>::max()) continue;\n                for (int j = 0;\
    \ j < V; j++) {\n                    if (dist2d[k][j] = std::numeric_limits<T>::max())\
    \ continue;\n                    dist2d[i][j] = min(dist2d[i][j], dist2d[i][k]\
    \ + dist2d[k][j]);\n                }\n            }\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_path.hpp
  requiredBy: []
  timestamp: '2020-10-04 15:46:40+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - graph/test/bellman_ford.test.cpp
  - graph/test/dijkstra.test.cpp
documentation_of: graph/shortest_path.hpp
layout: document
redirect_from:
- /library/graph/shortest_path.hpp
- /library/graph/shortest_path.hpp.html
title: graph/shortest_path.hpp
---
