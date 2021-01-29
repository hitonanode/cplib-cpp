---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/dijkstra.test.cpp
    title: graph/test/dijkstra.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/dijkstra.hpp\"\n#include <queue>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\nusing wedges = vector<vector<pair<long\
    \ long, long long>>>; // (to, weight)\n\nconstexpr long long int INF = 1e17;\n\
    pair<vector<long long int>, vector<int>> dijkstra(int N, int s, const wedges &w)\
    \ {\n    using lint = long long;\n    using plint = pair<long long, long long>;\n\
    \    vector<lint> dist(N, INF);\n    dist[s] = 0;\n    vector<int> prev(N, -1);\n\
    \    priority_queue<plint, vector<plint>, greater<plint>> pq;\n    pq.emplace(0,\
    \ s);\n    while (!pq.empty()) {\n        plint p = pq.top();\n        pq.pop();\n\
    \        int v = p.second;\n        if (dist[v] < p.first) continue;\n       \
    \ for (auto nx : w[v]) {\n            lint dnx = p.first + nx.second;\n      \
    \      if (dist[nx.first] > dnx) {\n                dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                pq.emplace(dnx, nx.first);\n            }\n        }\n\
    \    }\n    return make_pair(dist, prev); // (distance, previous_node)\n}\n"
  code: "#pragma once\n#include <queue>\n#include <utility>\n#include <vector>\nusing\
    \ namespace std;\n\nusing wedges = vector<vector<pair<long long, long long>>>;\
    \ // (to, weight)\n\nconstexpr long long int INF = 1e17;\npair<vector<long long\
    \ int>, vector<int>> dijkstra(int N, int s, const wedges &w) {\n    using lint\
    \ = long long;\n    using plint = pair<long long, long long>;\n    vector<lint>\
    \ dist(N, INF);\n    dist[s] = 0;\n    vector<int> prev(N, -1);\n    priority_queue<plint,\
    \ vector<plint>, greater<plint>> pq;\n    pq.emplace(0, s);\n    while (!pq.empty())\
    \ {\n        plint p = pq.top();\n        pq.pop();\n        int v = p.second;\n\
    \        if (dist[v] < p.first) continue;\n        for (auto nx : w[v]) {\n  \
    \          lint dnx = p.first + nx.second;\n            if (dist[nx.first] > dnx)\
    \ {\n                dist[nx.first] = dnx, prev[nx.first] = v;\n             \
    \   pq.emplace(dnx, nx.first);\n            }\n        }\n    }\n    return make_pair(dist,\
    \ prev); // (distance, previous_node)\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2020-11-21 18:08:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/dijkstra.test.cpp
documentation_of: graph/dijkstra.hpp
layout: document
redirect_from:
- /library/graph/dijkstra.hpp
- /library/graph/dijkstra.hpp.html
title: graph/dijkstra.hpp
---
