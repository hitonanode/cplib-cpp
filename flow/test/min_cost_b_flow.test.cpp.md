---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: flow/b-flow.hpp
    title: flow/b-flow.hpp
  - icon: ':question:'
    path: flow/mincostflow.hpp
    title: flow/mincostflow.hpp
  - icon: ':x:'
    path: utilities/int128.hpp
    title: utilities/int128.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_cost_b_flow
    links:
    - https://judge.yosupo.jp/problem/min_cost_b_flow
  bundledCode: "#line 2 \"flow/mincostflow.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <limits>\n#include <queue>\n#include <vector>\n\n// CUT begin\n// MinCostFlow\
    \ based on AtCoder Library, no namespace, no private variables, compatible with\
    \ C++11\n// Reference: <https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html>\n\
    // **NO NEGATIVE COST EDGES**\ntemplate <class Cap, class Cost>\nstruct mcf_graph\
    \ {\n    mcf_graph() {}\n    mcf_graph(int n) : _n(n), g(n) {}\n\n    int add_edge(int\
    \ from, int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n\
    \        assert(0 <= to && to < _n);\n        assert(0 <= cap);\n        assert(0\
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
    \ = 0; i < m; i++) {\n            result[i] = get_edge(i);\n        }\n      \
    \  return result;\n    }\n\n    std::pair<Cap, Cost> flow(int s, int t) {\n  \
    \      return flow(s, t, std::numeric_limits<Cap>::max());\n    }\n    std::pair<Cap,\
    \ Cost> flow(int s, int t, Cap flow_limit) {\n        return slope(s, t, flow_limit).back();\n\
    \    }\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {\n        return\
    \ slope(s, t, std::numeric_limits<Cap>::max());\n    }\n\n    std::vector<Cost>\
    \ dual, dist;\n    std::vector<int> pv, pe;\n    std::vector<bool> vis;\n    bool\
    \ _dual_ref(int s, int t) {\n        std::fill(dist.begin(), dist.end(), std::numeric_limits<Cost>::max());\n\
    \        std::fill(pv.begin(), pv.end(), -1);\n        std::fill(pe.begin(), pe.end(),\
    \ -1);\n        std::fill(vis.begin(), vis.end(), false);\n        struct Q {\n\
    \            Cost key;\n            int to;\n            bool operator<(Q r) const\
    \ { return key > r.key; }\n        };\n        std::priority_queue<Q> que;\n \
    \       dist[s] = 0;\n        que.push(Q{0, s});\n        while (!que.empty())\
    \ {\n            int v = que.top().to;\n            que.pop();\n            if\
    \ (vis[v]) continue;\n            vis[v] = true;\n            if (v == t) break;\n\
    \            // dist[v] = shortest(s, v) + dual[s] - dual[v]\n            // dist[v]\
    \ >= 0 (all reduced cost are positive)\n            // dist[v] <= (n-1)C\n   \
    \         for (int i = 0; i < int(g[v].size()); i++) {\n                auto e\
    \ = g[v][i];\n                if (vis[e.to] || !e.cap) continue;\n           \
    \     // |-dual[e.to] + dual[v]| <= (n-1)C\n                // cost <= C - -(n-1)C\
    \ + 0 = nC\n                Cost cost = e.cost - dual[e.to] + dual[v];\n     \
    \           if (dist[e.to] - dist[v] > cost) {\n                    dist[e.to]\
    \ = dist[v] + cost;\n                    pv[e.to] = v;\n                    pe[e.to]\
    \ = i;\n                    que.push(Q{dist[e.to], e.to});\n                }\n\
    \            }\n        }\n        if (!vis[t]) {\n            return false;\n\
    \        }\n\n        for (int v = 0; v < _n; v++) {\n            if (!vis[v])\
    \ continue;\n            // dual[v] = dual[v] - dist[t] + dist[v]\n          \
    \  //         = dual[v] - (shortest(s, t) + dual[s] - dual[t]) + (shortest(s,\
    \ v) + dual[s] - dual[v])\n            //         = - shortest(s, t) + dual[t]\
    \ + shortest(s, v)\n            //         = shortest(s, v) - shortest(s, t) >=\
    \ 0 - (n-1)C\n            dual[v] -= dist[t] - dist[v];\n        }\n        return\
    \ true;\n    }\n\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap\
    \ flow_limit) {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t\
    \ < _n);\n        assert(s != t);\n        // variants (C = maxcost):\n      \
    \  // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\n        // reduced cost (=\
    \ e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge\n        dual.assign(_n,\
    \ 0), dist.assign(_n, 0);\n        pv.assign(_n, 0), pe.assign(_n, 0);\n     \
    \   vis.assign(_n, false);\n        Cap flow = 0;\n        Cost cost = 0, prev_cost_per_flow\
    \ = -1;\n        std::vector<std::pair<Cap, Cost>> result;\n        result.push_back({flow,\
    \ cost});\n        while (flow < flow_limit) {\n            if (!_dual_ref(s,\
    \ t)) break;\n            Cap c = flow_limit - flow;\n            for (int v =\
    \ t; v != s; v = pv[v]) {\n                c = std::min(c, g[pv[v]][pe[v]].cap);\n\
    \            }\n            for (int v = t; v != s; v = pv[v]) {\n           \
    \     auto& e = g[pv[v]][pe[v]];\n                e.cap -= c;\n              \
    \  g[v][e.rev].cap += c;\n            }\n            Cost d = -dual[s];\n    \
    \        flow += c;\n            cost += c * d;\n            if (prev_cost_per_flow\
    \ == d) {\n                result.pop_back();\n            }\n            result.push_back({flow,\
    \ cost});\n            prev_cost_per_flow = d;\n        }\n        return result;\n\
    \    }\n\n    struct _edge {\n        int to, rev;\n        Cap cap;\n       \
    \ Cost cost;\n    };\n\n    int _n;\n    std::vector<std::pair<int, int>> pos;\n\
    \    std::vector<std::vector<_edge>> g;\n};\n#line 5 \"flow/b-flow.hpp\"\n\n\n\
    // CUT begin\ntemplate <typename CAP, typename COST>\nstruct B_Flow\n{\n    int\
    \ N, E;\n    COST cost_bias;\n    bool infeasible;\n    mcf_graph<CAP, COST> mcf;\n\
    \    std::vector<CAP> b;\n    std::vector<CAP> fbias;\n    std::vector<int> fdir;\n\
    \    std::vector<CAP> f;\n    std::vector<COST> potential;\n\n    B_Flow(int N\
    \ = 0) : N(N), E(0), cost_bias(0), infeasible(false), mcf(N + 2), b(N) {}\n\n\
    \    void add_supply(int v, CAP supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, CAP demand) { b[v] -= demand; }\n    void add_edge(int s, int t, CAP lower_cap,\
    \ CAP upper_cap, COST cost) {\n        assert(s >= 0 and s < N);\n        assert(t\
    \ >= 0 and t < N);\n        if (lower_cap > upper_cap) {\n            infeasible\
    \ = true;\n            return;\n        }\n        E++;\n        if (s == t) {\n\
    \            if (cost > 0) upper_cap = lower_cap;\n            else lower_cap\
    \ = upper_cap;\n        }\n        if (cost < 0) {\n            fbias.emplace_back(lower_cap);\n\
    \            fdir.emplace_back(-1);\n            cost_bias += cost * upper_cap;\n\
    \            b[s] -= upper_cap;\n            b[t] += upper_cap;\n            mcf.add_edge(t,\
    \ s, upper_cap - lower_cap, -cost);\n        } else {\n            fbias.emplace_back(upper_cap);\n\
    \            fdir.emplace_back(1);\n            if (lower_cap < 0) {\n       \
    \         cost_bias += cost * lower_cap, b[s] -= lower_cap, b[t] += lower_cap;\n\
    \                upper_cap -= lower_cap, lower_cap = 0;\n            }\n     \
    \       if (lower_cap > 0) {\n                cost_bias += cost * lower_cap;\n\
    \                b[s] -= lower_cap;\n                b[t] += lower_cap;\n    \
    \            upper_cap -= lower_cap;\n            }\n            mcf.add_edge(s,\
    \ t, upper_cap, cost);\n        }\n    }\n\n    std::pair<bool, COST> solve()\
    \ {\n        if (infeasible) {\n            return std::make_pair(false, 0);\n\
    \        }\n        CAP bsum = 0, bsum_negative = 0;\n        for (int i = 0;\
    \ i < N; i++) {\n            if (b[i] > 0) {\n                mcf.add_edge(N,\
    \ i, b[i], 0), bsum += b[i];\n            }\n            if (b[i] < 0) {\n   \
    \             mcf.add_edge(i, N + 1, -b[i], 0), bsum_negative -= b[i];\n     \
    \       }\n        }\n        if (bsum != bsum_negative) {\n            return\
    \ std::make_pair(false, 0);\n        }\n        std::fill(b.begin(), b.end(),\
    \ 0);\n        auto ret = mcf.flow(N, N + 1, bsum);\n        potential = mcf.dual,\
    \ potential.resize(N);\n        COST cost_ret = cost_bias + ret.second;\n    \
    \    cost_bias = 0;\n        bool succeeded = (ret.first == bsum);\n        f\
    \ = fbias;\n        for (int i = 0; i < E; i++) {\n            const std::pair<int,\
    \ int> &p = mcf.pos[i];\n            f[i] -= fdir[i] * mcf.g[p.first][p.second].cap;\n\
    \        }\n        return std::make_pair(succeeded, cost_ret);\n    }\n};\n#line\
    \ 2 \"utilities/int128.hpp\"\n\n#line 4 \"utilities/int128.hpp\"\n#include <iostream>\n\
    #line 6 \"utilities/int128.hpp\"\n#include <string>\n#line 8 \"utilities/int128.hpp\"\
    \n\n// CUT begin\ntemplate <>\nstruct std::numeric_limits<__int128>\n{\n    static\
    \ __int128 max() noexcept { return ((__int128(1) << 126) - 1) * 2 + 1; }\n   \
    \ static __int128 min() noexcept { return -max() - 1; }\n    static __int128 lowest()\
    \ noexcept { return min(); }\n};\n__int128 str2i128(std::string str)\n{\n    __int128\
    \ ret = 0;\n    bool minus = false;\n    for (auto c : str)\n    {\n        if\
    \ (c == '-') minus = true;\n        else ret = ret * 10 + c - '0';\n    }\n  \
    \  return minus ? -ret : ret;\n}\nstd::istream &operator>>(std::istream &is, __int128\
    \ &x)\n{\n    std::string s;\n    is >> s;\n    x = str2i128(s);\n    return is;\n\
    }\nstd::ostream &operator<<(std::ostream &os, const __int128& x)\n{\n    __int128\
    \ tmp = x;\n    if (tmp == 0) return os << 0;\n    std::vector<int> ds;\n    if\
    \ (tmp < 0)\n    {\n        os << '-';\n        while (tmp)\n        {\n     \
    \       int d = tmp % 10;\n            if (d > 0) d -= 10;\n            ds.emplace_back(-d),\
    \ tmp = (tmp - d) / 10;\n        }\n    }\n    else\n    {\n        while (tmp)\
    \ ds.emplace_back(tmp % 10), tmp /= 10;\n    }\n    std::reverse(ds.begin(), ds.end());\n\
    \    for (auto i : ds) os << i;\n    return os;\n}\n#line 3 \"flow/test/min_cost_b_flow.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n\nusing\
    \ namespace std;\n\nint main()\n{\n    int N, M;\n    cin >> N >> M;\n    B_Flow<long\
    \ long, __int128> bflow(N);\n\n    constexpr __int128 plim = 1000000000000000;\n\
    \    for (int i = 0; i < N; i++)\n    {\n        int b;\n        cin >> b;\n \
    \       bflow.add_supply(i, b);\n    }\n    for (int i = 0; i < M; i++)\n    {\n\
    \        int s, t, l, u;\n        __int128 c;\n        cin >> s >> t >> l >> u\
    \ >> c;\n        bflow.add_edge(s, t, l, u, c);\n    }\n    auto ret = bflow.solve();\n\
    \    if (ret.first)\n    {\n        cout << ret.second << '\\n';\n        for\
    \ (int i = 0; i < N; i++)\n        {\n            cout << clamp(bflow.potential[i],\
    \ -plim, plim) << '\\n';\n        }\n        for (int i = 0; i < M; i++)\n   \
    \     {\n            cout << bflow.f[i] << '\\n';\n        }\n    }\n    else\n\
    \    {\n        cout << \"infeasible\\n\";\n    }\n}\n"
  code: "#include \"flow/b-flow.hpp\"\n#include \"utilities/int128.hpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n\nusing namespace\
    \ std;\n\nint main()\n{\n    int N, M;\n    cin >> N >> M;\n    B_Flow<long long,\
    \ __int128> bflow(N);\n\n    constexpr __int128 plim = 1000000000000000;\n   \
    \ for (int i = 0; i < N; i++)\n    {\n        int b;\n        cin >> b;\n    \
    \    bflow.add_supply(i, b);\n    }\n    for (int i = 0; i < M; i++)\n    {\n\
    \        int s, t, l, u;\n        __int128 c;\n        cin >> s >> t >> l >> u\
    \ >> c;\n        bflow.add_edge(s, t, l, u, c);\n    }\n    auto ret = bflow.solve();\n\
    \    if (ret.first)\n    {\n        cout << ret.second << '\\n';\n        for\
    \ (int i = 0; i < N; i++)\n        {\n            cout << clamp(bflow.potential[i],\
    \ -plim, plim) << '\\n';\n        }\n        for (int i = 0; i < M; i++)\n   \
    \     {\n            cout << bflow.f[i] << '\\n';\n        }\n    }\n    else\n\
    \    {\n        cout << \"infeasible\\n\";\n    }\n}\n"
  dependsOn:
  - flow/b-flow.hpp
  - flow/mincostflow.hpp
  - utilities/int128.hpp
  isVerificationFile: true
  path: flow/test/min_cost_b_flow.test.cpp
  requiredBy: []
  timestamp: '2020-10-11 20:57:52+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: flow/test/min_cost_b_flow.test.cpp
layout: document
redirect_from:
- /verify/flow/test/min_cost_b_flow.test.cpp
- /verify/flow/test/min_cost_b_flow.test.cpp.html
title: flow/test/min_cost_b_flow.test.cpp
---
