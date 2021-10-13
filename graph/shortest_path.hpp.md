---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: combinatorial_opt/matroid_intersection.hpp
    title: "(Weighted) matroid intersecition \uFF08\uFF08\u91CD\u307F\u3064\u304D\uFF09\
      \u30DE\u30C8\u30ED\u30A4\u30C9\u4EA4\u53C9\uFF09"
  - icon: ':warning:'
    path: combinatorial_opt/matroid_union.hpp
    title: "Matroid union \uFF08\u30DE\u30C8\u30ED\u30A4\u30C9\u306E\u5408\u4F75\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/bellman_ford.test.cpp
    title: graph/test/bellman_ford.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/shortest_cycle.test.cpp
    title: graph/test/shortest_cycle.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/shortest_path.test.cpp
    title: graph/test/shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/shortest_path_dag.test.cpp
    title: graph/test/shortest_path_dag.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/spfa.test.cpp
    title: graph/test/spfa.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/warshallfloyd.test.cpp
    title: graph/test/warshallfloyd.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/frequency_table_of_tree_distance.stress.test.cpp
    title: tree/test/frequency_table_of_tree_distance.stress.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
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
    \ algorithm\n    // Complexity: O(E log E)\n    using Pque = std::priority_queue<std::pair<T,\
    \ int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>>;\n  \
    \  template <class Heap = Pque> void Dijkstra(int s) {\n        assert(0 <= s\
    \ and s < V);\n        dist.assign(V, INF);\n        dist[s] = 0;\n        prev.assign(V,\
    \ INVALID);\n        Heap pq;\n        pq.emplace(0, s);\n        while (!pq.empty())\
    \ {\n            T d;\n            int v;\n            std::tie(d, v) = pq.top();\n\
    \            pq.pop();\n            if (dist[v] < d) continue;\n            for\
    \ (auto nx : to[v]) {\n                T dnx = d + nx.second;\n              \
    \  if (dist[nx.first] > dnx) {\n                    dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                    pq.emplace(dnx, nx.first);\n                }\n  \
    \          }\n        }\n    }\n\n    // Dijkstra algorithm, O(V^2 + E)\n    void\
    \ DijkstraVquad(int s) {\n        assert(0 <= s and s < V);\n        dist.assign(V,\
    \ INF);\n        dist[s] = 0;\n        prev.assign(V, INVALID);\n        std::vector<char>\
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
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <deque>\n\
    #include <fstream>\n#include <functional>\n#include <limits>\n#include <queue>\n\
    #include <string>\n#include <utility>\n#include <vector>\n\n// CUT begin\ntemplate\
    \ <typename T, T INF = std::numeric_limits<T>::max() / 2, int INVALID = -1> struct\
    \ ShortestPath {\n    int V, E;\n    bool single_positive_weight;\n    T wmin,\
    \ wmax;\n    std::vector<std::vector<std::pair<int, T>>> to;\n\n    ShortestPath(int\
    \ V = 0) : V(V), E(0), single_positive_weight(true), wmin(0), wmax(0), to(V) {}\n\
    \    void add_edge(int s, int t, T w) {\n        assert(0 <= s and s < V);\n \
    \       assert(0 <= t and t < V);\n        to[s].emplace_back(t, w);\n       \
    \ E++;\n        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight =\
    \ false;\n        wmin = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n\
    \    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\n    // Dijkstra\
    \ algorithm\n    // Complexity: O(E log E)\n    using Pque = std::priority_queue<std::pair<T,\
    \ int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>>;\n  \
    \  template <class Heap = Pque> void Dijkstra(int s) {\n        assert(0 <= s\
    \ and s < V);\n        dist.assign(V, INF);\n        dist[s] = 0;\n        prev.assign(V,\
    \ INVALID);\n        Heap pq;\n        pq.emplace(0, s);\n        while (!pq.empty())\
    \ {\n            T d;\n            int v;\n            std::tie(d, v) = pq.top();\n\
    \            pq.pop();\n            if (dist[v] < d) continue;\n            for\
    \ (auto nx : to[v]) {\n                T dnx = d + nx.second;\n              \
    \  if (dist[nx.first] > dnx) {\n                    dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                    pq.emplace(dnx, nx.first);\n                }\n  \
    \          }\n        }\n    }\n\n    // Dijkstra algorithm, O(V^2 + E)\n    void\
    \ DijkstraVquad(int s) {\n        assert(0 <= s and s < V);\n        dist.assign(V,\
    \ INF);\n        dist[s] = 0;\n        prev.assign(V, INVALID);\n        std::vector<char>\
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
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_path.hpp
  requiredBy:
  - combinatorial_opt/matroid_union.hpp
  - combinatorial_opt/matroid_intersection.hpp
  timestamp: '2021-09-07 01:07:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/frequency_table_of_tree_distance.stress.test.cpp
  - graph/test/shortest_cycle.test.cpp
  - graph/test/shortest_path_dag.test.cpp
  - graph/test/warshallfloyd.test.cpp
  - graph/test/spfa.test.cpp
  - graph/test/bellman_ford.test.cpp
  - graph/test/shortest_path.test.cpp
documentation_of: graph/shortest_path.hpp
layout: document
title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
---

単一始点最短路問題を解く．`solve(int s)` 関数を用いると以下の要領でアルゴリズムが自動的に選択される．

- 負の重みの辺が存在するならば，Bellman-Ford 法で解く．$O(VE)$
- 全ての辺重みが非負で，非零の辺重みの値が高々一通りならば， 0-1 BFS で解く．$O(V + E)$
- それ以外の場合，Dijkstra 法で解く．$O(V^2 + E)$ または $O(E \log E)$

また，SPFA （$O(VE)$），全点対最短路アルゴリズム（Floyd-Warshall 法，$O(E + V^3)$），DAG用ソルバー（$O(V + E)$）も実装されている．`retrieve_path(int t)` で最短路の復元が，また `dump_graphviz(string filename)` で `.DOT` 形式のグラフ出力が可能．

## 使用方法

```cpp
constexpr long long INF = 1LL << 60;
ShortestPath<long long, INF> graph(N);
while (M--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.add_edge(a, b, c);
}

graph.solve(s);
cout << graph.dist[t] << '\n';

```

## 問題例

- [Library Checker - Shortest Path](https://judge.yosupo.jp/problem/shortest_path)
- [No.1660 Matrix Exponentiation - yukicoder](https://yukicoder.me/problems/no/1660) DAG の場合．
