---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/1989/submission/268026664
  bundledCode: "#line 2 \"graph/incremental_scc.hpp\"\n\n#include <algorithm>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n#line 3 \"graph/strongly_connected_components.hpp\"\
    \n#include <cassert>\n#line 5 \"graph/strongly_connected_components.hpp\"\n\n\
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
    \ true;\n    }\n};\n#line 9 \"graph/incremental_scc.hpp\"\n\n// edges[i] = (s,\
    \ t) means that the edge (s, t) is added at i-th tick.\n// Return the earliest\
    \ tick when the edge (s, t) is included in a cycle.\n// If the edge (s, t) is\
    \ never included in a cycle or s == t, return M.\n// Complexity: O(M log M), where\
    \ M = edges.size()\n// Verified: https://codeforces.com/contest/1989/submission/268026664\n\
    std::vector<int> incremental_scc(const std::vector<std::pair<int, int>> &edges)\
    \ {\n    int N = 1;\n    for (auto [s, t] : edges) N = std::max({N, s + 1, t +\
    \ 1});\n\n    const int M = edges.size();\n\n    std::vector<int> ret(M, M);\n\
    \n    std::vector<int> compressed_idx(N, -1);\n\n    using Edges = std::vector<std::tuple<int,\
    \ int, int>>;\n\n    auto rec = [&](auto &&self, const Edges &e, int tl, int tr)\
    \ -> void {\n        if (e.empty() or tl + 1 == tr) return;\n\n        int n =\
    \ 0;\n        for (const auto &[tick, s, t] : e) {\n            if (compressed_idx.at(s)\
    \ == -1) compressed_idx.at(s) = n++;\n            if (compressed_idx.at(t) ==\
    \ -1) compressed_idx.at(t) = n++;\n        }\n\n        const int tmid = (tl +\
    \ tr) / 2;\n\n        DirectedGraphSCC scc(n);\n        for (const auto &[tick,\
    \ s, t] : e) {\n            if (tick < tmid) scc.add_edge(compressed_idx.at(s),\
    \ compressed_idx.at(t));\n        }\n        scc.FindStronglyConnectedComponents();\n\
    \n        Edges left, right;\n\n        for (const auto &[tick, s, t] : e) {\n\
    \            const int sc = compressed_idx.at(s), tc = compressed_idx.at(t);\n\
    \            if (tick < tmid and scc.cmp.at(sc) == scc.cmp.at(tc)) {\n       \
    \         ret.at(tick) = tmid - 1;\n                left.emplace_back(tick, sc,\
    \ tc);\n            } else {\n                right.emplace_back(tick, scc.cmp.at(sc),\
    \ scc.cmp.at(tc));\n            }\n        }\n\n        for (auto [_, s, t] :\
    \ e) compressed_idx.at(s) = compressed_idx.at(t) = -1;\n\n        self(self, left,\
    \ tl, tmid);\n        self(self, right, tmid, tr);\n    };\n\n    Edges init;\n\
    \    init.reserve(M);\n    for (int tick = 0; tick < M; ++tick) {\n        if\
    \ (auto [s, t] = edges.at(tick); s != t) init.emplace_back(tick, s, t);\n    }\n\
    \n    rec(rec, init, 0, M + 1);\n\n    return ret;\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#include \"graph/strongly_connected_components.hpp\"\n\n\
    // edges[i] = (s, t) means that the edge (s, t) is added at i-th tick.\n// Return\
    \ the earliest tick when the edge (s, t) is included in a cycle.\n// If the edge\
    \ (s, t) is never included in a cycle or s == t, return M.\n// Complexity: O(M\
    \ log M), where M = edges.size()\n// Verified: https://codeforces.com/contest/1989/submission/268026664\n\
    std::vector<int> incremental_scc(const std::vector<std::pair<int, int>> &edges)\
    \ {\n    int N = 1;\n    for (auto [s, t] : edges) N = std::max({N, s + 1, t +\
    \ 1});\n\n    const int M = edges.size();\n\n    std::vector<int> ret(M, M);\n\
    \n    std::vector<int> compressed_idx(N, -1);\n\n    using Edges = std::vector<std::tuple<int,\
    \ int, int>>;\n\n    auto rec = [&](auto &&self, const Edges &e, int tl, int tr)\
    \ -> void {\n        if (e.empty() or tl + 1 == tr) return;\n\n        int n =\
    \ 0;\n        for (const auto &[tick, s, t] : e) {\n            if (compressed_idx.at(s)\
    \ == -1) compressed_idx.at(s) = n++;\n            if (compressed_idx.at(t) ==\
    \ -1) compressed_idx.at(t) = n++;\n        }\n\n        const int tmid = (tl +\
    \ tr) / 2;\n\n        DirectedGraphSCC scc(n);\n        for (const auto &[tick,\
    \ s, t] : e) {\n            if (tick < tmid) scc.add_edge(compressed_idx.at(s),\
    \ compressed_idx.at(t));\n        }\n        scc.FindStronglyConnectedComponents();\n\
    \n        Edges left, right;\n\n        for (const auto &[tick, s, t] : e) {\n\
    \            const int sc = compressed_idx.at(s), tc = compressed_idx.at(t);\n\
    \            if (tick < tmid and scc.cmp.at(sc) == scc.cmp.at(tc)) {\n       \
    \         ret.at(tick) = tmid - 1;\n                left.emplace_back(tick, sc,\
    \ tc);\n            } else {\n                right.emplace_back(tick, scc.cmp.at(sc),\
    \ scc.cmp.at(tc));\n            }\n        }\n\n        for (auto [_, s, t] :\
    \ e) compressed_idx.at(s) = compressed_idx.at(t) = -1;\n\n        self(self, left,\
    \ tl, tmid);\n        self(self, right, tmid, tr);\n    };\n\n    Edges init;\n\
    \    init.reserve(M);\n    for (int tick = 0; tick < M; ++tick) {\n        if\
    \ (auto [s, t] = edges.at(tick); s != t) init.emplace_back(tick, s, t);\n    }\n\
    \n    rec(rec, init, 0, M + 1);\n\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/incremental_scc.hpp
  requiredBy: []
  timestamp: '2024-07-06 10:40:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/incremental_scc.hpp
layout: document
title: "Incremental SCC \uFF08\u5F37\u9023\u7D50\u6210\u5206\uFF09"
---

$m$ 個の有向辺からなる列が与えられ，先頭の要素から順にグラフに追加していく．各有向辺について，グラフに何番目の辺まで追加したときに初めてその辺を含む閉路ができるかを $O(m \log m)$ で計算する．

この処理は以下のような用途に使える．

- UnionFind などのデータ構造を併用することで，各時点での強連結成分を管理できる．
- 各辺を含む閉路ができる時刻を重みとして最小全域木を求め，更に heavy-light decomposition やセグメント木と併用することで， 2 頂点が同一の強連結成分に初めて属する時刻をクエリ $O(n \log n)$ 等で計算できる．

## 使用方法

```cpp
vector<pair<int, int>> edges;  // 有向辺の列． edges[i] は時刻 i に追加される

auto ticks = incremental_scc(edges);

assert(ticks.size() == edges.size());
// ticks[i] = (edges[i] を含む閉路ができる時刻 (0 <= ticks[i] < m)) または m （閉路ができない場合・自己ループの場合）
```

## 問題例

- [Educational Codeforces Round 167 (Rated for Div. 2) F. Simultaneous Coloring](https://codeforces.com/contest/1989/problem/F)

## リンク

- [My own algorithm — offline incremental strongly connected components in O(m*log(m)) - Codeforces](https://codeforces.com/blog/entry/91608)
