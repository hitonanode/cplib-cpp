---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: graph/bellman_ford.hpp
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: graph/shortest_path.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B
  bundledCode: "#line 2 \"graph/bellman_ford.hpp\"\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\nusing wedges = vector<vector<pair<long long\
    \ int, long long int>>>; // (to, weight)\nconstexpr long long int INF = 1e17;\n\
    vector<long long int> bellman_ford(int s, const wedges &w, int T)\n{\n    int\
    \ N = w.size();\n    vector<long long int> d(N, INF);\n    d[s] = 0;\n    for(int\
    \ l = 0; l < T; l++) {\n        bool upd = false;\n        for (int i = 0; i <\
    \ N; i++)\n        {\n            if (d[i] >= INF) continue;\n            for\
    \ (auto pa : w[i]) {\n                if (d[pa.first] > d[i] + pa.second) {\n\
    \                    d[pa.first] = d[i] + pa.second;\n                    upd\
    \ = true;\n                }\n            }\n        }\n        if (!upd) break;\n\
    \    }\n    return d;\n}\n#line 2 \"graph/shortest_path.hpp\"\n#include <cassert>\n\
    #include <deque>\n#include <functional>\n#include <limits>\n#include <queue>\n\
    #line 9 \"graph/shortest_path.hpp\"\n\n// CUT begin\ntemplate<typename T>\nstruct\
    \ ShortestPath\n{\n    int V, E;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
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
    \ + dist2d[k][j]);\n                }\n            }\n        }\n    }\n};\n#line\
    \ 3 \"graph/test/bellman_ford.test.cpp\"\n#include <iostream>\n#line 5 \"graph/test/bellman_ford.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B\"\
    \n\nwedges e;\n\nint main() {\n    int V, E, r;\n    cin >> V >> E >> r;\n   \
    \ ShortestPath<long long int> graph(V);\n    e.resize(V);\n    for (int i = 0;\
    \ i < E; i++) {\n        int s, t, d;\n        cin >> s >> t >> d;\n        e[s].emplace_back(t,\
    \ d);\n        graph.add_edge(s, t, d);\n    }\n    vector<long long int> ret\
    \ = bellman_ford(r, e, V);\n\n    if (!graph.BellmanFord(r, V + 1)) {\n      \
    \  puts(\"NEGATIVE CYCLE\");\n        return 0;\n    }\n\n    for (int i = 0;\
    \ i < V; i++) {\n        if (graph.dist[i] >= INF) {\n            assert(ret[i]\
    \ == INF);\n            puts(\"INF\");\n        } else {\n            assert(ret[i]\
    \ == graph.dist[i]);\n            printf(\"%lld\\n\", graph.dist[i]);\n      \
    \  }\n    }\n}\n"
  code: "#include \"graph/bellman_ford.hpp\"\n#include \"graph/shortest_path.hpp\"\
    \n#include <iostream>\n#include <vector>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B\"\
    \n\nwedges e;\n\nint main() {\n    int V, E, r;\n    cin >> V >> E >> r;\n   \
    \ ShortestPath<long long int> graph(V);\n    e.resize(V);\n    for (int i = 0;\
    \ i < E; i++) {\n        int s, t, d;\n        cin >> s >> t >> d;\n        e[s].emplace_back(t,\
    \ d);\n        graph.add_edge(s, t, d);\n    }\n    vector<long long int> ret\
    \ = bellman_ford(r, e, V);\n\n    if (!graph.BellmanFord(r, V + 1)) {\n      \
    \  puts(\"NEGATIVE CYCLE\");\n        return 0;\n    }\n\n    for (int i = 0;\
    \ i < V; i++) {\n        if (graph.dist[i] >= INF) {\n            assert(ret[i]\
    \ == INF);\n            puts(\"INF\");\n        } else {\n            assert(ret[i]\
    \ == graph.dist[i]);\n            printf(\"%lld\\n\", graph.dist[i]);\n      \
    \  }\n    }\n}\n"
  dependsOn:
  - graph/bellman_ford.hpp
  - graph/shortest_path.hpp
  isVerificationFile: true
  path: graph/test/bellman_ford.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/bellman_ford.test.cpp
layout: document
redirect_from:
- /verify/graph/test/bellman_ford.test.cpp
- /verify/graph/test/bellman_ford.test.cpp.html
title: graph/test/bellman_ford.test.cpp
---
