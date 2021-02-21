---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: graph/dijkstra.hpp
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: graph/shortest_path.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
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
    \    }\n    return make_pair(dist, prev); // (distance, previous_node)\n}\n#line\
    \ 2 \"graph/shortest_path.hpp\"\n#include <cassert>\n#include <deque>\n#include\
    \ <functional>\n#include <limits>\n#line 9 \"graph/shortest_path.hpp\"\n\n// CUT\
    \ begin\ntemplate <typename T, T INF = std::numeric_limits<T>::max() / 2, int\
    \ INVALID = -1> struct ShortestPath {\n    int V, E;\n    bool single_positive_weight;\n\
    \    T wmin, wmax;\n    std::vector<std::vector<std::pair<int, T>>> to;\n\n  \
    \  ShortestPath(int V = 0) : V(V), E(0), single_positive_weight(true), wmin(0),\
    \ wmax(0), to(V) {}\n    void add_edge(int s, int t, T w) {\n        assert(0\
    \ <= s and s < V);\n        assert(0 <= t and t < V);\n        to[s].emplace_back(t,\
    \ w);\n        E++;\n        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight\
    \ = false;\n        wmin = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n\
    \    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\n    // Dijkstra\
    \ algorithm\n    // Complexity: O(E log E)\n    void Dijkstra(int s) {\n     \
    \   assert(0 <= s and s < V);\n        dist.assign(V, INF);\n        dist[s] =\
    \ 0;\n        prev.assign(V, INVALID);\n        using P = std::pair<T, int>;\n\
    \        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n       \
    \ pq.emplace(0, s);\n        while (!pq.empty()) {\n            T d;\n       \
    \     int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
    \            if (dist[v] < d) continue;\n            for (auto nx : to[v]) {\n\
    \                T dnx = d + nx.second;\n                if (dist[nx.first] >\
    \ dnx) {\n                    dist[nx.first] = dnx, prev[nx.first] = v;\n    \
    \                pq.emplace(dnx, nx.first);\n                }\n            }\n\
    \        }\n    }\n\n    // Bellman-Ford algorithm\n    // Complexity: O(VE)\n\
    \    bool BellmanFord(int s, int nb_loop) {\n        assert(0 <= s and s < V);\n\
    \        dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n\
    \        for (int l = 0; l < nb_loop; l++) {\n            bool upd = false;\n\
    \            for (int v = 0; v < V; v++) {\n                if (dist[v] == INF)\
    \ continue;\n                for (auto nx : to[v]) {\n                    T dnx\
    \ = dist[v] + nx.second;\n                    if (dist[nx.first] > dnx) dist[nx.first]\
    \ = dnx, prev[nx.first] = v, upd = true;\n                }\n            }\n \
    \           if (!upd) return true;\n        }\n        return false;\n    }\n\n\
    \    // Bellman-ford algorithm using queue (deque)\n    // Complexity: O(VE)\n\
    \    // Requirement: no negative loop\n    void SPFA(int s) {\n        assert(0\
    \ <= s and s < V);\n        dist.assign(V, INF);\n        prev.assign(V, INVALID);\n\
    \        std::deque<int> q;\n        std::vector<char> in_queue(V);\n        dist[s]\
    \ = 0;\n        q.push_back(s), in_queue[s] = 1;\n        while (!q.empty()) {\n\
    \            int now = q.front();\n            q.pop_front(), in_queue[now] =\
    \ 0;\n            for (auto nx : to[now]) {\n                T dnx = dist[now]\
    \ + nx.second;\n                int nxt = nx.first;\n                if (dist[nxt]\
    \ > dnx) {\n                    dist[nxt] = dnx;\n                    if (!in_queue[nxt])\
    \ {\n                        if (q.size() and dnx < dist[q.front()]) { // Small\
    \ label first optimization\n                            q.push_front(nxt);\n \
    \                       } else {\n                            q.push_back(nxt);\n\
    \                        }\n                        prev[nxt] = now, in_queue[nxt]\
    \ = 1;\n                    }\n                }\n            }\n        }\n \
    \   }\n\n    void ZeroOneBFS(int s) {\n        assert(0 <= s and s < V);\n   \
    \     dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n  \
    \      std::deque<int> que;\n        que.push_back(s);\n        while (!que.empty())\
    \ {\n            int v = que.front();\n            que.pop_front();\n        \
    \    for (auto nx : to[v]) {\n                T dnx = dist[v] + nx.second;\n \
    \               if (dist[nx.first] > dnx) {\n                    dist[nx.first]\
    \ = dnx, prev[nx.first] = v;\n                    if (nx.second) {\n         \
    \               que.push_back(nx.first);\n                    } else {\n     \
    \                   que.push_front(nx.first);\n                    }\n       \
    \         }\n            }\n        }\n    }\n\n    void solve(int s) {\n    \
    \    if (wmin >= 0) {\n            if (single_positive_weight) {\n           \
    \     ZeroOneBFS(s);\n            } else {\n                Dijkstra(s);\n   \
    \         }\n        } else {\n            BellmanFord(s, V);\n        }\n   \
    \ }\n\n    // Warshall-Floyd algorithm\n    // Complexity: O(E + V^3)\n    std::vector<std::vector<T>>\
    \ dist2d;\n    void WarshallFloyd() {\n        dist2d.assign(V, std::vector<T>(V,\
    \ INF));\n        for (int i = 0; i < V; i++) {\n            dist2d[i][i] = 0;\n\
    \            for (auto p : to[i]) dist2d[i][p.first] = min(dist2d[i][p.first],\
    \ p.second);\n        }\n        for (int k = 0; k < V; k++) {\n            for\
    \ (int i = 0; i < V; i++) {\n                if (dist2d[i][k] = INF) continue;\n\
    \                for (int j = 0; j < V; j++) {\n                    if (dist2d[k][j]\
    \ = INF) continue;\n                    dist2d[i][j] = min(dist2d[i][j], dist2d[i][k]\
    \ + dist2d[k][j]);\n                }\n            }\n        }\n    }\n};\n#line\
    \ 4 \"graph/test/dijkstra.test.cpp\"\n#include <iostream>\n#line 6 \"graph/test/dijkstra.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\
    \n\nwedges e;\n\nint main() {\n    int V, E, r;\n    cin >> V >> E >> r;\n   \
    \ e.resize(V);\n    ShortestPath<int> graph(V);\n    for (int i = 0; i < E; i++)\
    \ {\n        int s, t, d;\n        cin >> s >> t >> d;\n        e[s].emplace_back(t,\
    \ d);\n        graph.add_edge(s, t, d);\n    }\n    auto ret = dijkstra(V, r,\
    \ e);\n    graph.Dijkstra(r);\n\n    for (int i = 0; i < V; i++) {\n        if\
    \ (ret.first[i] == INF)\n            puts(\"INF\");\n        else {\n        \
    \    assert(ret.first[i] == graph.dist[i]);\n            printf(\"%lld\\n\", ret.first[i]);\n\
    \        }\n    }\n}\n"
  code: "#include \"../dijkstra.hpp\"\n#include \"../shortest_path.hpp\"\n#include\
    \ <cassert>\n#include <iostream>\n#include <vector>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A\"\
    \n\nwedges e;\n\nint main() {\n    int V, E, r;\n    cin >> V >> E >> r;\n   \
    \ e.resize(V);\n    ShortestPath<int> graph(V);\n    for (int i = 0; i < E; i++)\
    \ {\n        int s, t, d;\n        cin >> s >> t >> d;\n        e[s].emplace_back(t,\
    \ d);\n        graph.add_edge(s, t, d);\n    }\n    auto ret = dijkstra(V, r,\
    \ e);\n    graph.Dijkstra(r);\n\n    for (int i = 0; i < V; i++) {\n        if\
    \ (ret.first[i] == INF)\n            puts(\"INF\");\n        else {\n        \
    \    assert(ret.first[i] == graph.dist[i]);\n            printf(\"%lld\\n\", ret.first[i]);\n\
    \        }\n    }\n}"
  dependsOn:
  - graph/dijkstra.hpp
  - graph/shortest_path.hpp
  isVerificationFile: true
  path: graph/test/dijkstra.test.cpp
  requiredBy: []
  timestamp: '2021-02-21 14:54:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/dijkstra.test.cpp
layout: document
redirect_from:
- /verify/graph/test/dijkstra.test.cpp
- /verify/graph/test/dijkstra.test.cpp.html
title: graph/test/dijkstra.test.cpp
---
