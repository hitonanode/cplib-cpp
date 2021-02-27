---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/mincostflow.hpp
    title: combinatorial_opt/mincostflow.hpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/mincostflow_bellmanford.hpp
    title: combinatorial_opt/mincostflow_bellmanford.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
  bundledCode: "#line 2 \"combinatorial_opt/mincostflow.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <queue>\n#include <vector>\n\n\
    // CUT begin\n// MinCostFlow based on AtCoder Library, no namespace, no private\
    \ variables, compatible with C++11\n// **NO NEGATIVE COST EDGES**\n// Reference:\
    \ https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html\n\
    // Remark: You can use [radix heap](https://github.com/iwiwi/radix-heap) for Dijkstra\
    \ acceleration\ntemplate <class Cap, class Cost> struct mcf_graph {\n    mcf_graph()\
    \ {}\n    mcf_graph(int n) : _n(n), g(n) { static_assert(std::numeric_limits<Cap>::max()\
    \ > 0); }\n\n    int add_edge(int from, int to, Cap cap, Cost cost) {\n      \
    \  assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n    \
    \    assert(0 <= cap);\n        assert(0 <= cost);\n        int m = int(pos.size());\n\
    \        pos.push_back({from, int(g[from].size())});\n        int from_id = int(g[from].size());\n\
    \        int to_id = int(g[to].size());\n        if (from == to) to_id++;\n  \
    \      g[from].push_back(_edge{to, to_id, cap, cost});\n        g[to].push_back(_edge{from,\
    \ from_id, 0, -cost});\n        return m;\n    }\n\n    struct edge {\n      \
    \  int from, to;\n        Cap cap, flow;\n        Cost cost;\n    };\n\n    edge\
    \ get_edge(int i) {\n        int m = int(pos.size());\n        assert(0 <= i &&\
    \ i < m);\n        auto _e = g[pos[i].first][pos[i].second];\n        auto _re\
    \ = g[_e.to][_e.rev];\n        return edge{\n            pos[i].first, _e.to,\
    \ _e.cap + _re.cap, _re.cap, _e.cost,\n        };\n    }\n    std::vector<edge>\
    \ edges() {\n        int m = int(pos.size());\n        std::vector<edge> result(m);\n\
    \        for (int i = 0; i < m; i++) { result[i] = get_edge(i); }\n        return\
    \ result;\n    }\n\n    std::pair<Cap, Cost> flow(int s, int t) { return flow(s,\
    \ t, std::numeric_limits<Cap>::max()); }\n    std::pair<Cap, Cost> flow(int s,\
    \ int t, Cap flow_limit) { return slope(s, t, flow_limit).back(); }\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t) { return slope(s, t, std::numeric_limits<Cap>::max());\
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
    \ g;\n};\n#line 3 \"combinatorial_opt/mincostflow_bellmanford.hpp\"\n#include\
    \ <iostream>\n#line 7 \"combinatorial_opt/mincostflow_bellmanford.hpp\"\n\n//\
    \ CUT begin\n/*\nMinCostFlow: Minimum-cost flow problem solver WITH NO NEGATIVE\
    \ CYCLE (just negative cost edge is allowed)\nVerified by SRM 770 Div1 Medium\
    \ <https://community.topcoder.com/stat?c=problem_statement&pm=15702>\n*/\ntemplate\
    \ <typename CAP = long long, typename COST = long long> struct MinCostFlow {\n\
    \    const COST INF_COST = std::numeric_limits<COST>::max() / 2;\n    struct edge\
    \ {\n        int to, rev;\n        CAP cap;\n        COST cost;\n        friend\
    \ std::ostream &operator<<(std::ostream &os, const edge &e) {\n            os\
    \ << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';\n  \
    \          return os;\n        }\n    };\n    int V;\n    std::vector<std::vector<edge>>\
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
    \ }\n        return os;\n    }\n};\n#line 5 \"combinatorial_opt/test/mincostflow.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n\nint main() {\n    int V, E, F;\n    std::cin >> V >> E >> F;\n    mcf_graph<long\
    \ long, long long> mcf_ac(V);\n    MinCostFlow<long long, long long> mcf_bf(V);\n\
    \    for (int i = 0; i < E; i++) {\n        int u, v, c, d;\n        std::cin\
    \ >> u >> v >> c >> d;\n        mcf_ac.add_edge(u, v, c, d);\n        mcf_bf.add_edge(u,\
    \ v, c, d);\n    }\n\n    auto capcost_ac = mcf_ac.flow(0, V - 1, F);\n    auto\
    \ capcost_bf = mcf_bf.flow(0, V - 1, F);\n    assert(capcost_ac == capcost_bf);\n\
    \    std::cout << (capcost_ac.first == F ? capcost_ac.second : -1) << '\\n';\n\
    }\n"
  code: "#include \"../mincostflow.hpp\"\n#include \"../mincostflow_bellmanford.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n\nint main() {\n    int V, E, F;\n    std::cin >> V >> E >> F;\n    mcf_graph<long\
    \ long, long long> mcf_ac(V);\n    MinCostFlow<long long, long long> mcf_bf(V);\n\
    \    for (int i = 0; i < E; i++) {\n        int u, v, c, d;\n        std::cin\
    \ >> u >> v >> c >> d;\n        mcf_ac.add_edge(u, v, c, d);\n        mcf_bf.add_edge(u,\
    \ v, c, d);\n    }\n\n    auto capcost_ac = mcf_ac.flow(0, V - 1, F);\n    auto\
    \ capcost_bf = mcf_bf.flow(0, V - 1, F);\n    assert(capcost_ac == capcost_bf);\n\
    \    std::cout << (capcost_ac.first == F ? capcost_ac.second : -1) << '\\n';\n\
    }\n"
  dependsOn:
  - combinatorial_opt/mincostflow.hpp
  - combinatorial_opt/mincostflow_bellmanford.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/mincostflow.test.cpp
  requiredBy: []
  timestamp: '2021-02-27 23:24:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/mincostflow.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/mincostflow.test.cpp
- /verify/combinatorial_opt/test/mincostflow.test.cpp.html
title: combinatorial_opt/test/mincostflow.test.cpp
---
