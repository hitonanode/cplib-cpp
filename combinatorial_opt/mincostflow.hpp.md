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
  bundledCode: "#line 2 \"combinatorial_opt/mincostflow.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// MinCostFlow based on AC Library (no namespace)\n// **NO NEGATIVE\
    \ COST EDGES**\n// Reference: https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html\n\
    template <class Cap, class Cost> struct mcf_graph {\n    template <class E> struct\
    \ csr {\n        std::vector<int> start;\n        std::vector<E> elist;\n    \
    \    explicit csr(int n, const std::vector<std::pair<int, E>>& edges) : start(n\
    \ + 1), elist(edges.size()) {\n            for (auto e : edges) { start[e.first\
    \ + 1]++; }\n            for (int i = 1; i <= n; i++) { start[i] += start[i -\
    \ 1]; }\n            auto counter = start;\n            for (auto e : edges) {\
    \ elist[counter[e.first]++] = e.second; }\n        }\n    };\n\npublic:\n    mcf_graph()\
    \ {}\n    explicit mcf_graph(int n) : _n(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int add_edge(int from,\
    \ int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n   \
    \     assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        assert(0\
    \ <= cost);\n        int m = int(_edges.size());\n        _edges.push_back({from,\
    \ to, cap, 0, cost});\n        return m;\n    }\n\n    struct edge {\n       \
    \ int from, to;\n        Cap cap, flow;\n        Cost cost;\n    };\n\n    edge\
    \ get_edge(int i) {\n        int m = int(_edges.size());\n        assert(0 <=\
    \ i && i < m);\n        return _edges[i];\n    }\n    std::vector<edge> edges()\
    \ { return _edges; }\n\n    std::pair<Cap, Cost> flow(int s, int t) { return flow(s,\
    \ t, std::numeric_limits<Cap>::max()); }\n    std::pair<Cap, Cost> flow(int s,\
    \ int t, Cap flow_limit) { return slope(s, t, flow_limit).back(); }\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t) {\n        return slope(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)\
    \ {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t < _n);\n  \
    \      assert(s != t);\n\n        int m = int(_edges.size());\n        std::vector<int>\
    \ edge_idx(m);\n\n        auto g = [&]() {\n            std::vector<int> degree(_n),\
    \ redge_idx(m);\n            std::vector<std::pair<int, _edge>> elist;\n     \
    \       elist.reserve(2 * m);\n            for (int i = 0; i < m; i++) {\n   \
    \             auto e = _edges[i];\n                edge_idx[i] = degree[e.from]++;\n\
    \                redge_idx[i] = degree[e.to]++;\n                elist.push_back({e.from,\
    \ {e.to, -1, e.cap - e.flow, e.cost}});\n                elist.push_back({e.to,\
    \ {e.from, -1, e.flow, -e.cost}});\n            }\n            auto _g = csr<_edge>(_n,\
    \ elist);\n            for (int i = 0; i < m; i++) {\n                auto e =\
    \ _edges[i];\n                edge_idx[i] += _g.start[e.from];\n             \
    \   redge_idx[i] += _g.start[e.to];\n                _g.elist[edge_idx[i]].rev\
    \ = redge_idx[i];\n                _g.elist[redge_idx[i]].rev = edge_idx[i];\n\
    \            }\n            return _g;\n        }();\n\n        auto result =\
    \ slope(g, s, t, flow_limit);\n\n        for (int i = 0; i < m; i++) {\n     \
    \       auto e = g.elist[edge_idx[i]];\n            _edges[i].flow = _edges[i].cap\
    \ - e.cap;\n        }\n\n        return result;\n    }\n\nprivate:\n    int _n;\n\
    \    std::vector<edge> _edges;\n\n    // inside edge\n    struct _edge {\n   \
    \     int to, rev;\n        Cap cap;\n        Cost cost;\n    };\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(csr<_edge>& g, int s, int t, Cap flow_limit) {\n        // variants\
    \ (C = maxcost):\n        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n  \
    \      // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n\
    \n        // dual_dist[i] = (dual[i], dist[i])\n        std::vector<std::pair<Cost,\
    \ Cost>> dual_dist(_n);\n        std::vector<int> prev_e(_n);\n        std::vector<bool>\
    \ vis(_n);\n        struct Q {\n            Cost key;\n            int to;\n \
    \           bool operator<(Q r) const { return key > r.key; }\n        };\n  \
    \      std::vector<int> que_min;\n        std::vector<Q> que;\n        auto dual_ref\
    \ = [&]() {\n            for (int i = 0; i < _n; i++) { dual_dist[i].second =\
    \ std::numeric_limits<Cost>::max(); }\n            std::fill(vis.begin(), vis.end(),\
    \ false);\n            que_min.clear();\n            que.clear();\n\n        \
    \    // que[0..heap_r) was heapified\n            size_t heap_r = 0;\n\n     \
    \       dual_dist[s].second = 0;\n            que_min.push_back(s);\n        \
    \    while (!que_min.empty() || !que.empty()) {\n                int v;\n    \
    \            if (!que_min.empty()) {\n                    v = que_min.back();\n\
    \                    que_min.pop_back();\n                } else {\n         \
    \           while (heap_r < que.size()) {\n                        heap_r++;\n\
    \                        std::push_heap(que.begin(), que.begin() + heap_r);\n\
    \                    }\n                    v = que.front().to;\n            \
    \        std::pop_heap(que.begin(), que.end());\n                    que.pop_back();\n\
    \                    heap_r--;\n                }\n                if (vis[v])\
    \ continue;\n                vis[v] = true;\n                if (v == t) break;\n\
    \                // dist[v] = shortest(s, v) + dual[s] - dual[v]\n           \
    \     // dist[v] >= 0 (all reduced cost are positive)\n                // dist[v]\
    \ <= (n-1)C\n                Cost dual_v = dual_dist[v].first, dist_v = dual_dist[v].second;\n\
    \                for (int i = g.start[v]; i < g.start[v + 1]; i++) {\n       \
    \             auto e = g.elist[i];\n                    if (!e.cap) continue;\n\
    \                    // |-dual[e.to] + dual[v]| <= (n-1)C\n                  \
    \  // cost <= C - -(n-1)C + 0 = nC\n                    Cost cost = e.cost - dual_dist[e.to].first\
    \ + dual_v;\n                    if (dual_dist[e.to].second - dist_v > cost) {\n\
    \                        Cost dist_to = dist_v + cost;\n                     \
    \   dual_dist[e.to].second = dist_to;\n                        prev_e[e.to] =\
    \ e.rev;\n                        if (dist_to == dist_v) {\n                 \
    \           que_min.push_back(e.to);\n                        } else {\n     \
    \                       que.push_back(Q{dist_to, e.to});\n                   \
    \     }\n                    }\n                }\n            }\n           \
    \ if (!vis[t]) { return false; }\n\n            for (int v = 0; v < _n; v++) {\n\
    \                if (!vis[v]) continue;\n                // dual[v] = dual[v]\
    \ - dist[t] + dist[v]\n                //         = dual[v] - (shortest(s, t)\
    \ + dual[s] - dual[t]) +\n                //         (shortest(s, v) + dual[s]\
    \ - dual[v]) = - shortest(s,\n                //         t) + dual[t] + shortest(s,\
    \ v) = shortest(s, v) -\n                //         shortest(s, t) >= 0 - (n-1)C\n\
    \                dual_dist[v].first -= dual_dist[t].second - dual_dist[v].second;\n\
    \            }\n            return true;\n        };\n        Cap flow = 0;\n\
    \        Cost cost = 0, prev_cost_per_flow = -1;\n        std::vector<std::pair<Cap,\
    \ Cost>> result = {{Cap(0), Cost(0)}};\n        while (flow < flow_limit) {\n\
    \            if (!dual_ref()) break;\n            Cap c = flow_limit - flow;\n\
    \            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {\n          \
    \      c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);\n            }\n\
    \            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {\n          \
    \      auto& e = g.elist[prev_e[v]];\n                e.cap += c;\n          \
    \      g.elist[e.rev].cap -= c;\n            }\n            Cost d = -dual_dist[s].first;\n\
    \            flow += c;\n            cost += c * d;\n            if (prev_cost_per_flow\
    \ == d) { result.pop_back(); }\n            result.push_back({flow, cost});\n\
    \            prev_cost_per_flow = d;\n        }\n        return result;\n    }\n\
    };\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <limits>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// MinCostFlow based on\
    \ AC Library (no namespace)\n// **NO NEGATIVE COST EDGES**\n// Reference: https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html\n\
    template <class Cap, class Cost> struct mcf_graph {\n    template <class E> struct\
    \ csr {\n        std::vector<int> start;\n        std::vector<E> elist;\n    \
    \    explicit csr(int n, const std::vector<std::pair<int, E>>& edges) : start(n\
    \ + 1), elist(edges.size()) {\n            for (auto e : edges) { start[e.first\
    \ + 1]++; }\n            for (int i = 1; i <= n; i++) { start[i] += start[i -\
    \ 1]; }\n            auto counter = start;\n            for (auto e : edges) {\
    \ elist[counter[e.first]++] = e.second; }\n        }\n    };\n\npublic:\n    mcf_graph()\
    \ {}\n    explicit mcf_graph(int n) : _n(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int add_edge(int from,\
    \ int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n   \
    \     assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        assert(0\
    \ <= cost);\n        int m = int(_edges.size());\n        _edges.push_back({from,\
    \ to, cap, 0, cost});\n        return m;\n    }\n\n    struct edge {\n       \
    \ int from, to;\n        Cap cap, flow;\n        Cost cost;\n    };\n\n    edge\
    \ get_edge(int i) {\n        int m = int(_edges.size());\n        assert(0 <=\
    \ i && i < m);\n        return _edges[i];\n    }\n    std::vector<edge> edges()\
    \ { return _edges; }\n\n    std::pair<Cap, Cost> flow(int s, int t) { return flow(s,\
    \ t, std::numeric_limits<Cap>::max()); }\n    std::pair<Cap, Cost> flow(int s,\
    \ int t, Cap flow_limit) { return slope(s, t, flow_limit).back(); }\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t) {\n        return slope(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)\
    \ {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t < _n);\n  \
    \      assert(s != t);\n\n        int m = int(_edges.size());\n        std::vector<int>\
    \ edge_idx(m);\n\n        auto g = [&]() {\n            std::vector<int> degree(_n),\
    \ redge_idx(m);\n            std::vector<std::pair<int, _edge>> elist;\n     \
    \       elist.reserve(2 * m);\n            for (int i = 0; i < m; i++) {\n   \
    \             auto e = _edges[i];\n                edge_idx[i] = degree[e.from]++;\n\
    \                redge_idx[i] = degree[e.to]++;\n                elist.push_back({e.from,\
    \ {e.to, -1, e.cap - e.flow, e.cost}});\n                elist.push_back({e.to,\
    \ {e.from, -1, e.flow, -e.cost}});\n            }\n            auto _g = csr<_edge>(_n,\
    \ elist);\n            for (int i = 0; i < m; i++) {\n                auto e =\
    \ _edges[i];\n                edge_idx[i] += _g.start[e.from];\n             \
    \   redge_idx[i] += _g.start[e.to];\n                _g.elist[edge_idx[i]].rev\
    \ = redge_idx[i];\n                _g.elist[redge_idx[i]].rev = edge_idx[i];\n\
    \            }\n            return _g;\n        }();\n\n        auto result =\
    \ slope(g, s, t, flow_limit);\n\n        for (int i = 0; i < m; i++) {\n     \
    \       auto e = g.elist[edge_idx[i]];\n            _edges[i].flow = _edges[i].cap\
    \ - e.cap;\n        }\n\n        return result;\n    }\n\nprivate:\n    int _n;\n\
    \    std::vector<edge> _edges;\n\n    // inside edge\n    struct _edge {\n   \
    \     int to, rev;\n        Cap cap;\n        Cost cost;\n    };\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(csr<_edge>& g, int s, int t, Cap flow_limit) {\n        // variants\
    \ (C = maxcost):\n        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n  \
    \      // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n\
    \n        // dual_dist[i] = (dual[i], dist[i])\n        std::vector<std::pair<Cost,\
    \ Cost>> dual_dist(_n);\n        std::vector<int> prev_e(_n);\n        std::vector<bool>\
    \ vis(_n);\n        struct Q {\n            Cost key;\n            int to;\n \
    \           bool operator<(Q r) const { return key > r.key; }\n        };\n  \
    \      std::vector<int> que_min;\n        std::vector<Q> que;\n        auto dual_ref\
    \ = [&]() {\n            for (int i = 0; i < _n; i++) { dual_dist[i].second =\
    \ std::numeric_limits<Cost>::max(); }\n            std::fill(vis.begin(), vis.end(),\
    \ false);\n            que_min.clear();\n            que.clear();\n\n        \
    \    // que[0..heap_r) was heapified\n            size_t heap_r = 0;\n\n     \
    \       dual_dist[s].second = 0;\n            que_min.push_back(s);\n        \
    \    while (!que_min.empty() || !que.empty()) {\n                int v;\n    \
    \            if (!que_min.empty()) {\n                    v = que_min.back();\n\
    \                    que_min.pop_back();\n                } else {\n         \
    \           while (heap_r < que.size()) {\n                        heap_r++;\n\
    \                        std::push_heap(que.begin(), que.begin() + heap_r);\n\
    \                    }\n                    v = que.front().to;\n            \
    \        std::pop_heap(que.begin(), que.end());\n                    que.pop_back();\n\
    \                    heap_r--;\n                }\n                if (vis[v])\
    \ continue;\n                vis[v] = true;\n                if (v == t) break;\n\
    \                // dist[v] = shortest(s, v) + dual[s] - dual[v]\n           \
    \     // dist[v] >= 0 (all reduced cost are positive)\n                // dist[v]\
    \ <= (n-1)C\n                Cost dual_v = dual_dist[v].first, dist_v = dual_dist[v].second;\n\
    \                for (int i = g.start[v]; i < g.start[v + 1]; i++) {\n       \
    \             auto e = g.elist[i];\n                    if (!e.cap) continue;\n\
    \                    // |-dual[e.to] + dual[v]| <= (n-1)C\n                  \
    \  // cost <= C - -(n-1)C + 0 = nC\n                    Cost cost = e.cost - dual_dist[e.to].first\
    \ + dual_v;\n                    if (dual_dist[e.to].second - dist_v > cost) {\n\
    \                        Cost dist_to = dist_v + cost;\n                     \
    \   dual_dist[e.to].second = dist_to;\n                        prev_e[e.to] =\
    \ e.rev;\n                        if (dist_to == dist_v) {\n                 \
    \           que_min.push_back(e.to);\n                        } else {\n     \
    \                       que.push_back(Q{dist_to, e.to});\n                   \
    \     }\n                    }\n                }\n            }\n           \
    \ if (!vis[t]) { return false; }\n\n            for (int v = 0; v < _n; v++) {\n\
    \                if (!vis[v]) continue;\n                // dual[v] = dual[v]\
    \ - dist[t] + dist[v]\n                //         = dual[v] - (shortest(s, t)\
    \ + dual[s] - dual[t]) +\n                //         (shortest(s, v) + dual[s]\
    \ - dual[v]) = - shortest(s,\n                //         t) + dual[t] + shortest(s,\
    \ v) = shortest(s, v) -\n                //         shortest(s, t) >= 0 - (n-1)C\n\
    \                dual_dist[v].first -= dual_dist[t].second - dual_dist[v].second;\n\
    \            }\n            return true;\n        };\n        Cap flow = 0;\n\
    \        Cost cost = 0, prev_cost_per_flow = -1;\n        std::vector<std::pair<Cap,\
    \ Cost>> result = {{Cap(0), Cost(0)}};\n        while (flow < flow_limit) {\n\
    \            if (!dual_ref()) break;\n            Cap c = flow_limit - flow;\n\
    \            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {\n          \
    \      c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);\n            }\n\
    \            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {\n          \
    \      auto& e = g.elist[prev_e[v]];\n                e.cap += c;\n          \
    \      g.elist[e.rev].cap -= c;\n            }\n            Cost d = -dual_dist[s].first;\n\
    \            flow += c;\n            cost += c * d;\n            if (prev_cost_per_flow\
    \ == d) { result.pop_back(); }\n            result.push_back({flow, cost});\n\
    \            prev_cost_per_flow = d;\n        }\n        return result;\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/mincostflow.hpp
  requiredBy: []
  timestamp: '2021-09-11 00:53:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/mincostflow.test.cpp
documentation_of: combinatorial_opt/mincostflow.hpp
layout: document
title: Minimum cost flow (primal-dual, based on AC Library)
---

[AC Library](https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html) 由来の最小費用流．負辺は張れない．
