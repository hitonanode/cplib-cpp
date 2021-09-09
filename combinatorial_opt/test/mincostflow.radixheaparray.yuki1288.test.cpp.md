---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/mincostflow_nonegativeloop.hpp
    title: "Minimum cost flow without negative cycle \uFF08\u8CA0\u8FBA\u30EB\u30FC\
      \u30D7\u306A\u3057\u306E\u6700\u5C0F\u8CBB\u7528\u6D41\uFF09"
  - icon: ':heavy_check_mark:'
    path: data_structure/radix_heap_array.hpp
    title: "Array-like radix heap with decrease query\uFF08`chmin()` \u64CD\u4F5C\u304C\
      \u53EF\u80FD\u306A\u57FA\u6570\u30D2\u30FC\u30D7\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1288
    links:
    - https://yukicoder.me/problems/no/1288
  bundledCode: "#line 1 \"combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1288\"\n#line 2 \"data_structure/radix_heap_array.hpp\"\
    \n#include <array>\n#include <limits>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\ntemplate <class Uint> class radix_heap_array {\n    int sz;\n\
    \    Uint last;\n    std::array<std::vector<std::pair<Uint, int>>, std::numeric_limits<Uint>::digits\
    \ + 1> v;\n\n    struct smallpii {\n        unsigned b : 7;\n        int j : 25;\n\
    \    };\n    std::vector<smallpii> i2bj;\n\n    template <class U, typename std::enable_if<sizeof(U)\
    \ == 4>::type* = nullptr>\n    static inline unsigned bucket(U x) noexcept {\n\
    \        return x ? 32 - __builtin_clz(x) : 0;\n    }\n    template <class U,\
    \ typename std::enable_if<sizeof(U) == 8>::type* = nullptr>\n    static inline\
    \ unsigned bucket(U x) noexcept {\n        return x ? 64 - __builtin_clzll(x)\
    \ : 0;\n    }\n\n    void pull() {\n        if (!v[0].empty()) return;\n     \
    \   int b = 1;\n        while (v[b].empty()) ++b;\n        last = v[b].back().first;\n\
    \        for (int j = 0; j < int(v[b].size()); j++) last = std::min(last, v[b][j].first);\n\
    \        for (int j = 0; j < int(v[b].size()); j++) {\n            int i = v[b][j].second;\n\
    \            auto bnxt = bucket(v[b][j].first ^ last);\n            i2bj[i] =\
    \ {bnxt, int(v[bnxt].size())}, v[bnxt].emplace_back(std::move(v[b][j]));\n   \
    \     }\n        v[b].clear();\n    }\n\npublic:\n    radix_heap_array() : sz(0),\
    \ last(0) {}\n    bool empty() const noexcept { return sz == 0; }\n    int argmin_pop()\
    \ {\n        pull(), --sz;\n        int i = v[0].back().second;\n        i2bj[i].j\
    \ = -1;\n        v[0].pop_back();\n        return i;\n    }\n    void chmin(Uint\
    \ vnew, int i) {\n        if (i >= int(i2bj.size())) i2bj.resize(i + 1, {0, -1});\n\
    \        if (i2bj[i].j < 0) {\n            auto b = bucket(vnew ^ last);\n   \
    \         ++sz, i2bj[i] = {b, int(v[b].size())}, v[b].emplace_back(vnew, i);\n\
    \        } else if (v[i2bj[i].b][i2bj[i].j].first > vnew) {\n            auto\
    \ bold = i2bj[i].b, bnew = bucket(vnew ^ last);\n            if (bnew < bold)\
    \ {\n                int ilast = v[bold].back().second, j = i2bj[i].j;\n     \
    \           std::swap(v[bold][j], v[bold].back());\n                i2bj[ilast].j\
    \ = j, i2bj[i] = {bnew, int(v[bnew].size())};\n                v[bnew].emplace_back(vnew,\
    \ i), v[bold].pop_back();\n            } else {\n                v[bold][i2bj[i].j].first\
    \ = vnew;\n            }\n        }\n    }\n\n    void pop() { argmin_pop(); }\n\
    \    std::pair<Uint, int> top() { return pull(), v[0].back(); }\n    [[deprecated(\"\
    NOT usual emplace() opeation!\")]] void emplace(Uint vnew, int i) { chmin(vnew,\
    \ i); }\n\n    void clear() noexcept { sz = 0, last = 0, i2bj.clear(); }\n};\n\
    #line 2 \"combinatorial_opt/mincostflow_nonegativeloop.hpp\"\n#include <cassert>\n\
    #line 4 \"combinatorial_opt/mincostflow_nonegativeloop.hpp\"\n#include <queue>\n\
    #line 6 \"combinatorial_opt/mincostflow_nonegativeloop.hpp\"\n\n// CUT begin\n\
    // Minimum cost flow WITH NO NEGATIVE CYCLE (just negative cost edge is allowed)\n\
    // Verified:\n// - SRM 770 Div1 Medium https://community.topcoder.com/stat?c=problem_statement&pm=15702\n\
    // - CodeChef LTIME98 Ancient Magic https://www.codechef.com/problems/ANCT\ntemplate\
    \ <class Cap = long long, class Cost = long long, Cost INF_COST = std::numeric_limits<Cost>::max()\
    \ / 2>\nstruct MinCostFlow {\n    struct _edge {\n        int to, rev;\n     \
    \   Cap cap;\n        Cost cost;\n        template <class Ostream> friend Ostream\
    \ &operator<<(Ostream &os, const _edge &e) {\n            return os << '(' <<\
    \ e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';\n        }\n \
    \   };\n    bool _is_dual_infeasible;\n    int V;\n    std::vector<std::vector<_edge>>\
    \ g;\n    std::vector<Cost> dist;\n    std::vector<int> prevv, preve;\n    std::vector<Cost>\
    \ dual; // dual[V]: potential\n    std::vector<std::pair<int, int>> pos;\n\n \
    \   bool _initialize_dual_dag() {\n        std::vector<int> deg_in(V);\n     \
    \   for (int i = 0; i < V; i++) {\n            for (const auto &e : g[i]) deg_in[e.to]\
    \ += (e.cap > 0);\n        }\n        std::vector<int> st;\n        st.reserve(V);\n\
    \        for (int i = 0; i < V; i++) {\n            if (!deg_in[i]) st.push_back(i);\n\
    \        }\n        for (int n = 0; n < V; n++) {\n            if (int(st.size())\
    \ == n) return false; // Not DAG\n            int now = st[n];\n            for\
    \ (const auto &e : g[now]) {\n                if (!e.cap) continue;\n        \
    \        deg_in[e.to]--;\n                if (deg_in[e.to] == 0) st.push_back(e.to);\n\
    \                if (dual[e.to] >= dual[now] + e.cost) dual[e.to] = dual[now]\
    \ + e.cost;\n            }\n        }\n        return true;\n    }\n\n    bool\
    \ _initialize_dual_spfa() { // Find feasible dual's when negative cost edges exist\n\
    \        dual.assign(V, 0);\n        std::queue<int> q;\n        std::vector<int>\
    \ in_queue(V);\n        std::vector<int> nvis(V);\n        for (int i = 0; i <\
    \ V; i++) q.push(i), in_queue[i] = true;\n        while (q.size()) {\n       \
    \     int now = q.front();\n            q.pop(), in_queue[now] = false;\n    \
    \        if (nvis[now] > V) return false; // Negative cycle exists\n         \
    \   nvis[now]++;\n            for (const auto &e : g[now]) {\n               \
    \ if (!e.cap) continue;\n                if (dual[e.to] > dual[now] + e.cost)\
    \ {\n                    dual[e.to] = dual[now] + e.cost;\n                  \
    \  if (!in_queue[e.to]) in_queue[e.to] = true, q.push(e.to);\n               \
    \ }\n            }\n        }\n        return true;\n    }\n\n    bool initialize_dual()\
    \ {\n        return !_is_dual_infeasible or _initialize_dual_dag() or _initialize_dual_spfa();\n\
    \    }\n\n    template <class heap> void _dijkstra(int s) { // O(ElogV)\n    \
    \    prevv.assign(V, -1);\n        preve.assign(V, -1);\n        dist.assign(V,\
    \ INF_COST);\n        dist[s] = 0;\n        heap q;\n        q.emplace(0, s);\n\
    \        while (!q.empty()) {\n            auto p = q.top();\n            q.pop();\n\
    \            int v = p.second;\n            if (dist[v] < Cost(p.first)) continue;\n\
    \            for (int i = 0; i < (int)g[v].size(); i++) {\n                _edge\
    \ &e = g[v][i];\n                auto c = dist[v] + e.cost + dual[v] - dual[e.to];\n\
    \                if (e.cap > 0 and dist[e.to] > c) {\n                    dist[e.to]\
    \ = c, prevv[e.to] = v, preve[e.to] = i;\n                    q.emplace(dist[e.to],\
    \ e.to);\n                }\n            }\n        }\n    }\n\n    MinCostFlow(int\
    \ V = 0) : _is_dual_infeasible(false), V(V), g(V), dual(V, 0) {\n        static_assert(INF_COST\
    \ > 0, \"INF_COST must be positive\");\n    }\n\n    int add_edge(int from, int\
    \ to, Cap cap, Cost cost) {\n        assert(0 <= from and from < V);\n       \
    \ assert(0 <= to and to < V);\n        assert(cap >= 0);\n        if (cost < 0)\
    \ _is_dual_infeasible = true;\n        pos.emplace_back(from, g[from].size());\n\
    \        g[from].push_back({to, (int)g[to].size() + (from == to), cap, cost});\n\
    \        g[to].push_back({from, (int)g[from].size() - 1, (Cap)0, -cost});\n  \
    \      return int(pos.size()) - 1;\n    }\n\n    // Flush flow f from s to t.\
    \ Graph must not have negative cycle.\n    using Pque = std::priority_queue<std::pair<Cost,\
    \ int>, std::vector<std::pair<Cost, int>>, std::greater<std::pair<Cost, int>>>;\n\
    \    template <class heap = Pque> std::pair<Cap, Cost> flow(int s, int t, const\
    \ Cap &flow_limit) {\n        // You can also use radix_heap<typename std::make_unsigned<Cost>::type,\
    \ int> as prique\n        if (!initialize_dual()) throw; // Fail to find feasible\
    \ dual\n        Cost cost = 0;\n        Cap flow_rem = flow_limit;\n        while\
    \ (flow_rem > 0) {\n            _dijkstra<heap>(s);\n            if (dist[t] ==\
    \ INF_COST) break;\n            for (int v = 0; v < V; v++) dual[v] = std::min(dual[v]\
    \ + dist[v], INF_COST);\n            Cap d = flow_rem;\n            for (int v\
    \ = t; v != s; v = prevv[v]) d = std::min(d, g[prevv[v]][preve[v]].cap);\n   \
    \         flow_rem -= d;\n            cost += d * (dual[t] - dual[s]);\n     \
    \       for (int v = t; v != s; v = prevv[v]) {\n                _edge &e = g[prevv[v]][preve[v]];\n\
    \                e.cap -= d;\n                g[v][e.rev].cap += d;\n        \
    \    }\n        }\n        return std::make_pair(flow_limit - flow_rem, cost);\n\
    \    }\n\n    struct edge {\n        int from, to;\n        Cap cap, flow;\n \
    \       Cost cost;\n        template <class Ostream> friend Ostream &operator<<(Ostream\
    \ &os, const edge &e) {\n            return os << '(' << e.from << \"->\" << e.to\
    \ << ',' << e.flow << '/' << e.cap << \",$\" << e.cost << ')';\n        }\n  \
    \  };\n\n    edge get_edge(int edge_id) const {\n        int m = int(pos.size());\n\
    \        assert(0 <= edge_id and edge_id < m);\n        auto _e = g[pos[edge_id].first][pos[edge_id].second];\n\
    \        auto _re = g[_e.to][_e.rev];\n        return {pos[edge_id].first, _e.to,\
    \ _e.cap + _re.cap, _re.cap, _e.cost};\n    }\n    std::vector<edge> edges() const\
    \ {\n        std::vector<edge> ret(pos.size());\n        for (int i = 0; i < int(pos.size());\
    \ i++) ret[i] = get_edge(i);\n        return ret;\n    }\n\n    template <class\
    \ Ostream> friend Ostream &operator<<(Ostream &os, const MinCostFlow &mcf) {\n\
    \        os << \"[MinCostFlow]V=\" << mcf.V << \":\";\n        for (int i = 0;\
    \ i < mcf.V; i++) {\n            for (auto &e : mcf.g[i]) os << \"\\n\" << i <<\
    \ \"->\" << e.to << \":cap\" << e.cap << \",$\" << e.cost;\n        }\n      \
    \  return os;\n    }\n};\n#line 4 \"combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp\"\
    \n#include <iostream>\n#include <numeric>\n#include <string>\n#line 8 \"combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    int N;\n    string S;\n    cin >>\
    \ N >> S;\n    vector<long long> V(N);\n    for (auto &x : V) cin >> x;\n\n  \
    \  const int s = N * 5, t = s + 1;\n    MinCostFlow<int, long long> graph(t +\
    \ 1);\n    for (int d = 0; d < 5; d++) {\n        for (int i = 0; i < N - 1; i++)\
    \ graph.add_edge(d * N + i, d * N + i + 1, N / 4, 0);\n    }\n    graph.add_edge(s\
    \ - 1, 0, N / 4, 0);\n\n    for (int i = 0; i < N; i++) {\n        int b = 0;\n\
    \        if (S[i] == 'u') b = N * 1;\n        if (S[i] == 'k') b = N * 2;\n  \
    \      if (S[i] == 'i') b = N * 3;\n        int fr = b + i + N, to = b + i;\n\
    \        graph.add_edge(s, fr, 1, 0);\n        graph.add_edge(fr, to, 1, V[i]);\n\
    \        graph.add_edge(to, t, 1, 0);\n    }\n    auto cost = graph.flow<radix_heap_array<unsigned\
    \ long long>>(s, t, N).second;\n    cout << accumulate(V.begin(), V.end(), 0LL)\
    \ - cost << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1288\"\n#include \"../../data_structure/radix_heap_array.hpp\"\
    \n#include \"../mincostflow_nonegativeloop.hpp\"\n#include <iostream>\n#include\
    \ <numeric>\n#include <string>\n#include <vector>\nusing namespace std;\n\nint\
    \ main() {\n    int N;\n    string S;\n    cin >> N >> S;\n    vector<long long>\
    \ V(N);\n    for (auto &x : V) cin >> x;\n\n    const int s = N * 5, t = s + 1;\n\
    \    MinCostFlow<int, long long> graph(t + 1);\n    for (int d = 0; d < 5; d++)\
    \ {\n        for (int i = 0; i < N - 1; i++) graph.add_edge(d * N + i, d * N +\
    \ i + 1, N / 4, 0);\n    }\n    graph.add_edge(s - 1, 0, N / 4, 0);\n\n    for\
    \ (int i = 0; i < N; i++) {\n        int b = 0;\n        if (S[i] == 'u') b =\
    \ N * 1;\n        if (S[i] == 'k') b = N * 2;\n        if (S[i] == 'i') b = N\
    \ * 3;\n        int fr = b + i + N, to = b + i;\n        graph.add_edge(s, fr,\
    \ 1, 0);\n        graph.add_edge(fr, to, 1, V[i]);\n        graph.add_edge(to,\
    \ t, 1, 0);\n    }\n    auto cost = graph.flow<radix_heap_array<unsigned long\
    \ long>>(s, t, N).second;\n    cout << accumulate(V.begin(), V.end(), 0LL) - cost\
    \ << '\\n';\n}\n"
  dependsOn:
  - data_structure/radix_heap_array.hpp
  - combinatorial_opt/mincostflow_nonegativeloop.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
  requiredBy: []
  timestamp: '2021-09-09 22:48:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
- /verify/combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp.html
title: combinatorial_opt/test/mincostflow.radixheaparray.yuki1288.test.cpp
---
