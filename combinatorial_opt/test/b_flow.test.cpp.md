---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/b-flow.hpp
    title: combinatorial_opt/b-flow.hpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/maxflow.hpp
    title: combinatorial_opt/maxflow.hpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/mcf_costscaling.hpp
    title: "Minimum cost flow (cost scaling, Goldberg & Tarjan) \uFF08\u30B3\u30B9\
      \u30C8\u30B9\u30B1\u30FC\u30EA\u30F3\u30B0\u306B\u3088\u308B\u6700\u5C0F\u8CBB\
      \u7528\u6D41\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_cost_b_flow
    links:
    - https://judge.yosupo.jp/problem/min_cost_b_flow
  bundledCode: "#line 1 \"combinatorial_opt/test/b_flow.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n#line 2 \"combinatorial_opt/maxflow.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <fstream>\n#include <limits>\n\
    #include <string>\n#include <vector>\n\n// CUT begin\n// MaxFlow based and AtCoder\
    \ Library, single class, no namespace, no private variables, compatible\n// with\
    \ C++11 Reference: <https://atcoder.github.io/ac-library/production/document_ja/maxflow.html>\n\
    template <class Cap> struct mf_graph {\n    struct simple_queue_int {\n      \
    \  std::vector<int> payload;\n        int pos = 0;\n        void reserve(int n)\
    \ { payload.reserve(n); }\n        int size() const { return int(payload.size())\
    \ - pos; }\n        bool empty() const { return pos == int(payload.size()); }\n\
    \        void push(const int &t) { payload.push_back(t); }\n        int &front()\
    \ { return payload[pos]; }\n        void clear() {\n            payload.clear();\n\
    \            pos = 0;\n        }\n        void pop() { pos++; }\n    };\n\n  \
    \  mf_graph() : _n(0) {}\n    mf_graph(int n) : _n(n), g(n) {}\n\n    int add_edge(int\
    \ from, int to, Cap cap) {\n        assert(0 <= from && from < _n);\n        assert(0\
    \ <= to && to < _n);\n        assert(0 <= cap);\n        int m = int(pos.size());\n\
    \        pos.push_back({from, int(g[from].size())});\n        int from_id = int(g[from].size());\n\
    \        int to_id = int(g[to].size());\n        if (from == to) to_id++;\n  \
    \      g[from].push_back(_edge{to, to_id, cap});\n        g[to].push_back(_edge{from,\
    \ from_id, 0});\n        return m;\n    }\n\n    struct edge {\n        int from,\
    \ to;\n        Cap cap, flow;\n    };\n\n    edge get_edge(int i) {\n        int\
    \ m = int(pos.size());\n        assert(0 <= i && i < m);\n        auto _e = g[pos[i].first][pos[i].second];\n\
    \        auto _re = g[_e.to][_e.rev];\n        return edge{pos[i].first, _e.to,\
    \ _e.cap + _re.cap, _re.cap};\n    }\n    std::vector<edge> edges() {\n      \
    \  int m = int(pos.size());\n        std::vector<edge> result;\n        for (int\
    \ i = 0; i < m; i++) { result.push_back(get_edge(i)); }\n        return result;\n\
    \    }\n    void change_edge(int i, Cap new_cap, Cap new_flow) {\n        int\
    \ m = int(pos.size());\n        assert(0 <= i && i < m);\n        assert(0 <=\
    \ new_flow && new_flow <= new_cap);\n        auto &_e = g[pos[i].first][pos[i].second];\n\
    \        auto &_re = g[_e.to][_e.rev];\n        _e.cap = new_cap - new_flow;\n\
    \        _re.cap = new_flow;\n    }\n\n    std::vector<int> level, iter;\n   \
    \ simple_queue_int que;\n\n    void _bfs(int s, int t) {\n        std::fill(level.begin(),\
    \ level.end(), -1);\n        level[s] = 0;\n        que.clear();\n        que.push(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop();\n            for (auto e : g[v]) {\n                if (e.cap ==\
    \ 0 || level[e.to] >= 0) continue;\n                level[e.to] = level[v] + 1;\n\
    \                if (e.to == t) return;\n                que.push(e.to);\n   \
    \         }\n        }\n    }\n    Cap _dfs(int v, int s, Cap up) {\n        if\
    \ (v == s) return up;\n        Cap res = 0;\n        int level_v = level[v];\n\
    \        for (int &i = iter[v]; i < int(g[v].size()); i++) {\n            _edge\
    \ &e = g[v][i];\n            if (level_v <= level[e.to] || g[e.to][e.rev].cap\
    \ == 0) continue;\n            Cap d = _dfs(e.to, s, std::min(up - res, g[e.to][e.rev].cap));\n\
    \            if (d <= 0) continue;\n            g[v][i].cap += d;\n          \
    \  g[e.to][e.rev].cap -= d;\n            res += d;\n            if (res == up)\
    \ return res;\n        }\n        level[v] = _n;\n        return res;\n    }\n\
    \n    Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max());\
    \ }\n    Cap flow(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s\
    \ < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n     \
    \   level.assign(_n, 0), iter.assign(_n, 0);\n        que.clear();\n\n       \
    \ Cap flow = 0;\n        while (flow < flow_limit) {\n            _bfs(s, t);\n\
    \            if (level[t] == -1) break;\n            std::fill(iter.begin(), iter.end(),\
    \ 0);\n            Cap f = _dfs(t, s, flow_limit - flow);\n            if (!f)\
    \ break;\n            flow += f;\n        }\n        return flow;\n    }\n\n \
    \   std::vector<bool> min_cut(int s) {\n        std::vector<bool> visited(_n);\n\
    \        simple_queue_int que;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int p = que.front();\n            que.pop();\n            visited[p]\
    \ = true;\n            for (auto e : g[p]) {\n                if (e.cap && !visited[e.to])\
    \ {\n                    visited[e.to] = true;\n                    que.push(e.to);\n\
    \                }\n            }\n        }\n        return visited;\n    }\n\
    \n    void dump_graphviz(std::string filename = \"maxflow\") const {\n       \
    \ std::ofstream ss(filename + \".DOT\");\n        ss << \"digraph{\\n\";\n   \
    \     for (int i = 0; i < _n; i++) {\n            for (const auto &e : g[i]) {\n\
    \                if (e.cap > 0) ss << i << \"->\" << e.to << \"[label=\" << e.cap\
    \ << \"];\\n\";\n            }\n        }\n        ss << \"}\\n\";\n        ss.close();\n\
    \        return;\n    }\n\n    int _n;\n    struct _edge {\n        int to, rev;\n\
    \        Cap cap;\n    };\n    std::vector<std::pair<int, int>> pos;\n    std::vector<std::vector<_edge>>\
    \ g;\n};\n#line 4 \"combinatorial_opt/mcf_costscaling.hpp\"\n\n// Cost scaling\n\
    // https://people.orie.cornell.edu/dpw/orie633/\ntemplate <class Cap, class Cost,\
    \ int SCALING = 1, int REFINEMENT_ITER = 20>\nstruct mcf_costscaling {\n    mcf_costscaling()\
    \ = default;\n    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {}\n\n   \
    \ int _n;\n    std::vector<Cap> cap;\n    std::vector<Cost> cost;\n    std::vector<int>\
    \ opposite;\n    std::vector<std::vector<int>> to;\n    std::vector<Cap> b;\n\
    \    std::vector<Cost> p;\n\n    int add_edge(int from_, int to_, Cap cap_, Cost\
    \ cost_) {\n        assert(0 <= from_ and from_ < _n);\n        assert(0 <= to_\
    \ and to_ < _n);\n        assert(0 <= cap_);\n        cost_ *= (_n + 1);\n   \
    \     const int e = int(cap.size());\n        to[from_].push_back(e);\n      \
    \  cap.push_back(cap_);\n        cost.push_back(cost_);\n        opposite.push_back(to_);\n\
    \n        to[to_].push_back(e + 1);\n        cap.push_back(0);\n        cost.push_back(-cost_);\n\
    \        opposite.push_back(from_);\n        return e / 2;\n    }\n    void add_supply(int\
    \ v, Cap supply) { b[v] += supply; }\n    void add_demand(int v, Cap demand) {\
    \ add_supply(v, -demand); }\n\n    template <typename RetCost = Cost> RetCost\
    \ solve() {\n        Cost eps = 1;\n        std::vector<int> que;\n        for\
    \ (const auto c : cost) {\n            while (eps <= -c) eps <<= SCALING;\n  \
    \      }\n        for (; eps >>= SCALING;) {\n            auto no_admissible_cycle\
    \ = [&]() -> bool {\n                for (int i = 0; i < _n; i++) {\n        \
    \            if (b[i]) return false;\n                }\n                std::vector<Cost>\
    \ pp = p;\n                for (int iter = 0; iter < REFINEMENT_ITER; iter++)\
    \ {\n                    bool flg = false;\n                    for (int e = 0;\
    \ e < int(cap.size()); e++) {\n                        if (!cap[e]) continue;\n\
    \                        int i = opposite[e ^ 1], j = opposite[e];\n         \
    \               if (pp[j] > pp[i] + cost[e] + eps)\n                         \
    \   pp[j] = pp[i] + cost[e] + eps, flg = true;\n                    }\n      \
    \              if (!flg) return p = pp, true;\n                }\n           \
    \     return false;\n            };\n            if (no_admissible_cycle()) continue;\
    \ // Refine\n\n            for (int e = 0; e < int(cap.size()); e++) {\n     \
    \           const int i = opposite[e ^ 1], j = opposite[e];\n                const\
    \ Cost cp_ij = cost[e] + p[i] - p[j];\n                if (cap[e] and cp_ij <\
    \ 0)\n                    b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e],\
    \ cap[e] = 0;\n            }\n            que.clear();\n            int qh = 0;\n\
    \            for (int i = 0; i < _n; i++) {\n                if (b[i] > 0) que.push_back(i);\n\
    \            }\n            std::vector<int> iters(_n);\n            while (qh\
    \ < int(que.size())) {\n                const int i = que[qh++];\n           \
    \     for (; iters[i] < int(to[i].size()) and b[i]; ++iters[i]) { // Push\n  \
    \                  int e = to[i][iters[i]];\n                    if (!cap[e])\
    \ continue;\n                    int j = opposite[e];\n                    Cost\
    \ cp_ij = cost[e] + p[i] - p[j];\n                    if (cp_ij >= 0) continue;\n\
    \                    Cap f = b[i] > cap[e] ? cap[e] : b[i];\n                \
    \    if (b[j] <= 0 and b[j] + f > 0) que.push_back(j);\n                    b[i]\
    \ -= f, b[j] += f, cap[e] -= f, cap[e ^ 1] += f;\n                }\n\n      \
    \          if (b[i] > 0) { // Relabel\n                    bool flg = false;\n\
    \                    for (int e : to[i]) {\n                        if (!cap[e])\
    \ continue;\n                        Cost x = p[opposite[e]] - cost[e] - eps;\n\
    \                        if (!flg or x > p[i]) flg = true, p[i] = x;\n       \
    \             }\n                    que.push_back(i), iters[i] = 0;\n       \
    \         }\n            }\n        }\n        RetCost ret = 0;\n        for (int\
    \ e = 0; e < int(cap.size()); e += 2) ret += RetCost(cost[e]) * cap[e ^ 1];\n\
    \        return ret / (_n + 1);\n    }\n    std::vector<Cost> potential() const\
    \ {\n        std::vector<Cost> ret = p, c0 = cost;\n        for (auto &x : ret)\
    \ x /= (_n + 1);\n        for (auto &x : c0) x /= (_n + 1);\n        while (true)\
    \ {\n            bool flg = false;\n            for (int i = 0; i < _n; i++) {\n\
    \                for (const auto e : to[i]) {\n                    if (!cap[e])\
    \ continue;\n                    int j = opposite[e];\n                    auto\
    \ y = ret[i] + c0[e];\n                    if (ret[j] > y) ret[j] = y, flg = true;\n\
    \                }\n            }\n            if (!flg) break;\n        }\n \
    \       return ret;\n    }\n    struct edge {\n        int from, to;\n       \
    \ Cap cap, flow;\n        Cost cost;\n    };\n    edge get_edge(int e) const {\n\
    \        int m = cap.size() / 2;\n        assert(e >= 0 and e < m);\n        return\
    \ {opposite[e * 2 + 1], opposite[e * 2], cap[e * 2] + cap[e * 2 + 1], cap[e *\
    \ 2 + 1],\n                cost[e * 2] / (_n + 1)};\n    }\n    std::vector<edge>\
    \ edges() const {\n        int m = cap.size() / 2;\n        std::vector<edge>\
    \ result(m);\n        for (int i = 0; i < m; i++) result[i] = get_edge(i);\n \
    \       return result;\n    }\n};\n#line 6 \"combinatorial_opt/b-flow.hpp\"\n\n\
    // CUT begin\ntemplate <typename CAP, typename COST> struct B_Flow {\n    int\
    \ N, E;\n    COST cost_bias;\n    bool infeasible;\n    mf_graph<CAP> mf;\n  \
    \  mcf_costscaling<CAP, COST> mcf;\n    std::vector<CAP> b;\n    std::vector<CAP>\
    \ fbias;\n    std::vector<int> fdir;\n    std::vector<CAP> f;\n    std::vector<COST>\
    \ potential;\n\n    B_Flow(int N = 0) : N(N), E(0), cost_bias(0), infeasible(false),\
    \ mf(N + 2), mcf(N + 2), b(N) {}\n\n    void add_supply(int v, CAP supply) { b[v]\
    \ += supply; }\n    void add_demand(int v, CAP demand) { b[v] -= demand; }\n \
    \   void add_edge(int s, int t, CAP lower_cap, CAP upper_cap, COST cost) {\n \
    \       assert(s >= 0 and s < N);\n        assert(t >= 0 and t < N);\n       \
    \ if (lower_cap > upper_cap) {\n            infeasible = true;\n            return;\n\
    \        }\n        E++;\n        if (s == t) {\n            if (cost > 0) {\n\
    \                upper_cap = lower_cap;\n            } else {\n              \
    \  lower_cap = upper_cap;\n            }\n        }\n        if (cost < 0) {\n\
    \            fbias.emplace_back(lower_cap);\n            fdir.emplace_back(-1);\n\
    \            cost_bias += cost * upper_cap;\n            b[s] -= upper_cap;\n\
    \            b[t] += upper_cap;\n            mf.add_edge(t, s, upper_cap - lower_cap);\n\
    \            mcf.add_edge(t, s, upper_cap - lower_cap, -cost);\n        } else\
    \ {\n            fbias.emplace_back(upper_cap);\n            fdir.emplace_back(1);\n\
    \            if (lower_cap < 0) {\n                cost_bias += cost * lower_cap,\
    \ b[s] -= lower_cap, b[t] += lower_cap;\n                upper_cap -= lower_cap,\
    \ lower_cap = 0;\n            }\n            if (lower_cap > 0) {\n          \
    \      cost_bias += cost * lower_cap;\n                b[s] -= lower_cap;\n  \
    \              b[t] += lower_cap;\n                upper_cap -= lower_cap;\n \
    \           }\n            mf.add_edge(s, t, upper_cap);\n            mcf.add_edge(s,\
    \ t, upper_cap, cost);\n        }\n    }\n\n    std::pair<bool, COST> solve()\
    \ {\n        if (infeasible) return std::make_pair(false, 0);\n        CAP bsum\
    \ = 0, bsum_negative = 0;\n        for (int i = 0; i < N; i++) {\n           \
    \ if (b[i] > 0) {\n                mf.add_edge(N, i, b[i]), mcf.add_edge(N, i,\
    \ b[i], 0), bsum += b[i];\n            } else {\n                mf.add_edge(i,\
    \ N + 1, -b[i]), mcf.add_edge(i, N + 1, -b[i], 0),\n                    bsum_negative\
    \ -= b[i];\n            }\n        }\n        if (bsum != bsum_negative or mf.flow(N,\
    \ N + 1) < bsum) return std::make_pair(false, 0);\n        std::fill(b.begin(),\
    \ b.end(), 0);\n        mcf.add_supply(N, bsum);\n        mcf.add_demand(N + 1,\
    \ bsum);\n        COST ret = mcf.solve();\n        potential = mcf.potential(),\
    \ potential.resize(N);\n        COST cost_ret = cost_bias + ret;\n        cost_bias\
    \ = 0;\n        f = fbias;\n        auto edges = mcf.edges();\n        for (int\
    \ e = 0; e < E; e++) f[e] -= fdir[e] * (edges[e].cap - edges[e].flow);\n     \
    \   return std::make_pair(true, cost_ret);\n    }\n};\n#line 3 \"combinatorial_opt/test/b_flow.test.cpp\"\
    \n#include <iostream>\n\nusing namespace std;\n\nstd::ostream &operator<<(std::ostream\
    \ &os, const __int128 &x) {\n    __int128 tmp = x;\n    if (tmp == 0) return os\
    \ << 0;\n    std::vector<int> ds;\n    if (tmp < 0) {\n        os << '-';\n  \
    \      while (tmp) {\n            int d = tmp % 10;\n            if (d > 0) d\
    \ -= 10;\n            ds.emplace_back(-d), tmp = (tmp - d) / 10;\n        }\n\
    \    } else {\n        while (tmp) ds.emplace_back(tmp % 10), tmp /= 10;\n   \
    \ }\n    std::reverse(ds.begin(), ds.end());\n    for (auto i : ds) os << i;\n\
    \    return os;\n}\n\nint main() {\n    int N, M;\n    cin >> N >> M;\n    B_Flow<long\
    \ long, __int128> bflow(N);\n\n    for (int i = 0; i < N; i++) {\n        int\
    \ b;\n        cin >> b;\n        bflow.add_supply(i, b);\n    }\n    for (int\
    \ i = 0; i < M; i++) {\n        int s, t, l, u;\n        long long c;\n      \
    \  cin >> s >> t >> l >> u >> c;\n        bflow.add_edge(s, t, l, u, c);\n   \
    \ }\n    auto ret = bflow.solve();\n    if (ret.first) {\n        cout << ret.second\
    \ << '\\n';\n        for (auto p : bflow.potential) {\n            assert(p >=\
    \ -1e15 and p <= 1e15);\n            cout << p << '\\n';\n        }\n        for\
    \ (auto f : bflow.f) cout << f << '\\n';\n    } else {\n        cout << \"infeasible\\\
    n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n#include\
    \ \"../b-flow.hpp\"\n#include <iostream>\n\nusing namespace std;\n\nstd::ostream\
    \ &operator<<(std::ostream &os, const __int128 &x) {\n    __int128 tmp = x;\n\
    \    if (tmp == 0) return os << 0;\n    std::vector<int> ds;\n    if (tmp < 0)\
    \ {\n        os << '-';\n        while (tmp) {\n            int d = tmp % 10;\n\
    \            if (d > 0) d -= 10;\n            ds.emplace_back(-d), tmp = (tmp\
    \ - d) / 10;\n        }\n    } else {\n        while (tmp) ds.emplace_back(tmp\
    \ % 10), tmp /= 10;\n    }\n    std::reverse(ds.begin(), ds.end());\n    for (auto\
    \ i : ds) os << i;\n    return os;\n}\n\nint main() {\n    int N, M;\n    cin\
    \ >> N >> M;\n    B_Flow<long long, __int128> bflow(N);\n\n    for (int i = 0;\
    \ i < N; i++) {\n        int b;\n        cin >> b;\n        bflow.add_supply(i,\
    \ b);\n    }\n    for (int i = 0; i < M; i++) {\n        int s, t, l, u;\n   \
    \     long long c;\n        cin >> s >> t >> l >> u >> c;\n        bflow.add_edge(s,\
    \ t, l, u, c);\n    }\n    auto ret = bflow.solve();\n    if (ret.first) {\n \
    \       cout << ret.second << '\\n';\n        for (auto p : bflow.potential) {\n\
    \            assert(p >= -1e15 and p <= 1e15);\n            cout << p << '\\n';\n\
    \        }\n        for (auto f : bflow.f) cout << f << '\\n';\n    } else {\n\
    \        cout << \"infeasible\\n\";\n    }\n}\n"
  dependsOn:
  - combinatorial_opt/b-flow.hpp
  - combinatorial_opt/maxflow.hpp
  - combinatorial_opt/mcf_costscaling.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/b_flow.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/b_flow.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/b_flow.test.cpp
- /verify/combinatorial_opt/test/b_flow.test.cpp.html
title: combinatorial_opt/test/b_flow.test.cpp
---