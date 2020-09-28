---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: flow/test/assignment_problem.test.cpp
    title: flow/test/assignment_problem.test.cpp
  - icon: ':x:'
    path: flow/test/min_cost_b_flow.test.cpp
    title: flow/test/min_cost_b_flow.test.cpp
  - icon: ':heavy_check_mark:'
    path: flow/test/mincostflow.test.cpp
    title: flow/test/mincostflow.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links:
    - https://community.topcoder.com/stat?c=problem_statement&pm=15702>
  bundledCode: "#line 2 \"flow/mincostflow.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <limits>\n#include <queue>\n#include <vector>\n\n// CUT begin\n/*\nMinCostFlow:\
    \ Minimum-cost flow problem solver WITH NO NEGATIVE CYCLE\nVerified by SRM 770\
    \ Div1 Medium <https://community.topcoder.com/stat?c=problem_statement&pm=15702>\n\
    */\ntemplate <typename CAP = long long, typename COST = long long>\nstruct MinCostFlow\n\
    {\n    const COST INF_COST = std::numeric_limits<COST>::max() / 2;\n    struct\
    \ edge {\n        int to, rev;\n        CAP cap;\n        COST cost;\n       \
    \ friend std::ostream &operator<<(std::ostream &os, const edge &e) {\n       \
    \     os << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';\n\
    \            return os;\n        }\n    };\n    int V;\n    std::vector<std::vector<edge>>\
    \ G;\n    std::vector<COST> dist;\n    std::vector<int> prevv, preve;\n    std::vector<COST>\
    \ h;  // h[V]: potential\n    std::vector<std::pair<int, int>> einfo;\n\n    bool\
    \ _calc_distance_bellman_ford(int s) {  // O(VE), able to detect negative cycle\n\
    \        dist.assign(V, INF_COST);\n        dist[s] = 0;\n        bool upd = true;\n\
    \        int cnt = 0;\n        while (upd) {\n            upd = false;\n     \
    \       cnt++;\n            if (cnt > V) return false;  // Negative cycle existence\n\
    \            for (int v = 0; v < V; v++) if (dist[v] != INF_COST) {\n        \
    \        for (int i = 0; i < (int)G[v].size(); i++) {\n                    edge\
    \ &e = G[v][i];\n                    COST c = dist[v] + e.cost + h[v] - h[e.to];\n\
    \                    if (e.cap > 0 and dist[e.to] > c) {\n                   \
    \     dist[e.to] = c, prevv[e.to] = v, preve[e.to] = i;\n                    \
    \    upd = true;\n                    }\n                }\n            }\n  \
    \      }\n        return true;\n    }\n\n    bool _calc_distance_dijkstra(int\
    \ s) {  // O(ElogV)\n        dist.assign(V, INF_COST);\n        dist[s] = 0;\n\
    \        using P = std::pair<COST, int>;\n        std::priority_queue<P, std::vector<P>,\
    \ std::greater<P>> q;\n        q.emplace(0, s);\n        while (!q.empty()) {\n\
    \            P p = q.top();\n            q.pop();\n            int v = p.second;\n\
    \            if (dist[v] < p.first) continue;\n            for (int i = 0; i <\
    \ (int)G[v].size(); i++) {\n                edge &e = G[v][i];\n             \
    \   COST c = dist[v] + e.cost + h[v] - h[e.to];\n                if (e.cap > 0\
    \ and dist[e.to] > c) {\n                    dist[e.to] = c, prevv[e.to] = v,\
    \ preve[e.to] = i;\n                    q.emplace(dist[e.to], e.to);\n       \
    \         }\n            }\n        }\n        return true;\n    }\n\n    MinCostFlow(int\
    \ V=0) : V(V), G(V) {}\n\n    void add_edge(int from, int to, CAP cap, COST cost)\
    \ {\n        assert(0 <= from and from < V);\n        assert(0 <= to and to <\
    \ V);\n        einfo.emplace_back(from, G[from].size());\n        G[from].emplace_back(edge{to,\
    \ (int)G[to].size() + (from == to), cap, cost});\n        G[to].emplace_back(edge{from,\
    \ (int)G[from].size() - 1, (CAP)0, -cost});\n    }\n\n    std::pair<COST, std::pair<bool,\
    \ CAP>> flush(int s, int t, CAP f) {\n        /*\n        Flush amount of `f`\
    \ from `s` to `t` using the Dijkstra's algorithm\n        works for graph with\
    \ no negative cycles (negative cost edges are allowed)\n        retval: (min_flow,\
    \ ([succeeded or not], residue flow))\n        [Example] Succeeded: `([mincost],\
    \ (true, 0))`\n        */\n        COST ret = 0;\n        h.assign(V, 0);\n  \
    \      prevv.assign(V, -1);\n        preve.assign(V, -1);\n        while (f >\
    \ 0) {\n            _calc_distance_dijkstra(s);\n            if (dist[t] == INF_COST)\
    \ return std::make_pair(ret, std::make_pair(false, f));\n            for (int\
    \ v = 0; v < V; v++) h[v] = std::min(h[v] + dist[v], INF_COST);\n            CAP\
    \ d = f;\n            for (int v = t; v != s; v = prevv[v]) {\n              \
    \  d = std::min(d, G[prevv[v]][preve[v]].cap);\n            }\n            f -=\
    \ d;\n            ret += d * h[t];\n            for (int v = t; v != s; v = prevv[v])\
    \ {\n                edge &e = G[prevv[v]][preve[v]];\n                e.cap -=\
    \ d;\n                G[v][e.rev].cap += d;\n            }\n        }\n      \
    \  return std::make_pair(ret, std::make_pair(true, 0));\n    }\n\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const MinCostFlow &mcf) {\n        os << \"[MinCostFlow]V=\"\
    \ << mcf.V << \":\";\n        for (int i = 0; i < (int)mcf.G.size(); i++) for\
    \ (auto &e : mcf.G[i]) {\n            os << \"\\n\" << i << \"->\" << e.to <<\
    \ \": cap=\" << e.cap << \", cost=\" << e.cost;\n        }\n        return os;\n\
    \    }\n};\n\ntemplate <typename CAP, typename COST>\nstruct B_Flow\n{\n    int\
    \ N, E;\n    MinCostFlow<CAP, COST> mcf;\n    std::vector<CAP> b;\n    COST cost_bias;\n\
    \    std::vector<CAP> fbias;\n    std::vector<int> fdir;\n    bool infeasible;\n\
    \n    std::vector<CAP> f;\n    const std::vector<COST> &potential;\n\n    B_Flow(int\
    \ N = 0) : N(N), E(0), mcf(N + 2), b(N), cost_bias(0), infeasible(false), potential(mcf.h)\
    \ {}\n\n    void add_supply(int v, CAP supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, CAP demand) { b[v] -= demand; }\n    void add_edge(int s, int t, CAP lower_cap,\
    \ CAP upper_cap, COST cost)\n    {\n        assert(s >= 0 and s < N);\n      \
    \  assert(t >= 0 and t < N);\n        if (lower_cap > upper_cap)\n        {\n\
    \            infeasible = true;\n            return;\n        }\n        E++;\n\
    \        if (s == t)\n        {\n            if (cost > 0) upper_cap = lower_cap;\n\
    \            else lower_cap = upper_cap;\n        }\n        if (cost < 0)\n \
    \       {\n            fbias.emplace_back(lower_cap);\n            fdir.emplace_back(-1);\n\
    \            cost_bias += cost * upper_cap;\n            b[s] -= upper_cap;\n\
    \            b[t] += upper_cap;\n            mcf.add_edge(t, s, upper_cap - lower_cap,\
    \ -cost);\n        }\n        else\n        {\n            fbias.emplace_back(upper_cap);\n\
    \            fdir.emplace_back(1);\n            if (lower_cap < 0)\n         \
    \   {\n                cost_bias += cost * lower_cap, b[s] -= lower_cap, b[t]\
    \ += lower_cap;\n                upper_cap -= lower_cap, lower_cap = 0;\n    \
    \        }\n            if (lower_cap > 0)\n            {\n                cost_bias\
    \ += cost * lower_cap;\n                b[s] -= lower_cap;\n                b[t]\
    \ += lower_cap;\n                upper_cap -= lower_cap;\n            }\n    \
    \        mcf.add_edge(s, t, upper_cap, cost);\n        }\n    }\n\n    std::pair<bool,\
    \ COST> solve()\n    {\n        if (infeasible)\n        {\n            return\
    \ std::make_pair(false, 0);\n        }\n        CAP bsum = 0, bsum_negative =\
    \ 0;\n        for (int i = 0; i < N; i++)\n        {\n            if (b[i] > 0)\n\
    \            {\n                mcf.add_edge(N, i, b[i], 0);\n               \
    \ bsum += b[i];\n            }\n            if (b[i] < 0)\n            {\n   \
    \             mcf.add_edge(i, N + 1, -b[i], 0);\n                bsum_negative\
    \ -= b[i];\n            }\n        }\n        if (bsum != bsum_negative)\n   \
    \     {\n            return std::make_pair(false, 0);\n        }\n        std::fill(b.begin(),\
    \ b.end(), 0);\n        auto ret = mcf.flush(N, N + 1, bsum);\n        COST cost_ret\
    \ = cost_bias + ret.first;\n        cost_bias = 0;\n        bool succeeded = ret.second.first;\n\
    \        f = fbias;\n        for (int i = 0; i < E; i++)\n        {\n        \
    \    std::pair<int, int> p = mcf.einfo[i];\n            f[i] -= fdir[i] * mcf.G[p.first][p.second].cap;\n\
    \        }\n        return std::make_pair(succeeded, cost_ret);\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\n// CUT begin\n/*\nMinCostFlow: Minimum-cost\
    \ flow problem solver WITH NO NEGATIVE CYCLE\nVerified by SRM 770 Div1 Medium\
    \ <https://community.topcoder.com/stat?c=problem_statement&pm=15702>\n*/\ntemplate\
    \ <typename CAP = long long, typename COST = long long>\nstruct MinCostFlow\n\
    {\n    const COST INF_COST = std::numeric_limits<COST>::max() / 2;\n    struct\
    \ edge {\n        int to, rev;\n        CAP cap;\n        COST cost;\n       \
    \ friend std::ostream &operator<<(std::ostream &os, const edge &e) {\n       \
    \     os << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';\n\
    \            return os;\n        }\n    };\n    int V;\n    std::vector<std::vector<edge>>\
    \ G;\n    std::vector<COST> dist;\n    std::vector<int> prevv, preve;\n    std::vector<COST>\
    \ h;  // h[V]: potential\n    std::vector<std::pair<int, int>> einfo;\n\n    bool\
    \ _calc_distance_bellman_ford(int s) {  // O(VE), able to detect negative cycle\n\
    \        dist.assign(V, INF_COST);\n        dist[s] = 0;\n        bool upd = true;\n\
    \        int cnt = 0;\n        while (upd) {\n            upd = false;\n     \
    \       cnt++;\n            if (cnt > V) return false;  // Negative cycle existence\n\
    \            for (int v = 0; v < V; v++) if (dist[v] != INF_COST) {\n        \
    \        for (int i = 0; i < (int)G[v].size(); i++) {\n                    edge\
    \ &e = G[v][i];\n                    COST c = dist[v] + e.cost + h[v] - h[e.to];\n\
    \                    if (e.cap > 0 and dist[e.to] > c) {\n                   \
    \     dist[e.to] = c, prevv[e.to] = v, preve[e.to] = i;\n                    \
    \    upd = true;\n                    }\n                }\n            }\n  \
    \      }\n        return true;\n    }\n\n    bool _calc_distance_dijkstra(int\
    \ s) {  // O(ElogV)\n        dist.assign(V, INF_COST);\n        dist[s] = 0;\n\
    \        using P = std::pair<COST, int>;\n        std::priority_queue<P, std::vector<P>,\
    \ std::greater<P>> q;\n        q.emplace(0, s);\n        while (!q.empty()) {\n\
    \            P p = q.top();\n            q.pop();\n            int v = p.second;\n\
    \            if (dist[v] < p.first) continue;\n            for (int i = 0; i <\
    \ (int)G[v].size(); i++) {\n                edge &e = G[v][i];\n             \
    \   COST c = dist[v] + e.cost + h[v] - h[e.to];\n                if (e.cap > 0\
    \ and dist[e.to] > c) {\n                    dist[e.to] = c, prevv[e.to] = v,\
    \ preve[e.to] = i;\n                    q.emplace(dist[e.to], e.to);\n       \
    \         }\n            }\n        }\n        return true;\n    }\n\n    MinCostFlow(int\
    \ V=0) : V(V), G(V) {}\n\n    void add_edge(int from, int to, CAP cap, COST cost)\
    \ {\n        assert(0 <= from and from < V);\n        assert(0 <= to and to <\
    \ V);\n        einfo.emplace_back(from, G[from].size());\n        G[from].emplace_back(edge{to,\
    \ (int)G[to].size() + (from == to), cap, cost});\n        G[to].emplace_back(edge{from,\
    \ (int)G[from].size() - 1, (CAP)0, -cost});\n    }\n\n    std::pair<COST, std::pair<bool,\
    \ CAP>> flush(int s, int t, CAP f) {\n        /*\n        Flush amount of `f`\
    \ from `s` to `t` using the Dijkstra's algorithm\n        works for graph with\
    \ no negative cycles (negative cost edges are allowed)\n        retval: (min_flow,\
    \ ([succeeded or not], residue flow))\n        [Example] Succeeded: `([mincost],\
    \ (true, 0))`\n        */\n        COST ret = 0;\n        h.assign(V, 0);\n  \
    \      prevv.assign(V, -1);\n        preve.assign(V, -1);\n        while (f >\
    \ 0) {\n            _calc_distance_dijkstra(s);\n            if (dist[t] == INF_COST)\
    \ return std::make_pair(ret, std::make_pair(false, f));\n            for (int\
    \ v = 0; v < V; v++) h[v] = std::min(h[v] + dist[v], INF_COST);\n            CAP\
    \ d = f;\n            for (int v = t; v != s; v = prevv[v]) {\n              \
    \  d = std::min(d, G[prevv[v]][preve[v]].cap);\n            }\n            f -=\
    \ d;\n            ret += d * h[t];\n            for (int v = t; v != s; v = prevv[v])\
    \ {\n                edge &e = G[prevv[v]][preve[v]];\n                e.cap -=\
    \ d;\n                G[v][e.rev].cap += d;\n            }\n        }\n      \
    \  return std::make_pair(ret, std::make_pair(true, 0));\n    }\n\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const MinCostFlow &mcf) {\n        os << \"[MinCostFlow]V=\"\
    \ << mcf.V << \":\";\n        for (int i = 0; i < (int)mcf.G.size(); i++) for\
    \ (auto &e : mcf.G[i]) {\n            os << \"\\n\" << i << \"->\" << e.to <<\
    \ \": cap=\" << e.cap << \", cost=\" << e.cost;\n        }\n        return os;\n\
    \    }\n};\n\ntemplate <typename CAP, typename COST>\nstruct B_Flow\n{\n    int\
    \ N, E;\n    MinCostFlow<CAP, COST> mcf;\n    std::vector<CAP> b;\n    COST cost_bias;\n\
    \    std::vector<CAP> fbias;\n    std::vector<int> fdir;\n    bool infeasible;\n\
    \n    std::vector<CAP> f;\n    const std::vector<COST> &potential;\n\n    B_Flow(int\
    \ N = 0) : N(N), E(0), mcf(N + 2), b(N), cost_bias(0), infeasible(false), potential(mcf.h)\
    \ {}\n\n    void add_supply(int v, CAP supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, CAP demand) { b[v] -= demand; }\n    void add_edge(int s, int t, CAP lower_cap,\
    \ CAP upper_cap, COST cost)\n    {\n        assert(s >= 0 and s < N);\n      \
    \  assert(t >= 0 and t < N);\n        if (lower_cap > upper_cap)\n        {\n\
    \            infeasible = true;\n            return;\n        }\n        E++;\n\
    \        if (s == t)\n        {\n            if (cost > 0) upper_cap = lower_cap;\n\
    \            else lower_cap = upper_cap;\n        }\n        if (cost < 0)\n \
    \       {\n            fbias.emplace_back(lower_cap);\n            fdir.emplace_back(-1);\n\
    \            cost_bias += cost * upper_cap;\n            b[s] -= upper_cap;\n\
    \            b[t] += upper_cap;\n            mcf.add_edge(t, s, upper_cap - lower_cap,\
    \ -cost);\n        }\n        else\n        {\n            fbias.emplace_back(upper_cap);\n\
    \            fdir.emplace_back(1);\n            if (lower_cap < 0)\n         \
    \   {\n                cost_bias += cost * lower_cap, b[s] -= lower_cap, b[t]\
    \ += lower_cap;\n                upper_cap -= lower_cap, lower_cap = 0;\n    \
    \        }\n            if (lower_cap > 0)\n            {\n                cost_bias\
    \ += cost * lower_cap;\n                b[s] -= lower_cap;\n                b[t]\
    \ += lower_cap;\n                upper_cap -= lower_cap;\n            }\n    \
    \        mcf.add_edge(s, t, upper_cap, cost);\n        }\n    }\n\n    std::pair<bool,\
    \ COST> solve()\n    {\n        if (infeasible)\n        {\n            return\
    \ std::make_pair(false, 0);\n        }\n        CAP bsum = 0, bsum_negative =\
    \ 0;\n        for (int i = 0; i < N; i++)\n        {\n            if (b[i] > 0)\n\
    \            {\n                mcf.add_edge(N, i, b[i], 0);\n               \
    \ bsum += b[i];\n            }\n            if (b[i] < 0)\n            {\n   \
    \             mcf.add_edge(i, N + 1, -b[i], 0);\n                bsum_negative\
    \ -= b[i];\n            }\n        }\n        if (bsum != bsum_negative)\n   \
    \     {\n            return std::make_pair(false, 0);\n        }\n        std::fill(b.begin(),\
    \ b.end(), 0);\n        auto ret = mcf.flush(N, N + 1, bsum);\n        COST cost_ret\
    \ = cost_bias + ret.first;\n        cost_bias = 0;\n        bool succeeded = ret.second.first;\n\
    \        f = fbias;\n        for (int i = 0; i < E; i++)\n        {\n        \
    \    std::pair<int, int> p = mcf.einfo[i];\n            f[i] -= fdir[i] * mcf.G[p.first][p.second].cap;\n\
    \        }\n        return std::make_pair(succeeded, cost_ret);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/mincostflow.hpp
  requiredBy: []
  timestamp: '2020-09-29 02:28:46+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - flow/test/min_cost_b_flow.test.cpp
  - flow/test/assignment_problem.test.cpp
  - flow/test/mincostflow.test.cpp
documentation_of: flow/mincostflow.hpp
layout: document
redirect_from:
- /library/flow/mincostflow.hpp
- /library/flow/mincostflow.hpp.html
title: flow/mincostflow.hpp
---
