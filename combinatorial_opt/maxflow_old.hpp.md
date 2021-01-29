---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/maxflow_old.hpp\"\n#include <algorithm>\n\
    #include <limits>\n#include <vector>\n\n// CUT begin\n// MaxFlow (Dinic algorithm)\n\
    template <typename T> struct [[deprecated(\"use ACL based mf_graph\")]] MaxFlow\
    \ {\n    struct edge {\n        int to;\n        T cap;\n        int rev;\n  \
    \  };\n    std::vector<std::vector<edge>> edges;\n    std::vector<int> level;\
    \ // level[i] = distance between vertex S and i (Default: -1)\n    std::vector<int>\
    \ iter;  // iteration counter, used for Dinic's DFS\n    std::vector<int> used;\
    \  // Used for Ford-Fulkerson's Algorithm\n\n    struct simple_queue_int {\n \
    \       std::vector<int> payload;\n        int pos = 0;\n        void reserve(int\
    \ n) { payload.reserve(n); }\n        int size() const { return int(payload.size())\
    \ - pos; }\n        bool empty() const { return pos == int(payload.size()); }\n\
    \        void push(const int &t) { payload.push_back(t); }\n        int &front()\
    \ { return payload[pos]; }\n        void clear() {\n            payload.clear();\n\
    \            pos = 0;\n        }\n        void pop() { pos++; }\n    };\n    void\
    \ bfs(int s) {\n        level.assign(edges.size(), -1);\n        simple_queue_int\
    \ q;\n        level[s] = 0;\n        q.push(s);\n        while (!q.empty()) {\n\
    \            int v = q.front();\n            q.pop();\n            for (edge &e\
    \ : edges[v]) {\n                if (e.cap > 0 and level[e.to] < 0) {\n      \
    \              level[e.to] = level[v] + 1;\n                    q.push(e.to);\n\
    \                }\n            }\n        }\n    }\n\n    T dfs_dinic(int v,\
    \ int goal, T f) {\n        if (v == goal) return f;\n        for (int &i = iter[v];\
    \ i < (int)edges[v].size(); i++) {\n            edge &e = edges[v][i];\n     \
    \       if (e.cap > 0 and level[v] < level[e.to]) {\n                T d = dfs_dinic(e.to,\
    \ goal, std::min(f, e.cap));\n                if (d > 0) {\n                 \
    \   e.cap -= d;\n                    edges[e.to][e.rev].cap += d;\n          \
    \          return d;\n                }\n            }\n        }\n        return\
    \ 0;\n    }\n\n    T dfs_ff(int v, int goal, T f) {\n        if (v == goal) return\
    \ f;\n        used[v] = true;\n        for (edge &e : edges[v]) {\n          \
    \  if (e.cap > 0 && !used[e.to]) {\n                T d = dfs_ff(e.to, goal, std::min(f,\
    \ e.cap));\n                if (d > 0) {\n                    e.cap -= d;\n  \
    \                  edges[e.to][e.rev].cap += d;\n                    return d;\n\
    \                }\n            }\n        }\n        return 0;\n    }\n\n   \
    \ MaxFlow(int N) { edges.resize(N); }\n    void add_edge(int from, int to, T capacity)\
    \ {\n        edges[from].push_back(edge{to, capacity, (int)edges[to].size()});\n\
    \        edges[to].push_back(edge{from, (T)0, (int)edges[from].size() - 1});\n\
    \    }\n\n    // Dinic algorithm\n    // Complexity: O(V^2 E)\n    T Dinic(int\
    \ s, int t, T req) {\n        T flow = 0;\n        while (req > 0) {\n       \
    \     bfs(s);\n            if (level[t] < 0) break;\n            iter.assign(edges.size(),\
    \ 0);\n            T f;\n            while ((f = dfs_dinic(s, t, req)) > 0) flow\
    \ += f, req -= f;\n        }\n        return flow;\n    }\n    T Dinic(int s,\
    \ int t) { return Dinic(s, t, std::numeric_limits<T>::max()); }\n\n    // Ford-Fulkerson\
    \ algorithm\n    // Complexity: O(EF)\n    T FF(int s, int t) {\n        constexpr\
    \ T INF = std::numeric_limits<T>::max();\n        T flow = 0;\n        while (true)\
    \ {\n            used.assign(edges.size(), 0);\n            T f = dfs_ff(s, t,\
    \ INF);\n            if (f == 0) return flow;\n            flow += f;\n      \
    \  }\n    }\n\n    void back_flow(int s, int t, int s_e, int t_e, T capacity_reduce)\
    \ {\n        int i;\n        for (i = 0; edges[s_e][i].to != t_e;) i++;\n    \
    \    edge &e = edges[s_e][i];\n\n        if (capacity_reduce <= e.cap) {\n   \
    \         e.cap -= capacity_reduce;\n        } else {\n            T flow = capacity_reduce\
    \ - e.cap;\n            e.cap = 0;\n            edges[e.to][e.rev].cap -= flow;\n\
    \n            T f_sum = 0;\n            while (f_sum != flow) {\n            \
    \    used.assign(edges.size(), 0);\n                f_sum += dfs_ff(t, t_e, flow\
    \ - f_sum);\n            }\n            f_sum = 0;\n            while (f_sum !=\
    \ flow) {\n                used.assign(edges.size(), 0);\n                f_sum\
    \ += dfs_ff(s_e, s, flow - f_sum);\n            }\n        }\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <limits>\n#include <vector>\n\
    \n// CUT begin\n// MaxFlow (Dinic algorithm)\ntemplate <typename T> struct [[deprecated(\"\
    use ACL based mf_graph\")]] MaxFlow {\n    struct edge {\n        int to;\n  \
    \      T cap;\n        int rev;\n    };\n    std::vector<std::vector<edge>> edges;\n\
    \    std::vector<int> level; // level[i] = distance between vertex S and i (Default:\
    \ -1)\n    std::vector<int> iter;  // iteration counter, used for Dinic's DFS\n\
    \    std::vector<int> used;  // Used for Ford-Fulkerson's Algorithm\n\n    struct\
    \ simple_queue_int {\n        std::vector<int> payload;\n        int pos = 0;\n\
    \        void reserve(int n) { payload.reserve(n); }\n        int size() const\
    \ { return int(payload.size()) - pos; }\n        bool empty() const { return pos\
    \ == int(payload.size()); }\n        void push(const int &t) { payload.push_back(t);\
    \ }\n        int &front() { return payload[pos]; }\n        void clear() {\n \
    \           payload.clear();\n            pos = 0;\n        }\n        void pop()\
    \ { pos++; }\n    };\n    void bfs(int s) {\n        level.assign(edges.size(),\
    \ -1);\n        simple_queue_int q;\n        level[s] = 0;\n        q.push(s);\n\
    \        while (!q.empty()) {\n            int v = q.front();\n            q.pop();\n\
    \            for (edge &e : edges[v]) {\n                if (e.cap > 0 and level[e.to]\
    \ < 0) {\n                    level[e.to] = level[v] + 1;\n                  \
    \  q.push(e.to);\n                }\n            }\n        }\n    }\n\n    T\
    \ dfs_dinic(int v, int goal, T f) {\n        if (v == goal) return f;\n      \
    \  for (int &i = iter[v]; i < (int)edges[v].size(); i++) {\n            edge &e\
    \ = edges[v][i];\n            if (e.cap > 0 and level[v] < level[e.to]) {\n  \
    \              T d = dfs_dinic(e.to, goal, std::min(f, e.cap));\n            \
    \    if (d > 0) {\n                    e.cap -= d;\n                    edges[e.to][e.rev].cap\
    \ += d;\n                    return d;\n                }\n            }\n   \
    \     }\n        return 0;\n    }\n\n    T dfs_ff(int v, int goal, T f) {\n  \
    \      if (v == goal) return f;\n        used[v] = true;\n        for (edge &e\
    \ : edges[v]) {\n            if (e.cap > 0 && !used[e.to]) {\n               \
    \ T d = dfs_ff(e.to, goal, std::min(f, e.cap));\n                if (d > 0) {\n\
    \                    e.cap -= d;\n                    edges[e.to][e.rev].cap +=\
    \ d;\n                    return d;\n                }\n            }\n      \
    \  }\n        return 0;\n    }\n\n    MaxFlow(int N) { edges.resize(N); }\n  \
    \  void add_edge(int from, int to, T capacity) {\n        edges[from].push_back(edge{to,\
    \ capacity, (int)edges[to].size()});\n        edges[to].push_back(edge{from, (T)0,\
    \ (int)edges[from].size() - 1});\n    }\n\n    // Dinic algorithm\n    // Complexity:\
    \ O(V^2 E)\n    T Dinic(int s, int t, T req) {\n        T flow = 0;\n        while\
    \ (req > 0) {\n            bfs(s);\n            if (level[t] < 0) break;\n   \
    \         iter.assign(edges.size(), 0);\n            T f;\n            while ((f\
    \ = dfs_dinic(s, t, req)) > 0) flow += f, req -= f;\n        }\n        return\
    \ flow;\n    }\n    T Dinic(int s, int t) { return Dinic(s, t, std::numeric_limits<T>::max());\
    \ }\n\n    // Ford-Fulkerson algorithm\n    // Complexity: O(EF)\n    T FF(int\
    \ s, int t) {\n        constexpr T INF = std::numeric_limits<T>::max();\n    \
    \    T flow = 0;\n        while (true) {\n            used.assign(edges.size(),\
    \ 0);\n            T f = dfs_ff(s, t, INF);\n            if (f == 0) return flow;\n\
    \            flow += f;\n        }\n    }\n\n    void back_flow(int s, int t,\
    \ int s_e, int t_e, T capacity_reduce) {\n        int i;\n        for (i = 0;\
    \ edges[s_e][i].to != t_e;) i++;\n        edge &e = edges[s_e][i];\n\n       \
    \ if (capacity_reduce <= e.cap) {\n            e.cap -= capacity_reduce;\n   \
    \     } else {\n            T flow = capacity_reduce - e.cap;\n            e.cap\
    \ = 0;\n            edges[e.to][e.rev].cap -= flow;\n\n            T f_sum = 0;\n\
    \            while (f_sum != flow) {\n                used.assign(edges.size(),\
    \ 0);\n                f_sum += dfs_ff(t, t_e, flow - f_sum);\n            }\n\
    \            f_sum = 0;\n            while (f_sum != flow) {\n               \
    \ used.assign(edges.size(), 0);\n                f_sum += dfs_ff(s_e, s, flow\
    \ - f_sum);\n            }\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/maxflow_old.hpp
  requiredBy: []
  timestamp: '2020-12-14 02:23:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/maxflow_old.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/maxflow_old.hpp
- /library/combinatorial_opt/maxflow_old.hpp.html
title: combinatorial_opt/maxflow_old.hpp
---
