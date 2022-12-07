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
    PROBLEM: https://yukicoder.me/problems/no/1660
    links:
    - https://yukicoder.me/problems/no/1660
  bundledCode: "#line 1 \"graph/test/shortest_path_dag.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/1660\"\n#line 2 \"graph/shortest_path.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <deque>\n#include <fstream>\n\
    #include <functional>\n#include <limits>\n#include <queue>\n#include <string>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\ntemplate <typename\
    \ T, T INF = std::numeric_limits<T>::max() / 2, int INVALID = -1>\nstruct shortest_path\
    \ {\n    int V, E;\n    bool single_positive_weight;\n    T wmin, wmax;\n\n  \
    \  std::vector<std::pair<int, T>> tos;\n    std::vector<int> head;\n    std::vector<std::tuple<int,\
    \ int, T>> edges;\n\n    void build_() {\n        if (int(tos.size()) == E and\
    \ int(head.size()) == V + 1) return;\n        tos.resize(E);\n        head.assign(V\
    \ + 1, 0);\n        for (const auto &e : edges) ++head[std::get<0>(e) + 1];\n\
    \        for (int i = 0; i < V; ++i) head[i + 1] += head[i];\n        auto cur\
    \ = head;\n        for (const auto &e : edges) {\n            tos[cur[std::get<0>(e)]++]\
    \ = std::make_pair(std::get<1>(e), std::get<2>(e));\n        }\n    }\n\n    shortest_path(int\
    \ V = 0) : V(V), E(0), single_positive_weight(true), wmin(0), wmax(0) {}\n   \
    \ void add_edge(int s, int t, T w) {\n        assert(0 <= s and s < V);\n    \
    \    assert(0 <= t and t < V);\n        edges.emplace_back(s, t, w);\n       \
    \ ++E;\n        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight =\
    \ false;\n        wmin = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n\
    \    }\n\n    void add_bi_edge(int u, int v, T w) {\n        add_edge(u, v, w);\n\
    \        add_edge(v, u, w);\n    }\n\n    std::vector<T> dist;\n    std::vector<int>\
    \ prev;\n\n    // Dijkstra algorithm\n    // - Requirement: wmin >= 0\n    //\
    \ - Complexity: O(E log E)\n    using Pque = std::priority_queue<std::pair<T,\
    \ int>, std::vector<std::pair<T, int>>,\n                                    \
    \ std::greater<std::pair<T, int>>>;\n    template <class Heap = Pque> void dijkstra(int\
    \ s, int t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n\
    \        dist.assign(V, INF);\n        prev.assign(V, INVALID);\n        dist[s]\
    \ = 0;\n        Heap pq;\n        pq.emplace(0, s);\n        while (!pq.empty())\
    \ {\n            T d;\n            int v;\n            std::tie(d, v) = pq.top();\n\
    \            pq.pop();\n            if (t == v) return;\n            if (dist[v]\
    \ < d) continue;\n            for (int e = head[v]; e < head[v + 1]; ++e) {\n\
    \                const auto &nx = tos[e];\n                T dnx = d + nx.second;\n\
    \                if (dist[nx.first] > dnx) {\n                    dist[nx.first]\
    \ = dnx, prev[nx.first] = v;\n                    pq.emplace(dnx, nx.first);\n\
    \                }\n            }\n        }\n    }\n\n    // Dijkstra algorithm\n\
    \    // - Requirement: wmin >= 0\n    // - Complexity: O(V^2 + E)\n    void dijkstra_vquad(int\
    \ s, int t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n\
    \        dist.assign(V, INF);\n        prev.assign(V, INVALID);\n        dist[s]\
    \ = 0;\n        std::vector<char> fixed(V, false);\n        while (true) {\n \
    \           int r = INVALID;\n            T dr = INF;\n            for (int i\
    \ = 0; i < V; i++) {\n                if (!fixed[i] and dist[i] < dr) r = i, dr\
    \ = dist[i];\n            }\n            if (r == INVALID or r == t) break;\n\
    \            fixed[r] = true;\n            int nxt;\n            T dx;\n     \
    \       for (int e = head[r]; e < head[r + 1]; ++e) {\n                std::tie(nxt,\
    \ dx) = tos[e];\n                if (dist[nxt] > dist[r] + dx) dist[nxt] = dist[r]\
    \ + dx, prev[nxt] = r;\n            }\n        }\n    }\n\n    // Bellman-Ford\
    \ algorithm\n    // - Requirement: no negative loop\n    // - Complexity: O(VE)\n\
    \    bool bellman_ford(int s, int nb_loop) {\n        assert(0 <= s and s < V);\n\
    \        build_();\n        dist.assign(V, INF), prev.assign(V, INVALID);\n  \
    \      dist[s] = 0;\n        for (int l = 0; l < nb_loop; l++) {\n           \
    \ bool upd = false;\n            for (int v = 0; v < V; v++) {\n             \
    \   if (dist[v] == INF) continue;\n                for (int e = head[v]; e < head[v\
    \ + 1]; ++e) {\n                    const auto &nx = tos[e];\n               \
    \     T dnx = dist[v] + nx.second;\n                    if (dist[nx.first] > dnx)\
    \ dist[nx.first] = dnx, prev[nx.first] = v, upd = true;\n                }\n \
    \           }\n            if (!upd) return true;\n        }\n        return false;\n\
    \    }\n\n    // Bellman-ford algorithm using deque\n    // - Requirement: no\
    \ negative loop\n    // - Complexity: O(VE)\n    void spfa(int s) {\n        assert(0\
    \ <= s and s < V);\n        build_();\n        dist.assign(V, INF);\n        prev.assign(V,\
    \ INVALID);\n        dist[s] = 0;\n        std::deque<int> q;\n        std::vector<char>\
    \ in_queue(V);\n        q.push_back(s), in_queue[s] = 1;\n        while (!q.empty())\
    \ {\n            int now = q.front();\n            q.pop_front(), in_queue[now]\
    \ = 0;\n            for (int e = head[now]; e < head[now + 1]; ++e) {\n      \
    \          const auto &nx = tos[e];\n                T dnx = dist[now] + nx.second;\n\
    \                int nxt = nx.first;\n                if (dist[nxt] > dnx) {\n\
    \                    dist[nxt] = dnx;\n                    if (!in_queue[nxt])\
    \ {\n                        if (q.size() and dnx < dist[q.front()]) { // Small\
    \ label first optimization\n                            q.push_front(nxt);\n \
    \                       } else {\n                            q.push_back(nxt);\n\
    \                        }\n                        prev[nxt] = now, in_queue[nxt]\
    \ = 1;\n                    }\n                }\n            }\n        }\n \
    \   }\n\n    // 01-BFS\n    // - Requirement: all weights must be 0 or w (positive\
    \ constant).\n    // - Complexity: O(V + E)\n    void zero_one_bfs(int s, int\
    \ t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n     \
    \   dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n    \
    \    std::vector<int> q(V * 4);\n        int ql = V * 2, qr = V * 2;\n       \
    \ q[qr++] = s;\n        while (ql < qr) {\n            int v = q[ql++];\n    \
    \        if (v == t) return;\n            for (int e = head[v]; e < head[v + 1];\
    \ ++e) {\n                const auto &nx = tos[e];\n                T dnx = dist[v]\
    \ + nx.second;\n                if (dist[nx.first] > dnx) {\n                \
    \    dist[nx.first] = dnx, prev[nx.first] = v;\n                    if (nx.second)\
    \ {\n                        q[qr++] = nx.first;\n                    } else {\n\
    \                        q[--ql] = nx.first;\n                    }\n        \
    \        }\n            }\n        }\n    }\n\n    // Dial's algorithm\n    //\
    \ - Requirement: wmin >= 0\n    // - Complexity: O(wmax * V + E)\n    void dial(int\
    \ s, int t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n\
    \        dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n\
    \        std::vector<std::vector<std::pair<int, T>>> q(wmax + 1);\n        q[0].emplace_back(s,\
    \ dist[s]);\n        int ninq = 1;\n\n        int cur = 0;\n        T dcur = 0;\n\
    \        for (; ninq; ++cur, ++dcur) {\n            if (cur == wmax + 1) cur =\
    \ 0;\n            while (!q[cur].empty()) {\n                int v = q[cur].back().first;\n\
    \                T dnow = q[cur].back().second;\n                q[cur].pop_back(),\
    \ --ninq;\n                if (v == t) return;\n                if (dist[v] <\
    \ dnow) continue;\n\n                for (int e = head[v]; e < head[v + 1]; ++e)\
    \ {\n                    const auto &nx = tos[e];\n                    T dnx =\
    \ dist[v] + nx.second;\n                    if (dist[nx.first] > dnx) {\n    \
    \                    dist[nx.first] = dnx, prev[nx.first] = v;\n             \
    \           int nxtcur = cur + int(nx.second);\n                        if (nxtcur\
    \ >= int(q.size())) nxtcur -= q.size();\n                        q[nxtcur].emplace_back(nx.first,\
    \ dnx), ++ninq;\n                    }\n                }\n            }\n   \
    \     }\n    }\n\n    // Solver for DAG\n    // - Requirement: graph is DAG\n\
    \    // - Complexity: O(V + E)\n    bool dag_solver(int s) {\n        assert(0\
    \ <= s and s < V);\n        build_();\n        dist.assign(V, INF), prev.assign(V,\
    \ INVALID);\n        dist[s] = 0;\n        std::vector<int> indeg(V, 0);\n   \
    \     std::vector<int> q(V * 2);\n        int ql = 0, qr = 0;\n        q[qr++]\
    \ = s;\n        while (ql < qr) {\n            int now = q[ql++];\n          \
    \  for (int e = head[now]; e < head[now + 1]; ++e) {\n                const auto\
    \ &nx = tos[e];\n                ++indeg[nx.first];\n                if (indeg[nx.first]\
    \ == 1) q[qr++] = nx.first;\n            }\n        }\n        ql = qr = 0;\n\
    \        q[qr++] = s;\n        while (ql < qr) {\n            int now = q[ql++];\n\
    \            for (int e = head[now]; e < head[now + 1]; ++e) {\n             \
    \   const auto &nx = tos[e];\n                --indeg[nx.first];\n           \
    \     if (dist[nx.first] > dist[now] + nx.second)\n                    dist[nx.first]\
    \ = dist[now] + nx.second, prev[nx.first] = now;\n                if (indeg[nx.first]\
    \ == 0) q[qr++] = nx.first;\n            }\n        }\n        return *max_element(indeg.begin(),\
    \ indeg.end()) == 0;\n    }\n\n    // Retrieve a sequence of vertex ids that represents\
    \ shortest path [s, ..., goal]\n    // If not reachable to goal, return {}\n \
    \   std::vector<int> retrieve_path(int goal) const {\n        assert(int(prev.size())\
    \ == V);\n        assert(0 <= goal and goal < V);\n        if (dist[goal] == INF)\
    \ return {};\n        std::vector<int> ret{goal};\n        while (prev[goal] !=\
    \ INVALID) {\n            goal = prev[goal];\n            ret.push_back(goal);\n\
    \        }\n        std::reverse(ret.begin(), ret.end());\n        return ret;\n\
    \    }\n\n    void solve(int s, int t = INVALID) {\n        if (wmin >= 0) {\n\
    \            if (single_positive_weight) {\n                zero_one_bfs(s, t);\n\
    \            } else if (wmax <= 10) {\n                dial(s, t);\n         \
    \   } else {\n                if ((long long)V * V < (E << 4)) {\n           \
    \         dijkstra_vquad(s, t);\n                } else {\n                  \
    \  dijkstra(s, t);\n                }\n            }\n        } else {\n     \
    \       bellman_ford(s, V);\n        }\n    }\n\n    // Warshall-Floyd algorithm\n\
    \    // - Requirement: no negative loop\n    // - Complexity: O(E + V^3)\n   \
    \ std::vector<std::vector<T>> floyd_warshall() {\n        build_();\n        std::vector<std::vector<T>>\
    \ dist2d(V, std::vector<T>(V, INF));\n        for (int i = 0; i < V; i++) {\n\
    \            dist2d[i][i] = 0;\n            for (const auto &e : edges) {\n  \
    \              int s = std::get<0>(e), t = std::get<1>(e);\n                dist2d[s][t]\
    \ = std::min(dist2d[s][t], std::get<2>(e));\n            }\n        }\n      \
    \  for (int k = 0; k < V; k++) {\n            for (int i = 0; i < V; i++) {\n\
    \                if (dist2d[i][k] == INF) continue;\n                for (int\
    \ j = 0; j < V; j++) {\n                    if (dist2d[k][j] == INF) continue;\n\
    \                    dist2d[i][j] = std::min(dist2d[i][j], dist2d[i][k] + dist2d[k][j]);\n\
    \                }\n            }\n        }\n        return dist2d;\n    }\n\n\
    \    void to_dot(std::string filename = \"shortest_path\") const {\n        std::ofstream\
    \ ss(filename + \".DOT\");\n        ss << \"digraph{\\n\";\n        build_();\n\
    \        for (int i = 0; i < V; i++) {\n            for (int e = head[i]; e <\
    \ head[i + 1]; ++e) {\n                ss << i << \"->\" << tos[e].first << \"\
    [label=\" << tos[e].second << \"];\\n\";\n            }\n        }\n        ss\
    \ << \"}\\n\";\n        ss.close();\n        return;\n    }\n};\n#line 4 \"graph/test/shortest_path_dag.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, K;\n    cin >> N >> K;\n    shortest_path<int>\
    \ graph(N + 1);\n    vector<int> indeg(N);\n    while (K--) {\n        int r,\
    \ c;\n        cin >> r >> c;\n        r--, c--;\n        if (r == c) {\n     \
    \       cout << \"-1\\n\";\n            return 0;\n        }\n        indeg[c]++;\n\
    \        graph.add_edge(r, c, -1);\n    }\n    for (int i = 0; i < N; i++) graph.add_edge(N,\
    \ i, -1);\n    if (graph.dag_solver(N)) {\n        cout << -(*min_element(graph.dist.begin(),\
    \ graph.dist.end())) << '\\n';\n    } else {\n        cout << \"-1\\n\";\n   \
    \ }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1660\"\n#include \"../shortest_path.hpp\"\
    \n#include <algorithm>\n#include <iostream>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, K;\n    cin\
    \ >> N >> K;\n    shortest_path<int> graph(N + 1);\n    vector<int> indeg(N);\n\
    \    while (K--) {\n        int r, c;\n        cin >> r >> c;\n        r--, c--;\n\
    \        if (r == c) {\n            cout << \"-1\\n\";\n            return 0;\n\
    \        }\n        indeg[c]++;\n        graph.add_edge(r, c, -1);\n    }\n  \
    \  for (int i = 0; i < N; i++) graph.add_edge(N, i, -1);\n    if (graph.dag_solver(N))\
    \ {\n        cout << -(*min_element(graph.dist.begin(), graph.dist.end())) <<\
    \ '\\n';\n    } else {\n        cout << \"-1\\n\";\n    }\n}\n"
  dependsOn:
  - graph/shortest_path.hpp
  isVerificationFile: true
  path: graph/test/shortest_path_dag.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 15:28:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/shortest_path_dag.test.cpp
layout: document
redirect_from:
- /verify/graph/test/shortest_path_dag.test.cpp
- /verify/graph/test/shortest_path_dag.test.cpp.html
title: graph/test/shortest_path_dag.test.cpp
---