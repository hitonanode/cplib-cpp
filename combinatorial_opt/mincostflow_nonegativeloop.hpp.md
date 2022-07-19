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
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mincostflow.yuki1288.test.cpp
    title: combinatorial_opt/test/mincostflow.yuki1288.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mincostflow.yuki1324.test.cpp
    title: combinatorial_opt/test/mincostflow.yuki1324.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://community.topcoder.com/stat?c=problem_statement&pm=15702
    - https://www.codechef.com/problems/ANCT
  bundledCode: "#line 2 \"combinatorial_opt/mincostflow_nonegativeloop.hpp\"\n#include\
    \ <cassert>\n#include <limits>\n#include <queue>\n#include <vector>\n\n// CUT\
    \ begin\n// Minimum cost flow WITH NO NEGATIVE CYCLE (just negative cost edge\
    \ is allowed)\n// Verified:\n// - SRM 770 Div1 Medium https://community.topcoder.com/stat?c=problem_statement&pm=15702\n\
    // - CodeChef LTIME98 Ancient Magic https://www.codechef.com/problems/ANCT\ntemplate\
    \ <class Cap, class Cost, Cost INF_COST = std::numeric_limits<Cost>::max() / 2>\n\
    struct MinCostFlow {\n    template <class E> struct csr {\n        std::vector<int>\
    \ start;\n        std::vector<E> elist;\n        explicit csr(int n, const std::vector<std::pair<int,\
    \ E>> &edges)\n            : start(n + 1), elist(edges.size()) {\n           \
    \ for (auto e : edges) { start[e.first + 1]++; }\n            for (int i = 1;\
    \ i <= n; i++) { start[i] += start[i - 1]; }\n            auto counter = start;\n\
    \            for (auto e : edges) { elist[counter[e.first]++] = e.second; }\n\
    \        }\n    };\n\npublic:\n    MinCostFlow() {}\n    explicit MinCostFlow(int\
    \ n) : is_dual_infeasible(false), _n(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int add_edge(int from,\
    \ int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n   \
    \     assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        if (cost\
    \ < 0) is_dual_infeasible = true;\n        int m = int(_edges.size());\n     \
    \   _edges.push_back({from, to, cap, 0, cost});\n        return m;\n    }\n\n\
    \    struct edge {\n        int from, to;\n        Cap cap, flow;\n        Cost\
    \ cost;\n    };\n\n    edge get_edge(int i) {\n        int m = int(_edges.size());\n\
    \        assert(0 <= i && i < m);\n        return _edges[i];\n    }\n    std::vector<edge>\
    \ edges() { return _edges; }\n\n    std::pair<Cap, Cost> flow(int s, int t) {\
    \ return flow(s, t, std::numeric_limits<Cap>::max()); }\n    std::pair<Cap, Cost>\
    \ flow(int s, int t, Cap flow_limit) {\n        return slope(s, t, flow_limit).back();\n\
    \    }\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {\n        return\
    \ slope(s, t, std::numeric_limits<Cap>::max());\n    }\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n\
    \        assert(0 <= t && t < _n);\n        assert(s != t);\n\n        int m =\
    \ int(_edges.size());\n        std::vector<int> edge_idx(m);\n\n        auto g\
    \ = [&]() {\n            std::vector<int> degree(_n), redge_idx(m);\n        \
    \    std::vector<std::pair<int, _edge>> elist;\n            elist.reserve(2 *\
    \ m);\n            for (int i = 0; i < m; i++) {\n                auto e = _edges[i];\n\
    \                edge_idx[i] = degree[e.from]++;\n                redge_idx[i]\
    \ = degree[e.to]++;\n                elist.push_back({e.from, {e.to, -1, e.cap\
    \ - e.flow, e.cost}});\n                elist.push_back({e.to, {e.from, -1, e.flow,\
    \ -e.cost}});\n            }\n            auto _g = csr<_edge>(_n, elist);\n \
    \           for (int i = 0; i < m; i++) {\n                auto e = _edges[i];\n\
    \                edge_idx[i] += _g.start[e.from];\n                redge_idx[i]\
    \ += _g.start[e.to];\n                _g.elist[edge_idx[i]].rev = redge_idx[i];\n\
    \                _g.elist[redge_idx[i]].rev = edge_idx[i];\n            }\n  \
    \          return _g;\n        }();\n\n        auto result = slope(g, s, t, flow_limit);\n\
    \n        for (int i = 0; i < m; i++) {\n            auto e = g.elist[edge_idx[i]];\n\
    \            _edges[i].flow = _edges[i].cap - e.cap;\n        }\n\n        return\
    \ result;\n    }\n\nprivate:\n    bool is_dual_infeasible;\n    int _n;\n    std::vector<edge>\
    \ _edges;\n\n    // inside edge\n    struct _edge {\n        int to, rev;\n  \
    \      Cap cap;\n        Cost cost;\n    };\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(csr<_edge> &g, int s, int t, Cap flow_limit) {\n        // variants\
    \ (C = maxcost):\n        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n  \
    \      // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n\
    \n        // dual_dist[i] = (dual[i], dist[i])\n        std::vector<std::pair<Cost,\
    \ Cost>> dual_dist(_n);\n        if (is_dual_infeasible) {\n            auto check_dag\
    \ = [&]() {\n                std::vector<int> deg_in(_n);\n                for\
    \ (int v = 0; v < _n; v++) {\n                    for (int i = g.start[v]; i <\
    \ g.start[v + 1]; i++) {\n                        deg_in[g.elist[i].to] += g.elist[i].cap\
    \ > 0;\n                    }\n                }\n                std::vector<int>\
    \ st;\n                st.reserve(_n);\n                for (int i = 0; i < _n;\
    \ i++) {\n                    if (!deg_in[i]) st.push_back(i);\n             \
    \   }\n                for (int n = 0; n < _n; n++) {\n                    if\
    \ (int(st.size()) == n) return false; // Not DAG\n                    int now\
    \ = st[n];\n                    for (int i = g.start[now]; i < g.start[now + 1];\
    \ i++) {\n                        const auto &e = g.elist[i];\n              \
    \          if (!e.cap) continue;\n                        deg_in[e.to]--;\n  \
    \                      if (deg_in[e.to] == 0) st.push_back(e.to);\n          \
    \              if (dual_dist[e.to].first >= dual_dist[now].first + e.cost)\n \
    \                           dual_dist[e.to].first = dual_dist[now].first + e.cost;\n\
    \                    }\n                }\n                return true;\n    \
    \        }();\n            if (!check_dag) throw;\n            auto dt = dual_dist[t].first;\n\
    \            for (int v = 0; v < _n; v++) dual_dist[v].first -= dt;\n        \
    \    is_dual_infeasible = false;\n        }\n        std::vector<int> prev_e(_n);\n\
    \        std::vector<bool> vis(_n);\n        struct Q {\n            Cost key;\n\
    \            int to;\n            bool operator<(Q r) const { return key > r.key;\
    \ }\n        };\n        std::vector<int> que_min;\n        std::vector<Q> que;\n\
    \        auto dual_ref = [&]() {\n            for (int i = 0; i < _n; i++) {\n\
    \                dual_dist[i].second = std::numeric_limits<Cost>::max();\n   \
    \         }\n            std::fill(vis.begin(), vis.end(), false);\n         \
    \   que_min.clear();\n            que.clear();\n\n            // que[0..heap_r)\
    \ was heapified\n            unsigned heap_r = 0;\n\n            dual_dist[s].second\
    \ = 0;\n            que_min.push_back(s);\n            while (!que_min.empty()\
    \ || !que.empty()) {\n                int v;\n                if (!que_min.empty())\
    \ {\n                    v = que_min.back();\n                    que_min.pop_back();\n\
    \                } else {\n                    while (heap_r < que.size()) {\n\
    \                        heap_r++;\n                        std::push_heap(que.begin(),\
    \ que.begin() + heap_r);\n                    }\n                    v = que.front().to;\n\
    \                    std::pop_heap(que.begin(), que.end());\n                \
    \    que.pop_back();\n                    heap_r--;\n                }\n     \
    \           if (vis[v]) continue;\n                vis[v] = true;\n          \
    \      if (v == t) break;\n                // dist[v] = shortest(s, v) + dual[s]\
    \ - dual[v]\n                // dist[v] >= 0 (all reduced cost are positive)\n\
    \                // dist[v] <= (n-1)C\n                Cost dual_v = dual_dist[v].first,\
    \ dist_v = dual_dist[v].second;\n                for (int i = g.start[v]; i <\
    \ g.start[v + 1]; i++) {\n                    auto e = g.elist[i];\n         \
    \           if (!e.cap) continue;\n                    // |-dual[e.to] + dual[v]|\
    \ <= (n-1)C\n                    // cost <= C - -(n-1)C + 0 = nC\n           \
    \         Cost cost = e.cost - dual_dist[e.to].first + dual_v;\n             \
    \       if (dual_dist[e.to].second - dist_v > cost) {\n                      \
    \  Cost dist_to = dist_v + cost;\n                        dual_dist[e.to].second\
    \ = dist_to;\n                        prev_e[e.to] = e.rev;\n                \
    \        if (dist_to == dist_v) {\n                            que_min.push_back(e.to);\n\
    \                        } else {\n                            que.push_back(Q{dist_to,\
    \ e.to});\n                        }\n                    }\n                }\n\
    \            }\n            if (!vis[t]) { return false; }\n\n            for\
    \ (int v = 0; v < _n; v++) {\n                if (!vis[v]) continue;\n       \
    \         // dual[v] = dual[v] - dist[t] + dist[v]\n                //       \
    \  = dual[v] - (shortest(s, t) + dual[s] - dual[t]) +\n                //    \
    \     (shortest(s, v) + dual[s] - dual[v]) = - shortest(s,\n                //\
    \         t) + dual[t] + shortest(s, v) = shortest(s, v) -\n                //\
    \         shortest(s, t) >= 0 - (n-1)C\n                dual_dist[v].first -=\
    \ dual_dist[t].second - dual_dist[v].second;\n            }\n            return\
    \ true;\n        };\n        Cap flow = 0;\n        Cost cost = 0, prev_cost_per_flow\
    \ = -1;\n        std::vector<std::pair<Cap, Cost>> result = {{Cap(0), Cost(0)}};\n\
    \        while (flow < flow_limit) {\n            if (!dual_ref()) break;\n  \
    \          Cap c = flow_limit - flow;\n            for (int v = t; v != s; v =\
    \ g.elist[prev_e[v]].to) {\n                c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);\n\
    \            }\n            for (int v = t; v != s; v = g.elist[prev_e[v]].to)\
    \ {\n                auto &e = g.elist[prev_e[v]];\n                e.cap += c;\n\
    \                g.elist[e.rev].cap -= c;\n            }\n            Cost d =\
    \ -dual_dist[s].first;\n            flow += c;\n            cost += c * d;\n \
    \           if (prev_cost_per_flow == d) { result.pop_back(); }\n            result.push_back({flow,\
    \ cost});\n            prev_cost_per_flow = d;\n        }\n        return result;\n\
    \    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <limits>\n#include <queue>\n#include\
    \ <vector>\n\n// CUT begin\n// Minimum cost flow WITH NO NEGATIVE CYCLE (just\
    \ negative cost edge is allowed)\n// Verified:\n// - SRM 770 Div1 Medium https://community.topcoder.com/stat?c=problem_statement&pm=15702\n\
    // - CodeChef LTIME98 Ancient Magic https://www.codechef.com/problems/ANCT\ntemplate\
    \ <class Cap, class Cost, Cost INF_COST = std::numeric_limits<Cost>::max() / 2>\n\
    struct MinCostFlow {\n    template <class E> struct csr {\n        std::vector<int>\
    \ start;\n        std::vector<E> elist;\n        explicit csr(int n, const std::vector<std::pair<int,\
    \ E>> &edges)\n            : start(n + 1), elist(edges.size()) {\n           \
    \ for (auto e : edges) { start[e.first + 1]++; }\n            for (int i = 1;\
    \ i <= n; i++) { start[i] += start[i - 1]; }\n            auto counter = start;\n\
    \            for (auto e : edges) { elist[counter[e.first]++] = e.second; }\n\
    \        }\n    };\n\npublic:\n    MinCostFlow() {}\n    explicit MinCostFlow(int\
    \ n) : is_dual_infeasible(false), _n(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int add_edge(int from,\
    \ int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n   \
    \     assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        if (cost\
    \ < 0) is_dual_infeasible = true;\n        int m = int(_edges.size());\n     \
    \   _edges.push_back({from, to, cap, 0, cost});\n        return m;\n    }\n\n\
    \    struct edge {\n        int from, to;\n        Cap cap, flow;\n        Cost\
    \ cost;\n    };\n\n    edge get_edge(int i) {\n        int m = int(_edges.size());\n\
    \        assert(0 <= i && i < m);\n        return _edges[i];\n    }\n    std::vector<edge>\
    \ edges() { return _edges; }\n\n    std::pair<Cap, Cost> flow(int s, int t) {\
    \ return flow(s, t, std::numeric_limits<Cap>::max()); }\n    std::pair<Cap, Cost>\
    \ flow(int s, int t, Cap flow_limit) {\n        return slope(s, t, flow_limit).back();\n\
    \    }\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {\n        return\
    \ slope(s, t, std::numeric_limits<Cap>::max());\n    }\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n\
    \        assert(0 <= t && t < _n);\n        assert(s != t);\n\n        int m =\
    \ int(_edges.size());\n        std::vector<int> edge_idx(m);\n\n        auto g\
    \ = [&]() {\n            std::vector<int> degree(_n), redge_idx(m);\n        \
    \    std::vector<std::pair<int, _edge>> elist;\n            elist.reserve(2 *\
    \ m);\n            for (int i = 0; i < m; i++) {\n                auto e = _edges[i];\n\
    \                edge_idx[i] = degree[e.from]++;\n                redge_idx[i]\
    \ = degree[e.to]++;\n                elist.push_back({e.from, {e.to, -1, e.cap\
    \ - e.flow, e.cost}});\n                elist.push_back({e.to, {e.from, -1, e.flow,\
    \ -e.cost}});\n            }\n            auto _g = csr<_edge>(_n, elist);\n \
    \           for (int i = 0; i < m; i++) {\n                auto e = _edges[i];\n\
    \                edge_idx[i] += _g.start[e.from];\n                redge_idx[i]\
    \ += _g.start[e.to];\n                _g.elist[edge_idx[i]].rev = redge_idx[i];\n\
    \                _g.elist[redge_idx[i]].rev = edge_idx[i];\n            }\n  \
    \          return _g;\n        }();\n\n        auto result = slope(g, s, t, flow_limit);\n\
    \n        for (int i = 0; i < m; i++) {\n            auto e = g.elist[edge_idx[i]];\n\
    \            _edges[i].flow = _edges[i].cap - e.cap;\n        }\n\n        return\
    \ result;\n    }\n\nprivate:\n    bool is_dual_infeasible;\n    int _n;\n    std::vector<edge>\
    \ _edges;\n\n    // inside edge\n    struct _edge {\n        int to, rev;\n  \
    \      Cap cap;\n        Cost cost;\n    };\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(csr<_edge> &g, int s, int t, Cap flow_limit) {\n        // variants\
    \ (C = maxcost):\n        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n  \
    \      // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n\
    \n        // dual_dist[i] = (dual[i], dist[i])\n        std::vector<std::pair<Cost,\
    \ Cost>> dual_dist(_n);\n        if (is_dual_infeasible) {\n            auto check_dag\
    \ = [&]() {\n                std::vector<int> deg_in(_n);\n                for\
    \ (int v = 0; v < _n; v++) {\n                    for (int i = g.start[v]; i <\
    \ g.start[v + 1]; i++) {\n                        deg_in[g.elist[i].to] += g.elist[i].cap\
    \ > 0;\n                    }\n                }\n                std::vector<int>\
    \ st;\n                st.reserve(_n);\n                for (int i = 0; i < _n;\
    \ i++) {\n                    if (!deg_in[i]) st.push_back(i);\n             \
    \   }\n                for (int n = 0; n < _n; n++) {\n                    if\
    \ (int(st.size()) == n) return false; // Not DAG\n                    int now\
    \ = st[n];\n                    for (int i = g.start[now]; i < g.start[now + 1];\
    \ i++) {\n                        const auto &e = g.elist[i];\n              \
    \          if (!e.cap) continue;\n                        deg_in[e.to]--;\n  \
    \                      if (deg_in[e.to] == 0) st.push_back(e.to);\n          \
    \              if (dual_dist[e.to].first >= dual_dist[now].first + e.cost)\n \
    \                           dual_dist[e.to].first = dual_dist[now].first + e.cost;\n\
    \                    }\n                }\n                return true;\n    \
    \        }();\n            if (!check_dag) throw;\n            auto dt = dual_dist[t].first;\n\
    \            for (int v = 0; v < _n; v++) dual_dist[v].first -= dt;\n        \
    \    is_dual_infeasible = false;\n        }\n        std::vector<int> prev_e(_n);\n\
    \        std::vector<bool> vis(_n);\n        struct Q {\n            Cost key;\n\
    \            int to;\n            bool operator<(Q r) const { return key > r.key;\
    \ }\n        };\n        std::vector<int> que_min;\n        std::vector<Q> que;\n\
    \        auto dual_ref = [&]() {\n            for (int i = 0; i < _n; i++) {\n\
    \                dual_dist[i].second = std::numeric_limits<Cost>::max();\n   \
    \         }\n            std::fill(vis.begin(), vis.end(), false);\n         \
    \   que_min.clear();\n            que.clear();\n\n            // que[0..heap_r)\
    \ was heapified\n            unsigned heap_r = 0;\n\n            dual_dist[s].second\
    \ = 0;\n            que_min.push_back(s);\n            while (!que_min.empty()\
    \ || !que.empty()) {\n                int v;\n                if (!que_min.empty())\
    \ {\n                    v = que_min.back();\n                    que_min.pop_back();\n\
    \                } else {\n                    while (heap_r < que.size()) {\n\
    \                        heap_r++;\n                        std::push_heap(que.begin(),\
    \ que.begin() + heap_r);\n                    }\n                    v = que.front().to;\n\
    \                    std::pop_heap(que.begin(), que.end());\n                \
    \    que.pop_back();\n                    heap_r--;\n                }\n     \
    \           if (vis[v]) continue;\n                vis[v] = true;\n          \
    \      if (v == t) break;\n                // dist[v] = shortest(s, v) + dual[s]\
    \ - dual[v]\n                // dist[v] >= 0 (all reduced cost are positive)\n\
    \                // dist[v] <= (n-1)C\n                Cost dual_v = dual_dist[v].first,\
    \ dist_v = dual_dist[v].second;\n                for (int i = g.start[v]; i <\
    \ g.start[v + 1]; i++) {\n                    auto e = g.elist[i];\n         \
    \           if (!e.cap) continue;\n                    // |-dual[e.to] + dual[v]|\
    \ <= (n-1)C\n                    // cost <= C - -(n-1)C + 0 = nC\n           \
    \         Cost cost = e.cost - dual_dist[e.to].first + dual_v;\n             \
    \       if (dual_dist[e.to].second - dist_v > cost) {\n                      \
    \  Cost dist_to = dist_v + cost;\n                        dual_dist[e.to].second\
    \ = dist_to;\n                        prev_e[e.to] = e.rev;\n                \
    \        if (dist_to == dist_v) {\n                            que_min.push_back(e.to);\n\
    \                        } else {\n                            que.push_back(Q{dist_to,\
    \ e.to});\n                        }\n                    }\n                }\n\
    \            }\n            if (!vis[t]) { return false; }\n\n            for\
    \ (int v = 0; v < _n; v++) {\n                if (!vis[v]) continue;\n       \
    \         // dual[v] = dual[v] - dist[t] + dist[v]\n                //       \
    \  = dual[v] - (shortest(s, t) + dual[s] - dual[t]) +\n                //    \
    \     (shortest(s, v) + dual[s] - dual[v]) = - shortest(s,\n                //\
    \         t) + dual[t] + shortest(s, v) = shortest(s, v) -\n                //\
    \         shortest(s, t) >= 0 - (n-1)C\n                dual_dist[v].first -=\
    \ dual_dist[t].second - dual_dist[v].second;\n            }\n            return\
    \ true;\n        };\n        Cap flow = 0;\n        Cost cost = 0, prev_cost_per_flow\
    \ = -1;\n        std::vector<std::pair<Cap, Cost>> result = {{Cap(0), Cost(0)}};\n\
    \        while (flow < flow_limit) {\n            if (!dual_ref()) break;\n  \
    \          Cap c = flow_limit - flow;\n            for (int v = t; v != s; v =\
    \ g.elist[prev_e[v]].to) {\n                c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);\n\
    \            }\n            for (int v = t; v != s; v = g.elist[prev_e[v]].to)\
    \ {\n                auto &e = g.elist[prev_e[v]];\n                e.cap += c;\n\
    \                g.elist[e.rev].cap -= c;\n            }\n            Cost d =\
    \ -dual_dist[s].first;\n            flow += c;\n            cost += c * d;\n \
    \           if (prev_cost_per_flow == d) { result.pop_back(); }\n            result.push_back({flow,\
    \ cost});\n            prev_cost_per_flow = d;\n        }\n        return result;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/mincostflow_nonegativeloop.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/assignment_problem.test.cpp
  - combinatorial_opt/test/mincostflow.test.cpp
  - combinatorial_opt/test/mincostflow.yuki1288.test.cpp
  - combinatorial_opt/test/mincostflow.yuki1324.test.cpp
documentation_of: combinatorial_opt/mincostflow_nonegativeloop.hpp
layout: document
title: "Minimum cost flow without negative cycle \uFF08\u8CA0\u8FBA\u30EB\u30FC\u30D7\
  \u306A\u3057\u306E\u6700\u5C0F\u8CBB\u7528\u6D41\uFF09"
---

Negative cycle がない場合に使用可能な最小費用流．

負辺が存在する場合，DAG であれば線形時間でポテンシャルを求める．DAG でなければ例外を送出する．
