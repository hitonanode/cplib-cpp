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
    - https://codeforces.com/contest/1325/problem/E
    - https://codeforces.com/contest/1817/problem/B
  bundledCode: "#line 2 \"graph/shortest_cycle01.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <deque>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\n// Shortest cycle detection of UNDIRECTED SIMPLE graphs based on\
    \ 01-BFS\n// Assumption: only two types of edges are permitted: weight = 0 or\
    \ W ( > 0)\n// Complexity: O(E)\n// Verified: https://codeforces.com/contest/1325/problem/E\
    \ https://codeforces.com/contest/1817/problem/B\nstruct ShortestCycle01 {\n  \
    \  static constexpr int INF = std::numeric_limits<int>::max() / 2;\n    int V,\
    \ E;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int, int>>>\
    \ to; // (nxt, weight)\n    ShortestCycle01() = default;\n    ShortestCycle01(int\
    \ V) : V(V), E(0), to(V) {}\n    void add_edge(int s, int t, int len) {\n    \
    \    assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n        assert(len\
    \ >= 0);\n        to[s].emplace_back(t, len);\n        to[t].emplace_back(s, len);\n\
    \        E++;\n    }\n\n    std::vector<int> dist;\n    std::vector<int> prev;\n\
    \    std::vector<int> orig;\n    // Find minimum length simple cycle which passes\
    \ vertex `v`\n    // - return: (LEN, (a, b))\n    //   - LEN: length of the shortest\
    \ cycles if exists, INF otherwise.\n    //   - the cycle consists of vertices\
    \ [v, ..., prev[prev[a]], prev[a], a, b, prev[b], prev[prev[b]], ..., v]\n   \
    \ std::pair<int, std::pair<int, int>> Solve(int v) {\n        assert(0 <= v and\
    \ v < V);\n        dist.assign(V, INF);\n        prev.assign(V, -1);\n       \
    \ orig.assign(V, -1);\n        std::vector<int> root_weight(V, INF);\n       \
    \ std::deque<int> bfsq;\n        for (auto [nxt, weight] : to[v]) {\n        \
    \    if (weight >= dist[nxt]) continue;\n            dist[nxt] = weight;\n   \
    \         root_weight[nxt] = weight;\n            prev[nxt] = v;\n           \
    \ orig[nxt] = nxt;\n            if (weight)\n                bfsq.emplace_back(nxt);\n\
    \            else\n                bfsq.emplace_front(nxt);\n        }\n     \
    \   int minimum_cycle = INF;\n        int source_a = -1, source_b = -1;\n    \
    \    while (!bfsq.empty()) {\n            int now = bfsq.front();\n          \
    \  bfsq.pop_front();\n            for (auto [nxt, weight] : to[now]) {\n     \
    \           if (nxt == v) continue;\n                if (orig[nxt] >= 0 and orig[now]\
    \ != orig[nxt]) {\n                    int length = dist[now] + dist[nxt] + weight;\n\
    \                    if (length < minimum_cycle) {\n                        minimum_cycle\
    \ = length;\n                        source_a = orig[now], source_b = orig[nxt];\n\
    \                    }\n                }\n                int dnext = dist[now]\
    \ + weight;\n                if (dnext < dist[nxt]) {\n                    dist[nxt]\
    \ = dnext;\n                    prev[nxt] = now;\n                    orig[nxt]\
    \ = orig[now];\n                    if (weight)\n                        bfsq.emplace_back(nxt);\n\
    \                    else\n                        bfsq.emplace_front(nxt);\n\
    \                }\n            }\n        }\n        if (source_a < 0) return\
    \ std::make_pair(INF, std::make_pair(-1, -1));\n\n        std::vector<int> path_dist(V,\
    \ INF), path_prev(V, -1);\n        path_dist[source_a] = 0;\n        bfsq = {source_a};\n\
    \        while (!bfsq.empty()) {\n            int now = bfsq.front();\n      \
    \      bfsq.pop_front();\n            for (auto [nxt, weight] : to[now]) {\n \
    \               if (nxt == v) continue;\n                int dnext = path_dist[now]\
    \ + weight;\n                if (dnext < path_dist[nxt]) {\n                 \
    \   path_dist[nxt] = dnext;\n                    path_prev[nxt] = now;\n     \
    \               if (weight)\n                        bfsq.emplace_back(nxt);\n\
    \                    else\n                        bfsq.emplace_front(nxt);\n\
    \                }\n            }\n        }\n        std::vector<int> path;\n\
    \        for (int x = source_b; x >= 0; x = path_prev[x]) {\n            path.push_back(x);\n\
    \            if (x == source_a) break;\n        }\n        std::reverse(path.begin(),\
    \ path.end());\n        int split = (path.size() - 1) / 2;\n        prev[path.front()]\
    \ = v;\n        orig[path.front()] = path.front();\n        dist[path.front()]\
    \ = root_weight[path.front()];\n        for (int i = 1; i <= split; i++) {\n \
    \           prev[path[i]] = path[i - 1];\n            orig[path[i]] = path.front();\n\
    \        }\n        prev[path.back()] = v;\n        orig[path.back()] = path.back();\n\
    \        dist[path.back()] = root_weight[path.back()];\n        for (int i = path.size()\
    \ - 2; i > split; i--) {\n            prev[path[i]] = path[i + 1];\n         \
    \   orig[path[i]] = path.back();\n        }\n        minimum_cycle = root_weight[source_a]\
    \ + path_dist[source_b] + root_weight[source_b];\n        return std::make_pair(minimum_cycle,\
    \ std::make_pair(path[split], path[split + 1]));\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <deque>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\n// Shortest cycle\
    \ detection of UNDIRECTED SIMPLE graphs based on 01-BFS\n// Assumption: only two\
    \ types of edges are permitted: weight = 0 or W ( > 0)\n// Complexity: O(E)\n\
    // Verified: https://codeforces.com/contest/1325/problem/E https://codeforces.com/contest/1817/problem/B\n\
    struct ShortestCycle01 {\n    static constexpr int INF = std::numeric_limits<int>::max()\
    \ / 2;\n    int V, E;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> to; // (nxt, weight)\n    ShortestCycle01() = default;\n    ShortestCycle01(int\
    \ V) : V(V), E(0), to(V) {}\n    void add_edge(int s, int t, int len) {\n    \
    \    assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n        assert(len\
    \ >= 0);\n        to[s].emplace_back(t, len);\n        to[t].emplace_back(s, len);\n\
    \        E++;\n    }\n\n    std::vector<int> dist;\n    std::vector<int> prev;\n\
    \    std::vector<int> orig;\n    // Find minimum length simple cycle which passes\
    \ vertex `v`\n    // - return: (LEN, (a, b))\n    //   - LEN: length of the shortest\
    \ cycles if exists, INF otherwise.\n    //   - the cycle consists of vertices\
    \ [v, ..., prev[prev[a]], prev[a], a, b, prev[b], prev[prev[b]], ..., v]\n   \
    \ std::pair<int, std::pair<int, int>> Solve(int v) {\n        assert(0 <= v and\
    \ v < V);\n        dist.assign(V, INF);\n        prev.assign(V, -1);\n       \
    \ orig.assign(V, -1);\n        std::vector<int> root_weight(V, INF);\n       \
    \ std::deque<int> bfsq;\n        for (auto [nxt, weight] : to[v]) {\n        \
    \    if (weight >= dist[nxt]) continue;\n            dist[nxt] = weight;\n   \
    \         root_weight[nxt] = weight;\n            prev[nxt] = v;\n           \
    \ orig[nxt] = nxt;\n            if (weight)\n                bfsq.emplace_back(nxt);\n\
    \            else\n                bfsq.emplace_front(nxt);\n        }\n     \
    \   int minimum_cycle = INF;\n        int source_a = -1, source_b = -1;\n    \
    \    while (!bfsq.empty()) {\n            int now = bfsq.front();\n          \
    \  bfsq.pop_front();\n            for (auto [nxt, weight] : to[now]) {\n     \
    \           if (nxt == v) continue;\n                if (orig[nxt] >= 0 and orig[now]\
    \ != orig[nxt]) {\n                    int length = dist[now] + dist[nxt] + weight;\n\
    \                    if (length < minimum_cycle) {\n                        minimum_cycle\
    \ = length;\n                        source_a = orig[now], source_b = orig[nxt];\n\
    \                    }\n                }\n                int dnext = dist[now]\
    \ + weight;\n                if (dnext < dist[nxt]) {\n                    dist[nxt]\
    \ = dnext;\n                    prev[nxt] = now;\n                    orig[nxt]\
    \ = orig[now];\n                    if (weight)\n                        bfsq.emplace_back(nxt);\n\
    \                    else\n                        bfsq.emplace_front(nxt);\n\
    \                }\n            }\n        }\n        if (source_a < 0) return\
    \ std::make_pair(INF, std::make_pair(-1, -1));\n\n        std::vector<int> path_dist(V,\
    \ INF), path_prev(V, -1);\n        path_dist[source_a] = 0;\n        bfsq = {source_a};\n\
    \        while (!bfsq.empty()) {\n            int now = bfsq.front();\n      \
    \      bfsq.pop_front();\n            for (auto [nxt, weight] : to[now]) {\n \
    \               if (nxt == v) continue;\n                int dnext = path_dist[now]\
    \ + weight;\n                if (dnext < path_dist[nxt]) {\n                 \
    \   path_dist[nxt] = dnext;\n                    path_prev[nxt] = now;\n     \
    \               if (weight)\n                        bfsq.emplace_back(nxt);\n\
    \                    else\n                        bfsq.emplace_front(nxt);\n\
    \                }\n            }\n        }\n        std::vector<int> path;\n\
    \        for (int x = source_b; x >= 0; x = path_prev[x]) {\n            path.push_back(x);\n\
    \            if (x == source_a) break;\n        }\n        std::reverse(path.begin(),\
    \ path.end());\n        int split = (path.size() - 1) / 2;\n        prev[path.front()]\
    \ = v;\n        orig[path.front()] = path.front();\n        dist[path.front()]\
    \ = root_weight[path.front()];\n        for (int i = 1; i <= split; i++) {\n \
    \           prev[path[i]] = path[i - 1];\n            orig[path[i]] = path.front();\n\
    \        }\n        prev[path.back()] = v;\n        orig[path.back()] = path.back();\n\
    \        dist[path.back()] = root_weight[path.back()];\n        for (int i = path.size()\
    \ - 2; i > split; i--) {\n            prev[path[i]] = path[i + 1];\n         \
    \   orig[path[i]] = path.back();\n        }\n        minimum_cycle = root_weight[source_a]\
    \ + path_dist[source_b] + root_weight[source_b];\n        return std::make_pair(minimum_cycle,\
    \ std::make_pair(path[split], path[split + 1]));\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_cycle01.hpp
  requiredBy: []
  timestamp: '2026-09-05 15:18:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/shortest_cycle01.hpp
layout: document
redirect_from:
- /library/graph/shortest_cycle01.hpp
- /library/graph/shortest_cycle01.hpp.html
title: graph/shortest_cycle01.hpp
---
