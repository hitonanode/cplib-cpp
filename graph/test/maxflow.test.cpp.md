---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/maxflow.hpp
    title: graph/maxflow.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
  bundledCode: "#line 2 \"graph/maxflow.hpp\"\n#include <algorithm>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\n// CUT begin\n// MaxFlow (Dinic algorithm)\n\
    template <typename T>\nstruct MaxFlow\n{\n    struct edge { int to; T cap; int\
    \ rev; };\n    std::vector<std::vector<edge>> edges;\n    std::vector<int> level;\
    \  // level[i] = distance between vertex S and i (Default: -1)\n    std::vector<int>\
    \ iter;  // iteration counter, used for Dinic's DFS\n    std::vector<int> used;\
    \  // Used for Ford-Fulkerson's Algorithm\n\n    void bfs(int s)\n    {\n    \
    \    level.assign(edges.size(), -1);\n        std::queue<int> q;\n        level[s]\
    \ = 0;\n        q.push(s);\n        while (!q.empty()) {\n            int v =\
    \ q.front();\n            q.pop();\n            for (edge &e : edges[v]) {\n \
    \               if (e.cap > 0 and level[e.to] < 0) {\n                    level[e.to]\
    \ = level[v] + 1;\n                    q.push(e.to);\n                }\n    \
    \        }\n        }\n    }\n \n    T dfs_dinic(int v, int goal, T f)\n    {\n\
    \        if (v == goal) return f;\n        for (int &i = iter[v]; i < (int)edges[v].size();\
    \ i++) {\n            edge &e = edges[v][i];\n            if (e.cap > 0 and level[v]\
    \ < level[e.to]) {\n                T d = dfs_dinic(e.to, goal, std::min(f, e.cap));\n\
    \                if (d > 0) {\n                    e.cap -= d;\n             \
    \       edges[e.to][e.rev].cap += d;\n                    return d;\n        \
    \        }\n            }\n        }\n        return 0;\n    }\n \n    T dfs_ff(int\
    \ v, int goal, T f)\n    {\n        if (v == goal) return f;\n        used[v]\
    \ = true;\n        for (edge &e : edges[v]) {\n            if (e.cap > 0 && !used[e.to])\
    \ {\n                T d = dfs_ff(e.to, goal, std::min(f, e.cap));\n         \
    \       if (d > 0) {\n                    e.cap -= d;\n                    edges[e.to][e.rev].cap\
    \ += d;\n                    return d;\n                }\n            }\n   \
    \     }\n        return 0;\n    }\n \npublic:\n    MaxFlow(int N) { edges.resize(N);\
    \ }\n    void add_edge(int from, int to, T capacity)\n    {\n        edges[from].push_back(edge{to,\
    \ capacity, (int)edges[to].size()});\n        edges[to].push_back(edge{from, (T)0,\
    \ (int)edges[from].size() - 1});\n    }\n \n    // Dinic algorithm\n    // Complexity:\
    \ O(VE)\n    T Dinic(int s, int t)\n    {\n        constexpr T INF = std::numeric_limits<T>::max();\n\
    \        T flow = 0;\n        while (true) {\n            bfs(s);\n          \
    \  if (level[t] < 0) return flow;\n            iter.assign(edges.size(), 0);\n\
    \            T f;\n            while ((f = dfs_dinic(s, t, INF)) > 0) flow +=\
    \ f;\n        }\n    }\n\n    // Ford-Fulkerson algorithm\n    // Complexity:\
    \ O(EF)\n    T FF(int s, int t)\n    {\n        constexpr T INF = std::numeric_limits<T>::max();\n\
    \        T flow = 0;\n        while (true) {\n            used.assign(edges.size(),\
    \ 0);\n            T f = dfs_ff(s, t, INF);\n            if (f == 0) return flow;\n\
    \            flow += f;\n        }\n    }\n \n    void back_flow(int s, int t,\
    \ int s_e, int t_e, T capacity_reduce)\n    {\n        int i;\n        for (i=0;\
    \ edges[s_e][i].to != t_e; ) i++;\n        edge &e = edges[s_e][i];\n \n     \
    \   if (capacity_reduce <= e.cap) {\n            e.cap -= capacity_reduce;\n \
    \       }\n        else {\n            T flow = capacity_reduce - e.cap;\n   \
    \         e.cap = 0;\n            edges[e.to][e.rev].cap -= flow;\n \n       \
    \     T f_sum = 0;\n            while (f_sum != flow) {\n                used.assign(edges.size(),\
    \ 0);\n                f_sum += dfs_ff(t, t_e, flow - f_sum);\n            }\n\
    \            f_sum = 0;\n            while (f_sum != flow) {\n               \
    \ used.assign(edges.size(), 0);\n                f_sum += dfs_ff(s_e, s, flow\
    \ - f_sum);\n            }\n        }\n    }\n};\n#line 2 \"graph/test/maxflow.test.cpp\"\
    \n#include <cassert>\n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\
    \n\nint main()\n{\n    int V, E;\n    std::cin >> V >> E;\n    MaxFlow<int> ff(V),\
    \ dinic(V);\n    while (E--) {\n        int u, v, c;\n        std::cin >> u >>\
    \ v >> c;\n        ff.add_edge(u, v, c);\n        dinic.add_edge(u, v, c);\n \
    \   }\n    int ret_ff = ff.FF(0, V - 1);\n    int ret_dinic = dinic.Dinic(0, V\
    \ - 1);\n    assert(ret_ff == ret_dinic);\n    std::cout << ret_ff << std::endl;\n\
    }\n"
  code: "#include \"graph/maxflow.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\
    \n\nint main()\n{\n    int V, E;\n    std::cin >> V >> E;\n    MaxFlow<int> ff(V),\
    \ dinic(V);\n    while (E--) {\n        int u, v, c;\n        std::cin >> u >>\
    \ v >> c;\n        ff.add_edge(u, v, c);\n        dinic.add_edge(u, v, c);\n \
    \   }\n    int ret_ff = ff.FF(0, V - 1);\n    int ret_dinic = dinic.Dinic(0, V\
    \ - 1);\n    assert(ret_ff == ret_dinic);\n    std::cout << ret_ff << std::endl;\n\
    }\n"
  dependsOn:
  - graph/maxflow.hpp
  isVerificationFile: true
  path: graph/test/maxflow.test.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:40:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/maxflow.test.cpp
layout: document
redirect_from:
- /verify/graph/test/maxflow.test.cpp
- /verify/graph/test/maxflow.test.cpp.html
title: graph/test/maxflow.test.cpp
---
