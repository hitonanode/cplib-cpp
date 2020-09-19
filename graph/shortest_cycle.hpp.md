---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://codeforces.com/contest/1325/problem/E>
  bundledCode: "#line 2 \"graph/shortest_cycle.hpp\"\n#include <cassert>\n#include\
    \ <limits>\n#include <deque>\n#include <utility>\n#include <vector>\n\n// CUT\
    \ begin\n// Shortest cycle detection of UNDIRECTED SIMPLE graphs based on 01-BFS\n\
    // Assumption: only two types of edges are permitted: weight = 0 or W ( > 0)\n\
    // Complexity: O(E)\n// Verified: <https://codeforces.com/contest/1325/problem/E>\n\
    struct ShortestCycle01\n{\n    int V, E;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> to;  // (nxt, weight)\n    ShortestCycle01() = default;\n    ShortestCycle01(int\
    \ V) : V(V), E(0), to(V) {}\n    void add_edge(int s, int t, int len) {\n    \
    \    assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n        assert(len\
    \ >= 0);\n        to[s].emplace_back(t, len);\n        to[t].emplace_back(s, len);\n\
    \        E++;\n    }\n\n    std::vector<int> dist;\n    std::vector<int> prev;\n\
    \    // Find minimum length simple cycle which passes vertex `v`\n    // - return:\
    \ (LEN, (a, b))\n    //   - LEN: length of the shortest cycles if exists, numeric_limits<int>::max()\
    \ otherwise.\n    //   - the cycle consists of vertices [v, ..., prev[prev[a]],\
    \ prev[a], a, b, prev[b], prev[prev[b]], ..., v]\n    std::pair<int, std::pair<int,\
    \ int>> Solve(int v) {\n        assert(0 <= v and v < V);\n        dist.assign(V,\
    \ std::numeric_limits<int>::max());\n        dist[v] = 0;\n        prev.assign(V,\
    \ -1);\n        std::deque<std::pair<int, int>> bfsq;\n        std::vector<std::pair<std::pair<int,\
    \ int>, int>> add_edge;\n        bfsq.emplace_back(v, -1);\n        while (!bfsq.empty())\
    \ {\n            int now = bfsq.front().first, prv = bfsq.front().second;\n  \
    \          bfsq.pop_front();\n            for (auto nxt : to[now]) if (nxt.first\
    \ != prv) {\n                if (dist[nxt.first] == std::numeric_limits<int>::max())\
    \ {\n                    dist[nxt.first] = dist[now] + nxt.second;\n         \
    \           prev[nxt.first] = now;\n                    if (nxt.second) bfsq.emplace_back(nxt.first,\
    \ now);\n                    else bfsq.emplace_front(nxt.first, now);\n      \
    \          }\n                else add_edge.emplace_back(std::make_pair(now, nxt.first),\
    \ nxt.second);\n            }\n        }\n        int minimum_cycle = std::numeric_limits<int>::max();\n\
    \        int s = -1, t = -1;\n        for (auto edge : add_edge) {\n         \
    \   int a = edge.first.first, b = edge.first.second;\n            int L = dist[a]\
    \ + dist[b] + edge.second;\n            if (L < minimum_cycle) minimum_cycle =\
    \ L, s = a, t = b;\n        }\n        return std::make_pair(minimum_cycle, std::make_pair(s,\
    \ t));\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <limits>\n#include <deque>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// Shortest cycle detection of\
    \ UNDIRECTED SIMPLE graphs based on 01-BFS\n// Assumption: only two types of edges\
    \ are permitted: weight = 0 or W ( > 0)\n// Complexity: O(E)\n// Verified: <https://codeforces.com/contest/1325/problem/E>\n\
    struct ShortestCycle01\n{\n    int V, E;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> to;  // (nxt, weight)\n    ShortestCycle01() = default;\n    ShortestCycle01(int\
    \ V) : V(V), E(0), to(V) {}\n    void add_edge(int s, int t, int len) {\n    \
    \    assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n        assert(len\
    \ >= 0);\n        to[s].emplace_back(t, len);\n        to[t].emplace_back(s, len);\n\
    \        E++;\n    }\n\n    std::vector<int> dist;\n    std::vector<int> prev;\n\
    \    // Find minimum length simple cycle which passes vertex `v`\n    // - return:\
    \ (LEN, (a, b))\n    //   - LEN: length of the shortest cycles if exists, numeric_limits<int>::max()\
    \ otherwise.\n    //   - the cycle consists of vertices [v, ..., prev[prev[a]],\
    \ prev[a], a, b, prev[b], prev[prev[b]], ..., v]\n    std::pair<int, std::pair<int,\
    \ int>> Solve(int v) {\n        assert(0 <= v and v < V);\n        dist.assign(V,\
    \ std::numeric_limits<int>::max());\n        dist[v] = 0;\n        prev.assign(V,\
    \ -1);\n        std::deque<std::pair<int, int>> bfsq;\n        std::vector<std::pair<std::pair<int,\
    \ int>, int>> add_edge;\n        bfsq.emplace_back(v, -1);\n        while (!bfsq.empty())\
    \ {\n            int now = bfsq.front().first, prv = bfsq.front().second;\n  \
    \          bfsq.pop_front();\n            for (auto nxt : to[now]) if (nxt.first\
    \ != prv) {\n                if (dist[nxt.first] == std::numeric_limits<int>::max())\
    \ {\n                    dist[nxt.first] = dist[now] + nxt.second;\n         \
    \           prev[nxt.first] = now;\n                    if (nxt.second) bfsq.emplace_back(nxt.first,\
    \ now);\n                    else bfsq.emplace_front(nxt.first, now);\n      \
    \          }\n                else add_edge.emplace_back(std::make_pair(now, nxt.first),\
    \ nxt.second);\n            }\n        }\n        int minimum_cycle = std::numeric_limits<int>::max();\n\
    \        int s = -1, t = -1;\n        for (auto edge : add_edge) {\n         \
    \   int a = edge.first.first, b = edge.first.second;\n            int L = dist[a]\
    \ + dist[b] + edge.second;\n            if (L < minimum_cycle) minimum_cycle =\
    \ L, s = a, t = b;\n        }\n        return std::make_pair(minimum_cycle, std::make_pair(s,\
    \ t));\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_cycle.hpp
  requiredBy: []
  timestamp: '2020-03-15 20:16:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/shortest_cycle.hpp
layout: document
redirect_from:
- /library/graph/shortest_cycle.hpp
- /library/graph/shortest_cycle.hpp.html
title: graph/shortest_cycle.hpp
---
