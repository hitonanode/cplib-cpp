---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/assignment_problem.test.cpp
    title: combinatorial_opt/test/assignment_problem.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mincostflow.test.cpp
    title: combinatorial_opt/test/mincostflow.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://community.topcoder.com/stat?c=problem_statement&pm=15702>
  bundledCode: "#line 2 \"combinatorial_opt/mincostflow_bellmanford.hpp\"\n#include\
    \ <cassert>\n#include <iostream>\n#include <limits>\n#include <queue>\n#include\
    \ <vector>\n\n// CUT begin\n/*\nMinCostFlow: Minimum-cost flow problem solver\
    \ WITH NO NEGATIVE CYCLE (just negative cost edge is allowed)\nVerified by SRM\
    \ 770 Div1 Medium <https://community.topcoder.com/stat?c=problem_statement&pm=15702>\n\
    */\ntemplate <typename CAP = long long, typename COST = long long> struct MinCostFlow\
    \ {\n    const COST INF_COST = std::numeric_limits<COST>::max() / 2;\n    struct\
    \ edge {\n        int to, rev;\n        CAP cap;\n        COST cost;\n       \
    \ friend std::ostream &operator<<(std::ostream &os, const edge &e) {\n       \
    \     os << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';\n\
    \            return os;\n        }\n    };\n    int V;\n    std::vector<std::vector<edge>>\
    \ g;\n    std::vector<COST> dist;\n    std::vector<int> prevv, preve;\n    std::vector<COST>\
    \ dual; // dual[V]: potential\n    std::vector<std::pair<int, int>> pos;\n\n \
    \   bool _calc_distance_bellman_ford(int s) { // O(VE), able to detect negative\
    \ cycle\n        dist.assign(V, INF_COST);\n        dist[s] = 0;\n        bool\
    \ upd = true;\n        int cnt = 0;\n        while (upd) {\n            upd =\
    \ false;\n            cnt++;\n            if (cnt > V) return false; // Negative\
    \ cycle existence\n            for (int v = 0; v < V; v++)\n                if\
    \ (dist[v] != INF_COST) {\n                    for (int i = 0; i < (int)g[v].size();\
    \ i++) {\n                        edge &e = g[v][i];\n                       \
    \ COST c = dist[v] + e.cost + dual[v] - dual[e.to];\n                        if\
    \ (e.cap > 0 and dist[e.to] > c) {\n                            dist[e.to] = c,\
    \ prevv[e.to] = v, preve[e.to] = i;\n                            upd = true;\n\
    \                        }\n                    }\n                }\n       \
    \ }\n        return true;\n    }\n\n    bool _calc_distance_dijkstra(int s) {\
    \ // O(ElogV)\n        dist.assign(V, INF_COST);\n        dist[s] = 0;\n     \
    \   using P = std::pair<COST, int>;\n        std::priority_queue<P, std::vector<P>,\
    \ std::greater<P>> q;\n        q.emplace(0, s);\n        while (!q.empty()) {\n\
    \            P p = q.top();\n            q.pop();\n            int v = p.second;\n\
    \            if (dist[v] < p.first) continue;\n            for (int i = 0; i <\
    \ (int)g[v].size(); i++) {\n                edge &e = g[v][i];\n             \
    \   COST c = dist[v] + e.cost + dual[v] - dual[e.to];\n                if (e.cap\
    \ > 0 and dist[e.to] > c) {\n                    dist[e.to] = c, prevv[e.to] =\
    \ v, preve[e.to] = i;\n                    q.emplace(dist[e.to], e.to);\n    \
    \            }\n            }\n        }\n        return true;\n    }\n\n    MinCostFlow(int\
    \ V = 0) : V(V), g(V) {}\n\n    void add_edge(int from, int to, CAP cap, COST\
    \ cost) {\n        assert(0 <= from and from < V);\n        assert(0 <= to and\
    \ to < V);\n        pos.emplace_back(from, g[from].size());\n        g[from].emplace_back(edge{to,\
    \ (int)g[to].size() + (from == to), cap, cost});\n        g[to].emplace_back(edge{from,\
    \ (int)g[from].size() - 1, (CAP)0, -cost});\n    }\n\n    std::pair<CAP, COST>\
    \ flow(int s, int t, const CAP &f) {\n        /*\n        Flush amount of `f`\
    \ from `s` to `t` using the Dijkstra's algorithm\n        works for graph with\
    \ no negative cycles (negative cost edges are allowed)\n        retval: (flow,\
    \ cost)\n        */\n        COST ret = 0;\n        dual.assign(V, 0);\n     \
    \   prevv.assign(V, -1);\n        preve.assign(V, -1);\n        CAP frem = f;\n\
    \        while (frem > 0) {\n            _calc_distance_dijkstra(s);\n       \
    \     if (dist[t] == INF_COST) break;\n            for (int v = 0; v < V; v++)\
    \ dual[v] = std::min(dual[v] + dist[v], INF_COST);\n            CAP d = frem;\n\
    \            for (int v = t; v != s; v = prevv[v]) { d = std::min(d, g[prevv[v]][preve[v]].cap);\
    \ }\n            frem -= d;\n            ret += d * dual[t];\n            for\
    \ (int v = t; v != s; v = prevv[v]) {\n                edge &e = g[prevv[v]][preve[v]];\n\
    \                e.cap -= d;\n                g[v][e.rev].cap += d;\n        \
    \    }\n        }\n        return std::make_pair(f - frem, ret);\n    }\n\n  \
    \  friend std::ostream &operator<<(std::ostream &os, const MinCostFlow &mcf) {\n\
    \        os << \"[MinCostFlow]V=\" << mcf.V << \":\";\n        for (int i = 0;\
    \ i < (int)mcf.g.size(); i++)\n            for (auto &e : mcf.g[i]) { os << \"\
    \\n\" << i << \"->\" << e.to << \": cap=\" << e.cap << \", cost=\" << e.cost;\
    \ }\n        return os;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\n// CUT begin\n/*\nMinCostFlow: Minimum-cost\
    \ flow problem solver WITH NO NEGATIVE CYCLE (just negative cost edge is allowed)\n\
    Verified by SRM 770 Div1 Medium <https://community.topcoder.com/stat?c=problem_statement&pm=15702>\n\
    */\ntemplate <typename CAP = long long, typename COST = long long> struct MinCostFlow\
    \ {\n    const COST INF_COST = std::numeric_limits<COST>::max() / 2;\n    struct\
    \ edge {\n        int to, rev;\n        CAP cap;\n        COST cost;\n       \
    \ friend std::ostream &operator<<(std::ostream &os, const edge &e) {\n       \
    \     os << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';\n\
    \            return os;\n        }\n    };\n    int V;\n    std::vector<std::vector<edge>>\
    \ g;\n    std::vector<COST> dist;\n    std::vector<int> prevv, preve;\n    std::vector<COST>\
    \ dual; // dual[V]: potential\n    std::vector<std::pair<int, int>> pos;\n\n \
    \   bool _calc_distance_bellman_ford(int s) { // O(VE), able to detect negative\
    \ cycle\n        dist.assign(V, INF_COST);\n        dist[s] = 0;\n        bool\
    \ upd = true;\n        int cnt = 0;\n        while (upd) {\n            upd =\
    \ false;\n            cnt++;\n            if (cnt > V) return false; // Negative\
    \ cycle existence\n            for (int v = 0; v < V; v++)\n                if\
    \ (dist[v] != INF_COST) {\n                    for (int i = 0; i < (int)g[v].size();\
    \ i++) {\n                        edge &e = g[v][i];\n                       \
    \ COST c = dist[v] + e.cost + dual[v] - dual[e.to];\n                        if\
    \ (e.cap > 0 and dist[e.to] > c) {\n                            dist[e.to] = c,\
    \ prevv[e.to] = v, preve[e.to] = i;\n                            upd = true;\n\
    \                        }\n                    }\n                }\n       \
    \ }\n        return true;\n    }\n\n    bool _calc_distance_dijkstra(int s) {\
    \ // O(ElogV)\n        dist.assign(V, INF_COST);\n        dist[s] = 0;\n     \
    \   using P = std::pair<COST, int>;\n        std::priority_queue<P, std::vector<P>,\
    \ std::greater<P>> q;\n        q.emplace(0, s);\n        while (!q.empty()) {\n\
    \            P p = q.top();\n            q.pop();\n            int v = p.second;\n\
    \            if (dist[v] < p.first) continue;\n            for (int i = 0; i <\
    \ (int)g[v].size(); i++) {\n                edge &e = g[v][i];\n             \
    \   COST c = dist[v] + e.cost + dual[v] - dual[e.to];\n                if (e.cap\
    \ > 0 and dist[e.to] > c) {\n                    dist[e.to] = c, prevv[e.to] =\
    \ v, preve[e.to] = i;\n                    q.emplace(dist[e.to], e.to);\n    \
    \            }\n            }\n        }\n        return true;\n    }\n\n    MinCostFlow(int\
    \ V = 0) : V(V), g(V) {}\n\n    void add_edge(int from, int to, CAP cap, COST\
    \ cost) {\n        assert(0 <= from and from < V);\n        assert(0 <= to and\
    \ to < V);\n        pos.emplace_back(from, g[from].size());\n        g[from].emplace_back(edge{to,\
    \ (int)g[to].size() + (from == to), cap, cost});\n        g[to].emplace_back(edge{from,\
    \ (int)g[from].size() - 1, (CAP)0, -cost});\n    }\n\n    std::pair<CAP, COST>\
    \ flow(int s, int t, const CAP &f) {\n        /*\n        Flush amount of `f`\
    \ from `s` to `t` using the Dijkstra's algorithm\n        works for graph with\
    \ no negative cycles (negative cost edges are allowed)\n        retval: (flow,\
    \ cost)\n        */\n        COST ret = 0;\n        dual.assign(V, 0);\n     \
    \   prevv.assign(V, -1);\n        preve.assign(V, -1);\n        CAP frem = f;\n\
    \        while (frem > 0) {\n            _calc_distance_dijkstra(s);\n       \
    \     if (dist[t] == INF_COST) break;\n            for (int v = 0; v < V; v++)\
    \ dual[v] = std::min(dual[v] + dist[v], INF_COST);\n            CAP d = frem;\n\
    \            for (int v = t; v != s; v = prevv[v]) { d = std::min(d, g[prevv[v]][preve[v]].cap);\
    \ }\n            frem -= d;\n            ret += d * dual[t];\n            for\
    \ (int v = t; v != s; v = prevv[v]) {\n                edge &e = g[prevv[v]][preve[v]];\n\
    \                e.cap -= d;\n                g[v][e.rev].cap += d;\n        \
    \    }\n        }\n        return std::make_pair(f - frem, ret);\n    }\n\n  \
    \  friend std::ostream &operator<<(std::ostream &os, const MinCostFlow &mcf) {\n\
    \        os << \"[MinCostFlow]V=\" << mcf.V << \":\";\n        for (int i = 0;\
    \ i < (int)mcf.g.size(); i++)\n            for (auto &e : mcf.g[i]) { os << \"\
    \\n\" << i << \"->\" << e.to << \": cap=\" << e.cap << \", cost=\" << e.cost;\
    \ }\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/mincostflow_bellmanford.hpp
  requiredBy: []
  timestamp: '2020-12-14 02:23:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/mincostflow.test.cpp
  - combinatorial_opt/test/assignment_problem.test.cpp
documentation_of: combinatorial_opt/mincostflow_bellmanford.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/mincostflow_bellmanford.hpp
- /library/combinatorial_opt/mincostflow_bellmanford.hpp.html
title: combinatorial_opt/mincostflow_bellmanford.hpp
---
