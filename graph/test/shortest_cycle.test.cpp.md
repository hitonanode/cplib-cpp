---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/shortest_cycle_weighted.hpp
    title: graph/shortest_cycle_weighted.hpp
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
    PROBLEM: https://yukicoder.me/problems/no/1320
    links:
    - https://yukicoder.me/problems/no/1320
  bundledCode: "#line 1 \"graph/test/shortest_cycle.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/1320\"\n\n#line 2 \"graph/shortest_cycle_weighted.hpp\"\
    \n#include <cassert>\n#include <limits>\n#include <queue>\n#include <utility>\n\
    #include <vector>\n\n// Shortest cycle detection of UNDIRECTED SIMPLE graphs\n\
    // Verified: <https://yukicoder.me/submissions/594507>\ntemplate <typename T,\
    \ T INF = std::numeric_limits<T>::max() / 2> struct ShortestCycleOfUndirectedWeighted\
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
    \ std::make_pair(s, t));\n    }\n};\n#line 3 \"graph/shortest_path.hpp\"\n#include\
    \ <deque>\n#include <fstream>\n#include <functional>\n#line 8 \"graph/shortest_path.hpp\"\
    \n#include <string>\n#line 11 \"graph/shortest_path.hpp\"\n\n// CUT begin\ntemplate\
    \ <typename T, T INF = std::numeric_limits<T>::max() / 2, int INVALID = -1> struct\
    \ ShortestPath {\n    int V, E;\n    bool single_positive_weight;\n    T wmin,\
    \ wmax;\n    std::vector<std::vector<std::pair<int, T>>> to;\n\n    ShortestPath(int\
    \ V = 0) : V(V), E(0), single_positive_weight(true), wmin(0), wmax(0), to(V) {}\n\
    \    void add_edge(int s, int t, T w) {\n        assert(0 <= s and s < V);\n \
    \       assert(0 <= t and t < V);\n        to[s].emplace_back(t, w);\n       \
    \ E++;\n        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight =\
    \ false;\n        wmin = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n\
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
    \            for (auto p : to[i]) dist2d[i][p.first] = std::min(dist2d[i][p.first],\
    \ p.second);\n        }\n        for (int k = 0; k < V; k++) {\n            for\
    \ (int i = 0; i < V; i++) {\n                if (dist2d[i][k] == INF) continue;\n\
    \                for (int j = 0; j < V; j++) {\n                    if (dist2d[k][j]\
    \ == INF) continue;\n                    dist2d[i][j] = std::min(dist2d[i][j],\
    \ dist2d[i][k] + dist2d[k][j]);\n                }\n            }\n        }\n\
    \    }\n\n    void dump_graphviz(std::string filename = \"shortest_path\") const\
    \ {\n        std::ofstream ss(filename + \".DOT\");\n        ss << \"digraph{\\\
    n\";\n        for (int i = 0; i < V; i++) {\n            for (const auto &e :\
    \ to[i]) ss << i << \"->\" << e.first << \"[label=\" << e.second << \"];\\n\"\
    ;\n        }\n        ss << \"}\\n\";\n        ss.close();\n        return;\n\
    \    }\n};\n#line 5 \"graph/test/shortest_cycle.test.cpp\"\n\n#include <iostream>\n\
    #line 8 \"graph/test/shortest_cycle.test.cpp\"\nusing namespace std;\n\nint main()\
    \ {\n    int T, N, M;\n    cin >> T >> N >> M;\n    const long long INF = 1LL\
    \ << 60;\n    long long ret = INF;\n\n    if (T == 1) {\n        // Directed graph\n\
    \        vector<vector<pair<int, int>>> to(N);\n        while (M--) {\n      \
    \      int u, v, w;\n            cin >> u >> v >> w;\n            u--, v--;\n\
    \            to[u].emplace_back(v, w);\n        }\n        for (int s = 0; s <\
    \ N; s++) {\n            ShortestPath<long long, INF> graph(N + 1);\n        \
    \    for (int i = 0; i < N; i++) {\n                for (auto [j, w] : to[i])\
    \ {\n                    graph.add_edge(i, j, w);\n                    if (j ==\
    \ s) graph.add_edge(i, N, w);\n                }\n            }\n            graph.solve(s);\n\
    \            ret = min(ret, graph.dist[N]);\n        }\n    } else {\n       \
    \ // Undirected graph\n        ShortestCycleOfUndirectedWeighted<long long, INF>\
    \ graph(N);\n        while (M--) {\n            int u, v, w;\n            cin\
    \ >> u >> v >> w;\n            u--, v--;\n            graph.add_edge(u, v, w);\n\
    \        }\n        for (int i = 0; i < N; i++) ret = min(ret, graph.Solve(i).first);\n\
    \    }\n    cout << (ret < INF ? ret : -1) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1320\"\n\n#include \"\
    ../shortest_cycle_weighted.hpp\"\n#include \"../shortest_path.hpp\"\n\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\n\nint main() {\n    int\
    \ T, N, M;\n    cin >> T >> N >> M;\n    const long long INF = 1LL << 60;\n  \
    \  long long ret = INF;\n\n    if (T == 1) {\n        // Directed graph\n    \
    \    vector<vector<pair<int, int>>> to(N);\n        while (M--) {\n          \
    \  int u, v, w;\n            cin >> u >> v >> w;\n            u--, v--;\n    \
    \        to[u].emplace_back(v, w);\n        }\n        for (int s = 0; s < N;\
    \ s++) {\n            ShortestPath<long long, INF> graph(N + 1);\n           \
    \ for (int i = 0; i < N; i++) {\n                for (auto [j, w] : to[i]) {\n\
    \                    graph.add_edge(i, j, w);\n                    if (j == s)\
    \ graph.add_edge(i, N, w);\n                }\n            }\n            graph.solve(s);\n\
    \            ret = min(ret, graph.dist[N]);\n        }\n    } else {\n       \
    \ // Undirected graph\n        ShortestCycleOfUndirectedWeighted<long long, INF>\
    \ graph(N);\n        while (M--) {\n            int u, v, w;\n            cin\
    \ >> u >> v >> w;\n            u--, v--;\n            graph.add_edge(u, v, w);\n\
    \        }\n        for (int i = 0; i < N; i++) ret = min(ret, graph.Solve(i).first);\n\
    \    }\n    cout << (ret < INF ? ret : -1) << '\\n';\n}\n"
  dependsOn:
  - graph/shortest_cycle_weighted.hpp
  - graph/shortest_path.hpp
  isVerificationFile: true
  path: graph/test/shortest_cycle.test.cpp
  requiredBy: []
  timestamp: '2021-03-14 20:53:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/shortest_cycle.test.cpp
layout: document
redirect_from:
- /verify/graph/test/shortest_cycle.test.cpp
- /verify/graph/test/shortest_cycle.test.cpp.html
title: graph/test/shortest_cycle.test.cpp
---
