---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/
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
    \    }\n};\n#line 5 \"combinatorial_opt/matroid_intersection.hpp\"\n\n// CUT begin\n\
    // (Min weight) matroid intersection solver\n// Algorithm based on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/\n\
    // Complexity: O(CE^2 + E^3) (C : circuit query, non-weighted)\ntemplate <class\
    \ M1, class M2, class T = int>\nstd::vector<bool> MatroidIntersection(M1 matroid1,\
    \ M2 matroid2, std::vector<T> weights = {}) {\n    using State = std::vector<bool>;\n\
    \    using Element = int;\n    assert(matroid1.size() == matroid2.size());\n \
    \   const int M = matroid1.size();\n\n    for (auto &x : weights) x *= M + 1;\n\
    \    if (weights.empty()) weights.assign(M, 0);\n\n    const Element gs = M, gt\
    \ = M + 1;\n    State I(M);\n\n    while (true) {\n        ShortestPath<T> sssp(M\
    \ + 2);\n        matroid1.set(I);\n        matroid2.set(I);\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) continue;\n            auto c1 =\
    \ matroid1.circuit(e), c2 = matroid2.circuit(e);\n            if (c1.empty())\
    \ sssp.add_edge(e, gt, 0);\n            for (Element f : c1) {\n             \
    \   if (f != e) sssp.add_edge(e, f, -weights[f] + 1);\n            }\n       \
    \     if (c2.empty()) sssp.add_edge(gs, e, weights[e] + 1);\n            for (Element\
    \ f : c2) {\n                if (f != e) sssp.add_edge(f, e, weights[e] + 1);\n\
    \            }\n        }\n        sssp.solve(gs);\n        auto aug_path = sssp.retrieve_path(gt);\n\
    \        if (aug_path.empty()) break;\n        for (auto e : aug_path) {\n   \
    \         if (e != gs and e != gt) I[e] = !I[e];\n        }\n    }\n    return\
    \ I;\n}\n"
  code: "#pragma once\n#include \"../graph/shortest_path.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// CUT begin\n// (Min weight) matroid intersection solver\n\
    // Algorithm based on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/\n\
    // Complexity: O(CE^2 + E^3) (C : circuit query, non-weighted)\ntemplate <class\
    \ M1, class M2, class T = int>\nstd::vector<bool> MatroidIntersection(M1 matroid1,\
    \ M2 matroid2, std::vector<T> weights = {}) {\n    using State = std::vector<bool>;\n\
    \    using Element = int;\n    assert(matroid1.size() == matroid2.size());\n \
    \   const int M = matroid1.size();\n\n    for (auto &x : weights) x *= M + 1;\n\
    \    if (weights.empty()) weights.assign(M, 0);\n\n    const Element gs = M, gt\
    \ = M + 1;\n    State I(M);\n\n    while (true) {\n        ShortestPath<T> sssp(M\
    \ + 2);\n        matroid1.set(I);\n        matroid2.set(I);\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) continue;\n            auto c1 =\
    \ matroid1.circuit(e), c2 = matroid2.circuit(e);\n            if (c1.empty())\
    \ sssp.add_edge(e, gt, 0);\n            for (Element f : c1) {\n             \
    \   if (f != e) sssp.add_edge(e, f, -weights[f] + 1);\n            }\n       \
    \     if (c2.empty()) sssp.add_edge(gs, e, weights[e] + 1);\n            for (Element\
    \ f : c2) {\n                if (f != e) sssp.add_edge(f, e, weights[e] + 1);\n\
    \            }\n        }\n        sssp.solve(gs);\n        auto aug_path = sssp.retrieve_path(gt);\n\
    \        if (aug_path.empty()) break;\n        for (auto e : aug_path) {\n   \
    \         if (e != gs and e != gt) I[e] = !I[e];\n        }\n    }\n    return\
    \ I;\n}\n"
  dependsOn:
  - graph/shortest_path.hpp
  isVerificationFile: false
  path: combinatorial_opt/matroid_intersection.hpp
  requiredBy: []
  timestamp: '2021-09-07 01:07:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroid_intersection.hpp
layout: document
title: "(Weighted) matroid intersecition \uFF08\uFF08\u91CD\u307F\u3064\u304D\uFF09\
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

## 文献・リンク集

- [1] A. Frank, "A weighted matroid intersection algorithm,"
  Journal of Algorithms, 2(4), 328-336, 1981.
- [2] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/) とても初学者向き．
- [[Tutorial] Matroid intersection in simple words - Codeforces](https://codeforces.com/blog/entry/69287) コメント欄に問題例が多い．
