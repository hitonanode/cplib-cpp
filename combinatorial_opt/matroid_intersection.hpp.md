---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/shortest_path.hpp
    title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
    title: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
    title: combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/
  bundledCode: "#line 2 \"graph/shortest_path.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <deque>\n#include <fstream>\n#include <functional>\n#include\
    \ <limits>\n#include <queue>\n#include <string>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\ntemplate <typename T, T INF = std::numeric_limits<T>::max()\
    \ / 2, int INVALID = -1>\nstruct shortest_path {\n    int V, E;\n    bool single_positive_weight;\n\
    \    T wmin, wmax;\n\n    std::vector<std::pair<int, T>> tos;\n    std::vector<int>\
    \ head;\n    std::vector<std::tuple<int, int, T>> edges;\n\n    void build_()\
    \ {\n        if (int(tos.size()) == E and int(head.size()) == V + 1) return;\n\
    \        tos.resize(E);\n        head.assign(V + 1, 0);\n        for (const auto\
    \ &e : edges) ++head[std::get<0>(e) + 1];\n        for (int i = 0; i < V; ++i)\
    \ head[i + 1] += head[i];\n        auto cur = head;\n        for (const auto &e\
    \ : edges) {\n            tos[cur[std::get<0>(e)]++] = std::make_pair(std::get<1>(e),\
    \ std::get<2>(e));\n        }\n    }\n\n    shortest_path(int V = 0) : V(V), E(0),\
    \ single_positive_weight(true), wmin(0), wmax(0) {}\n    void add_edge(int s,\
    \ int t, T w) {\n        assert(0 <= s and s < V);\n        assert(0 <= t and\
    \ t < V);\n        edges.emplace_back(s, t, w);\n        ++E;\n        if (w >\
    \ 0 and wmax > 0 and wmax != w) single_positive_weight = false;\n        wmin\
    \ = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n    }\n\n    void add_bi_edge(int\
    \ u, int v, T w) {\n        add_edge(u, v, w);\n        add_edge(v, u, w);\n \
    \   }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\n    // Dijkstra\
    \ algorithm\n    // - Requirement: wmin >= 0\n    // - Complexity: O(E log E)\n\
    \    using Pque = std::priority_queue<std::pair<T, int>, std::vector<std::pair<T,\
    \ int>>,\n                                     std::greater<std::pair<T, int>>>;\n\
    \    template <class Heap = Pque> void dijkstra(int s, int t = INVALID) {\n  \
    \      assert(0 <= s and s < V);\n        build_();\n        dist.assign(V, INF);\n\
    \        prev.assign(V, INVALID);\n        dist[s] = 0;\n        Heap pq;\n  \
    \      pq.emplace(0, s);\n        while (!pq.empty()) {\n            T d;\n  \
    \          int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
    \            if (t == v) return;\n            if (dist[v] < d) continue;\n   \
    \         for (int e = head[v]; e < head[v + 1]; ++e) {\n                const\
    \ auto &nx = tos[e];\n                T dnx = d + nx.second;\n               \
    \ if (dist[nx.first] > dnx) {\n                    dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                    pq.emplace(dnx, nx.first);\n                }\n  \
    \          }\n        }\n    }\n\n    // Dijkstra algorithm\n    // - Requirement:\
    \ wmin >= 0\n    // - Complexity: O(V^2 + E)\n    void dijkstra_vquad(int s, int\
    \ t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n     \
    \   dist.assign(V, INF);\n        prev.assign(V, INVALID);\n        dist[s] =\
    \ 0;\n        std::vector<char> fixed(V, false);\n        while (true) {\n   \
    \         int r = INVALID;\n            T dr = INF;\n            for (int i =\
    \ 0; i < V; i++) {\n                if (!fixed[i] and dist[i] < dr) r = i, dr\
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
    \ << \"}\\n\";\n        ss.close();\n        return;\n    }\n};\n#line 5 \"combinatorial_opt/matroid_intersection.hpp\"\
    \n\n// (Min weight) matroid intersection solver\n// Algorithm based on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/\n\
    // Complexity: O(CE^2 + E^3) (C : circuit query, non-weighted)\ntemplate <class\
    \ M1, class M2, class T = int>\nstd::vector<bool> MatroidIntersection(M1 matroid1,\
    \ M2 matroid2, std::vector<T> weights = {}) {\n    using State = std::vector<bool>;\n\
    \    using Element = int;\n    assert(matroid1.size() == matroid2.size());\n \
    \   const int M = matroid1.size();\n\n    for (auto &x : weights) x *= M + 1;\n\
    \    if (weights.empty()) weights.assign(M, 0);\n\n    const Element gs = M, gt\
    \ = M + 1;\n    State I(M);\n\n    while (true) {\n        shortest_path<T> sssp(M\
    \ + 2);\n        matroid1.set(I);\n        matroid2.set(I);\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) continue;\n            auto c1 =\
    \ matroid1.circuit(e), c2 = matroid2.circuit(e);\n            if (c1.empty())\
    \ sssp.add_edge(e, gt, 0);\n            for (Element f : c1) {\n             \
    \   if (f != e) sssp.add_edge(e, f, -weights[f] + 1);\n            }\n       \
    \     if (c2.empty()) sssp.add_edge(gs, e, weights[e] + 1);\n            for (Element\
    \ f : c2) {\n                if (f != e) sssp.add_edge(f, e, weights[e] + 1);\n\
    \            }\n        }\n        sssp.solve(gs, gt);\n        auto aug_path\
    \ = sssp.retrieve_path(gt);\n        if (aug_path.empty()) break;\n        for\
    \ (auto e : aug_path) {\n            if (e != gs and e != gt) I[e] = !I[e];\n\
    \        }\n    }\n    return I;\n}\n"
  code: "#pragma once\n#include \"../graph/shortest_path.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// (Min weight) matroid intersection solver\n// Algorithm\
    \ based on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/\n// Complexity:\
    \ O(CE^2 + E^3) (C : circuit query, non-weighted)\ntemplate <class M1, class M2,\
    \ class T = int>\nstd::vector<bool> MatroidIntersection(M1 matroid1, M2 matroid2,\
    \ std::vector<T> weights = {}) {\n    using State = std::vector<bool>;\n    using\
    \ Element = int;\n    assert(matroid1.size() == matroid2.size());\n    const int\
    \ M = matroid1.size();\n\n    for (auto &x : weights) x *= M + 1;\n    if (weights.empty())\
    \ weights.assign(M, 0);\n\n    const Element gs = M, gt = M + 1;\n    State I(M);\n\
    \n    while (true) {\n        shortest_path<T> sssp(M + 2);\n        matroid1.set(I);\n\
    \        matroid2.set(I);\n        for (int e = 0; e < M; e++) {\n           \
    \ if (I[e]) continue;\n            auto c1 = matroid1.circuit(e), c2 = matroid2.circuit(e);\n\
    \            if (c1.empty()) sssp.add_edge(e, gt, 0);\n            for (Element\
    \ f : c1) {\n                if (f != e) sssp.add_edge(e, f, -weights[f] + 1);\n\
    \            }\n            if (c2.empty()) sssp.add_edge(gs, e, weights[e] +\
    \ 1);\n            for (Element f : c2) {\n                if (f != e) sssp.add_edge(f,\
    \ e, weights[e] + 1);\n            }\n        }\n        sssp.solve(gs, gt);\n\
    \        auto aug_path = sssp.retrieve_path(gt);\n        if (aug_path.empty())\
    \ break;\n        for (auto e : aug_path) {\n            if (e != gs and e !=\
    \ gt) I[e] = !I[e];\n        }\n    }\n    return I;\n}\n"
  dependsOn:
  - graph/shortest_path.hpp
  isVerificationFile: false
  path: combinatorial_opt/matroid_intersection.hpp
  requiredBy: []
  timestamp: '2022-05-01 15:28:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
  - combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
documentation_of: combinatorial_opt/matroid_intersection.hpp
layout: document
title: "(Weighted) matroid intersection \uFF08\uFF08\u91CD\u307F\u3064\u304D\uFF09\
  \u30DE\u30C8\u30ED\u30A4\u30C9\u4EA4\u53C9\uFF09"
---

マトロイド交叉（交差）問題 (matroid intersection)・共通独立集合問題とは，同じ台集合 $E$ を持つ二つのマトロイド
$M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$ が与えられたとき，$X \in \mathcal{I}\_{1} \cap \mathcal{I}\_{2}$ を満たす要素数最大の $X \subset E$ の一つを求めるもの．本問題は更に，重み関数 $f(e) : E \rightarrow \mathbb{R}$ が与えられたとき，要素数最大のもののうち特に $\sum\_{e \in X} f(e)$ を最小化（最大化）するようなものを求める重みつき共通独立集合問題 （weighted matroid intersection problem） に一般化される．

本コードは，$n = \|E\|$，解となる集合の要素数の上界（例えば各マトロイドのランクの最小値）を $r$，マトロイドクラスのサーキットクエリ一回あたりの計算量を $c$ として，（重みなしの）マトロイド交叉を $O(nr(n + c))$ で求める．重みつきの場合は最短増加路を求めるパートが Bellman-Ford 法に置き換えられ，計算量は $O(nr(n^2 + c))$ となる（この計算量は例えば [2] のアルゴリズムを用いることで $O(nr(r + c + \log n))$ まで改善可能）．

## 使用方法

`weights` を与えた場合，最小重み共通独立集合を求める．

```cpp
UserDefinedMatroid m1, m2;
vector<int> weights(M);

assert(m1.size() == M);
assert(m2.size() == M);

std::vector<bool> maxindepset = MatroidIntersection(m1, m2, weights);
```

## 問題例

- [Hello 2020 G. Seollal - Codeforces](https://codeforces.com/contest/1284/problem/G) グラフマトロイドと分割マトロイドの交差に帰着される．
- [Deltix Round, Summer 2021 H. DIY Tree - Codeforces](https://codeforces.com/contest/1556/problem/H) 少数の頂点に次数制約がついた最小全域木問題．グラフマトロイドと分割マトロイドの最小重み共通独立集合問題に帰着される．
- [2019 Petrozavodsk Winter Camp, Yandex Cup D. Pick Your Own Nim - Codeforces](https://codeforces.com/gym/102156/problem/D) 二値マトロイドと分割マトロイドの交差．
- [2128 - Demonstration of Honesty! - URI Online Judge](https://www.urionlinejudge.com.br/judge/en/problems/view/2128) 各辺に色がついている無向グラフで，同色の辺は一度しか使えない全域木構築判定問題．グラフマトロイドと分割マトロイドの交差．このライブラリでは TL が厳しいが，独立性を満たす範囲で乱択のアプローチ等によりある程度 $I$ に要素を追加した状態から増加路アルゴリズムを回すことで定数倍高速化し TL に間に合わせられる．
- [CodeChef October Challenge 2019: Faulty System](https://www.codechef.com/problems/CNNCT2) グラフマトロイドとグラフマトロイドの交差．
- [Rainbow Graph – Kattis, NAIPC 2018](https://naipc18.kattis.com/problems/rainbowgraph)
- [Google Code Jam 2019 Round 3 Datacenter Duplex](https://codingcompetitions.withgoogle.com/codejam/round/0000000000051707/0000000000158f1c)
- [AOJ GRL_2_B: 最小全域有向木](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B) 分割マトロイドとグラフマトロイドの重み付き交差でも解ける．
- [AOJ 1605: Bridge Construction Planning （橋の建造計画）](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605&lang=ja) 分割マトロイドとグラフマトロイドの重み付き交差．
- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差（横断マトロイドを考える代わりに辺を仮想的に増やし，分割マトロイドと解釈することも可能）．

## 文献・リンク集

- [1] A. Frank, "A weighted matroid intersection algorithm,"
  Journal of Algorithms, 2(4), 328-336, 1981.
- [2] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/) とても初学者向き．
- [[Tutorial] Matroid intersection in simple words - Codeforces](https://codeforces.com/blog/entry/69287) コメント欄に問題例が多い．
