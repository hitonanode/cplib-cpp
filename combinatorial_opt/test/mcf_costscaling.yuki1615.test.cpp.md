---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/mcf_costscaling.hpp
    title: "Cost scaling minimum cost flow (Goldberg, Tarjan) \uFF08\u30B3\u30B9\u30C8\
      \u30B9\u30B1\u30FC\u30EA\u30F3\u30B0\u306B\u3088\u308B\u6700\u5C0F\u8CBB\u7528\
      \u6D41\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1615
    links:
    - https://yukicoder.me/problems/no/1615
  bundledCode: "#line 1 \"combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1615\"\n#line 2 \"combinatorial_opt/mcf_costscaling.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// Cost scaling\n// https://people.orie.cornell.edu/dpw/orie633/\n\
    template <class Cap, class Cost, int SCALING = 1, int REFINEMENT_ITER = 20> struct\
    \ mcf_costscaling {\n    mcf_costscaling() = default;\n    mcf_costscaling(int\
    \ n) : _n(n), to(n), b(n), p(n) {}\n\n    int _n;\n    std::vector<Cap> cap;\n\
    \    std::vector<Cost> cost;\n    std::vector<int> opposite;\n    std::vector<std::vector<int>>\
    \ to;\n    std::vector<Cap> b;\n    std::vector<Cost> p;\n\n    int add_edge(int\
    \ from_, int to_, Cap cap_, Cost cost_) {\n        assert(0 <= from_ and from_\
    \ < _n);\n        assert(0 <= to_ and to_ < _n);\n        assert(0 <= cap_);\n\
    \        cost_ *= (_n + 1);\n        const int e = int(cap.size());\n        to[from_].push_back(e);\n\
    \        cap.push_back(cap_);\n        cost.push_back(cost_);\n        opposite.push_back(to_);\n\
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
    \               if (pp[j] > pp[i] + cost[e] + eps) pp[j] = pp[i] + cost[e] + eps,\
    \ flg = true;\n                    }\n                    if (!flg) return p =\
    \ pp, true;\n                }\n                return false;\n            };\n\
    \            if (no_admissible_cycle()) continue; // Refine\n\n            for\
    \ (int e = 0; e < int(cap.size()); e++) {\n                const int i = opposite[e\
    \ ^ 1], j = opposite[e];\n                const Cost cp_ij = cost[e] + p[i] -\
    \ p[j];\n                if (cap[e] and cp_ij < 0) b[i] -= cap[e], b[j] += cap[e],\
    \ cap[e ^ 1] += cap[e], cap[e] = 0;\n            }\n            que.clear();\n\
    \            int qh = 0;\n            for (int i = 0; i < _n; i++) {\n       \
    \         if (b[i] > 0) que.push_back(i);\n            }\n            std::vector<int>\
    \ iters(_n);\n            while (qh < int(que.size())) {\n                const\
    \ int i = que[qh++];\n                for (; iters[i] < int(to[i].size()) and\
    \ b[i]; ++iters[i]) { // Push\n                    int e = to[i][iters[i]];\n\
    \                    if (!cap[e]) continue;\n                    int j = opposite[e];\n\
    \                    Cost cp_ij = cost[e] + p[i] - p[j];\n                   \
    \ if (cp_ij >= 0) continue;\n                    Cap f = b[i] > cap[e] ? cap[e]\
    \ : b[i];\n                    if (b[j] <= 0 and b[j] + f > 0) que.push_back(j);\n\
    \                    b[i] -= f, b[j] += f, cap[e] -= f, cap[e ^ 1] += f;\n   \
    \             }\n\n                if (b[i] > 0) { // Relabel\n              \
    \      bool flg = false;\n                    for (int e : to[i]) {\n        \
    \                if (!cap[e]) continue;\n                        Cost x = p[opposite[e]]\
    \ - cost[e] - eps;\n                        if (!flg or x > p[i]) flg = true,\
    \ p[i] = x;\n                    }\n                    que.push_back(i), iters[i]\
    \ = 0;\n                }\n            }\n        }\n        RetCost ret = 0;\n\
    \        for (int e = 0; e < int(cap.size()); e += 2) ret += RetCost(cost[e])\
    \ * cap[e ^ 1];\n        return ret / (_n + 1);\n    }\n    std::vector<Cost>\
    \ potential() const {\n        std::vector<Cost> ret = p, c0 = cost;\n       \
    \ for (auto &x : ret) x /= (_n + 1);\n        for (auto &x : c0) x /= (_n + 1);\n\
    \        while (true) {\n            bool flg = false;\n            for (int i\
    \ = 0; i < _n; i++) {\n                for (const auto e : to[i]) {\n        \
    \            if (!cap[e]) continue;\n                    int j = opposite[e];\n\
    \                    auto y = ret[i] + c0[e];\n                    if (ret[j]\
    \ > y) ret[j] = y, flg = true;\n                }\n            }\n           \
    \ if (!flg) break;\n        }\n        return ret;\n    }\n    struct edge {\n\
    \        int from, to;\n        Cap cap, flow;\n        Cost cost;\n    };\n \
    \   edge get_edge(int e) const {\n        int m = cap.size() / 2;\n        assert(e\
    \ >= 0 and e < m);\n        return {opposite[e * 2 + 1], opposite[e * 2], cap[e\
    \ * 2] + cap[e * 2 + 1], cap[e * 2 + 1], cost[e * 2] / (_n + 1)};\n    }\n   \
    \ std::vector<edge> edges() const {\n        int m = cap.size() / 2;\n       \
    \ std::vector<edge> result(m);\n        for (int i = 0; i < m; i++) result[i]\
    \ = get_edge(i);\n        return result;\n    }\n};\n#line 3 \"combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M, K, L;\n    cin >> N >> M >> K >>\
    \ L;\n    mcf_costscaling<int, long long, 1, 10> mcf(N + M + 1);\n    for (int\
    \ l = 0; l < L; l++) {\n        int x, y, z;\n        cin >> x >> y >> z;\n  \
    \      mcf.add_edge(x, y + N, 1, -(1LL << z));\n    }\n    const int gs = 0;\n\
    \    for (int i = 0; i < N; i++) mcf.add_edge(gs, i + 1, 1, 0);\n    for (int\
    \ j = 0; j < M; j++) mcf.add_edge(N + j + 1, gs, 1, 0);\n    cout << -mcf.solve()\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1615\"\n#include \"../mcf_costscaling.hpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M, K, L;\n    cin >> N >> M >> K >>\
    \ L;\n    mcf_costscaling<int, long long, 1, 10> mcf(N + M + 1);\n    for (int\
    \ l = 0; l < L; l++) {\n        int x, y, z;\n        cin >> x >> y >> z;\n  \
    \      mcf.add_edge(x, y + N, 1, -(1LL << z));\n    }\n    const int gs = 0;\n\
    \    for (int i = 0; i < N; i++) mcf.add_edge(gs, i + 1, 1, 0);\n    for (int\
    \ j = 0; j < M; j++) mcf.add_edge(N + j + 1, gs, 1, 0);\n    cout << -mcf.solve()\
    \ << '\\n';\n}\n"
  dependsOn:
  - combinatorial_opt/mcf_costscaling.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
  requiredBy: []
  timestamp: '2021-08-18 23:55:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
- /verify/combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp.html
title: combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
---
