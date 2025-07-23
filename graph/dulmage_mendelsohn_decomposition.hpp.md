---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching.hpp
    title: "Bipartite matching (Hopcroft\u2013Karp)"
  - icon: ':heavy_check_mark:'
    path: graph/strongly_connected_components.hpp
    title: graph/strongly_connected_components.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: combinatorial_opt/matroids/transversal_matroid.hpp
    title: "Transversal matroid \uFF08\u6A2A\u65AD\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/dulmage_mendelsohn.yuki1615.test.cpp
    title: graph/test/dulmage_mendelsohn.yuki1615.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/dulmage_mendelsohn.yuki1744.test.cpp
    title: graph/test/dulmage_mendelsohn.yuki1744.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/dulmage_mendelsohn.yuki1745.test.cpp
    title: graph/test/dulmage_mendelsohn.yuki1745.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/problems/no/1615
  bundledCode: "#line 2 \"graph/bipartite_matching.hpp\"\n#include <cassert>\n#include\
    \ <iostream>\n#include <vector>\n\n// Bipartite matching of undirected bipartite\
    \ graph (Hopcroft-Karp)\n// https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html\n\
    // Complexity: O((V + E)sqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching {\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No partner)\n \
    \   std::vector<int> used, vv;\n    std::vector<int> color; // color of each node(checking\
    \ bipartition): 0/1/-1(not determined)\n\n    BipartiteMatching() = default;\n\
    \    BipartiteMatching(int V_) : V(V_), to(V_), match(V_, -1), used(V_), color(V_,\
    \ -1) {}\n\n    void add_edge(int u, int v) {\n        assert(u >= 0 and u < V\
    \ and v >= 0 and v < V and u != v);\n        to[u].push_back(v);\n        to[v].push_back(u);\n\
    \    }\n\n    void _bfs() {\n        dist.assign(V, -1);\n        std::vector<int>\
    \ q;\n        int lq = 0;\n        for (int i = 0; i < V; i++) {\n           \
    \ if (!color[i] and !used[i]) q.push_back(i), dist[i] = 0;\n        }\n\n    \
    \    while (lq < int(q.size())) {\n            int now = q[lq++];\n          \
    \  for (auto nxt : to[now]) {\n                int c = match[nxt];\n         \
    \       if (c >= 0 and dist[c] == -1) q.push_back(c), dist[c] = dist[now] + 1;\n\
    \            }\n        }\n    }\n\n    bool _dfs(int now) {\n        vv[now]\
    \ = true;\n        for (auto nxt : to[now]) {\n            int c = match[nxt];\n\
    \            if (c < 0 or (!vv[c] and dist[c] == dist[now] + 1 and _dfs(c))) {\n\
    \                match[nxt] = now, match[now] = nxt;\n                used[now]\
    \ = true;\n                return true;\n            }\n        }\n        return\
    \ false;\n    }\n\n    bool _color_bfs(int root) {\n        color[root] = 0;\n\
    \        std::vector<int> q{root};\n        int lq = 0;\n        while (lq < int(q.size()))\
    \ {\n            int now = q[lq++], c = color[now];\n            for (auto nxt\
    \ : to[now]) {\n                if (color[nxt] == -1) {\n                    color[nxt]\
    \ = !c, q.push_back(nxt);\n                } else if (color[nxt] == c) {\n   \
    \                 return false;\n                }\n            }\n        }\n\
    \        return true;\n    }\n\n    int solve() {\n        for (int i = 0; i <\
    \ V; i++) {\n            if (color[i] == -1 and !_color_bfs(i)) return -1;\n \
    \       }\n        int ret = 0;\n        while (true) {\n            _bfs();\n\
    \            vv.assign(V, false);\n            int flow = 0;\n            for\
    \ (int i = 0; i < V; i++) {\n                if (!color[i] and !used[i] and _dfs(i))\
    \ flow++;\n            }\n            if (!flow) break;\n            ret += flow;\n\
    \        }\n        return ret;\n    }\n\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const BipartiteMatching &bm) {\n        os\
    \ << \"{N=\" << bm.V << ':';\n        for (int i = 0; i < bm.V; i++) {\n     \
    \       if (bm.match[i] > i) os << '(' << i << '-' << bm.match[i] << \"),\";\n\
    \        }\n        return os << '}';\n    }\n};\n#line 2 \"graph/strongly_connected_components.hpp\"\
    \n#include <algorithm>\n#line 5 \"graph/strongly_connected_components.hpp\"\n\n\
    // CUT begin\n// Directed graph library to find strongly connected components\
    \ \uFF08\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\uFF09\n// 0-indexed directed\
    \ graph\n// Complexity: O(V + E)\nstruct DirectedGraphSCC {\n    int V; // # of\
    \ Vertices\n    std::vector<std::vector<int>> to, from;\n    std::vector<int>\
    \ used; // Only true/false\n    std::vector<int> vs;\n    std::vector<int> cmp;\n\
    \    int scc_num = -1;\n\n    DirectedGraphSCC(int V = 0) : V(V), to(V), from(V),\
    \ cmp(V) {}\n\n    void _dfs(int v) {\n        used[v] = true;\n        for (auto\
    \ t : to[v])\n            if (!used[t]) _dfs(t);\n        vs.push_back(v);\n \
    \   }\n    void _rdfs(int v, int k) {\n        used[v] = true;\n        cmp[v]\
    \ = k;\n        for (auto t : from[v])\n            if (!used[t]) _rdfs(t, k);\n\
    \    }\n\n    void add_edge(int from_, int to_) {\n        assert(from_ >= 0 and\
    \ from_ < V and to_ >= 0 and to_ < V);\n        to[from_].push_back(to_);\n  \
    \      from[to_].push_back(from_);\n    }\n\n    // Detect strongly connected\
    \ components and return # of them.\n    // Also, assign each vertex `v` the scc\
    \ id `cmp[v]` (0-indexed)\n    int FindStronglyConnectedComponents() {\n     \
    \   used.assign(V, false);\n        vs.clear();\n        for (int v = 0; v < V;\
    \ v++)\n            if (!used[v]) _dfs(v);\n        used.assign(V, false);\n \
    \       scc_num = 0;\n        for (int i = (int)vs.size() - 1; i >= 0; i--)\n\
    \            if (!used[vs[i]]) _rdfs(vs[i], scc_num++);\n        return scc_num;\n\
    \    }\n\n    // Find and output the vertices that form a closed cycle.\n    //\
    \ output: {v_1, ..., v_C}, where C is the length of cycle,\n    //         {}\
    \ if there's NO cycle (graph is DAG)\n    int _c, _init;\n    std::vector<int>\
    \ _ret_cycle;\n    bool _dfs_detectcycle(int now, bool b0) {\n        if (now\
    \ == _init and b0) return true;\n        for (auto nxt : to[now])\n          \
    \  if (cmp[nxt] == _c and !used[nxt]) {\n                _ret_cycle.emplace_back(nxt),\
    \ used[nxt] = 1;\n                if (_dfs_detectcycle(nxt, true)) return true;\n\
    \                _ret_cycle.pop_back();\n            }\n        return false;\n\
    \    }\n    std::vector<int> DetectCycle() {\n        int ns = FindStronglyConnectedComponents();\n\
    \        if (ns == V) return {};\n        std::vector<int> cnt(ns);\n        for\
    \ (auto x : cmp) cnt[x]++;\n        _c = std::find_if(cnt.begin(), cnt.end(),\
    \ [](int x) { return x > 1; }) - cnt.begin();\n        _init = std::find(cmp.begin(),\
    \ cmp.end(), _c) - cmp.begin();\n        used.assign(V, false);\n        _ret_cycle.clear();\n\
    \        _dfs_detectcycle(_init, false);\n        return _ret_cycle;\n    }\n\n\
    \    // After calling `FindStronglyConnectedComponents()`, generate a new graph\
    \ by uniting all\n    // vertices belonging to the same component(The resultant\
    \ graph is DAG).\n    DirectedGraphSCC GenerateTopologicalGraph() {\n        DirectedGraphSCC\
    \ newgraph(scc_num);\n        for (int s = 0; s < V; s++)\n            for (auto\
    \ t : to[s]) {\n                if (cmp[s] != cmp[t]) newgraph.add_edge(cmp[s],\
    \ cmp[t]);\n            }\n        return newgraph;\n    }\n};\n\n// 2-SAT solver:\
    \ Find a solution for  `(Ai v Aj) ^ (Ak v Al) ^ ... = true`\n// - `nb_sat_vars`:\
    \ Number of variables\n// - Considering a graph with `2 * nb_sat_vars` vertices\n\
    // - Vertices [0, nb_sat_vars) means `Ai`\n// - vertices [nb_sat_vars, 2 * nb_sat_vars)\
    \ means `not Ai`\nstruct SATSolver : DirectedGraphSCC {\n    int nb_sat_vars;\n\
    \    std::vector<int> solution;\n    SATSolver(int nb_variables = 0)\n       \
    \ : DirectedGraphSCC(nb_variables * 2), nb_sat_vars(nb_variables), solution(nb_sat_vars)\
    \ {}\n    void add_x_or_y_constraint(bool is_x_true, int x, bool is_y_true, int\
    \ y) {\n        assert(x >= 0 and x < nb_sat_vars);\n        assert(y >= 0 and\
    \ y < nb_sat_vars);\n        if (!is_x_true) x += nb_sat_vars;\n        if (!is_y_true)\
    \ y += nb_sat_vars;\n        add_edge((x + nb_sat_vars) % (nb_sat_vars * 2), y);\n\
    \        add_edge((y + nb_sat_vars) % (nb_sat_vars * 2), x);\n    }\n    // Solve\
    \ the 2-SAT problem. If no solution exists, return `false`.\n    // Otherwise,\
    \ dump one solution to `solution` and return `true`.\n    bool run() {\n     \
    \   FindStronglyConnectedComponents();\n        for (int i = 0; i < nb_sat_vars;\
    \ i++) {\n            if (cmp[i] == cmp[i + nb_sat_vars]) return false;\n    \
    \        solution[i] = cmp[i] > cmp[i + nb_sat_vars];\n        }\n        return\
    \ true;\n    }\n};\n#line 5 \"graph/dulmage_mendelsohn_decomposition.hpp\"\n#include\
    \ <utility>\n#line 7 \"graph/dulmage_mendelsohn_decomposition.hpp\"\n\n// Dulmage\u2013\
    Mendelsohn (DM) decomposition \uFF08DM \u5206\u89E3\uFF09\n// return: [(W+0, W-0),\
    \ (W+1,W-1),...,(W+(k+1), W-(k+1))]\n//         : sequence of pair (left vetrices,\
    \ right vertices)\n//         - |W+0| < |W-0| or both empty\n//         - |W+i|\
    \ = |W-i| (i = 1, ..., k)\n//         - |W+(k+1)| > |W-(k+1)| or both empty\n\
    //         - W is topologically sorted\n// Example:\n// (2, 2, [(0,0), (0,1),\
    \ (1,0)]) => [([],[]),([0,],[1,]),([1,],[0,]),([],[]),]\n// Complexity: O(N +\
    \ (N + M) sqrt(N))\n// Verified: https://yukicoder.me/problems/no/1615\nstd::vector<std::pair<std::vector<int>,\
    \ std::vector<int>>>\ndulmage_mendelsohn(int L, int R, const std::vector<std::pair<int,\
    \ int>> &edges) {\n    for (auto p : edges) {\n        assert(0 <= p.first and\
    \ p.first < L);\n        assert(0 <= p.second and p.second < R);\n    }\n\n  \
    \  BipartiteMatching bm(L + R);\n    for (auto p : edges) bm.add_edge(p.first,\
    \ L + p.second);\n    bm.solve();\n\n    DirectedGraphSCC scc(L + R);\n    for\
    \ (auto p : edges) scc.add_edge(p.first, L + p.second);\n    for (int l = 0; l\
    \ < L; ++l) {\n        if (bm.match[l] >= L) scc.add_edge(bm.match[l], l);\n \
    \   }\n\n    int nscc = scc.FindStronglyConnectedComponents();\n    std::vector<int>\
    \ cmp_map(nscc, -2);\n\n    std::vector<int> vis(L + R);\n    std::vector<int>\
    \ st;\n    for (int c = 0; c < 2; ++c) {\n        std::vector<std::vector<int>>\
    \ to(L + R);\n        auto color = [&L](int x) { return x >= L; };\n        for\
    \ (auto p : edges) {\n            int u = p.first, v = L + p.second;\n       \
    \     if (color(u) != c) std::swap(u, v);\n            to[u].push_back(v);\n \
    \           if (bm.match[u] == v) to[v].push_back(u);\n        }\n        for\
    \ (int i = 0; i < L + R; ++i) {\n            if (bm.match[i] >= 0 or color(i)\
    \ != c or vis[i]) continue;\n            vis[i] = 1, st = {i};\n            while\
    \ (!st.empty()) {\n                int now = st.back();\n                cmp_map[scc.cmp[now]]\
    \ = c - 1;\n                st.pop_back();\n                for (int nxt : to[now])\
    \ {\n                    if (!vis[nxt]) vis[nxt] = 1, st.push_back(nxt);\n   \
    \             }\n            }\n        }\n    }\n\n    int nset = 1;\n    for\
    \ (int n = 0; n < nscc; ++n) {\n        if (cmp_map[n] == -2) cmp_map[n] = nset++;\n\
    \    }\n    for (auto &x : cmp_map) {\n        if (x == -1) x = nset;\n    }\n\
    \    nset++;\n\n    std::vector<std::pair<std::vector<int>, std::vector<int>>>\
    \ groups(nset);\n\n    for (int l = 0; l < L; ++l) {\n        if (bm.match[l]\
    \ < 0) continue;\n        int c = cmp_map[scc.cmp[l]];\n        groups[c].first.push_back(l);\n\
    \        groups[c].second.push_back(bm.match[l] - L);\n    }\n    for (int l =\
    \ 0; l < L; ++l) {\n        if (bm.match[l] >= 0) continue;\n        int c = cmp_map[scc.cmp[l]];\n\
    \        groups[c].first.push_back(l);\n    }\n    for (int r = 0; r < R; ++r)\
    \ {\n        if (bm.match[L + r] >= 0) continue;\n        int c = cmp_map[scc.cmp[L\
    \ + r]];\n        groups[c].second.push_back(r);\n    }\n\n    return groups;\n\
    }\n"
  code: "#pragma once\n#include \"bipartite_matching.hpp\"\n#include \"strongly_connected_components.hpp\"\
    \n#include <cassert>\n#include <utility>\n#include <vector>\n\n// Dulmage\u2013\
    Mendelsohn (DM) decomposition \uFF08DM \u5206\u89E3\uFF09\n// return: [(W+0, W-0),\
    \ (W+1,W-1),...,(W+(k+1), W-(k+1))]\n//         : sequence of pair (left vetrices,\
    \ right vertices)\n//         - |W+0| < |W-0| or both empty\n//         - |W+i|\
    \ = |W-i| (i = 1, ..., k)\n//         - |W+(k+1)| > |W-(k+1)| or both empty\n\
    //         - W is topologically sorted\n// Example:\n// (2, 2, [(0,0), (0,1),\
    \ (1,0)]) => [([],[]),([0,],[1,]),([1,],[0,]),([],[]),]\n// Complexity: O(N +\
    \ (N + M) sqrt(N))\n// Verified: https://yukicoder.me/problems/no/1615\nstd::vector<std::pair<std::vector<int>,\
    \ std::vector<int>>>\ndulmage_mendelsohn(int L, int R, const std::vector<std::pair<int,\
    \ int>> &edges) {\n    for (auto p : edges) {\n        assert(0 <= p.first and\
    \ p.first < L);\n        assert(0 <= p.second and p.second < R);\n    }\n\n  \
    \  BipartiteMatching bm(L + R);\n    for (auto p : edges) bm.add_edge(p.first,\
    \ L + p.second);\n    bm.solve();\n\n    DirectedGraphSCC scc(L + R);\n    for\
    \ (auto p : edges) scc.add_edge(p.first, L + p.second);\n    for (int l = 0; l\
    \ < L; ++l) {\n        if (bm.match[l] >= L) scc.add_edge(bm.match[l], l);\n \
    \   }\n\n    int nscc = scc.FindStronglyConnectedComponents();\n    std::vector<int>\
    \ cmp_map(nscc, -2);\n\n    std::vector<int> vis(L + R);\n    std::vector<int>\
    \ st;\n    for (int c = 0; c < 2; ++c) {\n        std::vector<std::vector<int>>\
    \ to(L + R);\n        auto color = [&L](int x) { return x >= L; };\n        for\
    \ (auto p : edges) {\n            int u = p.first, v = L + p.second;\n       \
    \     if (color(u) != c) std::swap(u, v);\n            to[u].push_back(v);\n \
    \           if (bm.match[u] == v) to[v].push_back(u);\n        }\n        for\
    \ (int i = 0; i < L + R; ++i) {\n            if (bm.match[i] >= 0 or color(i)\
    \ != c or vis[i]) continue;\n            vis[i] = 1, st = {i};\n            while\
    \ (!st.empty()) {\n                int now = st.back();\n                cmp_map[scc.cmp[now]]\
    \ = c - 1;\n                st.pop_back();\n                for (int nxt : to[now])\
    \ {\n                    if (!vis[nxt]) vis[nxt] = 1, st.push_back(nxt);\n   \
    \             }\n            }\n        }\n    }\n\n    int nset = 1;\n    for\
    \ (int n = 0; n < nscc; ++n) {\n        if (cmp_map[n] == -2) cmp_map[n] = nset++;\n\
    \    }\n    for (auto &x : cmp_map) {\n        if (x == -1) x = nset;\n    }\n\
    \    nset++;\n\n    std::vector<std::pair<std::vector<int>, std::vector<int>>>\
    \ groups(nset);\n\n    for (int l = 0; l < L; ++l) {\n        if (bm.match[l]\
    \ < 0) continue;\n        int c = cmp_map[scc.cmp[l]];\n        groups[c].first.push_back(l);\n\
    \        groups[c].second.push_back(bm.match[l] - L);\n    }\n    for (int l =\
    \ 0; l < L; ++l) {\n        if (bm.match[l] >= 0) continue;\n        int c = cmp_map[scc.cmp[l]];\n\
    \        groups[c].first.push_back(l);\n    }\n    for (int r = 0; r < R; ++r)\
    \ {\n        if (bm.match[L + r] >= 0) continue;\n        int c = cmp_map[scc.cmp[L\
    \ + r]];\n        groups[c].second.push_back(r);\n    }\n\n    return groups;\n\
    }\n"
  dependsOn:
  - graph/bipartite_matching.hpp
  - graph/strongly_connected_components.hpp
  isVerificationFile: false
  path: graph/dulmage_mendelsohn_decomposition.hpp
  requiredBy:
  - combinatorial_opt/matroids/transversal_matroid.hpp
  timestamp: '2024-12-02 08:23:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/dulmage_mendelsohn.yuki1745.test.cpp
  - graph/test/dulmage_mendelsohn.yuki1615.test.cpp
  - graph/test/dulmage_mendelsohn.yuki1744.test.cpp
documentation_of: graph/dulmage_mendelsohn_decomposition.hpp
layout: document
title: "Dulmage\u2013Mendelsohn decomposition \uFF08DM \u5206\u89E3\uFF09"
---

二部グラフの Dulmage–Mendelsohn 分解（DM 分解）を行う．計算量は $O((N + M) \sqrt{N})$．

## 概要

左側頂点集合 $V^+$, 右側頂点集合 $V^-$, 辺集合 $E$ からなる二部グラフ $G = (V^+, V^-, E)$ を考える．Dulmage–Mendelsohn 分解とは，この二部グラフの最大マッチングの性質に基づいて，各頂点集合 $V^+, V^-$ を $V^{\pm} = W^{\pm}\_0 + \dots + W^{\pm}\_{K + 1}$ という $(K + 2)$ 個の部分集合 $(K \ge 0)$ へ分割するものである．

具体的には，この分割は以下の性質を満たす：

- グラフ $G$ の最大マッチングに採用されうる辺は $W^+\_k$ と $W^-\_k$ $(k = 0, \dots, K + 1)$ を両端点に持つものに限られる．
- $W^{\pm}\_0$ は「$G$ の任意の最大マッチングにおいて $W^+\_{0}$ の頂点は必ず使われるが $W^-\_{0}$ の各頂点は必ずしも使われるとは限らない」という性質を満たす．$\|W^+\_0\| < \|W^-\_0\|$ または $W^+\_0 = W^-\_0 = \emptyset$ が成立する．
- $W^{\pm}\_{k}$ $(k = 1, \dots, K)$ は「$G$ の任意の最大マッチングにおいて $W^+\_k$ と $W^-\_k$ の各頂点が一対一にマッチングする」という性質を満たす．すなわち $\|W^+\_k\| = \|W^-\_k\| > 0$ が成立する．
- $W^{\pm}\_{K + 1}$ は「$G$ の任意の最大マッチングにおいて $W^-\_{K + 1}$ の頂点は必ず使われるが $W^+\_{K + 1}$ の各頂点は必ずしも使われるとは限らない」という性質を満たす．$\|W^+\_{K + 1}\| > \|W^-\_{K + 1}\|$ または $W^+\_{K + 1} = W^-\_{K + 1} = \emptyset$ が成立する．
- 全ての辺 $(u, v) \in E \, (u \in V^+, v \in V^-)$ について，$u \in W^+\_a$, $v \in W^-\_b$ とすると $a \le b$ を満たす．すなわち，$W^{\pm}\_k$ たちは全ての辺を $V^+$ から $V^-$ への有向辺とみなした状況においてトポロジカル順序でソートされている．

$K$ が最大となる分割方法は実は（トポロジカル順序に従う並べ方の任意性を除いて）一意で，これが $G$ の DM 分解と呼ばれる．

## アルゴリズムの概要

- まず，与えられたグラフ $G$ の最大マッチング $M$ を具体的に一つ求める．
- 上記の最大マッチングで使われなかった頂点たちを始点に探索を行い，これらの頂点と交換可能な頂点集合（$M$ で使用されない頂点を使用して別の最大マッチングをとった際に使われなくなりうる頂点集合）を求める．この過程で探索した頂点たちで $W^{\pm}\_0, W^{\pm}\_{K + 1}$ が構成される．
- 残る頂点について，各辺 $(u, v) \in E, u \in V^+, v \in V^-$ について有向辺 $u \rightarrow v$ を張り，また $M$ でマッチングに使用された辺については逆辺も張る．このグラフ上で強連結成分分解・トポロジカルソートを行い残る $W^{\pm}\_{k}$ たちを構成する．

## 使用方法

```cpp
int L, R;
vector<pair<int, int>> edges;

// L: 左側頂点集合サイズ
// R: 右側頂点集合サイズ
// edges: 0 <= u < L, 0 <= v < R を満たす辺 (u, v) からなる
vector<pair<vector<int>, vector<int>>> ret = dulmage_mendelsohn(L, R, edges);
```

戻り値 `ret` は必ず（$L = R = 0$ であっても）長さ 2 以上の `vector` で，特に `ret` の先頭と最後の要素に関する `first`, `second` の各 `vector` は空である可能性がある．

`ret` に含まれる各 `pair<vector<int>, vector<int>>` について，`first` の第 $i$ 要素が指す $V^+$ の頂点と `second` の第 $i$ 要素が指す $V^-$ の頂点の間には必ず辺が存在する（すなわち，この戻り値を元に即座に最大マッチングが復元できる）．

## 問題例

- [No.1615 Double Down - yukicoder](https://yukicoder.me/problems/no/1615)
- [AtCoder Beginner Contest 223 G - Vertex Deletion](https://atcoder.jp/contests/abc223/tasks/abc223_g) 与えられた二部グラフ（木）を DM 分解した上で $W^-\_0$ と $W^+\_{K + 1}$ のサイズが求められればよい．

## リンク

- [Dulmage–Mendelsohn分解 (DM分解) - 室田一雄](http://www.misojiro.t.u-tokyo.ac.jp/~murota/lect-ouyousurigaku/dm050410.pdf)
- 伊理・藤重・大山『講座・数理計画法 7 グラフ・ネットワーク・マトロイド』産業図書 1986.
