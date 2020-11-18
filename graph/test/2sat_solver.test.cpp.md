---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/strongly_connected_components.hpp
    title: graph/strongly_connected_components.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "#line 1 \"graph/test/2sat_solver.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\
    \n#line 2 \"graph/strongly_connected_components.hpp\"\n#include <cassert>\n#include\
    \ <algorithm>\n#include <vector>\n\n// CUT begin\n// Directed graph library to\
    \ find strongly connected components \uFF08\u5F37\u9023\u7D50\u6210\u5206\u5206\
    \u89E3\uFF09\n// 0-indexed directed graph\n// Complexity: O(V + E)\nstruct DirectedGraphSCC\
    \ {\n    int V; // # of Vertices\n    std::vector<std::vector<int>> to, from;\n\
    \    std::vector<int> used;  // Only true/false\n    std::vector<int> vs;\n  \
    \  std::vector<int> cmp;\n    int scc_num = -1;\n\n    DirectedGraphSCC(int V\
    \ = 0) : V(V), to(V), from(V), cmp(V) {}\n\n    void _dfs(int v) {\n        used[v]\
    \ = true;\n        for (auto t : to[v]) if (!used[t]) _dfs(t);\n        vs.push_back(v);\n\
    \    }\n    void _rdfs(int v, int k) {\n        used[v] = true;\n        cmp[v]\
    \ = k;\n        for (auto t : from[v]) if (!used[t]) _rdfs(t, k);\n    }\n\n \
    \   void add_edge(int from_, int to_) {\n        assert(from_ >= 0 and from_ <\
    \ V and to_ >= 0 and to_ < V);\n        to[from_].push_back(to_);\n        from[to_].push_back(from_);\n\
    \    }\n\n    // Detect strongly connected components and return # of them.\n\
    \    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)\n    int\
    \ FindStronglyConnectedComponents() {\n        used.assign(V, false);\n      \
    \  vs.clear();\n        for (int v = 0; v < V; v++) if (!used[v]) _dfs(v);\n \
    \       used.assign(V, false);\n        scc_num = 0;\n        for (int i = (int)vs.size()\
    \ - 1; i >= 0; i--) if (!used[vs[i]]) _rdfs(vs[i], scc_num++);\n        return\
    \ scc_num;\n    }\n\n    // Find and output the vertices that form a closed cycle.\n\
    \    // output: {v_1, ..., v_C}, where C is the length of cycle,\n    //     \
    \    {} if there's NO cycle (graph is DAG)\n    std::vector<int> DetectCycle()\n\
    \    {\n        int ns = FindStronglyConnectedComponents();\n        if (ns ==\
    \ V) return {};\n        std::vector<int> cnt(ns);\n        for (auto x : cmp)\
    \ cnt[x]++;\n        const int c = std::find_if(cnt.begin(), cnt.end(), [](int\
    \ x) { return x > 1; }) - cnt.begin();\n        const int init = std::find(cmp.begin(),\
    \ cmp.end(), c) - cmp.begin();\n        used.assign(V, false);\n        std::vector<int>\
    \ ret;\n        auto dfs = [&](auto &&dfs, int now, bool b0) -> bool {\n     \
    \       if (now == init and b0) return true;\n            for (auto nxt : to[now])\
    \ if (cmp[nxt] == c and !used[nxt])\n            {\n                ret.emplace_back(nxt),\
    \ used[nxt] = 1;\n                if (dfs(dfs, nxt, true)) return true;\n    \
    \            ret.pop_back();\n            }\n            return false;\n     \
    \   };\n        dfs(dfs, init, false);\n        return ret;\n    }\n\n    // After\
    \ calling `FindStronglyConnectedComponents()`, generate a new graph by uniting\
    \ all vertices\n    // belonging to the same component(The resultant graph is\
    \ DAG).\n    DirectedGraphSCC GenerateTopologicalGraph() {\n        DirectedGraphSCC\
    \ newgraph(scc_num);\n        for (int s = 0; s < V; s++) for (auto t : to[s])\
    \ {\n            if (cmp[s] != cmp[t]) newgraph.add_edge(cmp[s], cmp[t]);\n  \
    \      }\n        return newgraph;\n    }\n};\n\n// 2-SAT solver: Find a solution\
    \ for  `(Ai v Aj) ^ (Ak v Al) ^ ... = true`\n// - `nb_sat_vars`: Number of variables\n\
    // - Considering a graph with `2 * nb_sat_vars` vertices\n// - Vertices [0, nb_sat_vars)\
    \ means `Ai`\n// - vertices [nb_sat_vars, 2 * nb_sat_vars) means `not Ai`\nstruct\
    \ SATSolver : DirectedGraphSCC {\n    int nb_sat_vars;\n    std::vector<int> solution;\n\
    \    SATSolver(int nb_variables = 0) : DirectedGraphSCC(nb_variables * 2), nb_sat_vars(nb_variables),\
    \ solution(nb_sat_vars) {}\n    void add_x_or_y_constraint(bool is_x_true, int\
    \ x, bool is_y_true, int y) {\n        assert(x >= 0 and x < nb_sat_vars);\n \
    \       assert(y >= 0 and y < nb_sat_vars);\n        if (!is_x_true) x += nb_sat_vars;\n\
    \        if (!is_y_true) y += nb_sat_vars;\n        add_edge((x + nb_sat_vars)\
    \ % (nb_sat_vars * 2), y);\n        add_edge((y + nb_sat_vars) % (nb_sat_vars\
    \ * 2), x);\n    }\n    // Solve the 2-SAT problem. If no solution exists, return\
    \ `false`.\n    // Otherwise, dump one solution to `solution` and return `true`.\n\
    \    bool run() {\n        FindStronglyConnectedComponents();\n        for (int\
    \ i = 0; i < nb_sat_vars; i++) {\n            if (cmp[i] == cmp[i + nb_sat_vars])\
    \ return false;\n            solution[i] = cmp[i] > cmp[i + nb_sat_vars];\n  \
    \      }\n        return true;\n    }\n};\n#line 4 \"graph/test/2sat_solver.test.cpp\"\
    \n#include <iostream>\n#include <stdio.h>\n#include <string>\n\nint main() {\n\
    \n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n    std::string\
    \ s;\n    int N, M;\n    std::cin >> s >> s >> N >> M;\n    SATSolver solver(N);\n\
    \    while (M--) {\n        int a, b;\n        std::cin >> a >> b >> s;\n    \
    \    solver.add_x_or_y_constraint(a > 0, abs(a) - 1, b > 0, abs(b) - 1);\n   \
    \ }\n    if (solver.run()) {\n        puts(\"s SATISFIABLE\");\n        printf(\"\
    v \");\n        for (int i = 0; i < N; i++) printf(\"%d \", (solver.solution[i]\
    \ ? 1 : -1) * (i + 1));\n        puts(\"0\");\n    } else {\n        puts(\"s\
    \ UNSATISFIABLE\");\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n#include \"\
    graph/strongly_connected_components.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <stdio.h>\n#include <string>\n\nint main() {\n\n    std::cin.tie(nullptr),\
    \ std::ios::sync_with_stdio(false);\n    std::string s;\n    int N, M;\n    std::cin\
    \ >> s >> s >> N >> M;\n    SATSolver solver(N);\n    while (M--) {\n        int\
    \ a, b;\n        std::cin >> a >> b >> s;\n        solver.add_x_or_y_constraint(a\
    \ > 0, abs(a) - 1, b > 0, abs(b) - 1);\n    }\n    if (solver.run()) {\n     \
    \   puts(\"s SATISFIABLE\");\n        printf(\"v \");\n        for (int i = 0;\
    \ i < N; i++) printf(\"%d \", (solver.solution[i] ? 1 : -1) * (i + 1));\n    \
    \    puts(\"0\");\n    } else {\n        puts(\"s UNSATISFIABLE\");\n    }\n}\n"
  dependsOn:
  - graph/strongly_connected_components.hpp
  isVerificationFile: true
  path: graph/test/2sat_solver.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/2sat_solver.test.cpp
layout: document
redirect_from:
- /verify/graph/test/2sat_solver.test.cpp
- /verify/graph/test/2sat_solver.test.cpp.html
title: graph/test/2sat_solver.test.cpp
---
