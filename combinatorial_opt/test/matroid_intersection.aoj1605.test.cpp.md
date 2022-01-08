---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/matroid_intersection.hpp
    title: "(Weighted) matroid intersection \uFF08\uFF08\u91CD\u307F\u3064\u304D\uFF09\
      \u30DE\u30C8\u30ED\u30A4\u30C9\u4EA4\u53C9\uFF09"
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/matroids/graphic_matroid.hpp
    title: "Graphic matroid \uFF08\u30B0\u30E9\u30D5\u30DE\u30C8\u30ED\u30A4\u30C9\
      \uFF09"
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/matroids/partition_matroid.hpp
    title: "Partition matroid \uFF08\u5206\u5272\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
  - icon: ':question:'
    path: graph/shortest_path.hpp
    title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605
  bundledCode: "#line 1 \"combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605\"\
    \n#line 2 \"graph/shortest_path.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <deque>\n#include <fstream>\n#include <functional>\n#include <limits>\n\
    #include <queue>\n#include <string>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\ntemplate <typename T, T INF = std::numeric_limits<T>::max() / 2,\
    \ int INVALID = -1>\nstruct ShortestPath {\n    int V, E;\n    bool single_positive_weight;\n\
    \    T wmin, wmax;\n    std::vector<std::vector<std::pair<int, T>>> to;\n\n  \
    \  ShortestPath(int V = 0) : V(V), E(0), single_positive_weight(true), wmin(0),\
    \ wmax(0), to(V) {}\n    void add_edge(int s, int t, T w) {\n        assert(0\
    \ <= s and s < V);\n        assert(0 <= t and t < V);\n        to[s].emplace_back(t,\
    \ w);\n        E++;\n        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight\
    \ = false;\n        wmin = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n\
    \    }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\n    // Dijkstra\
    \ algorithm\n    // Complexity: O(E log E)\n    using Pque = std::priority_queue<std::pair<T,\
    \ int>, std::vector<std::pair<T, int>>,\n                                    \
    \ std::greater<std::pair<T, int>>>;\n    template <class Heap = Pque> void Dijkstra(int\
    \ s) {\n        assert(0 <= s and s < V);\n        dist.assign(V, INF);\n    \
    \    dist[s] = 0;\n        prev.assign(V, INVALID);\n        Heap pq;\n      \
    \  pq.emplace(0, s);\n        while (!pq.empty()) {\n            T d;\n      \
    \      int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
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
    \ to[i])\n                ss << i << \"->\" << e.first << \"[label=\" << e.second\
    \ << \"];\\n\";\n        }\n        ss << \"}\\n\";\n        ss.close();\n   \
    \     return;\n    }\n};\n#line 5 \"combinatorial_opt/matroid_intersection.hpp\"\
    \n\n// CUT begin\n// (Min weight) matroid intersection solver\n// Algorithm based\
    \ on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/\n// Complexity: O(CE^2\
    \ + E^3) (C : circuit query, non-weighted)\ntemplate <class M1, class M2, class\
    \ T = int>\nstd::vector<bool> MatroidIntersection(M1 matroid1, M2 matroid2, std::vector<T>\
    \ weights = {}) {\n    using State = std::vector<bool>;\n    using Element = int;\n\
    \    assert(matroid1.size() == matroid2.size());\n    const int M = matroid1.size();\n\
    \n    for (auto &x : weights) x *= M + 1;\n    if (weights.empty()) weights.assign(M,\
    \ 0);\n\n    const Element gs = M, gt = M + 1;\n    State I(M);\n\n    while (true)\
    \ {\n        ShortestPath<T> sssp(M + 2);\n        matroid1.set(I);\n        matroid2.set(I);\n\
    \        for (int e = 0; e < M; e++) {\n            if (I[e]) continue;\n    \
    \        auto c1 = matroid1.circuit(e), c2 = matroid2.circuit(e);\n          \
    \  if (c1.empty()) sssp.add_edge(e, gt, 0);\n            for (Element f : c1)\
    \ {\n                if (f != e) sssp.add_edge(e, f, -weights[f] + 1);\n     \
    \       }\n            if (c2.empty()) sssp.add_edge(gs, e, weights[e] + 1);\n\
    \            for (Element f : c2) {\n                if (f != e) sssp.add_edge(f,\
    \ e, weights[e] + 1);\n            }\n        }\n        sssp.solve(gs);\n   \
    \     auto aug_path = sssp.retrieve_path(gt);\n        if (aug_path.empty()) break;\n\
    \        for (auto e : aug_path) {\n            if (e != gs and e != gt) I[e]\
    \ = !I[e];\n        }\n    }\n    return I;\n}\n#line 5 \"combinatorial_opt/matroids/graphic_matroid.hpp\"\
    \n\n// GraphicMatroid: subgraph of undirected graphs, without loops\nclass GraphicMatroid\
    \ {\n    using Vertex = int;\n    using Element = int;\n    int M;\n    int V;\
    \ // # of vertices of graph\n    std::vector<std::vector<std::pair<Vertex, Element>>>\
    \ to;\n    std::vector<std::pair<Vertex, Vertex>> edges;\n    std::vector<Element>\
    \ backtrack;\n    std::vector<Vertex> vprev;\n    std::vector<int> depth, root;\n\
    \npublic:\n    GraphicMatroid(int V, const std::vector<std::pair<Vertex, Vertex>>\
    \ &edges_)\n        : M(edges_.size()), V(V), to(V), edges(edges_) {\n       \
    \ for (int e = 0; e < int(edges_.size()); e++) {\n            int u = edges_[e].first,\
    \ v = edges_[e].second;\n            assert(0 <= u and u < V);\n            assert(0\
    \ <= v and v < V);\n            if (u != v) {\n                to[u].emplace_back(v,\
    \ e);\n                to[v].emplace_back(u, e);\n            }\n        }\n \
    \   }\n    int size() const { return M; }\n\n    std::vector<Vertex> que;\n  \
    \  template <class State> void set(State I) {\n        assert(int(I.size()) ==\
    \ M);\n        backtrack.assign(V, -1);\n        vprev.assign(V, -1);\n      \
    \  depth.assign(V, -1);\n        root.assign(V, -1);\n        que.resize(V);\n\
    \        int qb = 0, qe = 0;\n        for (Vertex i = 0; i < V; i++) {\n     \
    \       if (backtrack[i] >= 0) continue;\n            que[qb = 0] = i, qe = 1,\
    \ depth[i] = 0;\n            while (qb < qe) {\n                Vertex now = que[qb++];\n\
    \                root[now] = i;\n                for (auto nxt : to[now]) {\n\
    \                    if (depth[nxt.first] < 0 and I[nxt.second]) {\n         \
    \               backtrack[nxt.first] = nxt.second;\n                        vprev[nxt.first]\
    \ = now;\n                        depth[nxt.first] = depth[now] + 1;\n       \
    \                 que[qe++] = nxt.first;\n                    }\n            \
    \    }\n            }\n        }\n    }\n\n    std::vector<Element> circuit(const\
    \ Element e) const {\n        assert(0 <= e and e < M);\n        Vertex s = edges[e].first,\
    \ t = edges[e].second;\n        if (root[s] != root[t]) return {};\n        std::vector<Element>\
    \ ret{e};\n        auto step = [&](Vertex &i) { ret.push_back(backtrack[i]), i\
    \ = vprev[i]; };\n        int ddepth = depth[s] - depth[t];\n        for (; ddepth\
    \ > 0; --ddepth) step(s);\n        for (; ddepth < 0; ++ddepth) step(t);\n   \
    \     while (s != t) step(s), step(t);\n        return ret;\n    }\n};\n#line\
    \ 4 \"combinatorial_opt/matroids/partition_matroid.hpp\"\n\n// Partition matroid\
    \ (partitional matroid) : direct sum of uniform matroids\nclass PartitionMatroid\
    \ {\n    using Element = int;\n    int M;\n    std::vector<std::vector<Element>>\
    \ parts;\n    std::vector<int> belong;\n    std::vector<int> R;\n    std::vector<int>\
    \ cnt;\n    std::vector<std::vector<Element>> circuits;\n\npublic:\n    // parts:\
    \ partition of [0, 1, ..., M - 1]\n    // R: only R[i] elements from parts[i]\
    \ can be chosen for each i.\n    PartitionMatroid(int M, const std::vector<std::vector<int>>\
    \ &parts_, const std::vector<int> &R_)\n        : M(M), parts(parts_), belong(M,\
    \ -1), R(R_) {\n        assert(parts.size() == R.size());\n        for (int i\
    \ = 0; i < int(parts.size()); i++) {\n            for (Element e : parts[i]) belong[e]\
    \ = i;\n        }\n        for (Element e = 0; e < M; e++) {\n            // assert(belong[e]\
    \ != -1);\n            if (belong[e] == -1) {\n                belong[e] = parts.size();\n\
    \                parts.push_back({e});\n                R.push_back(1);\n    \
    \        }\n        }\n    }\n    int size() const { return M; }\n\n    template\
    \ <class State> void set(const State &I) {\n        cnt = R;\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) cnt[belong[e]]--;\n        }\n \
    \       circuits.assign(cnt.size(), {});\n        for (int e = 0; e < M; e++)\
    \ {\n            if (I[e] and cnt[belong[e]] == 0) circuits[belong[e]].push_back(e);\n\
    \        }\n    }\n\n    std::vector<Element> circuit(const Element e) const {\n\
    \        assert(0 <= e and e < M);\n        int p = belong[e];\n        if (cnt[p]\
    \ == 0) {\n            auto ret = circuits[p];\n            ret.push_back(e);\n\
    \            return ret;\n        }\n        return {};\n    }\n};\n#line 5 \"\
    combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp\"\n#include <iostream>\n\
    #include <numeric>\n#line 9 \"combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \    while (true) {\n        int N, M, K;\n        cin >> N >> M >> K;\n     \
    \   if (N == 0) break;\n        vector<vector<int>> partition(2);\n        vector<int>\
    \ R{K, N - 1 - K};\n        vector<pair<int, int>> edges;\n        vector<int>\
    \ weights;\n        for (int e = 0; e < M; ++e) {\n            int u, v, w;\n\
    \            char l;\n            cin >> u >> v >> w >> l;\n            --u, --v;\n\
    \            partition[l == 'B'].push_back(e);\n            edges.emplace_back(u,\
    \ v);\n            weights.push_back(w);\n        }\n        PartitionMatroid\
    \ M1(edges.size(), partition, R);\n        GraphicMatroid M2(N, edges);\n    \
    \    vector<bool> ret = MatroidIntersection(M1, M2, weights);\n        int ne\
    \ = accumulate(ret.begin(), ret.end(), 0);\n        if (ne < N - 1) {\n      \
    \      cout << \"-1\\n\";\n        } else {\n            int sum = 0;\n      \
    \      for (int e = 0; e < M; ++e) sum += ret[e] * weights[e];\n            cout\
    \ << sum << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605\"\
    \n#include \"../matroid_intersection.hpp\"\n#include \"../matroids/graphic_matroid.hpp\"\
    \n#include \"../matroids/partition_matroid.hpp\"\n#include <iostream>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    while\
    \ (true) {\n        int N, M, K;\n        cin >> N >> M >> K;\n        if (N ==\
    \ 0) break;\n        vector<vector<int>> partition(2);\n        vector<int> R{K,\
    \ N - 1 - K};\n        vector<pair<int, int>> edges;\n        vector<int> weights;\n\
    \        for (int e = 0; e < M; ++e) {\n            int u, v, w;\n           \
    \ char l;\n            cin >> u >> v >> w >> l;\n            --u, --v;\n     \
    \       partition[l == 'B'].push_back(e);\n            edges.emplace_back(u, v);\n\
    \            weights.push_back(w);\n        }\n        PartitionMatroid M1(edges.size(),\
    \ partition, R);\n        GraphicMatroid M2(N, edges);\n        vector<bool> ret\
    \ = MatroidIntersection(M1, M2, weights);\n        int ne = accumulate(ret.begin(),\
    \ ret.end(), 0);\n        if (ne < N - 1) {\n            cout << \"-1\\n\";\n\
    \        } else {\n            int sum = 0;\n            for (int e = 0; e < M;\
    \ ++e) sum += ret[e] * weights[e];\n            cout << sum << '\\n';\n      \
    \  }\n    }\n}\n"
  dependsOn:
  - combinatorial_opt/matroid_intersection.hpp
  - graph/shortest_path.hpp
  - combinatorial_opt/matroids/graphic_matroid.hpp
  - combinatorial_opt/matroids/partition_matroid.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
- /verify/combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp.html
title: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
---
