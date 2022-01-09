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
    - https://math.mit.edu/~goemans/18438F09/lec13.pdf
  bundledCode: "#line 2 \"graph/shortest_path.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <deque>\n#include <fstream>\n#include <functional>\n#include\
    \ <limits>\n#include <queue>\n#include <string>\n#include <utility>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <typename T, T INF = std::numeric_limits<T>::max()\
    \ / 2, int INVALID = -1>\nstruct ShortestPath {\n    int V, E;\n    bool single_positive_weight;\n\
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
    \     return;\n    }\n};\n#line 6 \"combinatorial_opt/matroid_union.hpp\"\n\n\
    // CUT begin\n// Union matroid augment\n// From I1, I2 (independent, exclusive),\n\
    // - find I1' and I2' s.t. |I1'| + |I2'| = |I1| + |I2| + 1 and return true\n//\
    \ - or return false\n// Complexity: O(n(c + r)) (r: current rank, c: circuit query)\n\
    // Algorithm based on https://math.mit.edu/~goemans/18438F09/lec13.pdf\n// Verified:\
    \ CodeChef HAMEL\ntemplate <class M1, class M2, class State1, class State2, class\
    \ T = int>\nbool augment_union_matroid(M1 &matroid1, M2 &matroid2, State1 &I1,\
    \ State2 &I2,\n                           const std::vector<T> &weights) {\n \
    \   const int M = matroid1.size();\n    const int gs = M, gt = M + 1;\n    ShortestPath<T>\
    \ sssp(M + 2);\n    std::vector<int> color(M, -1);\n    matroid1.set(I1);\n  \
    \  matroid2.set(I2);\n    for (int e = 0; e < M; e++) {\n        if (!I1[e] and\
    \ !I2[e]) sssp.add_edge(gs, e, weights.size() ? weights[e] : 0);\n        if (!I1[e])\
    \ {\n            auto c = matroid1.circuit(e);\n            if (c.empty()) sssp.add_edge(e,\
    \ gt, 0), color[e] = 0;\n            for (int f : c) {\n                if (f\
    \ != e) sssp.add_edge(e, f, 1);\n            }\n        }\n        if (!I2[e])\
    \ {\n            auto c = matroid2.circuit(e);\n            if (c.empty()) sssp.add_edge(e,\
    \ gt, 0), color[e] = 1;\n            for (int f : c) {\n                if (f\
    \ != e) sssp.add_edge(e, f, 1);\n            }\n        }\n    }\n    sssp.solve(gs);\n\
    \    auto aug_path = sssp.retrieve_path(gt);\n    if (aug_path.empty()) return\
    \ false;\n    assert(aug_path.size() >= 3);\n    int c0 = -1;\n    if (I1[aug_path[aug_path.size()\
    \ - 2]]) c0 = 1;\n    if (I2[aug_path[aug_path.size() - 2]]) c0 = 0;\n    if (c0\
    \ < 0) c0 = color[aug_path[aug_path.size() - 2]];\n    for (int k = int(aug_path.size())\
    \ - 2, e = aug_path[k]; k; e = aug_path[--k]) {\n        (c0 ? I2 : I1)[e] = 1,\
    \ (c0 ? I1 : I2)[e] = 0;\n        c0 ^= 1;\n    }\n    return true;\n}\n\n// (Min\
    \ weight) matroid partition\ntemplate <class M1, class M2, class T = int>\nstd::pair<std::vector<bool>,\
    \ std::vector<bool>>\nMinWeightMaxIndepSetInUnionMatroid(M1 mat1, M2 mat2, const\
    \ std::vector<T> &weights = {}) {\n    using State = std::vector<bool>;\n    assert(mat1.size()\
    \ == mat2.size());\n    const int M = mat1.size();\n    State I1(M), I2(M);\n\
    \    while (augment_union_matroid(mat1, mat2, I1, I2, weights)) {}\n    return\
    \ {I1, I2};\n}\n"
  code: "#pragma once\n#include \"../graph/shortest_path.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Union matroid augment\n\
    // From I1, I2 (independent, exclusive),\n// - find I1' and I2' s.t. |I1'| + |I2'|\
    \ = |I1| + |I2| + 1 and return true\n// - or return false\n// Complexity: O(n(c\
    \ + r)) (r: current rank, c: circuit query)\n// Algorithm based on https://math.mit.edu/~goemans/18438F09/lec13.pdf\n\
    // Verified: CodeChef HAMEL\ntemplate <class M1, class M2, class State1, class\
    \ State2, class T = int>\nbool augment_union_matroid(M1 &matroid1, M2 &matroid2,\
    \ State1 &I1, State2 &I2,\n                           const std::vector<T> &weights)\
    \ {\n    const int M = matroid1.size();\n    const int gs = M, gt = M + 1;\n \
    \   ShortestPath<T> sssp(M + 2);\n    std::vector<int> color(M, -1);\n    matroid1.set(I1);\n\
    \    matroid2.set(I2);\n    for (int e = 0; e < M; e++) {\n        if (!I1[e]\
    \ and !I2[e]) sssp.add_edge(gs, e, weights.size() ? weights[e] : 0);\n       \
    \ if (!I1[e]) {\n            auto c = matroid1.circuit(e);\n            if (c.empty())\
    \ sssp.add_edge(e, gt, 0), color[e] = 0;\n            for (int f : c) {\n    \
    \            if (f != e) sssp.add_edge(e, f, 1);\n            }\n        }\n \
    \       if (!I2[e]) {\n            auto c = matroid2.circuit(e);\n           \
    \ if (c.empty()) sssp.add_edge(e, gt, 0), color[e] = 1;\n            for (int\
    \ f : c) {\n                if (f != e) sssp.add_edge(e, f, 1);\n            }\n\
    \        }\n    }\n    sssp.solve(gs);\n    auto aug_path = sssp.retrieve_path(gt);\n\
    \    if (aug_path.empty()) return false;\n    assert(aug_path.size() >= 3);\n\
    \    int c0 = -1;\n    if (I1[aug_path[aug_path.size() - 2]]) c0 = 1;\n    if\
    \ (I2[aug_path[aug_path.size() - 2]]) c0 = 0;\n    if (c0 < 0) c0 = color[aug_path[aug_path.size()\
    \ - 2]];\n    for (int k = int(aug_path.size()) - 2, e = aug_path[k]; k; e = aug_path[--k])\
    \ {\n        (c0 ? I2 : I1)[e] = 1, (c0 ? I1 : I2)[e] = 0;\n        c0 ^= 1;\n\
    \    }\n    return true;\n}\n\n// (Min weight) matroid partition\ntemplate <class\
    \ M1, class M2, class T = int>\nstd::pair<std::vector<bool>, std::vector<bool>>\n\
    MinWeightMaxIndepSetInUnionMatroid(M1 mat1, M2 mat2, const std::vector<T> &weights\
    \ = {}) {\n    using State = std::vector<bool>;\n    assert(mat1.size() == mat2.size());\n\
    \    const int M = mat1.size();\n    State I1(M), I2(M);\n    while (augment_union_matroid(mat1,\
    \ mat2, I1, I2, weights)) {}\n    return {I1, I2};\n}\n"
  dependsOn:
  - graph/shortest_path.hpp
  isVerificationFile: false
  path: combinatorial_opt/matroid_union.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroid_union.hpp
layout: document
title: "Matroid union \uFF08\u30DE\u30C8\u30ED\u30A4\u30C9\u306E\u5408\u4F75\uFF09"
---

2つのマトロイド $M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$, $\mathcal{I}\_{1}$ に関して独立な集合 $I_1$, $\mathcal{I}\_{2}$ に関して独立な集合 $I\_2$ で $I\_1 \cup I\_2 = \emptyset$ を満たすものが与えられたとき，$I'\_1 + I'\_2 = I\_1 + I\_2 + \\{ e \\}$ を満たす新たな排反な独立集合 $I'\_1, I'\_2$ を見つけるアルゴリズム．特に重み最小の $e$ から貪欲に追加を試すことで，「合併したマトロイド」の最小重みサイズ $k$ 独立集合が $k = 1, 2, \dots$ について順次求められる．

これを応用すると，与えられた重み付き無向グラフについて，辺素な二つの全域木であって重みの総和が最小なものを見つけることも可能．

## アルゴリズムの概要

$\|E\| = n$ として，$e = 1, \dots, n$ に $s$, $t$ を加えた $n + 2$ 頂点のグラフに次の要領で辺を張る：

- $e \notin I\_1 \cup I\_2$ のとき，$s \rightarrow e$ （重み $0$）を張る．
- $e \notin I\_j$ かつ $I\_j + \\{e \\}$ が $M\_j$ における独立集合のとき， $e \rightarrow t$ （重み $w(e)$）を張る．$(j = 1, 2)$
- $e \notin I\_j$ かつ $I\_j + \\{e \\}$ が $M\_j$ における従属集合のとき，サーキットに含まれる各 $f$ について $e \rightarrow f$ （重み $1$）を張る．$(j=1, 2)$

このグラフで $s$ から $t$ への最短路を求め，$s$ の次に通った要素が新たに追加される（$s$ から $t$ に到達不能ならば $I\_1 \cup I\_2$ は既に合併したマトロイド上の最大独立集合である）．それ以降に通った要素は既に $I\_1$ または $I\_2$ に含まれているが，これらを集合間で出し入れすることで $I\_1$ と $I\_2$ の独立性が保たれる．

本コードには実装されていないが，3 個以上のマトロイドの合併に対しても同様のアルゴリズムが適用可能である．

## 使用方法

- `bool augment_union_matroid(matroid1, matroid2, I1, I2, weight)` 関数は，上述の追加可能な重み最小要素 $e$ を見つけ，$I\_1$ および $I\_2$ を追加後の状態に更新する．要素の追加が行われたならば `true` を，そうでなければ `false` を返す．
- `pair<vector<bool>, vector<bool>> MinWeightMaxIndepSetInUnionMatroid(matroid1, matroid2, weight)` 関数は，`augment_union_matroid()` 関数を繰り返し適用することで，2つのマトロイドを合併したマトロイドにおける（重み最小な）最大独立集合を構成する．

## 問題例

- [Hamel Paths \| CodeChef](https://www.codechef.com/problems/HAMEL) 無向グラフから2つの全域木を作る．
- [SRM 685 Div.1 450 FoxAirline2](https://community.topcoder.com/stat?c=problem_statement&pm=14194&rd=16689) 無向グラフから2つの全域木を作れるか判定する．
- [2018 TCO Round 3A 1000 ColoringEdgesDiv1](https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198) 各頂点の次数が3の単純無向グラフ（$n \le 1000, m = 3n/2$）の辺を2つの全域森に分割する方法を構成する．最初に乱択で辺を追加して全域森2つの初期解を構成し，その後全ての辺を割り当て終えるまで `augment_union_matroid()` を真面目に使用するというヒューリスティックによって [最大 200 ms 程度の実行時間で用意された全ケースに通る](https://vjudge.net/solution/32788901)（ただし，後述するように無向グラフの全域森への分割にはより高速なアルゴリズムが存在する：`edge_disjoint_min_spanning_forests.hpp` 参照）．

## 参考文献・リンク

- [1] J. Edmonds, "Minimum partition of a matroid into independent subsets,"
  J. Res. Nat. Bur. Standards Sect. B 69, 67-72, 1965.
- [18.438: Advanced Combinatorial Optimization, Fall 2009](http://www-math.mit.edu/~goemans/18438F09/18438.html): [lec13.pdf](http://www-math.mit.edu/~goemans/18438F09/lec13.pdf)
- [Matroid partitioning - Wikipedia](https://en.wikipedia.org/wiki/Matroid_partitioning#cite_ref-e65_3-0)
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/): [handout12.pdf](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/handout12.pdf)
- [AlgoWiki - Matroid](https://wiki.algo.is/Matroid) 問題へのリンクが豊富．
- [様々な全域木問題](https://www.slideshare.net/tmaehara/ss-17402143) 特に無向グラフのの辺素な全域森への分割を考える場合，より高速なアルゴリズムが存在する．
