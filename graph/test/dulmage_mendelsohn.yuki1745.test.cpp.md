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
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1745
    links:
    - https://yukicoder.me/problems/no/1745
  bundledCode: "#line 1 \"graph/test/dulmage_mendelsohn.yuki1745.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/1745\"\n#line 2 \"graph/bipartite_matching.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <vector>\n\n// Bipartite matching\
    \ of undirected bipartite graph (Hopcroft-Karp)\n// https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html\n\
    // Comprexity: O((V + E)sqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching {\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No parter)\n  \
    \  std::vector<int> used, vv;\n    std::vector<int> color; // color of each node(checking\
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
    }\n#line 4 \"graph/test/dulmage_mendelsohn.yuki1745.test.cpp\"\n#include <set>\n\
    #line 7 \"graph/test/dulmage_mendelsohn.yuki1745.test.cpp\"\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N, M, L;\n    cin >> N >> M >> L;\n    vector<pair<int, int>> edges(L);\n  \
    \  for (auto &[s, t] : edges) {\n        cin >> s >> t;\n        --s, --t;\n \
    \   }\n\n    auto dm = dulmage_mendelsohn(N, M, edges);\n    vector<int> grp1(N,\
    \ -1), grp2(M, -1);\n    for (int g = 0; g < dm.size(); ++g) {\n        for (auto\
    \ i : dm[g].first) grp1[i] = g;\n        for (auto i : dm[g].second) grp2[i] =\
    \ g;\n    }\n    for (auto [s, t] : edges) cout << (grp1[s] == grp2[t] ? \"Yes\"\
    \ : \"No\") << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1745\"\n#include \"../dulmage_mendelsohn_decomposition.hpp\"\
    \n#include <iostream>\n#include <set>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, M, L;\n    cin >> N >> M >> L;\n    vector<pair<int, int>> edges(L);\n\
    \    for (auto &[s, t] : edges) {\n        cin >> s >> t;\n        --s, --t;\n\
    \    }\n\n    auto dm = dulmage_mendelsohn(N, M, edges);\n    vector<int> grp1(N,\
    \ -1), grp2(M, -1);\n    for (int g = 0; g < dm.size(); ++g) {\n        for (auto\
    \ i : dm[g].first) grp1[i] = g;\n        for (auto i : dm[g].second) grp2[i] =\
    \ g;\n    }\n    for (auto [s, t] : edges) cout << (grp1[s] == grp2[t] ? \"Yes\"\
    \ : \"No\") << '\\n';\n}\n"
  dependsOn:
  - graph/dulmage_mendelsohn_decomposition.hpp
  - graph/bipartite_matching.hpp
  - graph/strongly_connected_components.hpp
  isVerificationFile: true
  path: graph/test/dulmage_mendelsohn.yuki1745.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/dulmage_mendelsohn.yuki1745.test.cpp
layout: document
redirect_from:
- /verify/graph/test/dulmage_mendelsohn.yuki1745.test.cpp
- /verify/graph/test/dulmage_mendelsohn.yuki1745.test.cpp.html
title: graph/test/dulmage_mendelsohn.yuki1745.test.cpp
---