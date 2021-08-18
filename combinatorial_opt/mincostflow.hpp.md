---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mincostflow.test.cpp
    title: combinatorial_opt/test/mincostflow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html
    - https://github.com/iwiwi/radix-heap)
  bundledCode: "#line 2 \"combinatorial_opt/mincostflow.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <queue>\n#include <vector>\n\n\
    // CUT begin\n// MinCostFlow based on AtCoder Library, no namespace, no private\
    \ variables, compatible with C++11\n// **NO NEGATIVE COST EDGES**\n// Reference:\
    \ https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html\n\
    // Remark: You can use [radix heap](https://github.com/iwiwi/radix-heap) for Dijkstra\
    \ acceleration\ntemplate <class Cap, class Cost> struct mcf_graph {\n    mcf_graph()\
    \ {}\n    mcf_graph(int n) : _n(n), g(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int add_edge(int from,\
    \ int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n   \
    \     assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        assert(0\
    \ <= cost);\n        int m = int(pos.size());\n        pos.push_back({from, int(g[from].size())});\n\
    \        int from_id = int(g[from].size());\n        int to_id = int(g[to].size());\n\
    \        if (from == to) to_id++;\n        g[from].push_back(_edge{to, to_id,\
    \ cap, cost});\n        g[to].push_back(_edge{from, from_id, 0, -cost});\n   \
    \     return m;\n    }\n\n    struct edge {\n        int from, to;\n        Cap\
    \ cap, flow;\n        Cost cost;\n    };\n\n    edge get_edge(int i) {\n     \
    \   int m = int(pos.size());\n        assert(0 <= i && i < m);\n        auto _e\
    \ = g[pos[i].first][pos[i].second];\n        auto _re = g[_e.to][_e.rev];\n  \
    \      return edge{\n            pos[i].first, _e.to, _e.cap + _re.cap, _re.cap,\
    \ _e.cost,\n        };\n    }\n    std::vector<edge> edges() {\n        int m\
    \ = int(pos.size());\n        std::vector<edge> result(m);\n        for (int i\
    \ = 0; i < m; i++) { result[i] = get_edge(i); }\n        return result;\n    }\n\
    \n    std::pair<Cap, Cost> flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max());\
    \ }\n    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) { return slope(s,\
    \ t, flow_limit).back(); }\n    std::vector<std::pair<Cap, Cost>> slope(int s,\
    \ int t) {\n        return slope(s, t, std::numeric_limits<Cap>::max());\n   \
    \ }\n\n    std::vector<Cost> dual, dist;\n    std::vector<int> pv, pe;\n    std::vector<bool>\
    \ vis;\n    struct Q {\n        Cost key;\n        int to;\n        bool operator<(Q\
    \ r) const { return key > r.key; }\n    };\n    std::vector<Q> que;\n    bool\
    \ _dual_ref(int s, int t) {\n        std::fill(dist.begin(), dist.end(), std::numeric_limits<Cost>::max());\n\
    \        std::fill(vis.begin(), vis.end(), false);\n        que.clear();\n\n \
    \       dist[s] = 0;\n        que.push_back(Q{0, s});\n        std::push_heap(que.begin(),\
    \ que.end());\n        while (!que.empty()) {\n            int v = que.front().to;\n\
    \            std::pop_heap(que.begin(), que.end());\n            que.pop_back();\n\
    \            if (vis[v]) continue;\n            vis[v] = true;\n            if\
    \ (v == t) break;\n            // dist[v] = shortest(s, v) + dual[s] - dual[v]\n\
    \            // dist[v] >= 0 (all reduced cost are positive)\n            // dist[v]\
    \ <= (n-1)C\n            for (int i = 0; i < int(g[v].size()); i++) {\n      \
    \          auto e = g[v][i];\n                if (vis[e.to] || !e.cap) continue;\n\
    \                // |-dual[e.to] + dual[v]| <= (n-1)C\n                // cost\
    \ <= C - -(n-1)C + 0 = nC\n                Cost cost = e.cost - dual[e.to] + dual[v];\n\
    \                if (dist[e.to] - dist[v] > cost) {\n                    dist[e.to]\
    \ = dist[v] + cost;\n                    pv[e.to] = v;\n                    pe[e.to]\
    \ = i;\n                    que.push_back(Q{dist[e.to], e.to});\n            \
    \        std::push_heap(que.begin(), que.end());\n                }\n        \
    \    }\n        }\n        if (!vis[t]) { return false; }\n\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (!vis[v]) continue;\n            // dual[v]\
    \ = dual[v] - dist[t] + dist[v]\n            //         = dual[v] - (shortest(s,\
    \ t) + dual[s] - dual[t]) + (shortest(s, v) + dual[s] - dual[v])\n           \
    \ //         = - shortest(s, t) + dual[t] + shortest(s, v)\n            //   \
    \      = shortest(s, v) - shortest(s, t) >= 0 - (n-1)C\n            dual[v] -=\
    \ dist[t] - dist[v];\n        }\n        return true;\n    }\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n\
    \        assert(0 <= t && t < _n);\n        assert(s != t);\n        // variants\
    \ (C = maxcost):\n        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n  \
    \      // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n\
    \        dual.assign(_n, 0), dist.assign(_n, 0);\n        pv.assign(_n, 0), pe.assign(_n,\
    \ 0);\n        vis.assign(_n, false);\n        Cap flow = 0;\n        Cost cost\
    \ = 0, prev_cost_per_flow = -1;\n        std::vector<std::pair<Cap, Cost>> result;\n\
    \        result.push_back({flow, cost});\n        while (flow < flow_limit) {\n\
    \            if (!_dual_ref(s, t)) break;\n            Cap c = flow_limit - flow;\n\
    \            for (int v = t; v != s; v = pv[v]) { c = std::min(c, g[pv[v]][pe[v]].cap);\
    \ }\n            for (int v = t; v != s; v = pv[v]) {\n                auto& e\
    \ = g[pv[v]][pe[v]];\n                e.cap -= c;\n                g[v][e.rev].cap\
    \ += c;\n            }\n            Cost d = -dual[s];\n            flow += c;\n\
    \            cost += c * d;\n            if (prev_cost_per_flow == d) { result.pop_back();\
    \ }\n            result.push_back({flow, cost});\n            prev_cost_per_flow\
    \ = d;\n        }\n        return result;\n    }\n\n    struct _edge {\n     \
    \   int to, rev;\n        Cap cap;\n        Cost cost;\n    };\n\n    int _n;\n\
    \    std::vector<std::pair<int, int>> pos;\n    std::vector<std::vector<_edge>>\
    \ g;\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\n// CUT begin\n// MinCostFlow based on AtCoder\
    \ Library, no namespace, no private variables, compatible with C++11\n// **NO\
    \ NEGATIVE COST EDGES**\n// Reference: https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html\n\
    // Remark: You can use [radix heap](https://github.com/iwiwi/radix-heap) for Dijkstra\
    \ acceleration\ntemplate <class Cap, class Cost> struct mcf_graph {\n    mcf_graph()\
    \ {}\n    mcf_graph(int n) : _n(n), g(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int add_edge(int from,\
    \ int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n   \
    \     assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        assert(0\
    \ <= cost);\n        int m = int(pos.size());\n        pos.push_back({from, int(g[from].size())});\n\
    \        int from_id = int(g[from].size());\n        int to_id = int(g[to].size());\n\
    \        if (from == to) to_id++;\n        g[from].push_back(_edge{to, to_id,\
    \ cap, cost});\n        g[to].push_back(_edge{from, from_id, 0, -cost});\n   \
    \     return m;\n    }\n\n    struct edge {\n        int from, to;\n        Cap\
    \ cap, flow;\n        Cost cost;\n    };\n\n    edge get_edge(int i) {\n     \
    \   int m = int(pos.size());\n        assert(0 <= i && i < m);\n        auto _e\
    \ = g[pos[i].first][pos[i].second];\n        auto _re = g[_e.to][_e.rev];\n  \
    \      return edge{\n            pos[i].first, _e.to, _e.cap + _re.cap, _re.cap,\
    \ _e.cost,\n        };\n    }\n    std::vector<edge> edges() {\n        int m\
    \ = int(pos.size());\n        std::vector<edge> result(m);\n        for (int i\
    \ = 0; i < m; i++) { result[i] = get_edge(i); }\n        return result;\n    }\n\
    \n    std::pair<Cap, Cost> flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max());\
    \ }\n    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) { return slope(s,\
    \ t, flow_limit).back(); }\n    std::vector<std::pair<Cap, Cost>> slope(int s,\
    \ int t) {\n        return slope(s, t, std::numeric_limits<Cap>::max());\n   \
    \ }\n\n    std::vector<Cost> dual, dist;\n    std::vector<int> pv, pe;\n    std::vector<bool>\
    \ vis;\n    struct Q {\n        Cost key;\n        int to;\n        bool operator<(Q\
    \ r) const { return key > r.key; }\n    };\n    std::vector<Q> que;\n    bool\
    \ _dual_ref(int s, int t) {\n        std::fill(dist.begin(), dist.end(), std::numeric_limits<Cost>::max());\n\
    \        std::fill(vis.begin(), vis.end(), false);\n        que.clear();\n\n \
    \       dist[s] = 0;\n        que.push_back(Q{0, s});\n        std::push_heap(que.begin(),\
    \ que.end());\n        while (!que.empty()) {\n            int v = que.front().to;\n\
    \            std::pop_heap(que.begin(), que.end());\n            que.pop_back();\n\
    \            if (vis[v]) continue;\n            vis[v] = true;\n            if\
    \ (v == t) break;\n            // dist[v] = shortest(s, v) + dual[s] - dual[v]\n\
    \            // dist[v] >= 0 (all reduced cost are positive)\n            // dist[v]\
    \ <= (n-1)C\n            for (int i = 0; i < int(g[v].size()); i++) {\n      \
    \          auto e = g[v][i];\n                if (vis[e.to] || !e.cap) continue;\n\
    \                // |-dual[e.to] + dual[v]| <= (n-1)C\n                // cost\
    \ <= C - -(n-1)C + 0 = nC\n                Cost cost = e.cost - dual[e.to] + dual[v];\n\
    \                if (dist[e.to] - dist[v] > cost) {\n                    dist[e.to]\
    \ = dist[v] + cost;\n                    pv[e.to] = v;\n                    pe[e.to]\
    \ = i;\n                    que.push_back(Q{dist[e.to], e.to});\n            \
    \        std::push_heap(que.begin(), que.end());\n                }\n        \
    \    }\n        }\n        if (!vis[t]) { return false; }\n\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (!vis[v]) continue;\n            // dual[v]\
    \ = dual[v] - dist[t] + dist[v]\n            //         = dual[v] - (shortest(s,\
    \ t) + dual[s] - dual[t]) + (shortest(s, v) + dual[s] - dual[v])\n           \
    \ //         = - shortest(s, t) + dual[t] + shortest(s, v)\n            //   \
    \      = shortest(s, v) - shortest(s, t) >= 0 - (n-1)C\n            dual[v] -=\
    \ dist[t] - dist[v];\n        }\n        return true;\n    }\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n\
    \        assert(0 <= t && t < _n);\n        assert(s != t);\n        // variants\
    \ (C = maxcost):\n        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n  \
    \      // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n\
    \        dual.assign(_n, 0), dist.assign(_n, 0);\n        pv.assign(_n, 0), pe.assign(_n,\
    \ 0);\n        vis.assign(_n, false);\n        Cap flow = 0;\n        Cost cost\
    \ = 0, prev_cost_per_flow = -1;\n        std::vector<std::pair<Cap, Cost>> result;\n\
    \        result.push_back({flow, cost});\n        while (flow < flow_limit) {\n\
    \            if (!_dual_ref(s, t)) break;\n            Cap c = flow_limit - flow;\n\
    \            for (int v = t; v != s; v = pv[v]) { c = std::min(c, g[pv[v]][pe[v]].cap);\
    \ }\n            for (int v = t; v != s; v = pv[v]) {\n                auto& e\
    \ = g[pv[v]][pe[v]];\n                e.cap -= c;\n                g[v][e.rev].cap\
    \ += c;\n            }\n            Cost d = -dual[s];\n            flow += c;\n\
    \            cost += c * d;\n            if (prev_cost_per_flow == d) { result.pop_back();\
    \ }\n            result.push_back({flow, cost});\n            prev_cost_per_flow\
    \ = d;\n        }\n        return result;\n    }\n\n    struct _edge {\n     \
    \   int to, rev;\n        Cap cap;\n        Cost cost;\n    };\n\n    int _n;\n\
    \    std::vector<std::pair<int, int>> pos;\n    std::vector<std::vector<_edge>>\
    \ g;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/mincostflow.hpp
  requiredBy: []
  timestamp: '2021-07-06 00:01:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/mincostflow.test.cpp
documentation_of: combinatorial_opt/mincostflow.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/mincostflow.hpp
- /library/combinatorial_opt/mincostflow.hpp.html
title: combinatorial_opt/mincostflow.hpp
---
