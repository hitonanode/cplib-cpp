---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/shortest_cycle.test.cpp
    title: graph/test/shortest_cycle.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/submissions/594507
  bundledCode: "#line 2 \"graph/shortest_cycle_weighted.hpp\"\n#include <cassert>\n\
    #include <limits>\n#include <queue>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Shortest cycle detection of UNDIRECTED SIMPLE graphs\n// Verified:\
    \ https://yukicoder.me/submissions/594507\ntemplate <typename T, T INF = std::numeric_limits<T>::max()\
    \ / 2> struct ShortestCycleOfUndirectedWeighted {\n    int V, E;\n    std::vector<std::vector<std::pair<int,\
    \ T>>> to; // (nxt, weight)\n    ShortestCycleOfUndirectedWeighted() = default;\n\
    \    ShortestCycleOfUndirectedWeighted(int V) : V(V), E(0), to(V) {}\n    void\
    \ add_edge(int s, int t, T len) {\n        assert(0 <= s and s < V);\n       \
    \ assert(0 <= t and t < V);\n        assert(len >= 0);\n        to[s].emplace_back(t,\
    \ len);\n        to[t].emplace_back(s, len);\n        E++;\n    }\n\n    std::vector<T>\
    \ dist;\n    std::vector<int> prev;\n    // Find minimum length simple cycle which\
    \ passes vertex `v`\n    // - Complexity: O(E log V)\n    // - return: (LEN, (a,\
    \ b))\n    //   - LEN: length of the shortest cycles if exists, INF ( = numeric_limits<int>::max()\
    \ / 2 ) otherwise.\n    //   - the cycle consists of vertices [v, ..., prev[prev[a]],\
    \ prev[a], a, b, prev[b], prev[prev[b]], ..., v]\n    std::pair<T, std::pair<int,\
    \ int>> Solve(int v) {\n        assert(0 <= v and v < V);\n        dist.assign(V,\
    \ INF), dist[v] = 0;\n        prev.assign(V, -1);\n\n        using P = std::pair<T,\
    \ std::pair<int, int>>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ pq;\n        std::vector<std::pair<std::pair<int, int>, T>> add_edge;\n\n  \
    \      pq.emplace(0, std::make_pair(v, -1));\n        while (!pq.empty()) {\n\
    \            const int now = pq.top().second.first, prv = pq.top().second.second;\n\
    \            pq.pop();\n            for (const auto &nxt : to[now])\n        \
    \        if (nxt.first != prv) {\n                    if (dist[nxt.first] == INF)\
    \ {\n                        dist[nxt.first] = dist[now] + nxt.second;\n     \
    \                   prev[nxt.first] = now;\n                        pq.emplace(dist[nxt.first],\
    \ std::make_pair(nxt.first, now));\n                    } else {\n           \
    \             add_edge.emplace_back(std::make_pair(now, nxt.first), nxt.second);\n\
    \                    }\n                }\n        }\n        T minimum_cycle\
    \ = INF;\n        int s = -1, t = -1;\n        for (auto edge : add_edge) {\n\
    \            int a = edge.first.first, b = edge.first.second;\n            T L\
    \ = dist[a] + dist[b] + edge.second;\n            if (L < minimum_cycle) minimum_cycle\
    \ = L, s = a, t = b;\n        }\n        return std::make_pair(minimum_cycle,\
    \ std::make_pair(s, t));\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <limits>\n#include <queue>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// Shortest cycle detection of\
    \ UNDIRECTED SIMPLE graphs\n// Verified: https://yukicoder.me/submissions/594507\n\
    template <typename T, T INF = std::numeric_limits<T>::max() / 2> struct ShortestCycleOfUndirectedWeighted\
    \ {\n    int V, E;\n    std::vector<std::vector<std::pair<int, T>>> to; // (nxt,\
    \ weight)\n    ShortestCycleOfUndirectedWeighted() = default;\n    ShortestCycleOfUndirectedWeighted(int\
    \ V) : V(V), E(0), to(V) {}\n    void add_edge(int s, int t, T len) {\n      \
    \  assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n        assert(len\
    \ >= 0);\n        to[s].emplace_back(t, len);\n        to[t].emplace_back(s, len);\n\
    \        E++;\n    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\
    \    // Find minimum length simple cycle which passes vertex `v`\n    // - Complexity:\
    \ O(E log V)\n    // - return: (LEN, (a, b))\n    //   - LEN: length of the shortest\
    \ cycles if exists, INF ( = numeric_limits<int>::max() / 2 ) otherwise.\n    //\
    \   - the cycle consists of vertices [v, ..., prev[prev[a]], prev[a], a, b, prev[b],\
    \ prev[prev[b]], ..., v]\n    std::pair<T, std::pair<int, int>> Solve(int v) {\n\
    \        assert(0 <= v and v < V);\n        dist.assign(V, INF), dist[v] = 0;\n\
    \        prev.assign(V, -1);\n\n        using P = std::pair<T, std::pair<int,\
    \ int>>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        std::vector<std::pair<std::pair<int, int>, T>> add_edge;\n\n        pq.emplace(0,\
    \ std::make_pair(v, -1));\n        while (!pq.empty()) {\n            const int\
    \ now = pq.top().second.first, prv = pq.top().second.second;\n            pq.pop();\n\
    \            for (const auto &nxt : to[now])\n                if (nxt.first !=\
    \ prv) {\n                    if (dist[nxt.first] == INF) {\n                \
    \        dist[nxt.first] = dist[now] + nxt.second;\n                        prev[nxt.first]\
    \ = now;\n                        pq.emplace(dist[nxt.first], std::make_pair(nxt.first,\
    \ now));\n                    } else {\n                        add_edge.emplace_back(std::make_pair(now,\
    \ nxt.first), nxt.second);\n                    }\n                }\n       \
    \ }\n        T minimum_cycle = INF;\n        int s = -1, t = -1;\n        for\
    \ (auto edge : add_edge) {\n            int a = edge.first.first, b = edge.first.second;\n\
    \            T L = dist[a] + dist[b] + edge.second;\n            if (L < minimum_cycle)\
    \ minimum_cycle = L, s = a, t = b;\n        }\n        return std::make_pair(minimum_cycle,\
    \ std::make_pair(s, t));\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_cycle_weighted.hpp
  requiredBy: []
  timestamp: '2021-05-01 20:55:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/shortest_cycle.test.cpp
documentation_of: graph/shortest_cycle_weighted.hpp
layout: document
redirect_from:
- /library/graph/shortest_cycle_weighted.hpp
- /library/graph/shortest_cycle_weighted.hpp.html
title: graph/shortest_cycle_weighted.hpp
---
