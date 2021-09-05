---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "#line 2 \"graph/shortest_path.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <deque>\n#include <fstream>\n#include <functional>\n#include\
    \ <limits>\n#include <queue>\n#include <string>\n#include <utility>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <typename T, T INF = std::numeric_limits<T>::max()\
    \ / 2, int INVALID = -1> struct ShortestPath {\n    int V, E;\n    bool single_positive_weight;\n\
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
    \        }\n    }\n\n    // Dijkstra algorithm, O(V^2 + E)\n    void DijkstraVquad(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, INF);\n    \
    \    dist[s] = 0;\n        prev.assign(V, INVALID);\n        std::vector<char>\
    \ fixed(V, false);\n        while (true) {\n            int r = INVALID;\n   \
    \         T dr = INF;\n            for (int i = 0; i < V; i++) {\n           \
    \     if (!fixed[i] and dist[i] < dr) r = i, dr = dist[i];\n            }\n  \
    \          if (r == INVALID) break;\n            fixed[r] = true;\n          \
    \  int nxt;\n            T dx;\n            for (auto p : to[r]) {\n         \
    \       std::tie(nxt, dx) = p;\n                if (dist[nxt] > dist[r] + dx)\
    \ dist[nxt] = dist[r] + dx, prev[nxt] = r;\n            }\n        }\n    }\n\n\
    \    // Bellman-Ford algorithm\n    // Complexity: O(VE)\n    bool BellmanFord(int\
    \ s, int nb_loop) {\n        assert(0 <= s and s < V);\n        dist.assign(V,\
    \ INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n        for (int l = 0;\
    \ l < nb_loop; l++) {\n            bool upd = false;\n            for (int v =\
    \ 0; v < V; v++) {\n                if (dist[v] == INF) continue;\n          \
    \      for (auto nx : to[v]) {\n                    T dnx = dist[v] + nx.second;\n\
    \                    if (dist[nx.first] > dnx) dist[nx.first] = dnx, prev[nx.first]\
    \ = v, upd = true;\n                }\n            }\n            if (!upd) return\
    \ true;\n        }\n        return false;\n    }\n\n    // Bellman-ford algorithm\
    \ using queue (deque)\n    // Complexity: O(VE)\n    // Requirement: no negative\
    \ loop\n    void SPFA(int s) {\n        assert(0 <= s and s < V);\n        dist.assign(V,\
    \ INF);\n        prev.assign(V, INVALID);\n        std::deque<int> q;\n      \
    \  std::vector<char> in_queue(V);\n        dist[s] = 0;\n        q.push_back(s),\
    \ in_queue[s] = 1;\n        while (!q.empty()) {\n            int now = q.front();\n\
    \            q.pop_front(), in_queue[now] = 0;\n            for (auto nx : to[now])\
    \ {\n                T dnx = dist[now] + nx.second;\n                int nxt =\
    \ nx.first;\n                if (dist[nxt] > dnx) {\n                    dist[nxt]\
    \ = dnx;\n                    if (!in_queue[nxt]) {\n                        if\
    \ (q.size() and dnx < dist[q.front()]) { // Small label first optimization\n \
    \                           q.push_front(nxt);\n                        } else\
    \ {\n                            q.push_back(nxt);\n                        }\n\
    \                        prev[nxt] = now, in_queue[nxt] = 1;\n               \
    \     }\n                }\n            }\n        }\n    }\n\n    void ZeroOneBFS(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, INF), prev.assign(V,\
    \ INVALID);\n        dist[s] = 0;\n        std::deque<int> que;\n        que.push_back(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop_front();\n            for (auto nx : to[v]) {\n                T dnx\
    \ = dist[v] + nx.second;\n                if (dist[nx.first] > dnx) {\n      \
    \              dist[nx.first] = dnx, prev[nx.first] = v;\n                   \
    \ if (nx.second) {\n                        que.push_back(nx.first);\n       \
    \             } else {\n                        que.push_front(nx.first);\n  \
    \                  }\n                }\n            }\n        }\n    }\n\n \
    \   bool dag_solver(int s) {\n        assert(0 <= s and s < V);\n        std::vector<int>\
    \ indeg(V, 0);\n        std::queue<int> que;\n        que.push(s);\n        while\
    \ (que.size()) {\n            int now = que.front();\n            que.pop();\n\
    \            for (auto nx : to[now]) {\n                indeg[nx.first]++;\n \
    \               if (indeg[nx.first] == 1) que.push(nx.first);\n            }\n\
    \        }\n        dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s]\
    \ = 0;\n        que.push(s);\n        while (que.size()) {\n            int now\
    \ = que.front();\n            que.pop();\n            for (auto nx : to[now])\
    \ {\n                indeg[nx.first]--;\n                if (dist[nx.first] >\
    \ dist[now] + nx.second)\n                    dist[nx.first] = dist[now] + nx.second,\
    \ prev[nx.first] = now;\n                if (indeg[nx.first] == 0) que.push(nx.first);\n\
    \            }\n        }\n        return *max_element(indeg.begin(), indeg.end())\
    \ == 0;\n    }\n\n    // Retrieve a sequence of vertex ids that represents shortest\
    \ path [s, ..., goal]\n    // If not reachable to goal, return {}\n    std::vector<int>\
    \ retrieve_path(int goal) const {\n        assert(int(prev.size()) == V);\n  \
    \      assert(0 <= goal and goal < V);\n        if (dist[goal] == INF) return\
    \ {};\n        std::vector<int> ret{goal};\n        while (prev[goal] != INVALID)\
    \ {\n            goal = prev[goal];\n            ret.push_back(goal);\n      \
    \  }\n        std::reverse(ret.begin(), ret.end());\n        return ret;\n   \
    \ }\n\n    void solve(int s) {\n        if (wmin >= 0) {\n            if (single_positive_weight)\
    \ {\n                ZeroOneBFS(s);\n            } else {\n                if\
    \ ((long long)V * V < (E << 4)) {\n                    DijkstraVquad(s);\n   \
    \             } else {\n                    Dijkstra(s);\n                }\n\
    \            }\n        } else {\n            BellmanFord(s, V);\n        }\n\
    \    }\n\n    // Warshall-Floyd algorithm\n    // Complexity: O(E + V^3)\n   \
    \ std::vector<std::vector<T>> dist2d;\n    void WarshallFloyd() {\n        dist2d.assign(V,\
    \ std::vector<T>(V, INF));\n        for (int i = 0; i < V; i++) {\n          \
    \  dist2d[i][i] = 0;\n            for (auto p : to[i]) dist2d[i][p.first] = std::min(dist2d[i][p.first],\
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
    \    }\n};\n#line 3 \"graph/test/shortest_path.test.cpp\"\n#include <iostream>\n\
    #line 5 \"graph/test/shortest_path.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\
    \nusing namespace std;\n\nint main() {\n    int N, M, s, t;\n    cin >> N >> M\
    \ >> s >> t;\n    constexpr long long INF = 1LL << 60;\n    ShortestPath<long\
    \ long, INF> graph(N);\n    while (M--) {\n        int a, b, c;\n        cin >>\
    \ a >> b >> c;\n        graph.add_edge(a, b, c);\n    }\n\n    graph.solve(s);\n\
    \n    if (graph.dist[t] == INF) {\n        cout << \"-1\\n\";\n        return\
    \ 0;\n    }\n\n    vector<int> path;\n    int now = t;\n    while (true) {\n \
    \       path.push_back(now);\n        if (now == s) break;\n        now = graph.prev[now];\n\
    \    }\n    std::reverse(path.begin(), path.end());\n    cout << graph.dist[t]\
    \ << ' ' << path.size() - 1 << '\\n';\n    for (unsigned i = 0; i + 1 < path.size();\
    \ i++) cout << path[i] << ' ' << path[i + 1] << '\\n';\n}\n"
  code: "#include \"../shortest_path.hpp\"\n#include <algorithm>\n#include <iostream>\n\
    #include <vector>\n#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\
    \nusing namespace std;\n\nint main() {\n    int N, M, s, t;\n    cin >> N >> M\
    \ >> s >> t;\n    constexpr long long INF = 1LL << 60;\n    ShortestPath<long\
    \ long, INF> graph(N);\n    while (M--) {\n        int a, b, c;\n        cin >>\
    \ a >> b >> c;\n        graph.add_edge(a, b, c);\n    }\n\n    graph.solve(s);\n\
    \n    if (graph.dist[t] == INF) {\n        cout << \"-1\\n\";\n        return\
    \ 0;\n    }\n\n    vector<int> path;\n    int now = t;\n    while (true) {\n \
    \       path.push_back(now);\n        if (now == s) break;\n        now = graph.prev[now];\n\
    \    }\n    std::reverse(path.begin(), path.end());\n    cout << graph.dist[t]\
    \ << ' ' << path.size() - 1 << '\\n';\n    for (unsigned i = 0; i + 1 < path.size();\
    \ i++) cout << path[i] << ' ' << path[i + 1] << '\\n';\n}\n"
  dependsOn:
  - graph/shortest_path.hpp
  isVerificationFile: true
  path: graph/test/shortest_path.test.cpp
  requiredBy: []
  timestamp: '2021-08-28 00:57:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/shortest_path.test.cpp
layout: document
redirect_from:
- /verify/graph/test/shortest_path.test.cpp
- /verify/graph/test/shortest_path.test.cpp.html
title: graph/test/shortest_path.test.cpp
---
