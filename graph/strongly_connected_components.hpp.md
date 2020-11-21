---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/2sat_solver.test.cpp
    title: graph/test/2sat_solver.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/cycle_detection_directed.test.cpp
    title: graph/test/cycle_detection_directed.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/strongly_connected_components.test.cpp
    title: graph/test/strongly_connected_components.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/topological_sort.test.cpp
    title: graph/test/topological_sort.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/strongly_connected_components.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Directed graph library\
    \ to find strongly connected components \uFF08\u5F37\u9023\u7D50\u6210\u5206\u5206\
    \u89E3\uFF09\n// 0-indexed directed graph\n// Complexity: O(V + E)\nstruct DirectedGraphSCC\
    \ {\n    int V; // # of Vertices\n    std::vector<std::vector<int>> to, from;\n\
    \    std::vector<int> used; // Only true/false\n    std::vector<int> vs;\n   \
    \ std::vector<int> cmp;\n    int scc_num = -1;\n\n    DirectedGraphSCC(int V =\
    \ 0) : V(V), to(V), from(V), cmp(V) {}\n\n    void _dfs(int v) {\n        used[v]\
    \ = true;\n        for (auto t : to[v])\n            if (!used[t]) _dfs(t);\n\
    \        vs.push_back(v);\n    }\n    void _rdfs(int v, int k) {\n        used[v]\
    \ = true;\n        cmp[v] = k;\n        for (auto t : from[v])\n            if\
    \ (!used[t]) _rdfs(t, k);\n    }\n\n    void add_edge(int from_, int to_) {\n\
    \        assert(from_ >= 0 and from_ < V and to_ >= 0 and to_ < V);\n        to[from_].push_back(to_);\n\
    \        from[to_].push_back(from_);\n    }\n\n    // Detect strongly connected\
    \ components and return # of them.\n    // Also, assign each vertex `v` the scc\
    \ id `cmp[v]` (0-indexed)\n    int FindStronglyConnectedComponents() {\n     \
    \   used.assign(V, false);\n        vs.clear();\n        for (int v = 0; v < V;\
    \ v++)\n            if (!used[v]) _dfs(v);\n        used.assign(V, false);\n \
    \       scc_num = 0;\n        for (int i = (int)vs.size() - 1; i >= 0; i--)\n\
    \            if (!used[vs[i]]) _rdfs(vs[i], scc_num++);\n        return scc_num;\n\
    \    }\n\n    // Find and output the vertices that form a closed cycle.\n    //\
    \ output: {v_1, ..., v_C}, where C is the length of cycle,\n    //         {}\
    \ if there's NO cycle (graph is DAG)\n    std::vector<int> DetectCycle() {\n \
    \       int ns = FindStronglyConnectedComponents();\n        if (ns == V) return\
    \ {};\n        std::vector<int> cnt(ns);\n        for (auto x : cmp) cnt[x]++;\n\
    \        const int c = std::find_if(cnt.begin(), cnt.end(), [](int x) { return\
    \ x > 1; }) - cnt.begin();\n        const int init = std::find(cmp.begin(), cmp.end(),\
    \ c) - cmp.begin();\n        used.assign(V, false);\n        std::vector<int>\
    \ ret;\n        auto dfs = [&](auto &&dfs, int now, bool b0) -> bool {\n     \
    \       if (now == init and b0) return true;\n            for (auto nxt : to[now])\n\
    \                if (cmp[nxt] == c and !used[nxt]) {\n                    ret.emplace_back(nxt),\
    \ used[nxt] = 1;\n                    if (dfs(dfs, nxt, true)) return true;\n\
    \                    ret.pop_back();\n                }\n            return false;\n\
    \        };\n        dfs(dfs, init, false);\n        return ret;\n    }\n\n  \
    \  // After calling `FindStronglyConnectedComponents()`, generate a new graph\
    \ by uniting all vertices\n    // belonging to the same component(The resultant\
    \ graph is DAG).\n    DirectedGraphSCC GenerateTopologicalGraph() {\n        DirectedGraphSCC\
    \ newgraph(scc_num);\n        for (int s = 0; s < V; s++)\n            for (auto\
    \ t : to[s]) {\n                if (cmp[s] != cmp[t]) newgraph.add_edge(cmp[s],\
    \ cmp[t]);\n            }\n        return newgraph;\n    }\n};\n\n// 2-SAT solver:\
    \ Find a solution for  `(Ai v Aj) ^ (Ak v Al) ^ ... = true`\n// - `nb_sat_vars`:\
    \ Number of variables\n// - Considering a graph with `2 * nb_sat_vars` vertices\n\
    // - Vertices [0, nb_sat_vars) means `Ai`\n// - vertices [nb_sat_vars, 2 * nb_sat_vars)\
    \ means `not Ai`\nstruct SATSolver : DirectedGraphSCC {\n    int nb_sat_vars;\n\
    \    std::vector<int> solution;\n    SATSolver(int nb_variables = 0) : DirectedGraphSCC(nb_variables\
    \ * 2), nb_sat_vars(nb_variables), solution(nb_sat_vars) {}\n    void add_x_or_y_constraint(bool\
    \ is_x_true, int x, bool is_y_true, int y) {\n        assert(x >= 0 and x < nb_sat_vars);\n\
    \        assert(y >= 0 and y < nb_sat_vars);\n        if (!is_x_true) x += nb_sat_vars;\n\
    \        if (!is_y_true) y += nb_sat_vars;\n        add_edge((x + nb_sat_vars)\
    \ % (nb_sat_vars * 2), y);\n        add_edge((y + nb_sat_vars) % (nb_sat_vars\
    \ * 2), x);\n    }\n    // Solve the 2-SAT problem. If no solution exists, return\
    \ `false`.\n    // Otherwise, dump one solution to `solution` and return `true`.\n\
    \    bool run() {\n        FindStronglyConnectedComponents();\n        for (int\
    \ i = 0; i < nb_sat_vars; i++) {\n            if (cmp[i] == cmp[i + nb_sat_vars])\
    \ return false;\n            solution[i] = cmp[i] > cmp[i + nb_sat_vars];\n  \
    \      }\n        return true;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\
    \n// CUT begin\n// Directed graph library to find strongly connected components\
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
    \ if there's NO cycle (graph is DAG)\n    std::vector<int> DetectCycle() {\n \
    \       int ns = FindStronglyConnectedComponents();\n        if (ns == V) return\
    \ {};\n        std::vector<int> cnt(ns);\n        for (auto x : cmp) cnt[x]++;\n\
    \        const int c = std::find_if(cnt.begin(), cnt.end(), [](int x) { return\
    \ x > 1; }) - cnt.begin();\n        const int init = std::find(cmp.begin(), cmp.end(),\
    \ c) - cmp.begin();\n        used.assign(V, false);\n        std::vector<int>\
    \ ret;\n        auto dfs = [&](auto &&dfs, int now, bool b0) -> bool {\n     \
    \       if (now == init and b0) return true;\n            for (auto nxt : to[now])\n\
    \                if (cmp[nxt] == c and !used[nxt]) {\n                    ret.emplace_back(nxt),\
    \ used[nxt] = 1;\n                    if (dfs(dfs, nxt, true)) return true;\n\
    \                    ret.pop_back();\n                }\n            return false;\n\
    \        };\n        dfs(dfs, init, false);\n        return ret;\n    }\n\n  \
    \  // After calling `FindStronglyConnectedComponents()`, generate a new graph\
    \ by uniting all vertices\n    // belonging to the same component(The resultant\
    \ graph is DAG).\n    DirectedGraphSCC GenerateTopologicalGraph() {\n        DirectedGraphSCC\
    \ newgraph(scc_num);\n        for (int s = 0; s < V; s++)\n            for (auto\
    \ t : to[s]) {\n                if (cmp[s] != cmp[t]) newgraph.add_edge(cmp[s],\
    \ cmp[t]);\n            }\n        return newgraph;\n    }\n};\n\n// 2-SAT solver:\
    \ Find a solution for  `(Ai v Aj) ^ (Ak v Al) ^ ... = true`\n// - `nb_sat_vars`:\
    \ Number of variables\n// - Considering a graph with `2 * nb_sat_vars` vertices\n\
    // - Vertices [0, nb_sat_vars) means `Ai`\n// - vertices [nb_sat_vars, 2 * nb_sat_vars)\
    \ means `not Ai`\nstruct SATSolver : DirectedGraphSCC {\n    int nb_sat_vars;\n\
    \    std::vector<int> solution;\n    SATSolver(int nb_variables = 0) : DirectedGraphSCC(nb_variables\
    \ * 2), nb_sat_vars(nb_variables), solution(nb_sat_vars) {}\n    void add_x_or_y_constraint(bool\
    \ is_x_true, int x, bool is_y_true, int y) {\n        assert(x >= 0 and x < nb_sat_vars);\n\
    \        assert(y >= 0 and y < nb_sat_vars);\n        if (!is_x_true) x += nb_sat_vars;\n\
    \        if (!is_y_true) y += nb_sat_vars;\n        add_edge((x + nb_sat_vars)\
    \ % (nb_sat_vars * 2), y);\n        add_edge((y + nb_sat_vars) % (nb_sat_vars\
    \ * 2), x);\n    }\n    // Solve the 2-SAT problem. If no solution exists, return\
    \ `false`.\n    // Otherwise, dump one solution to `solution` and return `true`.\n\
    \    bool run() {\n        FindStronglyConnectedComponents();\n        for (int\
    \ i = 0; i < nb_sat_vars; i++) {\n            if (cmp[i] == cmp[i + nb_sat_vars])\
    \ return false;\n            solution[i] = cmp[i] > cmp[i + nb_sat_vars];\n  \
    \      }\n        return true;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/strongly_connected_components.hpp
  requiredBy: []
  timestamp: '2020-11-21 18:08:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/2sat_solver.test.cpp
  - graph/test/cycle_detection_directed.test.cpp
  - graph/test/strongly_connected_components.test.cpp
  - graph/test/topological_sort.test.cpp
documentation_of: graph/strongly_connected_components.hpp
layout: document
redirect_from:
- /library/graph/strongly_connected_components.hpp
- /library/graph/strongly_connected_components.hpp.html
title: graph/strongly_connected_components.hpp
---
