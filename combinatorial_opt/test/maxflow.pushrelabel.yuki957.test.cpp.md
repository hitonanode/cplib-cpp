---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/maxflow_pushrelabel.hpp
    title: "Maxflow (push-relabel, Goldberg & Tarjan) \uFF08Push-relabel \u306B\u3088\
      \u308B\u6700\u5927\u6D41\uFF09"
  - icon: ':heavy_check_mark:'
    path: utilities/reader.hpp
    title: "\u9AD8\u901F\u6A19\u6E96\u5165\u529B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/957
    links:
    - https://yukicoder.me/problems/no/957
  bundledCode: "#line 1 \"combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/957\"\n#line 2 \"utilities/reader.hpp\"\
    \n#include <cstdio>\n#include <string>\n\n// CUT begin\ntemplate <typename T>\
    \ T rd_integer() {\n    T ret = 0;\n    bool minus = false;\n\n    char c = getchar_unlocked();\n\
    \    while (!isdigit(c)) minus |= (c == '-'), c = getchar_unlocked();\n    while\
    \ (isdigit(c)) ret = (ret << 1) + (ret << 3) + (c ^ 48), c = getchar_unlocked();\n\
    \n    return minus ? -ret : ret;\n}\nint rdi() { return rd_integer<int>(); }\n\
    long long rdll() { return rd_integer<long long>(); }\nstd::string rdstr() {\n\
    \    std::string ret;\n    char c = getchar_unlocked();\n    while (!isgraph(c))\
    \ c = getchar_unlocked();\n    while (isgraph(c)) ret += c, c = getchar_unlocked();\n\
    \    return ret;\n}\n#line 2 \"combinatorial_opt/maxflow_pushrelabel.hpp\"\n#include\
    \ <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\n// Maxflow\
    \ (push-relabel, highest-label)\n// Complexity: O(N^2 M^(1/2))\ntemplate <class\
    \ Cap, int GlobalRelabelFreq = 5, bool UseGapRelabeling = true>\nstruct mf_pushrelabel\
    \ {\n    struct pque_ {\n        std::vector<std::pair<int, int>> even_, odd_;\n\
    \        int se, so;\n        void init(int n) { even_.resize(n), odd_.resize(n),\
    \ se = so = 0; };\n        void clear() { se = so = 0; }\n        bool empty()\
    \ const { return se + so == 0; }\n        void push(int i, int h) { (h & 1 ? odd_[so++]\
    \ : even_[se++]) = {i, h}; }\n        int highest() const {\n            int a\
    \ = se ? even_[se - 1].second : -1, b = so ? odd_[so - 1].second : -1;\n     \
    \       return a > b ? a : b;\n        }\n        int pop() {\n            if\
    \ (!se or (so and odd_[so - 1].second > even_[se - 1].second))\n             \
    \   return odd_[--so].first;\n            return even_[--se].first;\n        }\n\
    \    } pque;\n    int _n;\n    struct _edge {\n        int to, rev;\n        Cap\
    \ cap;\n    };\n    std::vector<std::vector<_edge>> g;\n    std::vector<std::pair<int,\
    \ int>> pos;\n    mf_pushrelabel(int n) : _n(n), g(n) {\n        static_assert(GlobalRelabelFreq\
    \ >= 0, \"Global relabel parameter must be nonnegative.\");\n    }\n    int add_edge(int\
    \ from, int to, Cap cap) {\n        assert(0 <= from and from < _n);\n       \
    \ assert(0 <= to and to < _n);\n        assert(0 <= cap);\n        int m = int(pos.size());\n\
    \        pos.emplace_back(from, int(g[from].size()));\n        int from_id = g[from].size(),\
    \ to_id = g[to].size() + (from == to);\n        g[from].push_back({to, to_id,\
    \ cap});\n        g[to].push_back({from, from_id, Cap(0)});\n        return m;\n\
    \    }\n\n    struct edge {\n        int from, to;\n        Cap cap, flow;\n \
    \   };\n\n    edge get_edge(int i) const {\n        int m = int(pos.size());\n\
    \        assert(0 <= i and i < m);\n        auto e = g[pos[i].first][pos[i].second],\
    \ re = g[e.to][e.rev];\n        return edge{pos[i].first, e.to, e.cap + re.cap,\
    \ re.cap};\n    }\n    std::vector<edge> edges() const {\n        std::vector<edge>\
    \ ret(pos.size());\n        for (int i = 0; i < int(pos.size()); i++) ret[i] =\
    \ get_edge(i);\n        return ret;\n    }\n\n    std::vector<int> dist;\n   \
    \ std::vector<int> dcnt;\n    std::vector<Cap> excess;\n    int gap;\n    void\
    \ global_relabeling(int t) {\n        dist.assign(_n, _n), dist[t] = 0;\n    \
    \    static std::vector<int> q;\n        if (q.empty()) q.resize(_n);\n      \
    \  q[0] = t;\n        int qb = 0, qe = 1;\n        pque.clear();\n        if (UseGapRelabeling)\
    \ gap = 1, dcnt.assign(_n + 1, 0);\n\n        while (qb < qe) {\n            int\
    \ now = q[qb++];\n            if (UseGapRelabeling) gap = dist[now] + 1, dcnt[dist[now]]++;\n\
    \            if (excess[now] > 0) pque.push(now, dist[now]);\n            for\
    \ (const auto &e : g[now]) {\n                if (g[e.to][e.rev].cap and dist[e.to]\
    \ == _n) {\n                    dist[e.to] = dist[now] + 1;\n                \
    \    while (int(q.size()) <= qe) q.push_back(0);\n                    q[qe++]\
    \ = e.to;\n                }\n            }\n        }\n    }\n    Cap flow(int\
    \ s, int t) { return flow(s, t, std::numeric_limits<Cap>::max(), true); }\n  \
    \  Cap flow(int s, int t, Cap flow_limit, bool retrieve = true) {\n        assert(0\
    \ <= s and s < _n);\n        assert(0 <= t and t < _n);\n        assert(s != t);\n\
    \        excess.resize(_n, 0);\n        excess[s] += flow_limit, excess[t] -=\
    \ flow_limit;\n        dist.assign(_n, 0);\n        dist[s] = _n;\n        if\
    \ (UseGapRelabeling) gap = 1, dcnt.assign(_n + 1, 0), dcnt[0] = _n - 1;\n    \
    \    pque.init(_n);\n        for (auto &e : g[s]) _push(s, e);\n        _run(t);\n\
    \        Cap ret = excess[t] + flow_limit;\n        excess[s] += excess[t], excess[t]\
    \ = 0;\n        if (retrieve) {\n            global_relabeling(s);\n         \
    \   _run(s);\n            assert(excess == std::vector<Cap>(_n, 0));\n       \
    \ }\n        return ret;\n    }\n    void _run(int t) {\n        if (GlobalRelabelFreq)\
    \ global_relabeling(t);\n        int tick = pos.size() * GlobalRelabelFreq;\n\
    \        while (!pque.empty()) {\n            int i = pque.pop();\n          \
    \  if (UseGapRelabeling and dist[i] > gap) continue;\n            int dnxt = _n\
    \ * 2 - 1;\n            for (auto &e : g[i]) {\n                if (!e.cap) continue;\n\
    \                if (dist[e.to] == dist[i] - 1) {\n                    _push(i,\
    \ e);\n                    if (excess[i] == 0) break;\n                } else\
    \ {\n                    if (dist[e.to] + 1 < dnxt) dnxt = dist[e.to] + 1;\n \
    \               }\n            }\n            if (excess[i] > 0) {\n         \
    \       if (UseGapRelabeling) {\n                    if (dnxt != dist[i] and dcnt[dist[i]]\
    \ == 1 and dist[i] < gap) gap = dist[i];\n                    if (dnxt == gap)\
    \ gap++;\n                    while (pque.highest() > gap) pque.pop();\n     \
    \               if (dnxt > gap) dnxt = _n;\n                    if (dist[i] !=\
    \ dnxt) dcnt[dist[i]]--, dcnt[dnxt]++;\n                }\n                dist[i]\
    \ = dnxt;\n                if (!UseGapRelabeling or dist[i] < gap) pque.push(i,\
    \ dist[i]);\n            }\n            if (GlobalRelabelFreq and --tick == 0)\
    \ {\n                tick = pos.size() * GlobalRelabelFreq, global_relabeling(t);\n\
    \            }\n        }\n        return;\n    }\n\n    void _push(int i, _edge\
    \ &e) {\n        Cap delta = e.cap < excess[i] ? e.cap : excess[i];\n        excess[i]\
    \ -= delta, e.cap -= delta;\n        excess[e.to] += delta, g[e.to][e.rev].cap\
    \ += delta;\n        if (excess[e.to] > 0 and excess[e.to] <= delta) {\n     \
    \       if (!UseGapRelabeling or dist[e.to] <= gap) pque.push(e.to, dist[e.to]);\n\
    \        }\n    }\n};\n#line 4 \"combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp\"\
    \n#include <algorithm>\n#include <iostream>\n#include <numeric>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int H = rdi(), W = rdi();\n    vector<vector<int>> G(H, vector<int>(W));\n\
    \    for (auto &v : G) {\n        for (auto &x : v) x = rdi();\n    }\n    vector<int>\
    \ R(H), C(W);\n    long long tot = 0;\n    for (auto &x : R) x = rdi(), tot +=\
    \ x;\n    for (auto &x : C) x = rdi(), tot += x;\n\n    int Z = 1 + H + W;\n \
    \   mf_pushrelabel<long long, 6, true> g(Z + 1);\n\n    for (int i = 0; i < H;\
    \ i++) {\n        auto gtot = accumulate(G[i].begin(), G[i].end(), 0LL);\n   \
    \     auto f0 = min<long long>(gtot, R[i]);\n        tot -= f0;\n        if (gtot\
    \ > f0) g.add_edge(0, i + 1, gtot - f0);\n        for (int j = 0; j < W; j++)\
    \ g.add_edge(i + 1, H + 1 + j, G[i][j]);\n    }\n    for (int j = 0; j < W; j++)\
    \ g.add_edge(H + 1 + j, Z, C[j]);\n    cout << tot - g.flow(0, Z, numeric_limits<long\
    \ long>::max(), false) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/957\"\n#include \"../../utilities/reader.hpp\"\
    \n#include \"../maxflow_pushrelabel.hpp\"\n#include <algorithm>\n#include <iostream>\n\
    #include <numeric>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int H = rdi(), W = rdi();\n    vector<vector<int>>\
    \ G(H, vector<int>(W));\n    for (auto &v : G) {\n        for (auto &x : v) x\
    \ = rdi();\n    }\n    vector<int> R(H), C(W);\n    long long tot = 0;\n    for\
    \ (auto &x : R) x = rdi(), tot += x;\n    for (auto &x : C) x = rdi(), tot +=\
    \ x;\n\n    int Z = 1 + H + W;\n    mf_pushrelabel<long long, 6, true> g(Z + 1);\n\
    \n    for (int i = 0; i < H; i++) {\n        auto gtot = accumulate(G[i].begin(),\
    \ G[i].end(), 0LL);\n        auto f0 = min<long long>(gtot, R[i]);\n        tot\
    \ -= f0;\n        if (gtot > f0) g.add_edge(0, i + 1, gtot - f0);\n        for\
    \ (int j = 0; j < W; j++) g.add_edge(i + 1, H + 1 + j, G[i][j]);\n    }\n    for\
    \ (int j = 0; j < W; j++) g.add_edge(H + 1 + j, Z, C[j]);\n    cout << tot - g.flow(0,\
    \ Z, numeric_limits<long long>::max(), false) << '\\n';\n}\n"
  dependsOn:
  - utilities/reader.hpp
  - combinatorial_opt/maxflow_pushrelabel.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 11:21:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
- /verify/combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp.html
title: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
---
