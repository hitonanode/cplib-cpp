---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching.hpp
    title: "Bipartite matching (Hopcroft\u2013Karp)"
  - icon: ':heavy_check_mark:'
    path: graph/dulmage_mendelsohn_decomposition.hpp
    title: "Dulmage\u2013Mendelsohn decomposition \uFF08DM \u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: graph/strongly_connected_components.hpp
    title: graph/strongly_connected_components.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
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
    }\n#line 4 \"combinatorial_opt/matroids/transversal_matroid.hpp\"\n\nstruct TransversalMatroid\
    \ {\n    int M, W;\n    std::vector<std::vector<int>> to;\n    TransversalMatroid(int\
    \ M_, int Mopp, const std::vector<std::pair<int, int>> &edges_)\n        : M(M_),\
    \ W(Mopp), to(M_) {\n        for (auto p : edges_) to[p.first].push_back(p.second);\n\
    \    }\n\n    int size() const { return M; }\n\n    std::vector<int> is_opp_fixed;\n\
    \    std::vector<std::vector<int>> _to_dfs;\n    template <class State = std::vector<bool>>\
    \ void set(State I) {\n        std::vector<std::pair<int, int>> edges;\n\n   \
    \     for (int e = 0; e < M; ++e) {\n            if (I[e]) {\n               \
    \ for (int w : to[e]) edges.emplace_back(e, w);\n            }\n        }\n  \
    \      auto dm = dulmage_mendelsohn(M, W, edges);\n        is_opp_fixed.assign(W,\
    \ 1);\n        for (auto w : dm.front().second) is_opp_fixed[w] = 0;\n\n     \
    \   _to_dfs.assign(M + W, {});\n        for (int e = 0; e < int(to.size()); ++e)\
    \ {\n            for (int w : to[e]) _to_dfs[e].push_back(M + w);\n        }\n\
    \        for (const auto &p : dm) {\n            const auto &es = p.first, &ws\
    \ = p.second;\n            for (int i = 0; i < std::min<int>(es.size(), ws.size());\
    \ ++i) {\n                _to_dfs[M + ws[i]].push_back(es[i]);\n            }\n\
    \        }\n    }\n\n    std::vector<int> circuit(int e) const {\n        for\
    \ (int w : to[e]) {\n            if (!is_opp_fixed[w]) return {};\n        }\n\
    \        std::vector<int> vis(M + W);\n        std::vector<int> st{e};\n     \
    \   vis[e] = 1;\n        while (st.size()) {\n            int now = st.back();\n\
    \            st.pop_back();\n            for (auto nxt : _to_dfs[now]) {\n   \
    \             if (vis[nxt] == 0) {\n                    vis[nxt] = 1;\n      \
    \              st.push_back(nxt);\n                }\n            }\n        }\n\
    \        std::vector<int> ret;\n        for (int e = 0; e < M; ++e) {\n      \
    \      if (vis[e]) ret.push_back(e);\n        }\n        return ret;\n    }\n\
    };\n"
  code: "#pragma once\n#include \"../../graph/dulmage_mendelsohn_decomposition.hpp\"\
    \n#include <vector>\n\nstruct TransversalMatroid {\n    int M, W;\n    std::vector<std::vector<int>>\
    \ to;\n    TransversalMatroid(int M_, int Mopp, const std::vector<std::pair<int,\
    \ int>> &edges_)\n        : M(M_), W(Mopp), to(M_) {\n        for (auto p : edges_)\
    \ to[p.first].push_back(p.second);\n    }\n\n    int size() const { return M;\
    \ }\n\n    std::vector<int> is_opp_fixed;\n    std::vector<std::vector<int>> _to_dfs;\n\
    \    template <class State = std::vector<bool>> void set(State I) {\n        std::vector<std::pair<int,\
    \ int>> edges;\n\n        for (int e = 0; e < M; ++e) {\n            if (I[e])\
    \ {\n                for (int w : to[e]) edges.emplace_back(e, w);\n         \
    \   }\n        }\n        auto dm = dulmage_mendelsohn(M, W, edges);\n       \
    \ is_opp_fixed.assign(W, 1);\n        for (auto w : dm.front().second) is_opp_fixed[w]\
    \ = 0;\n\n        _to_dfs.assign(M + W, {});\n        for (int e = 0; e < int(to.size());\
    \ ++e) {\n            for (int w : to[e]) _to_dfs[e].push_back(M + w);\n     \
    \   }\n        for (const auto &p : dm) {\n            const auto &es = p.first,\
    \ &ws = p.second;\n            for (int i = 0; i < std::min<int>(es.size(), ws.size());\
    \ ++i) {\n                _to_dfs[M + ws[i]].push_back(es[i]);\n            }\n\
    \        }\n    }\n\n    std::vector<int> circuit(int e) const {\n        for\
    \ (int w : to[e]) {\n            if (!is_opp_fixed[w]) return {};\n        }\n\
    \        std::vector<int> vis(M + W);\n        std::vector<int> st{e};\n     \
    \   vis[e] = 1;\n        while (st.size()) {\n            int now = st.back();\n\
    \            st.pop_back();\n            for (auto nxt : _to_dfs[now]) {\n   \
    \             if (vis[nxt] == 0) {\n                    vis[nxt] = 1;\n      \
    \              st.push_back(nxt);\n                }\n            }\n        }\n\
    \        std::vector<int> ret;\n        for (int e = 0; e < M; ++e) {\n      \
    \      if (vis[e]) ret.push_back(e);\n        }\n        return ret;\n    }\n\
    };\n"
  dependsOn:
  - graph/dulmage_mendelsohn_decomposition.hpp
  - graph/bipartite_matching.hpp
  - graph/strongly_connected_components.hpp
  isVerificationFile: false
  path: combinatorial_opt/matroids/transversal_matroid.hpp
  requiredBy: []
  timestamp: '2024-12-02 08:23:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/transversal_matroid.hpp
layout: document
title: "Transversal matroid \uFF08\u6A2A\u65AD\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
---

頂点集合 $U, V$，辺集合 $E$ からなる二部グラフ $G = (U, V, E)$ について定義されるマトロイド．台集合は $U$．$U$ の部分集合の独立性を，「その集合を被覆するようなマッチングが存在すること」で定義する．

計算量は，$\|U\| + \|V\| = n, \|E\| = m$ とすると，独立集合 $I \subset U$ の設定（`set()`）が $O((n + m) \sqrt{n})$，$I + \{e\}$ に対するサーキットの取得（`circuit()`）がクエリあたり $O(n + m)$．

## 使用例

```cpp
int U = 4, V = 2;
vector<pair<int, int>> edges;
edges.emplace_back(0, 0); // 0 <= u < U, 0 <= v < V
edges.emplace_back(1, 0);
edges.emplace_back(2, 1);

TransversalMatroid M1(U, V, edges);
vector<bool> I{1, 0, 0, 0};
M1.set(I);
vector<int> a = M1.circuit(1); // [0, 1]
vector<int> b = M1.circuit(2); // [] (I + {2} is still independent)
```

## 問題例

- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差．

## リンク

- [離散最適化基礎論 第 6回 マトロイドに対する貪欲アルゴリズム](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/handout06.pdf)
